#include "SkinConfigCallback.hpp"


namespace LayersConfiguration
{
	vtkSkinConfigCallback::vtkSkinConfigCallback()
	{
		_volumeProperty = nullptr;
		_sliderWidget_W = nullptr;
		_sliderWidget_L = nullptr;
		_currentSetup = nullptr;
	}

	vtkSkinConfigCallback* vtkSkinConfigCallback::New()
	{
		return new vtkSkinConfigCallback;
	}

	void vtkSkinConfigCallback::Execute(vtkObject* caller_, unsigned long, void*)
	{
		_currentSetup->wl = 0.0;
		_currentSetup->ww = 1040.0;

		dynamic_cast<vtkSliderRepresentation*>(_sliderWidget_L->GetRepresentation())->SetValue(_currentSetup->wl);
		dynamic_cast<vtkSliderRepresentation*>(_sliderWidget_W->GetRepresentation())->SetValue(_currentSetup->ww);

		setColorAndOpacityFunction(_volumeProperty, _currentSetup->wl, _currentSetup->ww);
	}
}
