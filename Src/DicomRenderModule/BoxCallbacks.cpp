#include "BoxCallbacks.h"



vtkBoxCallback::vtkBoxCallback()
{
	_volume = nullptr;
	_planes = nullptr;
	_imageCurrentData = nullptr;
	_imagePreData = nullptr;
}

vtkBoxCallback* vtkBoxCallback::New()
{
	return new vtkBoxCallback;
}

void vtkBoxCallback::Execute(vtkObject* caller_, unsigned long mode_, void*)
{
	const auto l_box_widget = vtkBoxWidget2::SafeDownCast(caller_);
	dynamic_cast<vtkBoxRepresentation*>(l_box_widget->GetRepresentation())->GetPlanes(_planes);

	if (mode_ != boxMode::Drilling)
	{
		_imageCurrentData->DeepCopy(_imagePreData); 
	}

	const int* extent = _imageCurrentData->GetExtent();
	for (int n = 0; n < _planes->GetNumberOfPlanes(); ++n)
	{
		vtkNew<vtkPlane> plane;
		_planes->GetPlane(n, plane);
		const double* normal = plane->GetNormal();
		const double* origin = plane->GetOrigin();

		double ijk[3];
		_imageCurrentData->TransformPhysicalPointToContinuousIndex(origin, ijk);
		ijk[0] = std::round(ijk[0]);
		ijk[1] = std::round(ijk[1]);
		ijk[2] = std::round(ijk[2]);

		if (abs(normal[0]) == 1.0)
		{
			const int i = static_cast<int>(ijk[0]);
			if (ijk[0] > 0 && ijk[0] < extent[1])
			{
				for (int j = 0; j <= extent[3]; ++j)
				{
					for (int k = 0; k <= extent[5]; ++k)
					{
						*static_cast<int*>(_imageCurrentData->GetScalarPointer(i, j, k)) = 0;
					}
				}
			}
		}
		else if (abs(normal[1]) == 1.0)
		{
			const int j = static_cast<int>(ijk[1]);
			if (ijk[1] > 0 && ijk[1] < extent[3])
			{
				for (int i = 0; i <= extent[1]; ++i)
				{
					for (int k = 0; k <= extent[5]; ++k)
					{
						*static_cast<int*>(_imageCurrentData->GetScalarPointer(i, j, k)) = 0;
					}
				}
			}
		}
		else if (abs(normal[2]) == 1.0)
		{
			const int k = static_cast<int>(ijk[2]);
			if (ijk[2] > 0 && ijk[2] < extent[5])
			{
				for (int i = 0; i <= extent[1]; ++i)
				{
					for (int j = 0; j <= extent[3]; ++j)
					{
						*static_cast<int*>(_imageCurrentData->GetScalarPointer(i, j, k)) = 0;
					}
				}
			}
		}
	}

	const auto currentMapper = dynamic_cast<vtkGPUVolumeRayCastMapper*>(_volume->GetMapper());

	vtkNew<vtkGPUVolumeRayCastMapper> newMapper;
	newMapper->SetUseJittering(currentMapper->GetUseJittering());
	newMapper->SetMaximumImageSampleDistance(currentMapper->GetMaximumImageSampleDistance());
	newMapper->SetInputData(_imageCurrentData);
	_volume->SetMapper(newMapper);
	newMapper->SetClippingPlanes(_planes);
}
