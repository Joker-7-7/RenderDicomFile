#ifndef SOLIDCONFIGCALLBACK_H
#define SOLIDCONFIGCALLBACK_H

#include "AbstractCallback.hpp"
#include "Src/DicomRenderModule/SceneInteractionParameters/LayersConfiguration.hpp"

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
        vtkVolumeProperty* volumeProperty;

    public:
		vtkSolidConfigCallback();

		static vtkSolidConfigCallback* New();
		void Execute(vtkObject* caller, unsigned long, void*) override;
	};
}

#endif