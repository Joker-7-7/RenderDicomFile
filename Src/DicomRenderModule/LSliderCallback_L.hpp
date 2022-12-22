#ifndef LSLIDERCALLBACKL_H
#define LSLIDERCALLBACKL_H

#include "AbstractCallback.hpp"
#include "LayersConfiguration.hpp"

#include <vtkSliderRepresentation.h>
#include <vtkSliderWidget.h>

namespace LayersConfiguration
{
	/// <summary>
	/// Callback for L slider
	/// </summary>
	class vtkLSliderCallback_L final : public AbstractCallback
	{
	public:
		vtkVolumeProperty* _volumeProperty;
		setupWLWW* _currentSetup;

    public:
        vtkLSliderCallback_L();
        
		static vtkLSliderCallback_L* New();
		void Execute(vtkObject* caller_, unsigned long, void*) override;
	};
}

#endif