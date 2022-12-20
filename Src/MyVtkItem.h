#ifndef MYVTKITEM_H
#define MYVTKITEM_H

#include "MyVtkData.h"

#include "QQuickVtkItem.h"

class MyVtkItem : public QQuickVtkItem
{
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
    /// <summary>
    /// Open file button click
    /// </summary>
    Q_INVOKABLE void OnClickButtonResetCamera();

signals:
    void showMessageBox();
public:
    MyVtkData* _sceneData;

};

#endif // MYVTKITEM_H
