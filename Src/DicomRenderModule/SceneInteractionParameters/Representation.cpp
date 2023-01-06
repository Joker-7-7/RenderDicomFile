#include "Representation.hpp"

Representation::Representation(vtkRenderWindowInteractor* interactor, vtkRenderer* renderer) {
    vtkNew<vtkInteractorStyleTrackballCamera> trackballStyle;
    interactor->SetInteractorStyle(trackballStyle);

    vtkNew<vtkBoxRepresentation> boxRepresentation;
    boxRepresentation->SetInsideOut(true);

    boxWidget->RotationEnabledOff();
    boxWidget->TranslationEnabledOff();
    boxWidget->SetRepresentation(boxRepresentation);
    boxWidget->SetInteractor(interactor);
    boxWidget->GetRepresentation()->SetPlaceFactor(1.);

    cameraAxisOrientManipulator->SetParentRenderer(renderer);
    cameraAxisOrientManipulator->SetInteractor(interactor);
    cameraAxisOrientManipulator->On();
}

void Representation::SetReader(vtkImageReader2* ptrReader) {
    boxWidget->GetRepresentation()->PlaceWidget(ptrReader->GetOutput()->GetBounds());
}

