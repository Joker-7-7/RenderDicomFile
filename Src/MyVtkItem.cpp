
#include "MyVtkItem.h"

#include <vtkRenderWindow.h>

vtkStandardNewMacro(MyVtkData);


QQuickVtkItem::vtkUserData MyVtkItem::initializeVTK(vtkRenderWindow *renderWindow)
{
    auto vtk = vtkNew<MyVtkData>();
    _sceneData = vtk;

    // A renderer and render window
    renderWindow->SetSize(renderWindow->GetScreenSize());
    renderWindow->AddRenderer(_sceneData->_renderer);
    renderWindow->SetWindowName("MainWindow");
    _sceneData->_renderWindow = renderWindow;

    return vtk;
}

void MyVtkItem::OnClickButtonOpenDirectory(QString directory) {
    qDebug() << "Zoom camera";
    std::function<void(vtkRenderWindow*, vtkUserData)> foo([this, directory] (vtkRenderWindow* , const vtkUserData& ){
        if(!_sceneData->OpenDirectory(directory))
        {
            emit showMessageBox();
        }
    });
    QQuickVtkItem::dispatch_async(foo);
}

void MyVtkItem::OnClickButtonOpenFile(QString singleFile) {

}
