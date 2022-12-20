#include "ButtonVisibilityDrillCallback.h"

vtkButtonVisibilityDrillCallback::vtkButtonVisibilityDrillCallback()
{
	_drill = nullptr;
}

vtkButtonVisibilityDrillCallback* vtkButtonVisibilityDrillCallback::New()
{
	return new vtkButtonVisibilityDrillCallback;
}

void vtkButtonVisibilityDrillCallback::Execute(vtkObject* caller_, unsigned long, void*)
{
	_drill->changeVisibilityMode();
}