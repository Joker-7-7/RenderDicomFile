#pragma once

#include <Src/GraphicPrimitives/GraphicPrimitives.h>

#include <vtkRenderer.h>
#include <vtkImageData.h>
#include <vtkCubeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCellPicker.h>
#include <vtkInteractorStyle.h>
#include <vtkSTLReader.h>
#include <vtkOpenGLPolyDataMapper.h>


struct LengthSetup
{
	double x;
	double y;
	double z;
};


enum class DrillVisibilityMode
{
	WholeDrillVisible,
	TransparentDrillBody,
	OnlyHeadVisibly
};

/// <summary>
/// Class for drill imitation
/// </summary>
class Drill
{
private:
	// .stl model drill  
	vtkNew<vtkActor> _drillActor;
	// drill tip object in a rendered scene 
	vtkNew<vtkActor> _tipActor;
	// Length drill tip
    LengthSetup _lengthTip;
	// Drill visibility mode
	DrillVisibilityMode _mode;
	// reverse mode
	int _reverse;
	// movement lock
	bool _changePosition;

protected:
	bool checkPointBoundaries(const GraphicPrimitives::Point3D& ijk, const int* iExtents);

public:
	Drill();

	explicit Drill(vtkRenderer* renderer_);
	
	/// <summary>
	/// Read .stl drill model and create _drillActor
	/// </summary>
	void loadSTLDrillModel();

	/// <summary>
	/// Read .stl drill head model and create _drillActor
	/// </summary>
	void loadSTLDrillHeadModel();

	/// <summary>
	/// Set drill opacity
	/// </summary>
	void setOpacity(double value);

	/// <summary>
	/// This method changes the visibility of the drill on each call, in a closed pipeline
	/// if current mode WholeDrillVisible then change to a TransparentDrillBody mode
	/// if current mode TransparentDrillBody then change to a OnlyHeadVisibly mode
	/// if current mode OnlyHeadVisibly then change to a WholeDrillVisible mode
	/// </summary>
	void changeVisibilityMode();

	/// <summary>
	/// // Set visibility mode to whole
	/// </summary>
	void setWholeVisibility();

	/// <summary>
	/// // Set visibility mode to Transparent
	/// </summary>
	void setTransparentVisibility();

	/// <summary>
	/// // Set visibility mode to Head
	/// </summary>
	void setHeadVisibility();

	/// <summary>
	/// Set drill render
	/// </summary>
	/// <param name="l_renderer"></param>
	void setRender(vtkRenderer* renderer_) const;

	/// <summary>
	/// Set drill world position 
	/// </summary>
	/// <param name="newPosition"></param>
	void setPosition(double* newPosition_);

	/// <summary>
	/// Get drill visibility
	/// </summary>
	bool getVisibility();

	/// <summary>
	/// Drill On visibility
	/// </summary>
	void visibilityOn();

	/// <summary>
	/// Drill Off visibility
	/// </summary>
	void visibilityOff();

	/// <summary>
	/// Drilling volume model
	/// </summary>
	/// <param name="volume"></param>
	/// <param name="imageData"></param>
	/// <param name="imagePreData"></param>
	void drillingVolume(vtkVolume* volume_, vtkImageData* imageCurrentData_, vtkImageData* imagePreData_);

	/// <summary>
	/// Move click callback function for drill
	/// </summary>
	/// <param name="caller"></param>
	/// <param name="eventId"></param>
	/// <param name="clientData"></param>
	/// <param name="callData"></param>
	static void drillMovedClickCallbackFunction(vtkObject* caller_, long unsigned int eventId_, void* clientData_,
	                                            void* callData_);

	/// <summary>
	/// Move drill in X-axis
	/// </summary>
	void moveX(float positionStep_);

	/// <summary>
	/// Move drill in Y-axis
	/// </summary>
	void moveY(float positionStep_);

	/// <summary>
	/// move drill Up Z-axis
	/// </summary>
	void moveZ(float positionStep_);

	/// <summary>
	/// Rotate drill around Z-axis
	/// </summary>
	void rotateZ(float angleStep_);

	/// <summary>
	/// Rotate drill around X-axis
	/// </summary>
	void rotateX(float angleStep_);

	/// <summary>
	/// Rotate drill around X-axis
	/// </summary>
	void rotateY(float angleStep_);

	/// <summary>
	/// Reverse drill
	/// </summary>
	void reverseDrill();
	/// <summary>
	/// Mov� drill by key
	/// </summary>
	/// <param name="key_"></param>
	/// <param name="angleStep"></param>
	/// <param name="positionStep"></param>
	void moveDrillByKey(const char* key_, const float angleStep, const float positionStep);
	/// <summary>
	///  Set _changePosition
	/// </summary>
	void setChangePositionMode(bool value);
	/// <summary>
	/// Get _changePosition
	/// </summary>
	[[nodiscard]] bool IsChangingPositionMode() const;

};
