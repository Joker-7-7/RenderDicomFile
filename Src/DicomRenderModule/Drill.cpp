#include "Drill.h"

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

	loadSTLDrillModel();
    _drillActor->VisibilityOff();
}

Drill::Drill(vtkRenderer* renderer_) : Drill()
{
	setRender(renderer_);
}

void Drill::loadSTLDrillModel()
{
    QString path = QDir::currentPath() + "/STLModelResources/Drill.stl";

    vtkNew<vtkSTLReader> STLReader;
    STLReader->SetFileName(path.toStdString().c_str());
    STLReader->Update();

	vtkNew<vtkOpenGLPolyDataMapper> stlDrillMapper;
	stlDrillMapper->SetInputData(STLReader->GetOutput());
	_drillActor->SetMapper(stlDrillMapper);
}

void Drill::loadSTLDrillHeadModel()
{
    QString path = QDir::currentPath() + "/STLModelResources/drillHead.stl";

	vtkNew<vtkSTLReader> STLReader;
    STLReader->SetFileName(path.toStdString().c_str());
	STLReader->Update();

	vtkNew<vtkOpenGLPolyDataMapper> stlDrillMapper;
	stlDrillMapper->SetInputData(STLReader->GetOutput());
	_drillActor->SetMapper(stlDrillMapper);
}

void Drill::setWholeVisibility()
{
	setOpacity(1.0);
	loadSTLDrillModel();
}

void Drill::setTransparentVisibility()
{
	setOpacity(0.1);
}

void Drill::setHeadVisibility()
{
	setOpacity(1.0);
	loadSTLDrillHeadModel();
}

void Drill::changeVisibilityMode()
{
	if (getVisibility())
	{
		switch (_mode)
		{
		case DrillVisibilityMode::WholeDrillVisible:
			setTransparentVisibility();
			_mode = DrillVisibilityMode::TransparentDrillBody;
			break;
		case DrillVisibilityMode::TransparentDrillBody:
			setHeadVisibility();
			_mode = DrillVisibilityMode::OnlyHeadVisibly;
			break;
		case DrillVisibilityMode::OnlyHeadVisibly:
			setWholeVisibility();
			_mode = DrillVisibilityMode::WholeDrillVisible;
			break;
		}
	}
}

void Drill::setOpacity(double value)
{
	_drillActor->GetProperty()->SetOpacity(value);
}

void Drill::setRender(vtkRenderer* renderer_) const
{
	renderer_->AddActor(_tipActor);
	renderer_->AddActor(_drillActor);
}

void Drill::setPosition(double* newPosition_)
{
	_drillActor->SetPosition(newPosition_);
	_tipActor->SetPosition(newPosition_);
}

bool Drill::getVisibility()
{
	return _drillActor->GetVisibility();
}

void Drill::visibilityOn()
{
	_drillActor->VisibilityOn();
	_tipActor->VisibilityOn();
}

void Drill::visibilityOff()
{
	_drillActor->VisibilityOff();
	_tipActor->VisibilityOff();
}

void Drill::moveX(float positionStep_)
{
	double newPosition[3] = { positionStep_, 0.0, 0.0};
	_drillActor->AddPosition(newPosition);
	_tipActor->AddPosition(newPosition);
}

void Drill::moveY(float positionStep_)
{
	double newPosition[3] = {0.0, positionStep_, 0.0};
	_drillActor->AddPosition(newPosition);
	_tipActor->AddPosition(newPosition);
}

void Drill::moveZ(float positionStep_)
{
	double newPosition[3] = {0.0, 0.0, positionStep_ };
	_drillActor->AddPosition(newPosition);
	_tipActor->AddPosition(newPosition);
}

void Drill::rotateX(float angleStep_)
{
	_drillActor->RotateX(angleStep_);
	_tipActor->RotateX(angleStep_);
}

void Drill::rotateY(float angleStep_)
{
	_drillActor->RotateY(angleStep_);
	_tipActor->RotateY(angleStep_);
}

void Drill::rotateZ(float angleStep_)
{
	_drillActor->RotateZ(angleStep_);
	_tipActor->RotateZ(angleStep_);
}

void Drill::reverseDrill()
{
	_reverse *= -1;
	rotateY(180);
}

void Drill::moveDrillByKey(const char* key_, const float angleStep, const float positionStep)
{
	if (!std::strcmp(key_, "Right"))
	{
		moveX(positionStep);
	}
	else if (!std::strcmp(key_, "Left"))
	{
		moveX(-positionStep);
	}
	else if (!std::strcmp(key_, "Down"))
	{
		moveY(positionStep);
	}
	else if (!std::strcmp(key_, "Up"))
	{
		moveY(-positionStep);
	}
	else if (!std::strcmp(key_, "z"))
	{
		moveZ(positionStep);
	}
	else if (!std::strcmp(key_, "x"))
	{
		moveZ(-positionStep);
	}
	else if (!std::strcmp(key_, "c"))
	{
		rotateZ(angleStep);
	}
	else if (!std::strcmp(key_, "v"))
	{
		rotateZ(-angleStep);
	}
	else if (!std::strcmp(key_, "b"))
	{
		rotateY(angleStep);
	}
	else if (!std::strcmp(key_, "n"))
	{
		rotateY(-angleStep);
	}
	else if (!std::strcmp(key_, "g"))
	{
		rotateX(angleStep);
	}
	else if (!std::strcmp(key_, "h"))
	{
		rotateX(-angleStep);
	}
}

bool Drill::IsChangingPositionMode() const
{
	return _changePosition;
}

void Drill::setChangePositionMode(bool value)
{
	_changePosition = value;
}

bool Drill::checkPointBoundaries(const GraphicPrimitives::Point3D& ijk, const int* iExtents)
{
	bool isValidXposDownBound = ijk.x > 7;
	bool isValidYposDownBound = ijk.y > 7;
	bool isValidZposDownBound = ijk.z > 7;
	bool isValidXposUpperBound = ijk.x < iExtents[1] - 7;
	bool isValidYposUpperBound = ijk.y < iExtents[3] - 7;
	bool isValidZposUpperBound = ijk.z < iExtents[5] - 7;

	return isValidXposDownBound && isValidYposDownBound && isValidZposDownBound && isValidXposUpperBound && isValidYposUpperBound && isValidZposUpperBound;
}

void Drill::drillingVolume(vtkVolume* volume_, vtkImageData* imageCurrentData_, vtkImageData* imagePreData_)
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
	bool isInBound = checkPointBoundaries(ijkPoint, iExtents);

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

void Drill::drillMovedClickCallbackFunction(vtkObject* caller_, long unsigned int eventId_, void* clientData_,
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
		ptrDrill->setPosition(worldPosition);
	}
}
