#ifndef MYVTKDATA_H
#define MYVTKDATA_H

#include <vtkObject.h>
#include <vtkObjectFactory.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

struct MyVtkData : vtkObject
{
    static MyVtkData* New();

    vtkTypeMacro(MyVtkData, vtkObject);
    MyVtkData();

    void SetupRender();
    void SetupGPU();
public:
    vtkNew<vtkRenderer> _renderer;
    vtkSmartPointer<vtkRenderWindow> _renderWindow;
    // Place all your persistant VTK objects here
};

#endif // MYVTKDATA_H
