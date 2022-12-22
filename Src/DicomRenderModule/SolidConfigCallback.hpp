#ifndef SOLIDCONFIGCALLBACK_H
#define SOLIDCONFIGCALLBACK_H

#include "AbstractCallback.hpp"
#include "LayersConfiguration.hpp"

#include <vtkSliderRepresentation.h>
#include <vtkSliderWidget.h>

namespace LayersConfiguration
{
	/// <summary>
	/// Callback to set Solid Config for sliders
	/// </summary>
	class vtkSolidConfigCallback final : public AbstractCallback
	{
	public:
        vtkVolumeProperty* _volumeProperty;
        vtkSliderWidget* _sliderWidget_W;
        vtkSliderWidget* _sliderWidget_L;
        setupWLWW* _currentSetup;

    public:
		vtkSolidConfigCallback();

		static vtkSolidConfigCallback* New();
		void Execute(vtkObject* caller_, unsigned long, void*) override;
	};
}

#endif