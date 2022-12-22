#include "ButtonReverseDrillCallback.hpp"

vtkButtonReverseDrillCallback::vtkButtonReverseDrillCallback()
{
	_drill = nullptr;
}

vtkButtonReverseDrillCallback* vtkButtonReverseDrillCallback::New()
{
	return new vtkButtonReverseDrillCallback;
}

void vtkButtonReverseDrillCallback::Execute(vtkObject* caller_, unsigned long, void*)
{
	_drill->reverseDrill();
}
