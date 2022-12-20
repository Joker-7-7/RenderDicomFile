#include "Sliders.h"


Sliders::Sliders(vtkRenderWindowInteractor* iren_, vtkVolumeProperty* volumeProperty_)
{
#pragma region create slider L
	vtkNew<vtkSliderRepresentation2D> sliderRep_L;
	sliderRep_L->SetMinimumValue(0.0);
	sliderRep_L->SetMaximumValue(4000.0);
	sliderRep_L->SetValue(_setupWLWWConfig->wl);
	sliderRep_L->SetTitleText("Level L");
    sliderRep_L->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedViewport();
	sliderRep_L->GetPoint1Coordinate()->SetValue(0.7, 0.2);
    sliderRep_L->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedViewport();
	sliderRep_L->GetPoint2Coordinate()->SetValue(.95, 0.2);
	sliderRep_L->SetLabelFormat("%.0f");
	sliderRep_L->SetSliderLength(0.002);
	sliderRep_L->SetSliderWidth(0.02);
	sliderRep_L->SetEndCapLength(0.02);
	sliderRep_L->SetEndCapWidth(0.02);

	_sliderWidget_L->SetInteractor(iren_);
	_sliderWidget_L->SetRepresentation(sliderRep_L);
	_sliderWidget_L->SetAnimationModeToAnimate();
	//_sliderWidget_L->EnabledOn();
#pragma endregion

#pragma region create slider W
	vtkNew<vtkSliderRepresentation2D> sliderRep_W;
	sliderRep_W->SetMinimumValue(10.0);
	sliderRep_W->SetMaximumValue(2000.0);
	sliderRep_W->SetValue(_setupWLWWConfig->ww);
	sliderRep_W->SetTitleText("Level W");
    sliderRep_W->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedViewport();
	sliderRep_W->GetPoint1Coordinate()->SetValue(0.7, 0.08);
    sliderRep_W->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedViewport();
	sliderRep_W->GetPoint2Coordinate()->SetValue(0.95, 0.08);
	sliderRep_W->SetLabelFormat("%.0f");
	sliderRep_W->SetSliderLength(0.002);
	sliderRep_W->SetSliderWidth(0.02);
	sliderRep_W->SetEndCapLength(0.02);
	sliderRep_W->SetEndCapWidth(0.02);

	_sliderWidget_W->SetInteractor(iren_);
	_sliderWidget_W->SetRepresentation(sliderRep_W);
	_sliderWidget_W->SetAnimationModeToAnimate();
	//_sliderWidget_W->EnabledOn();
#pragma endregion
}
