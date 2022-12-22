#include "PolylineRulerWidget.hpp"

#include <vtkCoordinate.h>
#include <vtkDistanceRepresentation2D.h>
#include <vtkEventData.h>
#include <vtkHandleRepresentation.h>
#include <vtkObjectFactory.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkWidgetCallbackMapper.h>
#include <vtkWidgetEventTranslator.h>
#include "vtkSphereSource.h"
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRendererCollection.h>
#include <vtkCellPicker.h>

vtkStandardNewMacro(PolylineRulerWidget);

PolylineRulerWidget::PolylineRulerWidget()
{
	_isWidgetOn = false;
	_state = State::Process;

	_points = vtkSmartPointer<vtkPoints>::New();
	_polyLine = vtkSmartPointer<vtkPolyLine>::New();
	_actor = vtkSmartPointer<vtkActor>::New();
	_text = vtkSmartPointer<vtkTextActor>::New();

	_text->SetInput("0.0");
	_text->GetTextProperty()->SetFontSize(36);
}

void PolylineRulerWidget::CreateDefaultRepresentation()
{
	if (!WidgetRep)
	{
		WidgetRep = vtkDistanceRepresentation2D::New();
	}
}

double PolylineRulerWidget::GetLength() const noexcept
{
	double sum = 0.0;

	if (_vectorPoints.size() < 2)
	{
		return sum;
	}

	for (size_t i = 0; i < _vectorPoints.size() - 1; ++i)
	{
		auto pt1 = _vectorPoints[i];
		auto pt2 = _vectorPoints[i + 1];

		double len_quad = 0.0;

		len_quad = pow(pt2.x - pt1.x, 2.0) +
			pow(pt2.y - pt1.y, 2.0) +
			pow(pt2.z - pt1.z, 2.0);

		sum += sqrt(len_quad);
	}
	return sum;
}

void PolylineRulerWidget::InsertNewPoint(double vs_[3])
{
	if (_state == State::End)
	{
		return;
	}

	_points->InsertNextPoint(vs_);
	auto list = _polyLine->GetPointIds();
	list->InsertNextId(list->GetNumberOfIds());

	_vectorPoints.push_back(*(vec3*)vs_);

	vtkNew<vtkCellArray>_cells;
	_cells->InsertNextCell(_polyLine);

	vtkNew<vtkPolyData> _polyData;
	_polyData->SetPoints(_points);
	_polyData->SetLines(_cells);

	vtkNew<vtkPolyDataMapper> _mapper;
	_mapper->SetInputDataObject(_polyData);
	_actor->SetMapper(_mapper);
	_actor->GetProperty()->SetLineWidth(2.0);

	vtkNew<vtkSphereSource> sphereSource;
	sphereSource->SetRadius(0.5);
	sphereSource->SetCenter(vs_);
	vtkNew<vtkPolyDataMapper> sphereMapper;
	sphereMapper->SetInputConnection(sphereSource->GetOutputPort());

	auto sphereActor = vtkSmartPointer<vtkActor>::New();
	sphereActor->GetProperty()->SetColor(0, 1, 0);
	sphereActor->SetMapper(sphereMapper);
	this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(sphereActor);

	_sphereActors.push_back(sphereActor);

	const double dPolylineLen = GetLength();
	const auto output = std::to_string(dPolylineLen);
	_text->SetInput(output.c_str());

    UpdateText();
}

void PolylineRulerWidget::UpdateText()
{
	vtkNew<vtkCoordinate> cord;
	vec3 pt = !_vectorPoints.empty() ? _vectorPoints.back() : pt = {0.0, 0.0, 0.0};
	const double picked[3]{pt.x, pt.y, pt.z};
	cord->SetCoordinateSystemToWorld();
	cord->SetValue(picked);
	const auto pos = cord->GetComputedViewportValue(
		Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
	_text->SetDisplayPosition(pos[0], pos[1]);
}

void PolylineRulerWidget::DeleteLastPoint()
{
	if (_vectorPoints.empty())
	{
		return;
	}

	_vectorPoints.pop_back();

	Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(
		_sphereActors[_sphereActors.size() - 1]);

	_sphereActors.pop_back();

	_points = vtkSmartPointer<vtkPoints>::New();
	_polyLine = vtkSmartPointer<vtkPolyLine>::New();

	for (size_t i = 0; i < _vectorPoints.size(); ++i)
	{
		_points->InsertNextPoint(reinterpret_cast<double*>(&_vectorPoints[i]));
		_polyLine->GetPointIds()->InsertNextId(i);
	}

	vtkNew<vtkCellArray>_cells;
	_cells->InsertNextCell(_polyLine);

	vtkNew<vtkPolyData> _polyData;
	_polyData->SetPoints(_points);
	_polyData->SetLines(_cells);

	vtkNew<vtkPolyDataMapper> _mapper;
	_mapper->SetInputDataObject(_polyData);
	_mapper->Update();
	_actor->SetMapper(_mapper);

	const double dPolylineLen = GetLength();
	const auto output = std::to_string(dPolylineLen);
	_text->SetInput(output.c_str());

    UpdateText();
}

PolylineRulerWidget::~PolylineRulerWidget()
{
	_isWidgetOn = false;
	for (size_t i = _sphereActors.size() - 1; i >= 0; --i)
	{
		Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(_sphereActors[i]);
	}

	Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(_actor);
	Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(_text);
}

void PolylineRulerWidget::Execute()
{
	_isWidgetOn = true;
	_actor->GetProperty()->SetColor(0, 1, 0);
	Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(_actor);
	Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(_text);
}
