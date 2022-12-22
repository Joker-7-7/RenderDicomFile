#include "Representation.hpp"



Representation::Representation(vtkRenderWindowInteractor* iren_, vtkRenderer* renderer_)
{
    vtkNew<vtkInteractorStyleTrackballCamera> l_trackball;
    iren_->SetInteractorStyle(l_trackball);

    vtkNew<vtkBoxRepresentation> l_box_rep;
    l_box_rep->SetInsideOut(true);

    _boxWidget->RotationEnabledOff();
    _boxWidget->TranslationEnabledOff();
    _boxWidget->SetRepresentation(l_box_rep);
    _boxWidget->SetInteractor(iren_);
    _boxWidget->GetRepresentation()->SetPlaceFactor(1.);

    _cameraAxisOrientManipulator->SetParentRenderer(renderer_);
    _cameraAxisOrientManipulator->SetInteractor(iren_);
    //_cameraAxisOrientManipulator->On();
}

void Representation::setReader(vtkImageReader2* ptrReader)
{
    _boxWidget->GetRepresentation()->PlaceWidget(ptrReader->GetOutput()->GetBounds());
}

