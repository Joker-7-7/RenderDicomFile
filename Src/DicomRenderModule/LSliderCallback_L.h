#ifndef LSLIDERCALLBACKL_H
#define LSLIDERCALLBACKL_H

#include "AbstractCallback.h"
#include "LayersConfiguration.h"

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
		vtkLSliderCallback_L();

		vtkVolumeProperty* _volumeProperty;

		setupWLWW* _currentSetup;

		static vtkLSliderCallback_L* New();

		void Execute(vtkObject* caller_, unsigned long, void*) override;
	};
}

#endif