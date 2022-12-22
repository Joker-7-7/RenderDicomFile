#include "VolumeParametersCallback.h"

vtkButtonJitteringModeCallback::vtkButtonJitteringModeCallback()
{
	_volume = nullptr;
	_isJitteringMode = false;
}

vtkButtonJitteringModeCallback* vtkButtonJitteringModeCallback::New()
{
	return new vtkButtonJitteringModeCallback;
}

void vtkButtonJitteringModeCallback::Execute(vtkObject* caller_, unsigned long, void*)
{
	auto curMapper = dynamic_cast<vtkGPUVolumeRayCastMapper*>(_volume->GetMapper());

	_isJitteringMode ? curMapper->UseJitteringOn() : curMapper->UseJitteringOff();
	_isJitteringMode = !_isJitteringMode;
}
