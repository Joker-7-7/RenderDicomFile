#include "Representation.hpp"



Representation::Representation(vtkRenderWindowInteractor* interactor, vtkRenderer* renderer)
{
    vtkNew<vtkInteractorStyleTrackballCamera> l_trackball;
    interactor->SetInteractorStyle(l_trackball);

    vtkNew<vtkBoxRepresentation> l_box_rep;
    l_box_rep->SetInsideOut(true);

    _boxWidget->RotationEnabledOff();
    _boxWidget->TranslationEnabledOff();
    _boxWidget->SetRepresentation(l_box_rep);
    _boxWidget->SetInteractor(interactor);
    _boxWidget->GetRepresentation()->SetPlaceFactor(1.);

    _cameraAxisOrientManipulator->SetParentRenderer(renderer);
    _cameraAxisOrientManipulator->SetInteractor(interactor);
    _cameraAxisOrientManipulator->On();
}

void Representation::SetReader(vtkImageReader2* ptrReader)
{
    _boxWidget->GetRepresentation()->PlaceWidget(ptrReader->GetOutput()->GetBounds());
}

