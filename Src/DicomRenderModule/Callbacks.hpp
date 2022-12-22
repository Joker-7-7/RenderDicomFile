#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "ButtonReverseDrillCallback.hpp"
#include "ButtonPolylineRulerCallback.hpp"
#include "TeethConfigCallback.hpp"
#include "SkinConfigCallback.hpp"
#include "SolidConfigCallback.hpp"
#include "DefaultConfigCallback.hpp"
#include "LSliderCallback_W.hpp"
#include "LSliderCallback_L.hpp"
#include "ButtonDrillCallback.hpp"
#include "KeyPressInteractorStyle.hpp"
#include "ButtonRulerCallback.hpp"
#include "BoxCallbacks.hpp"
#include "ButtonBoxCallback.hpp"
#include "VolumeParametersCallback.hpp"
#include "ButtonVisibilityDrillCallback.hpp"

#include "Representation.hpp"
#include "Sliders.hpp"

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