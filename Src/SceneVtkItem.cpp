
#include "SceneVtkItem.h"

#include <vtkRenderWindow.h>

vtkStandardNewMacro(SceneVtkData);


QQuickVtkItem::vtkUserData SceneVtkItem::initializeVTK(vtkRenderWindow *renderWindow)
{
    auto vtk = vtkNew<SceneVtkData>();
    _sceneData = vtk;
    _sceneData->InitSceneVTKData(renderWindow);
    // A renderer and render window

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

void SceneVtkItem::OnClickButtonRuler() {
    std::function<void(vtkRenderWindow*, vtkUserData)> foo([this] (vtkRenderWindow* w, const vtkUserData& ){
        _sceneData->Execute<RulerOptions::vtkButtonRulerCallback>();
    });
    QQuickVtkItem::dispatch_async(foo);
}
