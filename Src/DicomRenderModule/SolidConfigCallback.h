#ifndef SOLIDCONFIGCALLBACK_H
#define SOLIDCONFIGCALLBACK_H

#include "AbstractCallback.h"
#include "LayersConfiguration.h"

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
		vtkSolidConfigCallback();

		vtkVolumeProperty* _volumeProperty;

		vtkSliderWidget* _sliderWidget_W;

		vtkSliderWidget* _sliderWidget_L;

		setupWLWW* _currentSetup;

		static vtkSolidConfigCallback* New();

		void Execute(vtkObject* caller_, unsigned long, void*) override;
	};
}

#endif