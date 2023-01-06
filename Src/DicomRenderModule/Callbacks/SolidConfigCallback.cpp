#include "SolidConfigCallback.hpp"


namespace LayersConfiguration
{
    vtkSolidConfigCallback::vtkSolidConfigCallback() {
        volumeProperty = nullptr;
    }

    vtkSolidConfigCallback* vtkSolidConfigCallback::New() {
        return new vtkSolidConfigCallback;
    }

    void vtkSolidConfigCallback::Execute(vtkObject* caller, unsigned long, void*) {
        static constexpr double wl = 1560.0;
        static constexpr double ww = 250.0;

        SetColorAndOpacityFunction(volumeProperty, wl, ww);
    }
}
