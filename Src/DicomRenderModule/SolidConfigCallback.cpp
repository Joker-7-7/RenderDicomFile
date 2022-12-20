#include "SolidConfigCallback.h"


namespace LayersConfiguration
{
	vtkSolidConfigCallback::vtkSolidConfigCallback()
	{
		_volumeProperty = nullptr;
		_sliderWidget_W = nullptr;
		_sliderWidget_L = nullptr;
		_currentSetup = nullptr;
	}

	vtkSolidConfigCallback* vtkSolidConfigCallback::New()
	{
		return new vtkSolidConfigCallback;
	}

	void vtkSolidConfigCallback::Execute(vtkObject* caller_, unsigned long, void*)
	{
		_currentSetup->wl = 1560.0;
		_currentSetup->ww = 250.0;

		dynamic_cast<vtkSliderRepresentation*>(_sliderWidget_L->GetRepresentation())->SetValue(_currentSetup->wl);
		dynamic_cast<vtkSliderRepresentation*>(_sliderWidget_W->GetRepresentation())->SetValue(_currentSetup->ww);

		setColorAndOpacityFunction(_volumeProperty, _currentSetup->wl, _currentSetup->ww);
	}
}
