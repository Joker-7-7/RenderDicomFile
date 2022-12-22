#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "ButtonReverseDrillCallback.h"
#include "ButtonPolylineRulerCallback.h"
#include "TeethConfigCallback.h"
#include "SkinConfigCallback.h"
#include "SolidConfigCallback.h"
#include "DefaultConfigCallback.h"
#include "LSliderCallback_W.h"
#include "LSliderCallback_L.h"
#include "ButtonDrillCallback.h"
#include "KeyPressInteractorStyle.h"
#include "ButtonRulerCallback.h"
#include "BoxCallbacks.h"
#include "ButtonBoxCallback.h"
#include "VolumeParametersCallback.h"
#include "ButtonVisibilityDrillCallback.h"

#include "Representation.h"
#include "Sliders.h"

#include <vtkCallbackCommand.h>
#include <vtkRenderWindowInteractor.h>

struct CallbacksData
{
	vtkVolume* _volume = nullptr;
	Representation* _representation = nullptr;
	Sliders* _sliders = nullptr;
	Drill* _drill = nullptr;
	vtkImageReader2* _reader = nullptr;
	vtkImageReader2* _preReader = nullptr;
	vtkVolumeProperty* _volumeProperty = nullptr;
	vtkRenderWindowInteractor* _interactor = nullptr;
	vtkRenderer* _renderer = nullptr;
};


class Callbacks
{
public:
	// All data for callbacks
	CallbacksData _callbacksData;
	std::vector<AbstractCallback*> _vectorCallbacks;
	vtkSmartPointer<vtkCallbackCommand> _drillMovedClickCallback;
	vtkSmartPointer<KeyPressInteractorStyle> _interactorStyleCallback;

	Callbacks() = default;

	void setupCallbacks();
	void disconnectCallbacks();

	template<typename T>
	AbstractCallback* getCallback()
	{
		AbstractCallback* res = nullptr;
		for (auto callback : _vectorCallbacks)
		{
			if (callback != nullptr)
			{
				if (typeid(T).name() == typeid(*callback).name())
				{
					res = callback;
					break;
				}
			}
		}
		return res;
	}
};

#endif