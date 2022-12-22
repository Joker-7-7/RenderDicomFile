#ifndef KEYPRESSINTERACTORSTYLE_H
#define KEYPRESSINTERACTORSTYLE_H

#include "BoxCallbacks.hpp"
#include "PolylineRulerWidget.hpp"
#include "Drill.hpp"
#include "AbstractCallback.hpp"

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

	void OnLeftButtonUp() override;
	void OnKeyDown() override;
	void OnMouseMove() override;
	void OnKeyRelease() override;

	void SetDrill(Drill* drill);
	void SetImageCurrentData(vtkImageData* imageCurrentData);
	void SetImagePreData(vtkImageData* imagePreData);
	void SetVolume(vtkVolume* volume);
	void SetBoxCallback(vtkBoxCallback* boxCallback);
	void SetBoxWidget(vtkBoxWidget2* boxWidget);
	void SetPolyline(PolylineRulerWidget* polylineWidget);

private:
    Drill* _drill;
    vtkImageData* _imageCurrentData;
    vtkImageData* _imagePreData;
    vtkVolume* _volume;
    vtkBoxCallback* _boxCallback;
    vtkBoxWidget2* _boxWidget;
    PolylineRulerWidget* _polylineWidget;
};

#endif