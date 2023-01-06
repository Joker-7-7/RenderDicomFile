#include "SkinConfigCallback.hpp"


namespace LayersConfiguration
{
    vtkSkinConfigCallback::vtkSkinConfigCallback() {
        volumeProperty = nullptr;
    }

    vtkSkinConfigCallback* vtkSkinConfigCallback::New() {
        return new vtkSkinConfigCallback;
    }

    void vtkSkinConfigCallback::Execute(vtkObject* caller, unsigned long, void*) {
        static constexpr double wl = 0.0;
        static constexpr double ww = 1040.0;

        SetColorAndOpacityFunction(volumeProperty, wl, ww);
    }
}
