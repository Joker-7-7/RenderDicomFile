#ifndef SKINCONFIGCALLBACK_H
#define SKINCONFIGCALLBACK_H

#include "AbstractCallback.hpp"
#include "Src/DicomRenderModule/SceneInteractionParameters/LayersConfiguration.hpp"

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
        vtkVolumeProperty* volumeProperty;

    public:
		vtkSkinConfigCallback();

		static vtkSkinConfigCallback* New();
		void Execute(vtkObject* caller, unsigned long, void*) override;
	};
}

#endif