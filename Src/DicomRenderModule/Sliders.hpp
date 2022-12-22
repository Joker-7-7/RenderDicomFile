#ifndef SKIDERS_H
#define SKIDERS_H

#include "LayersConfiguration.hpp"

#include <vtkSliderWidget.h>
#include <vtkNew.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVolumeProperty.h>
#include <vtkSliderRepresentation2D.h>

/// <summary>
/// A class that includes all application sliders
/// </summary>
class Sliders
{
public:
	// slider for L parameter
	vtkNew<vtkSliderWidget> _sliderWidget_L;
	// slider for W parameter
	vtkNew<vtkSliderWidget> _sliderWidget_W;
	// setup ww and wl linking slider L and slider W
	std::unique_ptr<LayersConfiguration::setupWLWW> _setupWLWWConfig =
		std::make_unique<LayersConfiguration::setupWLWW>();

	Sliders(vtkRenderWindowInteractor* iren_, vtkVolumeProperty* volumeProperty_);
};
#endif
