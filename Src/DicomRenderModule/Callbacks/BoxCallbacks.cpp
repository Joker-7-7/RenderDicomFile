#include "BoxCallbacks.hpp"

vtkBoxCallback::vtkBoxCallback() {
    volume = nullptr;
    planes = nullptr;
    imageCurrentData = nullptr;
    imagePreData = nullptr;
}

vtkBoxCallback* vtkBoxCallback::New() {
    return new vtkBoxCallback;
}

void vtkBoxCallback::Execute(vtkObject* caller, unsigned long mode, void*) {
    const auto boxWidget = vtkBoxWidget2::SafeDownCast(caller);
    dynamic_cast<vtkBoxRepresentation *>(boxWidget->GetRepresentation())->GetPlanes(planes);

    if (static_cast<BoxMode>(mode) != BoxMode::Drilling) {
        imageCurrentData->DeepCopy(imagePreData);
    }

    const int *extent = imageCurrentData->GetExtent();
    for (int n = 0; n < planes->GetNumberOfPlanes(); ++n) {
        vtkNew<vtkPlane> plane;
        planes->GetPlane(n, plane);

        const double *normal = plane->GetNormal();
        const double *origin = plane->GetOrigin();

        double originVoxelIndex[3];
        imageCurrentData->TransformPhysicalPointToContinuousIndex(origin, originVoxelIndex);
        originVoxelIndex[0] = std::round(originVoxelIndex[0]);
        originVoxelIndex[1] = std::round(originVoxelIndex[1]);
        originVoxelIndex[2] = std::round(originVoxelIndex[2]);

        if (abs(normal[0]) == 1.0) {
            const int i = static_cast<int>(originVoxelIndex[0]);

            if (originVoxelIndex[0] > 0 && originVoxelIndex[0] < extent[1]) {
                for (int j = 0; j <= extent[3]; ++j) {
                    for (int k = 0; k <= extent[5]; ++k) {
                        *static_cast<int *>(imageCurrentData->GetScalarPointer(i, j, k)) = 0;
                    }
                }
            }
        }
        else if (abs(normal[1]) == 1.0) {
            const int j = static_cast<int>(originVoxelIndex[1]);

            if (originVoxelIndex[1] > 0 && originVoxelIndex[1] < extent[3]) {
                for (int i = 0; i <= extent[1]; ++i) {
                    for (int k = 0; k <= extent[5]; ++k) {
                        *static_cast<int *>(imageCurrentData->GetScalarPointer(i, j, k)) = 0;
                    }
                }
            }
        }
        else if (abs(normal[2]) == 1.0) {
            const int k = static_cast<int>(originVoxelIndex[2]);
            
            if (originVoxelIndex[2] > 0 && originVoxelIndex[2] < extent[5]) {
                for (int i = 0; i <= extent[1]; ++i) {
                    for (int j = 0; j <= extent[3]; ++j) {
                        *static_cast<int *>(imageCurrentData->GetScalarPointer(i, j, k)) = 0;
                    }
                }
            }
        }
    }

    const auto currentMapper = dynamic_cast<vtkGPUVolumeRayCastMapper*>(volume->GetMapper());

    vtkNew<vtkGPUVolumeRayCastMapper> newMapper;
    newMapper->SetUseJittering(currentMapper->GetUseJittering());
    newMapper->SetMaximumImageSampleDistance(currentMapper->GetMaximumImageSampleDistance());
    newMapper->SetInputData(imageCurrentData);
    volume->SetMapper(newMapper);
    newMapper->SetClippingPlanes(planes);
}
