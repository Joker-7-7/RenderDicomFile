#include "MyVtkData.h"

#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkMinimalStandardRandomSequence.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkObjectFactory.h>
#include <vtkPolyDataMapper.h>
#include <vtkPropPicker.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>

MyVtkData::MyVtkData() {
    SetupRender();
    SetupGPU();
}

void MyVtkData::SetupRender() {
    vtkNew<vtkNamedColors> colors;

    _renderer->SetBackground(0.3, 0.3, 0.3);
    int numberOfSpheres = 10;
    vtkNew<vtkMinimalStandardRandomSequence> randomSequence;
    randomSequence->SetSeed(8775070);
    for (int i = 0; i < numberOfSpheres; ++i)
    {
        vtkNew<vtkSphereSource> source;
        double x, y, z, radius;
        // random position and radius
        x = randomSequence->GetRangeValue(-5.0, 5.0);
        randomSequence->Next();
        y = randomSequence->GetRangeValue(-5.0, 5.0);
        randomSequence->Next();
        z = randomSequence->GetRangeValue(-5.0, 5.0);
        randomSequence->Next();
        radius = randomSequence->GetRangeValue(0.5, 1.0);
        randomSequence->Next();
        source->SetRadius(radius);
        source->SetCenter(x, y, z);
        source->SetPhiResolution(11);
        source->SetThetaResolution(21);
        vtkNew<vtkPolyDataMapper> mapper;
        mapper->SetInputConnection(source->GetOutputPort());
        vtkNew<vtkActor> actor;
        actor->SetMapper(mapper);
        double r, g, b;
        r = randomSequence->GetRangeValue(0.4, 1.0);
        randomSequence->Next();
        g = randomSequence->GetRangeValue(0.4, 1.0);
        randomSequence->Next();
        b = randomSequence->GetRangeValue(0.4, 1.0);
        randomSequence->Next();
        actor->GetProperty()->SetDiffuseColor(r, g, b);
        actor->GetProperty()->SetDiffuse(0.8);
        actor->GetProperty()->SetSpecular(0.5);
        actor->GetProperty()->SetSpecularColor(
                colors->GetColor3d("White").GetData());
        actor->GetProperty()->SetSpecularPower(30.0);
        _renderer->AddActor(actor);
    }
}

void MyVtkData::SetupGPU() {

}
