#include "LSliderCallback_L.h"



namespace LayersConfiguration
{
	vtkLSliderCallback_L::vtkLSliderCallback_L()
	{
		_volumeProperty = nullptr;
		_currentSetup = nullptr;
	}

	vtkLSliderCallback_L* vtkLSliderCallback_L::New()
	{
		return new vtkLSliderCallback_L;
	}

	void vtkLSliderCallback_L::Execute(vtkObject* caller_, unsigned long, void*)
	{
		auto sliderWidget = vtkSliderWidget::SafeDownCast(caller_);
		const double newWL = dynamic_cast<vtkSliderRepresentation*>(sliderWidget->GetRepresentation())->GetValue();
		_currentSetup->wl = newWL;
		setColorAndOpacityFunction(_volumeProperty, _currentSetup->wl, _currentSetup->ww);
	}
}
