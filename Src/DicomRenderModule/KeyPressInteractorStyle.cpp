#include "KeyPressInteractorStyle.hpp"

KeyPressInteractorStyle::KeyPressInteractorStyle()
{
	_polylineWidget = nullptr;
	_drill = nullptr;
	_imageCurrentData = nullptr;
	_imagePreData = nullptr;
	_volume = nullptr;
	_boxCallback = nullptr;
	_boxWidget = nullptr;
}

KeyPressInteractorStyle* KeyPressInteractorStyle::New()
{
	return new KeyPressInteractorStyle;
}

void KeyPressInteractorStyle::OnLeftButtonUp()
{
	if (_polylineWidget != nullptr)
	{
		if (_polylineWidget->_isWidgetOn && _polylineWidget->_state == State::Process)
		{
			const int* pos = Interactor->GetEventPosition();

			vtkNew<vtkCellPicker> picker;
			picker->SetTolerance(0.0005);

			// Pick from this location.
			picker->Pick(pos[0], pos[1], 0, Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());

			if (picker->GetCellId() != -1)
			{
				double picked[3];
				picker->GetPickPosition(picked);
				_polylineWidget->insertNewPoint(picked);
			}
		}
	}
	// Forward events
	vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
}

void KeyPressInteractorStyle::OnKeyDown()
{
	// Get the keypress
	vtkRenderWindowInteractor* rwi = Interactor;
	const char* key = rwi->GetKeySym();
	// int temp = rwi->GetKeyCode();
	const float angleStep = 2.f;
	const float positionStep = 0.05f;
	if (_drill->IsChangingPositionMode())
	{
		_drill->moveDrillByKey(key, angleStep, positionStep);
		_drill->drillingVolume(_volume, _imageCurrentData, _imagePreData);
		_boxCallback->Execute(_boxWidget, vtkBoxCallback::Drilling, nullptr);
		GetCurrentRenderer()->GetRenderWindow()->Render();
	}
	// Forward events
	vtkInteractorStyleTrackballCamera::OnKeyPress();
	GetCurrentRenderer()->GetRenderWindow()->WaitForCompletion();
}

void KeyPressInteractorStyle::OnMouseMove()
{
	if (_polylineWidget && _polylineWidget->_isWidgetOn)
	{
		_polylineWidget->updateText();
	}
	vtkInteractorStyleTrackballCamera::OnMouseMove();
	GetCurrentRenderer()->GetRenderWindow()->WaitForCompletion();
}

void KeyPressInteractorStyle::OnKeyRelease()
{
	const std::string input = Interactor->GetKeySym();
	if (_polylineWidget && _polylineWidget->_state == State::Process)
	{
		if (input == "Return")
		{
			_polylineWidget->_state = State::End;
		}
		else if (input == "z" || input == "Z")
		{
			_polylineWidget->deleteLastPoint();
		}
		GetCurrentRenderer()->GetRenderWindow()->Render();
	}
	vtkInteractorStyleTrackballCamera::OnKeyRelease();
}

void KeyPressInteractorStyle::setDrill(Drill* drill)
{
	_drill = drill;
}

void KeyPressInteractorStyle::setImageCurrentData(vtkImageData* imageCurrentData)
{
	_imageCurrentData = imageCurrentData;
}

void KeyPressInteractorStyle::setImagePreData(vtkImageData* imagePreData)
{
	_imagePreData = imagePreData;
}

void KeyPressInteractorStyle::setVolume(vtkVolume* volume)
{
	_volume = volume;
}

void KeyPressInteractorStyle::setBoxCallback(vtkBoxCallback* boxCallback)
{
	_boxCallback = boxCallback;
}

void KeyPressInteractorStyle::setBoxWidget(vtkBoxWidget2* boxWidget)
{
	_boxWidget = boxWidget;
}

void KeyPressInteractorStyle::setPolyline(PolylineRulerWidget* polylineWidget)
{
	_polylineWidget = polylineWidget;
}

