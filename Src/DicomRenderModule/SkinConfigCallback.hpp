#ifndef SKINCONFIGCALLBACK_H
#define SKINCONFIGCALLBACK_H

#include "AbstractCallback.hpp"
#include "LayersConfiguration.hpp"

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
        vtkVolumeProperty* _volumeProperty;
        vtkSliderWidget* _sliderWidget_W;
        vtkSliderWidget* _sliderWidget_L;
        setupWLWW* _currentSetup;

    public:
		vtkSkinConfigCallback();

		static vtkSkinConfigCallback* New();
		void Execute(vtkObject* caller_, unsigned long, void*) override;
	};
}

#endif