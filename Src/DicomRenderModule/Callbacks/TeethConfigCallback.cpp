#include "TeethConfigCallback.hpp"


namespace LayersConfiguration
{
    vtkTeethConfigCallback::vtkTeethConfigCallback() {
        volumeProperty = nullptr;
    }

    vtkTeethConfigCallback* vtkTeethConfigCallback::New() {
        return new vtkTeethConfigCallback;
    }

    void vtkTeethConfigCallback::Execute(vtkObject* caller, unsigned long, void*) {
        static constexpr double wl = 1830.0;
        static constexpr double ww = 140.0;

        SetColorAndOpacityFunction(volumeProperty, wl, ww);
    }
}
