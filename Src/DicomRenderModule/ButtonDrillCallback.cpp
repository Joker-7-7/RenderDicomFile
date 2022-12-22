#include "ButtonDrillCallback.hpp"

vtkButtonDrillCallback::vtkButtonDrillCallback()
{
	_modeOn = false;
	_drill = nullptr;
}

vtkButtonDrillCallback* vtkButtonDrillCallback::New()
{
	return new vtkButtonDrillCallback;
}

void vtkButtonDrillCallback::Execute(vtkObject* caller_, unsigned long, void*)
{
	_modeOn = !_modeOn;
	_modeOn ? _drill->visibilityOn() : _drill->visibilityOff();
	_drill->setChangePositionMode(_modeOn);
}
