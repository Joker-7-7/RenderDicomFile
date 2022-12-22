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
                _polylineWidget->InsertNewPoint(picked);
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
        _drill->MoveDrillByKey(key, angleStep, positionStep);
        _drill->DrillingVolume(_imageCurrentData, _imagePreData);
		_boxCallback->Execute(_boxWidget, static_cast<long>(vtkBoxCallback::BoxMode::Drilling), nullptr);
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
        _polylineWidget->UpdateText();
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
            _polylineWidget->DeleteLastPoint();
		}
		GetCurrentRenderer()->GetRenderWindow()->Render();
	}
	vtkInteractorStyleTrackballCamera::OnKeyRelease();
}

void KeyPressInteractorStyle::SetDrill(Drill* drill) noexcept
{
	_drill = drill;
}

void KeyPressInteractorStyle::SetImageCurrentData(vtkImageData* imageCurrentData) noexcept
{
	_imageCurrentData = imageCurrentData;
}

void KeyPressInteractorStyle::SetImagePreData(vtkImageData* imagePreData) noexcept
{
	_imagePreData = imagePreData;
}

void KeyPressInteractorStyle::SetVolume(vtkVolume* volume) noexcept
{
	_volume = volume;
}

void KeyPressInteractorStyle::SetBoxCallback(vtkBoxCallback* boxCallback) noexcept
{
	_boxCallback = boxCallback;
}

void KeyPressInteractorStyle::SetBoxWidget(vtkBoxWidget2* boxWidget) noexcept
{
	_boxWidget = boxWidget;
}

void KeyPressInteractorStyle::SetPolyline(PolylineRulerWidget* polylineWidget) noexcept
{
	_polylineWidget = polylineWidget;
}

