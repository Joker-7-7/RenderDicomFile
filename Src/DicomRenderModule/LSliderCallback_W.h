#ifndef LSLIDERCALLBACKW_H
#define LSLIDERCALLBACKW_H

#include "AbstractCallback.h"
#include "LayersConfiguration.h"

#include <vtkSliderRepresentation.h>
#include <vtkSliderWidget.h>

namespace LayersConfiguration
{
	/// <summary>
	/// Callback for W slider
	/// </summary>
	class vtkLSliderCallback_W final : public AbstractCallback
	{
	public:
		vtkLSliderCallback_W();

		vtkVolumeProperty* _volumeProperty;

		setupWLWW* _currentSetup;

		static vtkLSliderCallback_W* New();

		void Execute(vtkObject* caller_, unsigned long, void*) override;
	};
}

#endif