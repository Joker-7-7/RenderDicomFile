#include "DefaultConfigCallback.hpp"


namespace LayersConfiguration
{
	vtkDefaultConfigCallback::vtkDefaultConfigCallback()
	{
		_volumeProperty = nullptr;
		_sliderWidget_W = nullptr;
		_sliderWidget_L = nullptr;
		_currentSetup = nullptr;
	}

	vtkDefaultConfigCallback* vtkDefaultConfigCallback::New()
	{
		return new vtkDefaultConfigCallback;
	}

	void vtkDefaultConfigCallback::Execute(vtkObject* caller_, unsigned long, void*)
	{
		_currentSetup->wl = 900.0;
		_currentSetup->ww = 300.0;

		dynamic_cast<vtkSliderRepresentation*>(_sliderWidget_L->GetRepresentation())->SetValue(_currentSetup->wl);
		dynamic_cast<vtkSliderRepresentation*>(_sliderWidget_W->GetRepresentation())->SetValue(_currentSetup->ww);

        SetColorAndOpacityFunction(_volumeProperty, _currentSetup->wl, _currentSetup->ww);
	}
}
