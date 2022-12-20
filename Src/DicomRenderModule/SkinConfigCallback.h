#pragma once

#include "AbstractCallback.h"
#include "LayersConfiguration.h"

#include <vtkSliderRepresentation.h>
#include <vtkSliderWidget.h>

namespace LayersConfiguration
{
	/// <summary>
	/// Callback to set Skin Config for sliders
	/// </summary>
	class vtkSkinConfigCallback final : public AbstractCallback
	{
	public:
		vtkSkinConfigCallback();

		vtkVolumeProperty* _volumeProperty;

		vtkSliderWidget* _sliderWidget_W;

		vtkSliderWidget* _sliderWidget_L;

		setupWLWW* _currentSetup;

		static vtkSkinConfigCallback* New();

		void Execute(vtkObject* caller_, unsigned long, void*) override;
	};
}
