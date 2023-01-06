#include "VolumeParametersCallback.hpp"

vtkButtonJitteringModeCallback::vtkButtonJitteringModeCallback() {
    volume = nullptr;
    isJitteringMode = false;
}

vtkButtonJitteringModeCallback* vtkButtonJitteringModeCallback::New() {
    return new vtkButtonJitteringModeCallback;
}

void vtkButtonJitteringModeCallback::Execute(vtkObject* caller, unsigned long, void*) {
    auto curMapper = dynamic_cast<vtkGPUVolumeRayCastMapper *>(volume->GetMapper());

    isJitteringMode ? curMapper->UseJitteringOn() : curMapper->UseJitteringOff();
    isJitteringMode = !isJitteringMode;
}
