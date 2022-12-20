#ifndef MYVTKITEM_H
#define MYVTKITEM_H

#include "MyVtkData.h"

#include "QQuickVtkItem.h"

class MyVtkItem : public QQuickVtkItem
{
Q_OBJECT
public:

    vtkUserData initializeVTK(vtkRenderWindow *renderWindow) override;

    Q_INVOKABLE void OnClickButtonOpenDirectory(QString directory);

public:
    MyVtkData* _sceneData;

};

#endif // MYVTKITEM_H
