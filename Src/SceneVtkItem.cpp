#include "SceneVtkItem.hpp"

#include <vtkRenderWindow.h>

vtkStandardNewMacro(SceneVtkData);

QQuickVtkItem::vtkUserData SceneVtkItem::initializeVTK(vtkRenderWindow* renderWindow) {
    auto vtkScene = vtkNew<SceneVtkData>();
    _sceneData = vtkScene;
    _sceneData->InitSceneVTKData(renderWindow);
    return vtkScene;
}

void SceneVtkItem::OnOpenDirectoryClicked(QString directory) {
    std::function<void(vtkRenderWindow *, vtkUserData)> openDirectory([this, directory](vtkRenderWindow*, const vtkUserData&) {
        if (!_sceneData->OpenDirectory(directory)) {
            emit showMessageBox();
        }
    });
    QQuickVtkItem::dispatch_async(openDirectory);
}

void SceneVtkItem::OnOpenFileClicked(QString singleFile) {
    std::function<void(vtkRenderWindow*, vtkUserData)> openFile([this, singleFile](vtkRenderWindow*, const vtkUserData&) {
        if (!_sceneData->OpenSingleFile(singleFile)) {
            emit showMessageBox();
        }
    });
    QQuickVtkItem::dispatch_async(openFile);
}

void SceneVtkItem::OnResetCameraClicked() {
    std::function<void(vtkRenderWindow*, vtkUserData)> zoomExtent([this](vtkRenderWindow*, const vtkUserData&) {
        _sceneData->ZoomToExtent();
    });
    QQuickVtkItem::dispatch_async(zoomExtent);
}

void SceneVtkItem::OnSliderChanged(int value, QString sliderType) {
    std::function<void(vtkRenderWindow*, vtkUserData)> sliderChanged([this, value, sliderType](vtkRenderWindow*, const vtkUserData&) {
        if (sliderType == "W") {
            _sceneData->viewSettings.wLevel = value;
        }
        else if (sliderType == "L") {
            _sceneData->viewSettings.lLevel = value;
        }
        LayersConfiguration::SetColorAndOpacityFunction(_sceneData->volumeProperty, _sceneData->viewSettings.lLevel, _sceneData->viewSettings.wLevel);
    });
    QQuickVtkItem::dispatch_async(sliderChanged);
}

void SceneVtkItem::OnRulerClicked() {
    TryToExecute<RulerOptions::vtkButtonRulerCallback>();
}

void SceneVtkItem::OnBoxRepresentationClicked() {
    TryToExecute<vtkButtonBoxCallback>();
}

void SceneVtkItem::OnTeethConfigClicked() {
    TryToExecute<LayersConfiguration::vtkTeethConfigCallback>();
}

void SceneVtkItem::OnSolidConfigClicked() {
    TryToExecute<LayersConfiguration::vtkSolidConfigCallback>();
}

void SceneVtkItem::OnSkinConfigClicked() {
    TryToExecute<LayersConfiguration::vtkSkinConfigCallback>();
}

void SceneVtkItem::OnJitteringModeClicked() {
    TryToExecute<vtkButtonJitteringModeCallback>();
}


