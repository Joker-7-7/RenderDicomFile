#ifndef TEETHCONFIGCALLBACK_H
#define TEETHCONFIGCALLBACK_H

#include "AbstractCallback.hpp"
#include "Src/DicomRenderModule/SceneInteractionParameters/LayersConfiguration.hpp"

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
        vtkVolumeProperty* volumeProperty;

	public:
		vtkTeethConfigCallback();

		static vtkTeethConfigCallback* New();
		void Execute(vtkObject* caller, unsigned long, void*) override;
	};
}

#endif