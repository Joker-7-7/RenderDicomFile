#ifndef POLYLINERULERWIDGET_H
#define POLYLINERULERWIDGET_H

#include <vtkSmartVolumeMapper.h>
#include <vtkAbstractWidget.h>
#include <vtkInteractionWidgetsModule.h>

#include <vtkNew.h>
#include <vtkPoints.h>
#include <vtkPolyLine.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkTextActor.h>
#include <vtkTextActor3D.h>
#include <vtkTextProperty.h>
#include <vtkCallbackCommand.h>

/// <summary>
/// Polyline state
/// </summary>
enum class State
{
	Process,
	End
};

/// <summary>
/// 3D vector for polyline
/// </summary>
struct vec3
{
	double x;
	double y;
	double z;
};

/// <summary>
/// Class for polyline widget
/// </summary>
class PolylineRulerWidget
	: public vtkAbstractWidget
{
public:
	// polyline vertices
	vtkSmartPointer<vtkPoints> _points;
	// polyline lines
	vtkSmartPointer<vtkPolyLine> _polyLine;
	// polyline object in a rendered scene
	vtkSmartPointer<vtkActor> _actor;
	// vertices spheres objects in a rendered scene
	std::vector<vtkSmartPointer<vtkActor>> _sphereActors;
	// polyline text object in a rendered scene
	vtkSmartPointer<vtkTextActor> _text;
	// vector points for polyline vertices
	std::vector<vec3> _vectorPoints;
	// polyline state
	State _state;
	// polyline widget On/Off
	bool _isWidgetOn;

public:
	PolylineRulerWidget();
	~PolylineRulerWidget() override;

    static PolylineRulerWidget* New();

	PolylineRulerWidget(const PolylineRulerWidget&) = delete;
	void operator=(const PolylineRulerWidget&) = delete;
    
	void CreateDefaultRepresentation() override;

	/// <summary>
	/// Start create polyline
	/// </summary>
	void Execute();

	/// <summary>
	/// Insert new vertex in polyline
	/// </summary>
	/// <param name="vs"></param>
	void insertNewPoint(double vs_[3]);

	/// <summary>
	/// Delete the last vertex in polyline
	/// </summary>
	void deleteLastPoint();

	/// <summary>
	/// Update polyline text
	/// </summary>
	void updateText();

	/// <summary>
	/// Get polyline lenght
	/// </summary>
	/// <returns></returns>
	double getLenght();
};

#endif