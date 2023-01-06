#ifndef LAYERSCONFIGURATION_H
#define LAYERSCONFIGURATION_H

#include "Src/DicomRenderModule/Callbacks/AbstractCallback.hpp"

#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>

namespace LayersConfiguration
{
	/// <summary>
	/// Function to set color function and opacity function for volume model
	/// </summary>
	/// <param name="volume_property"></param>
	/// <param name="wl"></param>
	/// <param name="ww"></param>
	void SetColorAndOpacityFunction(vtkVolumeProperty* volumeProperty, double wl, double ww);
}

#endif