#include "Drill.hpp"

#include <vtkProperty.h>
#include <vtkVector.h>

#include <qfile.h>
#include <qdir.h>


Drill::Drill()
	:_lengthTip{ 0.5, 0.5, 10.0 }
{
	_reverse = 1;
	_changePosition = false;
	_mode = DrillVisibilityMode::WholeDrillVisible;

	// cube for drill tip 
	vtkNew<vtkCubeSource> _tipSource;
	// set drill tip dimensions
	_tipSource->SetXLength(_lengthTip.x);
	_tipSource->SetYLength(_lengthTip.y);
	_tipSource->SetZLength(_lengthTip.z);
	_tipSource->SetCenter(0.0, 0.0, -_lengthTip.z / 2.0);
	// drill tip polygonal data
	vtkNew<vtkPolyDataMapper> _tipMapper;
	_tipMapper->SetInputConnection(_tipSource->GetOutputPort());
	_tipActor->SetMapper(_tipMapper);
	_tipActor->VisibilityOff();

    LoadSTLDrillModel();
    _drillActor->VisibilityOff();
}

Drill::Drill(vtkRenderer* renderer_) : Drill()
{
    SetRender(renderer_);
}

void Drill::LoadSTLDrillModel()
{
    QString path = QDir::currentPath() + "/STLModelResources/Drill.stl";

    vtkNew<vtkSTLReader> STLReader;
    STLReader->SetFileName(path.toStdString().c_str());
    STLReader->Update();

	vtkNew<vtkOpenGLPolyDataMapper> stlDrillMapper;
	stlDrillMapper->SetInputData(STLReader->GetOutput());
	_drillActor->SetMapper(stlDrillMapper);
}

void Drill::LoadSTLDrillHeadModel()
{
    QString path = QDir::currentPath() + "/STLModelResources/drillHead.stl";

	vtkNew<vtkSTLReader> STLReader;
    STLReader->SetFileName(path.toStdString().c_str());
	STLReader->Update();

	vtkNew<vtkOpenGLPolyDataMapper> stlDrillMapper;
	stlDrillMapper->SetInputData(STLReader->GetOutput());
	_drillActor->SetMapper(stlDrillMapper);
}

void Drill::SetWholeVisibility()
{
    SetOpacity(1.0);
    LoadSTLDrillModel();
}

void Drill::SetTransparentVisibility()
{
    SetOpacity(0.1);
}

void Drill::SetHeadVisibility()
{
    SetOpacity(1.0);
    LoadSTLDrillHeadModel();
}

void Drill::ChangeVisibilityMode()
{
	if (GetVisibility())
	{
		switch (_mode)
		{
		case DrillVisibilityMode::WholeDrillVisible:
            SetTransparentVisibility();
			_mode = DrillVisibilityMode::TransparentDrillBody;
			break;
		case DrillVisibilityMode::TransparentDrillBody:
            SetHeadVisibility();
			_mode = DrillVisibilityMode::OnlyHeadVisibly;
			break;
		case DrillVisibilityMode::OnlyHeadVisibly:
            SetWholeVisibility();
			_mode = DrillVisibilityMode::WholeDrillVisible;
			break;
		}
	}
}

void Drill::SetOpacity(double value)
{
	_drillActor->GetProperty()->SetOpacity(value);
}

void Drill::SetRender(vtkRenderer* renderer_) const
{
	renderer_->AddActor(_tipActor);
	renderer_->AddActor(_drillActor);
}

void Drill::SetPosition(double* newPosition_)
{
	_drillActor->SetPosition(newPosition_);
	_tipActor->SetPosition(newPosition_);
}

bool Drill::GetVisibility()
{
	return _drillActor->GetVisibility();
}

void Drill::VisibilityOn()
{
	_drillActor->VisibilityOn();
	_tipActor->VisibilityOn();
}

void Drill::VisibilityOff()
{
	_drillActor->VisibilityOff();
	_tipActor->VisibilityOff();
}

void Drill::MoveX(float positionStep_)
{
	double newPosition[3] = { positionStep_, 0.0, 0.0};
	_drillActor->AddPosition(newPosition);
	_tipActor->AddPosition(newPosition);
}

void Drill::MoveY(float positionStep_)
{
	double newPosition[3] = {0.0, positionStep_, 0.0};
	_drillActor->AddPosition(newPosition);
	_tipActor->AddPosition(newPosition);
}

void Drill::MoveZ(float positionStep_)
{
	double newPosition[3] = {0.0, 0.0, positionStep_ };
	_drillActor->AddPosition(newPosition);
	_tipActor->AddPosition(newPosition);
}

void Drill::RotateX(float angleStep_)
{
	_drillActor->RotateX(angleStep_);
	_tipActor->RotateX(angleStep_);
}

void Drill::RotateY(float angleStep_)
{
	_drillActor->RotateY(angleStep_);
	_tipActor->RotateY(angleStep_);
}

void Drill::RotateZ(float angleStep_)
{
	_drillActor->RotateZ(angleStep_);
	_tipActor->RotateZ(angleStep_);
}

void Drill::ReverseDrill()
{
	_reverse *= -1;
    RotateY(180);
}

void Drill::MoveDrillByKey(const char* key_, const float angleStep, const float positionStep)
{
	if (!std::strcmp(key_, "Right"))
	{
        MoveX(positionStep);
	}
	else if (!std::strcmp(key_, "Left"))
	{
        MoveX(-positionStep);
	}
	else if (!std::strcmp(key_, "Down"))
	{
        MoveY(positionStep);
	}
	else if (!std::strcmp(key_, "Up"))
	{
        MoveY(-positionStep);
	}
	else if (!std::strcmp(key_, "z"))
	{
        MoveZ(positionStep);
	}
	else if (!std::strcmp(key_, "x"))
	{
        MoveZ(-positionStep);
	}
	else if (!std::strcmp(key_, "c"))
	{
        RotateZ(angleStep);
	}
	else if (!std::strcmp(key_, "v"))
	{
        RotateZ(-angleStep);
	}
	else if (!std::strcmp(key_, "b"))
	{
        RotateY(angleStep);
	}
	else if (!std::strcmp(key_, "n"))
	{
        RotateY(-angleStep);
	}
	else if (!std::strcmp(key_, "g"))
	{
        RotateX(angleStep);
	}
	else if (!std::strcmp(key_, "h"))
	{
        RotateX(-angleStep);
	}
}

bool Drill::IsChangingPositionMode() const
{
	return _changePosition;
}

void Drill::SetChangePositionMode(bool value)
{
	_changePosition = value;
}

bool Drill::CheckPointBoundaries(const GraphicPrimitives::Point3D& ijk, const int* iExtents)
{
	bool isValidXposDownBound = ijk.x > 7;
	bool isValidYposDownBound = ijk.y > 7;
	bool isValidZposDownBound = ijk.z > 7;
	bool isValidXposUpperBound = ijk.x < iExtents[1] - 7;
	bool isValidYposUpperBound = ijk.y < iExtents[3] - 7;
	bool isValidZposUpperBound = ijk.z < iExtents[5] - 7;

	return isValidXposDownBound && isValidYposDownBound && isValidZposDownBound && isValidXposUpperBound && isValidYposUpperBound && isValidZposUpperBound;
}

void Drill::DrillingVolume(vtkVolume* volume_, vtkImageData* imageCurrentData_, vtkImageData* imagePreData_)
{
	double* dSpacing = imageCurrentData_->GetSpacing();
	GraphicPrimitives::Point3D dTipPosition (_tipActor->GetPosition());
	GraphicPrimitives::Point3D dTipCenter (_tipActor->GetCenter());

	vtkVector3d dTipVector(dTipCenter.x - dTipPosition.x, dTipCenter.y - dTipPosition.y, dTipCenter.z - dTipPosition.z);
	dTipVector.Normalize();

	GraphicPrimitives::Point3D dCurrentTipPoint(dTipPosition);

	double ijkTmp[3];
	imageCurrentData_->TransformPhysicalPointToContinuousIndex(reinterpret_cast<const double*>(&dCurrentTipPoint), ijkTmp);
	GraphicPrimitives::Point3D ijkPoint(ijkTmp);
	ijkPoint.round();

	int* iExtents =  imageCurrentData_->GetExtent();
	bool isInBound = CheckPointBoundaries(ijkPoint, iExtents);

	if (isInBound)
	{
		for (int n = 0; n < 6; ++n)
		{
			for (int i = -1; i <= 1; ++i)
			{
				for (int j = -1; j <= 1; ++j)
				{
					for (int k = -1; k <= 1; ++k)
					{
						*static_cast<uint16_t*>(imageCurrentData_->GetScalarPointer(ijkPoint.x + i, ijkPoint.y + j, ijkPoint.z + k)) = 0;
						*static_cast<uint16_t*>(imagePreData_->GetScalarPointer(ijkPoint.x + i, ijkPoint.y + j, ijkPoint.z + k)) = 0;
					}
				}
			}

			dCurrentTipPoint.x = dCurrentTipPoint.x + dTipVector.GetX() * (*dSpacing);
			dCurrentTipPoint.y = dCurrentTipPoint.y + dTipVector.GetY() * (*dSpacing);
			dCurrentTipPoint.z = dCurrentTipPoint.z + dTipVector.GetZ() * (*dSpacing);

			imageCurrentData_->TransformPhysicalPointToContinuousIndex(reinterpret_cast<const double*>(&dCurrentTipPoint), ijkTmp);
			ijkPoint = ijkTmp;
			ijkPoint.round();
		}
	}
}

void Drill::DrillMovedClickCallbackFunction(vtkObject* caller_, long unsigned int eventId_, void* clientData_,
                                            void* callData_)
{
	vtkRenderWindowInteractor* inter = vtkRenderWindowInteractor::SafeDownCast(caller_);
	auto ptrDrill = static_cast<Drill*>(clientData_);

	int* pos = inter->GetEventPosition();

	vtkNew<vtkCellPicker> picker;
	picker->SetTolerance(0.0005);

	// Pick from this location.
	picker->Pick(pos[0], pos[1], 0, inter->GetInteractorStyle()->GetCurrentRenderer());

	double* worldPosition = picker->GetPickPosition();
	if (picker->GetCellId() != -1 && ptrDrill->_changePosition)
	{
        ptrDrill->SetPosition(worldPosition);
	}
}
