#include "DefaultConfigCallback.hpp"


namespace LayersConfiguration
{
    vtkDefaultConfigCallback::vtkDefaultConfigCallback() {
        volumeProperty = nullptr;
    }

    vtkDefaultConfigCallback* vtkDefaultConfigCallback::New() {
        return new vtkDefaultConfigCallback;
    }

    void vtkDefaultConfigCallback::Execute(vtkObject* caller, unsigned long, void*) {
        static constexpr double wl = 900.0;
        static constexpr double ww = 300.0;

        SetColorAndOpacityFunction(volumeProperty, wl, ww);
    }
}
