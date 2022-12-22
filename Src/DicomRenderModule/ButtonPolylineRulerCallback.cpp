#include "ButtonPolylineRulerCallback.hpp"

#include <vtkRenderWindowInteractor.h>

vtkButtonPolylineRulerCallback::vtkButtonPolylineRulerCallback()
{
	_widget = nullptr;
	_lIren = nullptr;
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
		_widget = PolylineRulerWidget::New();
		_widget->SetInteractor(_lIren);
		_widget->Execute();
	}
	else
	{
		_widget->Delete();
		_widget = nullptr;
	}
	_modeOn = !_modeOn;
    dynamic_cast<KeyPressInteractorStyle *>(_lIren->GetInteractorStyle())->SetPolyline(_widget);
}

vtkButtonPolylineRulerCallback::~vtkButtonPolylineRulerCallback()
{
	if (_widget)
	{
		_widget->Delete();
	}
}
