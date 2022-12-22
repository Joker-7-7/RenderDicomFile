#include "LayersConfiguration.hpp"


namespace LayersConfiguration
{
	void SetColorAndOpacityFunction(vtkVolumeProperty* volumeProperty_, double wl_, double ww_)
	{
		vtkColorTransferFunction* colFun = volumeProperty_->GetRGBTransferFunction();
		colFun->RemoveAllPoints();
		vtkPiecewiseFunction* opacityFun = volumeProperty_->GetScalarOpacity();
		opacityFun->RemoveAllPoints();

		colFun->SetColorSpaceToRGB();
		colFun->AddRGBPoint(wl_ - ww_ / 2.0, 0.0, 0.0, 0.0);
		colFun->AddRGBPoint(wl_ - ww_ / 2.0 + 94.0 * (ww_ / 255.0), 1.0, 21.0 / 255.0, 27.0 / 255.0);
		colFun->AddRGBPoint(wl_ - ww_ / 2.0 + 147.0 * (ww_ / 255.0), 1.0, 176.0 / 255.0, 9.0 / 255.0);
		colFun->AddRGBPoint(wl_ - ww_ / 2.0 + 201.0 * (ww_ / 255.0), 1.0, 241.0 / 255.0, 39.0 / 255.0);
		colFun->AddRGBPoint(wl_ - ww_ / 2.0 + 255.0 * (ww_ / 255.0), 1.0, 1.0, 1.0);

		opacityFun->AddPoint(wl_ - ww_ / 2.0, 0.0);
		opacityFun->AddPoint(wl_ + ww_ / 2.0, 1.0);
	}
}
