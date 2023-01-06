#ifndef DEFAULTCONFIGCALLBACK_H
#define DEFAULTCONFIGCALLBACK_H

#include "AbstractCallback.hpp"
#include "Src/DicomRenderModule/SceneInteractionParameters/LayersConfiguration.hpp"

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
        vtkVolumeProperty* volumeProperty;
        
    public:

		vtkDefaultConfigCallback();

		static vtkDefaultConfigCallback* New();
		void Execute(vtkObject* caller, unsigned long, void*) override;
	};
}

#endif