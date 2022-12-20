#include "ButtonBoxCallback.h"

vtkButtonBoxCallback::vtkButtonBoxCallback()
{
	_box = nullptr;
	_modeOn = false;
}

vtkButtonBoxCallback* vtkButtonBoxCallback::New()
{
	return new vtkButtonBoxCallback;
}

void vtkButtonBoxCallback::Execute(vtkObject* caller_, unsigned long, void*)
{
	_modeOn = !_modeOn;
	_box->SetEnabled(_modeOn);
}

vtkButtonBoxCallback::~vtkButtonBoxCallback()
{
	_box->SetEnabled(false);
}
