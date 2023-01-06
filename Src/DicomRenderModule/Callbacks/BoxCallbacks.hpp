#ifndef BOXCALLBACKS_H
#define BOXCALLBACKS_H

#include "AbstractCallback.hpp"

#include <vtkObject.h>
#include <vtkBoxWidget2.h>
#include <vtkNew.h>
#include <vtkPlane.h>
#include <vtkBoxRepresentation.h>
#include <vtkPlanes.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkVolume.h>
#include <vtkImageData.h>


/// <summary>
/// Clipping Box interaction callback
/// </summary>
class vtkBoxCallback final : public AbstractCallback
{
public:
	enum class BoxMode{
		Drilling = 10
	};

    vtkVolume* volume;
    vtkPlanes* planes;
    vtkImageData* imageCurrentData;
    vtkImageData* imagePreData;

public:
	vtkBoxCallback();

	static vtkBoxCallback* New();
	void Execute(vtkObject* caller, unsigned long mode, void*) override;
};

#endif