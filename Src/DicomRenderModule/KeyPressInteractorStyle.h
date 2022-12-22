#ifndef KEYPRESSINTERACTORSTYLE_H
#define KEYPRESSINTERACTORSTYLE_H

#include "BoxCallbacks.h"
#include "PolylineRulerWidget.h"
#include "Drill.h"
#include "AbstractCallback.h"

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
private:

	Drill* _drill;

	vtkImageData* _imageCurrentData;

	vtkImageData* _imagePreData;

	vtkVolume* _volume;

	vtkBoxCallback* _boxCallback;

	vtkBoxWidget2* _boxWidget;

	PolylineRulerWidget* _polylineWidget;
public:
	KeyPressInteractorStyle();

	static KeyPressInteractorStyle* New();

	void OnLeftButtonUp() override;

	void OnKeyDown() override;

	void OnMouseMove() override;

	void OnKeyRelease() override;

	void setDrill(Drill* drill);
	void setImageCurrentData(vtkImageData* imageCurrentData);
	void setImagePreData(vtkImageData* imagePreData);
	void setVolume(vtkVolume* volume);
	void setBoxCallback(vtkBoxCallback* boxCallback);
	void setBoxWidget(vtkBoxWidget2* boxWidget);
	void setPolyline(PolylineRulerWidget* polylineWidget);
};

#endif