#include "LSliderCallback_W.hpp"

namespace LayersConfiguration
{
	vtkLSliderCallback_W::vtkLSliderCallback_W()
	{
		_volumeProperty = nullptr;
		_currentSetup = nullptr;
	}

	vtkLSliderCallback_W* vtkLSliderCallback_W::New()
	{
		return new vtkLSliderCallback_W;
	}

	void vtkLSliderCallback_W::Execute(vtkObject* caller_, unsigned long, void*)
	{
		vtkSliderWidget* sliderWidget = vtkSliderWidget::SafeDownCast(caller_);
		const double newWW = dynamic_cast<vtkSliderRepresentation*>(sliderWidget->GetRepresentation())->GetValue();
		_currentSetup->ww = newWW;
        SetColorAndOpacityFunction(this->_volumeProperty, _currentSetup->wl, _currentSetup->ww);
	}
}
