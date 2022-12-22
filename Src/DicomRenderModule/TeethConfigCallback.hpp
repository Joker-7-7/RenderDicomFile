#ifndef TEETHCONFIGCALLBACK_H
#define TEETHCONFIGCALLBACK_H

#include "AbstractCallback.hpp"
#include "LayersConfiguration.hpp"

#include <vtkSliderRepresentation.h>
#include <vtkSliderWidget.h>

namespace LayersConfiguration
{
	/// <summary>
	/// Callback to set Teeth Config for sliders
	/// </summary>
	class vtkTeethConfigCallback final : public AbstractCallback
	{
	public:
		vtkTeethConfigCallback();

		vtkVolumeProperty* _volumeProperty;

		vtkSliderWidget* _sliderWidget_W;

		vtkSliderWidget* _sliderWidget_L;

		setupWLWW* _currentSetup;

		static vtkTeethConfigCallback* New();

		void Execute(vtkObject* caller_, unsigned long, void*) override;
	};
}

#endif