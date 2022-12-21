#ifndef MYVTKITEM_H
#define MYVTKITEM_H

#include "SceneVtkData.h"

#include "QQuickVtkItem.h"

class SceneVtkItem : public QQuickVtkItem
{
public:
Q_OBJECT
public:

    vtkUserData initializeVTK(vtkRenderWindow *renderWindow) override;

    /// <summary>
    /// Open file button click
    /// </summary>
    Q_INVOKABLE void OnClickButtonOpenFile(QString singleFile);
    /// <summary>
    /// Open file button click
    /// </summary>
    Q_INVOKABLE void OnClickButtonOpenDirectory(QString directory);
    /// <summary>`
    /// Open file button click
    /// </summary>
    Q_INVOKABLE void OnClickButtonResetCamera();
    /// <summary>
    /// Ruler button click
    /// </summary>
    Q_INVOKABLE void OnClickButtonRuler();
    /// <summary>
    /// Clipping Box button click
    /// </summary>
    Q_INVOKABLE void OnClickButtonBoxRep();
        /// <summary>
    /// Teeth Config button click
    /// </summary>
    Q_INVOKABLE void OnClickButtonTeethConfig();
    /// <summary>
    /// Solid Config button click
    /// </summary>
    Q_INVOKABLE void OnClickButtonSolidConfig();
    /// <summary>
    /// Skin Config button click
    /// </summary>
    Q_INVOKABLE void OnClickButtonSkinConfig();
    /// <summary>
    /// Jittering mode button click
    /// </summary>
    Q_INVOKABLE void OnClickButtonJitteringMode();
signals:
    void showMessageBox();
public:
    SceneVtkData* _sceneData;

};

#endif // MYVTKITEM_H
