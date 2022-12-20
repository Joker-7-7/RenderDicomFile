
#include "SceneVtkItem.h"

#include <vtkRenderWindow.h>

vtkStandardNewMacro(SceneVtkData);


QQuickVtkItem::vtkUserData SceneVtkItem::initializeVTK(vtkRenderWindow *renderWindow)
{
    auto vtk = vtkNew<SceneVtkData>();
    _sceneData = vtk;

    // A renderer and render windo

    renderWindow->SetSize(renderWindow->GetScreenSize());
    renderWindow->AddRenderer(_sceneData->_renderer);
    renderWindow->SetWindowName("MainWindow");
    _sceneData->_renderWindow = renderWindow;

    return vtk;
}

void SceneVtkItem::OnClickButtonOpenDirectory(QString directory) {
    std::function<void(vtkRenderWindow*, vtkUserData)> foo([this, directory] (vtkRenderWindow* , const vtkUserData& ){
        if(!_sceneData->OpenDirectory(directory))
        {
            emit showMessageBox();
        }
    });
    QQuickVtkItem::dispatch_async(foo);
}

void SceneVtkItem::OnClickButtonOpenFile(QString singleFile) {

    std::function<void(vtkRenderWindow*, vtkUserData)> foo([this, singleFile] (vtkRenderWindow* , const vtkUserData& ){
        if(!_sceneData->OpenSingleFile(singleFile))
        {
            emit showMessageBox();
        }
    });
    QQuickVtkItem::dispatch_async(foo);
}

void SceneVtkItem::OnClickButtonResetCamera() {
    std::function<void(vtkRenderWindow*, vtkUserData)> foo([this] (vtkRenderWindow* , const vtkUserData& ){
        _sceneData->ZoomToExtent();
    });
    QQuickVtkItem::dispatch_async(foo);
}
