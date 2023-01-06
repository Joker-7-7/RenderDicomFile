#include "ButtonRulerCallback.hpp"


namespace RulerOptions
{
    void ClickCallbackFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* vtkNotUsed(callData)) {
        vtkRenderWindowInteractor *interactor = vtkRenderWindowInteractor::SafeDownCast(dynamic_cast<vtkDistanceWidget *>(caller)->GetInteractor());
        auto distanceWidget = static_cast<vtkDistanceWidget *>(clientData);
        // Get the location of the click (in window coordinates)

        int *eventPosition = interactor->GetEventPosition();

        vtkNew<vtkCellPicker> picker;
        picker->SetTolerance(0.0005);

        // Pick from this location.
        picker->Pick(eventPosition[0], eventPosition[1], 0,
                     dynamic_cast<vtkDistanceWidget *>(caller)->GetCurrentRenderer());

        double *worldPosition = picker->GetPickPosition();

        auto representation = static_cast<vtkDistanceRepresentation3D *>(distanceWidget->GetRepresentation());
        if (picker->GetCellId() != -1) {
            if (!secondPoint) {
                representation->SetPoint1WorldPosition(worldPosition);
            }
            else {
                representation->SetPoint2WorldPosition(worldPosition);
                distanceWidget->On();

                dynamic_cast<vtkDistanceWidget *>(caller)->SetEnabled(false);
            }
            secondPoint = !secondPoint;
            std::cout << "Pick position is: (" << worldPosition[0] << ", " << worldPosition[1] << ", " << worldPosition[
                    2] << ")" << std::endl;
        }
    }

    vtkButtonRulerCallback::vtkButtonRulerCallback() {
        distanceWidget = nullptr;
        tempDistanceWidget = nullptr;
        interactor = nullptr;
        modeOn = false;
    }

    vtkButtonRulerCallback* vtkButtonRulerCallback::New() {
        return new vtkButtonRulerCallback;
    }

    void vtkButtonRulerCallback::Execute(vtkObject* caller, unsigned long, void*) {
        modeOn = !modeOn;

        if (modeOn) {
            distanceWidget = vtkDistanceWidget::New();
            distanceWidget->SetInteractor(interactor);
            distanceWidget->SetWidgetStateToManipulate();
            dynamic_cast<vtkDistanceRepresentation *>(distanceWidget->GetRepresentation())->
                    SetLabelFormat("%-#6.3g mm");
            distanceWidget->PickingManagedOff();
            distanceWidget->ProcessEventsOff();
            distanceWidget->KeyPressActivationOff();
            distanceWidget->DebugOff();

            vtkNew<vtkDistanceRepresentation3D> representation;
            tempDistanceWidget = vtkDistanceWidget::New();
            tempDistanceWidget->SetInteractor(interactor);
            tempDistanceWidget->SetRepresentation(representation);

            vtkNew<vtkCallbackCommand> clickCallback;
            clickCallback->SetCallback(ClickCallbackFunction);
            clickCallback->SetClientData(distanceWidget);

            tempDistanceWidget->AddObserver(vtkCommand::PlacePointEvent, clickCallback);
            tempDistanceWidget->On();
        }
        else {
            secondPoint = false;
            distanceWidget->Delete();
            distanceWidget = nullptr;
            tempDistanceWidget->Delete();
            tempDistanceWidget = nullptr;
        }
    }

    vtkButtonRulerCallback::~vtkButtonRulerCallback() {
        if (distanceWidget)
            distanceWidget->Delete();
        if (tempDistanceWidget)
            tempDistanceWidget->Delete();
    }
}
