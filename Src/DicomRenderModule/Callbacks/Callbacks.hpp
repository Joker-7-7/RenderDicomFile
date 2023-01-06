#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "TeethConfigCallback.hpp"
#include "SkinConfigCallback.hpp"
#include "SolidConfigCallback.hpp"
#include "DefaultConfigCallback.hpp"
#include "ButtonRulerCallback.hpp"
#include "BoxCallbacks.hpp"
#include "ButtonBoxCallback.hpp"
#include "VolumeParametersCallback.hpp"
#include "Src/DicomRenderModule/SceneInteractionParameters/Representation.hpp"
#include "Src/DicomRenderModule/SceneInteractionParameters/KeyPressInteractorStyle.hpp"

#include <vtkCallbackCommand.h>
#include <vtkRenderWindowInteractor.h>

struct CallbacksData {
    vtkVolume* volume = nullptr;
    Representation* representation = nullptr;
    vtkImageReader2* reader = nullptr;
    vtkImageReader2* preReader = nullptr;
    vtkVolumeProperty* volumeProperty = nullptr;
    vtkRenderWindowInteractor* interactor = nullptr;
    vtkRenderer* renderer = nullptr;
};


class Callbacks {
public:
    // All data for callbacks
    CallbacksData callbacksData;
    std::vector<AbstractCallback*> vectorCallbacks;
    vtkSmartPointer<vtkCallbackCommand> drillMovedClickCallback;
    vtkSmartPointer<KeyPressInteractorStyle> interactorStyleCallback;

public:
    Callbacks() = default;

    void SetupCallbacks();

    void DisconnectCallbacks();

    template<typename TCallback>
    AbstractCallback* GetCallback() {
        AbstractCallback* res = nullptr;
        for (auto callback: vectorCallbacks) {
            if (callback != nullptr) {
                if (typeid(TCallback).name() == typeid(*callback).name()) {
                    res = callback;
                    break;
                }
            }
        }
        return res;
    }
};

#endif