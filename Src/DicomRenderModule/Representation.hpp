#ifndef REPRESENTATION_H
#define REPRESENTATION_H

#include "KeyPressInteractorStyle.hpp"

#include <vtkBoxWidget2.h>
#include <vtkNew.h>
#include <vtkCameraOrientationWidget.h>
#include <vtkPlanes.h>
#include <vtkImageReader2.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkBoxRepresentation.h>
#include <vtkAxesActor.h>
#include <vtkImageData.h>


/// <summary>
/// A class that includes all application representation objects
/// </summary>
class Representation
{
public:
	// clipping box
	vtkNew<vtkBoxWidget2> _boxWidget;
	// clipping planes
	vtkNew<vtkPlanes> _planes;
	// dynamic orientation axis
	vtkNew<vtkCameraOrientationWidget> _cameraAxisOrientManipulator;

	Representation(vtkRenderWindowInteractor* iren_, vtkRenderer* renderer_);
	~Representation() = default;
	void setReader(vtkImageReader2* ptrReader);
};

#endif