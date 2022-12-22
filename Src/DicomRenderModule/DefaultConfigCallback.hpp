#ifndef DEFAULTCONFIGCALLBACK_H
#define DEFAULTCONFIGCALLBACK_H

#include "AbstractCallback.hpp"
#include "LayersConfiguration.hpp"

#include <vtkSliderRepresentation.h>
#include <vtkSliderWidget.h>

namespace LayersConfiguration
{
	/// <summary>
	/// Callback to set Default Config for sliders
	/// </summary>
	class vtkDefaultConfigCallback final : public AbstractCallback
	{
	public:
        vtkVolumeProperty* _volumeProperty;
        vtkSliderWidget* _sliderWidget_W;
        vtkSliderWidget* _sliderWidget_L;
        setupWLWW* _currentSetup;
        
    public:

		vtkDefaultConfigCallback();

		static vtkDefaultConfigCallback* New();
		void Execute(vtkObject* caller_, unsigned long, void*) override;
	};
}

#endif