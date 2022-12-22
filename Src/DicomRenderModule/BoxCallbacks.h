#ifndef BOXCALLBACKS_H
#define BOXCALLBACKS_H

#include "AbstractCallback.h"
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
	enum boxMode{
		Drilling = 10
	};
	vtkBoxCallback();

	vtkVolume* _volume;

	vtkPlanes* _planes;

	vtkImageData* _imageCurrentData;

	vtkImageData* _imagePreData;

	static vtkBoxCallback* New();

	void Execute(vtkObject* caller_, unsigned long mode_, void*) override;
};

#endif