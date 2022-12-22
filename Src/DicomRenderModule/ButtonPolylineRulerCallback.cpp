#include "ButtonPolylineRulerCallback.hpp"

#include <vtkRenderWindowInteractor.h>

vtkButtonPolylineRulerCallback::vtkButtonPolylineRulerCallback()
{
    _polylineWidget = nullptr;
    _interactor = nullptr;
	_modeOn = true;
}

vtkButtonPolylineRulerCallback* vtkButtonPolylineRulerCallback::New()
{
	return new vtkButtonPolylineRulerCallback;
}

void vtkButtonPolylineRulerCallback::Execute(vtkObject* caller_, unsigned long, void*)
{
	if (_modeOn)
	{
        _polylineWidget = PolylineRulerWidget::New();
		_polylineWidget->SetInteractor(_interactor);
		_polylineWidget->Execute();
	}
	else
	{
		_polylineWidget->Delete();
        _polylineWidget = nullptr;
	}
	_modeOn = !_modeOn;
    dynamic_cast<KeyPressInteractorStyle *>(_interactor->GetInteractorStyle())->SetPolyline(_polylineWidget);
}

vtkButtonPolylineRulerCallback::~vtkButtonPolylineRulerCallback()
{
	if (_polylineWidget)
	{
		_polylineWidget->Delete();
	}
}
