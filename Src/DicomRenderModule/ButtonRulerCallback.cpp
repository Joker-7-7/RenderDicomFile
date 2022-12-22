#include "ButtonRulerCallback.hpp"


namespace RulerOptions
{
	void ClickCallbackFunction(vtkObject* caller_, long unsigned int eventId_, void* clientData_,
                               void* vtkNotUsed(callData))
	{
		vtkRenderWindowInteractor* inter = vtkRenderWindowInteractor::SafeDownCast(
			dynamic_cast<vtkDistanceWidget*>(caller_)->GetInteractor());
		auto ptrDistanceWidget = static_cast<vtkDistanceWidget*>(clientData_);
		// Get the location of the click (in window coordinates)

		int* pos = inter->GetEventPosition();

		vtkNew<vtkCellPicker> picker;
		picker->SetTolerance(0.0005);

		// Pick from this location.
		picker->Pick(pos[0], pos[1], 0, dynamic_cast<vtkDistanceWidget*>(caller_)->GetCurrentRenderer());

		double* worldPosition = picker->GetPickPosition();

		auto rep = static_cast<vtkDistanceRepresentation3D*>(ptrDistanceWidget->GetRepresentation());
		if (picker->GetCellId() != -1)
		{
			if (!secondPoint)
			{
				rep->SetPoint1WorldPosition(worldPosition);
			}
			else
			{
				rep->SetPoint2WorldPosition(worldPosition);
				ptrDistanceWidget->On();

				dynamic_cast<vtkDistanceWidget*>(caller_)->SetEnabled(false);
			}
			secondPoint = !secondPoint;
			std::cout << "Pick position is: (" << worldPosition[0] << ", " << worldPosition[1] << ", " << worldPosition[
				2] << ")" << std::endl;
		}
	}

	vtkButtonRulerCallback::vtkButtonRulerCallback()
	{
		_distanceWidget = nullptr;
		_tempDistanceWidget = nullptr;
        _interactor = nullptr;
		_modeOn = false;
	}

	vtkButtonRulerCallback* vtkButtonRulerCallback::New()
	{
		return new vtkButtonRulerCallback;
	}

	void vtkButtonRulerCallback::Execute(vtkObject* caller_, unsigned long, void*)
	{
		_modeOn = !_modeOn;

		if (_modeOn)
		{
			_distanceWidget = vtkDistanceWidget::New();
			_distanceWidget->SetInteractor(_interactor);
			_distanceWidget->SetWidgetStateToManipulate();
			dynamic_cast<vtkDistanceRepresentation*>(_distanceWidget->GetRepresentation())->
				SetLabelFormat("%-#6.3g mm");
			_distanceWidget->PickingManagedOff();
			_distanceWidget->ProcessEventsOff();
			_distanceWidget->KeyPressActivationOff();
			_distanceWidget->DebugOff();


			vtkNew<vtkDistanceRepresentation3D> repres;
			_tempDistanceWidget = vtkDistanceWidget::New();
			_tempDistanceWidget->SetInteractor(_interactor);
			_tempDistanceWidget->SetRepresentation(repres);

			vtkNew<vtkCallbackCommand> clickCallback;
            clickCallback->SetCallback(ClickCallbackFunction);
			clickCallback->SetClientData(_distanceWidget);

			_tempDistanceWidget->AddObserver(vtkCommand::PlacePointEvent, clickCallback);
			_tempDistanceWidget->On();
		}
		else
		{
			secondPoint = false;
			_distanceWidget->Delete();
			_distanceWidget = nullptr;
			_tempDistanceWidget->Delete();
			_tempDistanceWidget = nullptr;
		}
	}

	vtkButtonRulerCallback::~vtkButtonRulerCallback() {
        if(_distanceWidget)
            _distanceWidget->Delete();
        if(_tempDistanceWidget)
            _tempDistanceWidget->Delete();
    }
}
