
#include "SceneVtkItem.h"

#include <vtkRenderWindow.h>

vtkStandardNewMacro(SceneVtkData);

QQuickVtkItem::vtkUserData SceneVtkItem::initializeVTK(vtkRenderWindow *renderWindow)
{
    auto vtkScene = vtkNew<SceneVtkData>();
    _sceneData = vtkScene;
    _sceneData->InitSceneVTKData(renderWindow);

    return vtkScene;
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
    TryToExecute<RulerOptions::vtkButtonRulerCallback>();
}

void SceneVtkItem::OnClickButtonBoxRep() {
    TryToExecute<vtkButtonBoxCallback>();
}

void SceneVtkItem::OnClickButtonTeethConfig() {
    TryToExecute<LayersConfiguration::vtkTeethConfigCallback>();
}

void SceneVtkItem::OnClickButtonSolidConfig() {
    TryToExecute<LayersConfiguration::vtkSolidConfigCallback>();
}

void SceneVtkItem::OnClickButtonSkinConfig() {
    TryToExecute<LayersConfiguration::vtkSkinConfigCallback>();
}
void SceneVtkItem::OnClickButtonJitteringMode() {
    TryToExecute<vtkButtonJitteringModeCallback>();
}