#pragma once

#include "AbstractCallback.h"
#include "LayersConfiguration.h"

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
		vtkDefaultConfigCallback();

		vtkVolumeProperty* _volumeProperty;

		vtkSliderWidget* _sliderWidget_W;

		vtkSliderWidget* _sliderWidget_L;

		setupWLWW* _currentSetup;

		static vtkDefaultConfigCallback* New();

		void Execute(vtkObject* caller_, unsigned long, void*) override;
	};
}
