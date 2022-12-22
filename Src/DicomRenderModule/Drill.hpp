#ifndef DRILL_H
#define DRILL_H

#include "Src/GraphicPrimitives/GraphicPrimitives.hpp"

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
public:
	Drill();

	explicit Drill(vtkRenderer* renderer_);
	
	/// <summary>
	/// Read .stl drill model and create _drillActor
	/// </summary>
	void LoadSTLDrillModel();

	/// <summary>
	/// Read .stl drill head model and create _drillActor
	/// </summary>
	void LoadSTLDrillHeadModel();

	/// <summary>
	/// Set drill opacity
	/// </summary>
	void SetOpacity(double value) noexcept;

	/// <summary>
	/// This method changes the visibility of the drill on each call, in a closed pipeline
	/// if current mode WholeDrillVisible then change to a TransparentDrillBody mode
	/// if current mode TransparentDrillBody then change to a OnlyHeadVisibly mode
	/// if current mode OnlyHeadVisibly then change to a WholeDrillVisible mode
	/// </summary>
	void ChangeVisibilityMode();

	/// <summary>
	/// // Set visibility mode to whole
	/// </summary>
	void SetWholeVisibility();

	/// <summary>
	/// // Set visibility mode to Transparent
	/// </summary>
	void SetTransparentVisibility() noexcept;

	/// <summary>
	/// // Set visibility mode to Head
	/// </summary>
	void SetHeadVisibility();

	/// <summary>
	/// Set drill render
	/// </summary>
	/// <param name="l_renderer"></param>
	void SetRender(vtkRenderer* renderer_) const;

	/// <summary>
	/// Set drill world position 
	/// </summary>
	/// <param name="newPosition"></param>
	void SetPosition(double* newPosition_) noexcept;

	/// <summary>
	/// Get drill visibility
	/// </summary>
	[[nodiscard]] bool GetVisibility() const noexcept;

	/// <summary>
	/// Drill On visibility
	/// </summary>
	void VisibilityOn() noexcept;

	/// <summary>
	/// Drill Off visibility
	/// </summary>
	void VisibilityOff() noexcept;

	/// <summary>
	/// Drilling volume model
	/// </summary>
	/// <param name="volume"></param>
	/// <param name="imageData"></param>
	/// <param name="imagePreData"></param>
	void DrillingVolume(vtkImageData* imageCurrentData_, vtkImageData* imagePreData_);

	/// <summary>
	/// Move click callback function for drill
	/// </summary>
	/// <param name="caller"></param>
	/// <param name="eventId"></param>
	/// <param name="clientData"></param>
	/// <param name="callData"></param>
	static void DrillMovedClickCallbackFunction(vtkObject* caller_, long unsigned int eventId_, void* clientData_,
                                                void* callData_);

	/// <summary>
	/// Move drill in X-axis
	/// </summary>
	void MoveX(float positionStep_) noexcept;

	/// <summary>
	/// Move drill in Y-axis
	/// </summary>
	void MoveY(float positionStep_) noexcept;

	/// <summary>
	/// move drill Up Z-axis
	/// </summary>
	void MoveZ(float positionStep_) noexcept;

	/// <summary>
	/// Rotate drill around Z-axis
	/// </summary>
	void RotateZ(float angleStep_) noexcept;

	/// <summary>
	/// Rotate drill around X-axis
	/// </summary>
	void RotateX(float angleStep_) noexcept;

	/// <summary>
	/// Rotate drill around X-axis
	/// </summary>
	void RotateY(float angleStep_) noexcept;

	/// <summary>
	/// Reverse drill
	/// </summary>
	void ReverseDrill() noexcept;
	/// <summary>
	/// Move drill by key
	/// </summary>
	/// <param name="key_"></param>
	/// <param name="angleStep"></param>
	/// <param name="positionStep"></param>
	void MoveDrillByKey(const char* key_, const float angleStep, const float positionStep)  noexcept;
	/// <summary>
	///  Set _changePosition
	/// </summary>
	void SetChangePositionMode(bool value) noexcept;
	/// <summary>
	/// Get _changePosition
	/// </summary>
	[[nodiscard]] bool IsChangingPositionMode() const noexcept;

protected:
    bool CheckPointBoundaries(const GraphicPrimitives::Point3D& ijk, const int* iExtents) const noexcept;

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
};

#endif