#ifndef LAYERSCONFIGURATION_H
#define LAYERSCONFIGURATION_H

#include "AbstractCallback.hpp"

#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>

namespace LayersConfiguration
{
	/// <summary>
	/// Parameters WW and WL
	/// </summary>
	struct setupWLWW
	{
		double wl = 900.0;
		double ww = 300.0;
	};

	/// <summary>
	/// Function to set color function and opacity function for volume model
	/// </summary>
	/// <param name="volume_property"></param>
	/// <param name="wl"></param>
	/// <param name="ww"></param>
	void SetColorAndOpacityFunction(vtkVolumeProperty* volumeProperty_, double wl_, double ww_);
}

#endif