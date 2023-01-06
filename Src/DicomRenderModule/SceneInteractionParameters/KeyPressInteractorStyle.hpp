#ifndef KEYPRESSINTERACTORSTYLE_H
#define KEYPRESSINTERACTORSTYLE_H

#include "Src/DicomRenderModule/Callbacks/BoxCallbacks.hpp"
#include "Src/DicomRenderModule/Callbacks/AbstractCallback.hpp"

#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRendererCollection.h>
#include <vtkCellPicker.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

/// <summary>
/// Interactor style with render scene
/// </summary>
class KeyPressInteractorStyle : public vtkInteractorStyleTrackballCamera
{

public:
	KeyPressInteractorStyle();

	static KeyPressInteractorStyle* New();

	void SetImageCurrentData(vtkImageData* imageCurrentData) noexcept;
	void SetImagePreData(vtkImageData* imagePreData) noexcept;
	void SetBoxCallback(vtkBoxCallback* boxCallback) noexcept;
	void SetBoxWidget(vtkBoxWidget2* boxWidget) noexcept;

private:
    vtkImageData* _imageCurrentData;
    vtkImageData* _imagePreData;
    vtkBoxCallback* _boxCallback;
    vtkBoxWidget2* _boxWidget;
};

#endif