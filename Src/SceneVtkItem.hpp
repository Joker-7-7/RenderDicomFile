#ifndef MYVTKITEM_H
#define MYVTKITEM_H

#include "SceneVtkData.hpp"
#include "Src/ThirdParty/QQuickVtkItem.h"

class SceneVtkItem : public QQuickVtkItem
{
public:
    Q_OBJECT
public:

    vtkUserData initializeVTK(vtkRenderWindow* renderWindow) override;
    /// <summary>
    /// Open file button click
    /// </summary>
    Q_INVOKABLE void OnOpenFileClicked(QString singleFile);
    /// <summary>
    /// Open file button click
    /// </summary>
    Q_INVOKABLE void OnOpenDirectoryClicked(QString directory);
    /// <summary>`
    /// Reset camera button click
    /// </summary>
    Q_INVOKABLE void OnResetCameraClicked();
    /// <summary>
    /// Ruler button click
    /// </summary>
    Q_INVOKABLE void OnRulerClicked();
    /// <summary>
    /// Clipping Box button click
    /// </summary>
    Q_INVOKABLE void OnBoxRepresentationClicked();
    /// <summary>
    /// Teeth Config button click
    /// </summary>
    Q_INVOKABLE void OnTeethConfigClicked();
    /// <summary>
    /// Solid Config button click
    /// </summary>
    Q_INVOKABLE void OnSolidConfigClicked();
    /// <summary>
    /// Skin Config button click
    /// </summary>
    Q_INVOKABLE void OnSkinConfigClicked();
    /// <summary>
    /// Jittering mode button click
    /// </summary>
    Q_INVOKABLE void OnJitteringModeClicked();
    /// <summary>
    /// Update volum parameters when moving the slider
    /// </summary>
    /// <param name="value">- Value to update</param>
    /// <param name="sliderType">- Slider type</param>
    /// <returns></returns>
    Q_INVOKABLE void OnSliderChanged(int value, QString sliderType);

signals:
    void showMessageBox();

private:
    SceneVtkData* _sceneData;

private:
    template<class TCallback>
    void TryToExecute() {
        std::function<void(vtkRenderWindow*, vtkUserData)> callback([this] (vtkRenderWindow* w, const vtkUserData& ){
            _sceneData->Execute<TCallback>();
        });
        QQuickVtkItem::dispatch_async(callback);
    }
};

#endif
