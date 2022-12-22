#include "Callbacks.hpp"


void Callbacks::SetupCallbacks()
{
#pragma region create box rep callback
	vtkSmartPointer<vtkBoxCallback>_boxCallback = vtkBoxCallback::New();
	_boxCallback->_volume = _callbacksData._volume;
	_boxCallback->_planes = _callbacksData._representation->_planes;
	_boxCallback->_imageCurrentData = _callbacksData._reader->GetOutput();
	_boxCallback->_imagePreData = _callbacksData._preReader->GetOutput();
	_callbacksData._representation->_boxWidget->AddObserver(vtkCommand::EndInteractionEvent, _boxCallback);
	_vectorCallbacks.push_back(_boxCallback.Get());
#pragma endregion

#pragma region create L slider callback
	vtkSmartPointer<LayersConfiguration::vtkLSliderCallback_L> _sliderCallback_L = LayersConfiguration::vtkLSliderCallback_L::New();
	_sliderCallback_L->_volumeProperty = _callbacksData._volumeProperty;
	_sliderCallback_L->_currentSetup = _callbacksData._sliders->_setupWLWWConfig.get();
	_callbacksData._sliders->_sliderWidget_L->AddObserver(vtkCommand::InteractionEvent, _sliderCallback_L);
	_vectorCallbacks.push_back(_sliderCallback_L.Get());
#pragma endregion

#pragma region create W slider callback
	vtkSmartPointer<LayersConfiguration::vtkLSliderCallback_W> _sliderCallback_W = LayersConfiguration::vtkLSliderCallback_W::New();
	_sliderCallback_W->_volumeProperty = _callbacksData._volumeProperty;
	_sliderCallback_W->_currentSetup = _callbacksData._sliders->_setupWLWWConfig.get();
	_callbacksData._sliders->_sliderWidget_W->AddObserver(vtkCommand::InteractionEvent, _sliderCallback_W);
	_vectorCallbacks.push_back(_sliderCallback_W.Get());
#pragma endregion

#pragma region create ruler button callback
	vtkSmartPointer<RulerOptions::vtkButtonRulerCallback> _distanceCallbackButton = RulerOptions::vtkButtonRulerCallback::New();
	_distanceCallbackButton->_lIren = _callbacksData._interactor;
	_vectorCallbacks.push_back(_distanceCallbackButton.Get());
#pragma endregion

#pragma region create polyline ruler button callback
	vtkSmartPointer<vtkButtonPolylineRulerCallback> _polylineRulerCallbackButton = vtkButtonPolylineRulerCallback::New();
	_polylineRulerCallbackButton->_lIren = _callbacksData._interactor;
	_vectorCallbacks.push_back(_polylineRulerCallbackButton.Get());
#pragma endregion

#pragma region create box button callback
	vtkSmartPointer<vtkButtonBoxCallback>  _boxCallbackButton = vtkButtonBoxCallback::New();
	_boxCallbackButton->_box = _callbacksData._representation->_boxWidget;
	_vectorCallbacks.push_back(_boxCallbackButton.Get());
#pragma endregion

#pragma region create drill button callback
	vtkSmartPointer<vtkButtonDrillCallback> _drillCallbackButton = vtkButtonDrillCallback::New();
	_drillCallbackButton->_drill = _callbacksData._drill;
	_vectorCallbacks.push_back(_drillCallbackButton.Get());
#pragma endregion

#pragma region create drill visibility mode button callback
	vtkSmartPointer<vtkButtonVisibilityDrillCallback> _drillVisibilityCallbackButton = vtkButtonVisibilityDrillCallback::New();
	_drillVisibilityCallbackButton->_drill = _callbacksData._drill;
	_vectorCallbacks.push_back(_drillVisibilityCallbackButton.Get());
#pragma endregion

#pragma region create drill orientation callback
	vtkSmartPointer<vtkButtonReverseDrillCallback> _drillReverseCallbackButton = vtkButtonReverseDrillCallback::New();
	_drillReverseCallbackButton->_drill = _callbacksData._drill;
	_vectorCallbacks.push_back(_drillReverseCallbackButton.Get());
#pragma endregion

#pragma region create  Skin Configuration callback
	vtkSmartPointer<LayersConfiguration::vtkSkinConfigCallback> _skinCallbackButton = LayersConfiguration::vtkSkinConfigCallback::New();
	_skinCallbackButton->_volumeProperty = _callbacksData._volumeProperty;
	_skinCallbackButton->_sliderWidget_W = _callbacksData._sliders->_sliderWidget_W;
	_skinCallbackButton->_currentSetup = _callbacksData._sliders->_setupWLWWConfig.get();
	_skinCallbackButton->_sliderWidget_L = _callbacksData._sliders->_sliderWidget_L;
	_vectorCallbacks.push_back(_skinCallbackButton.Get());
#pragma endregion

#pragma region create Default configuration callback
	vtkSmartPointer<LayersConfiguration::vtkDefaultConfigCallback> _defaultCallbackButton = LayersConfiguration::vtkDefaultConfigCallback::New();
	_defaultCallbackButton->_volumeProperty = _callbacksData._volumeProperty;
	_defaultCallbackButton->_sliderWidget_W = _callbacksData._sliders->_sliderWidget_W;
	_defaultCallbackButton->_sliderWidget_L = _callbacksData._sliders->_sliderWidget_L;
	_defaultCallbackButton->_currentSetup = _callbacksData._sliders->_setupWLWWConfig.get();
	_vectorCallbacks.push_back(_defaultCallbackButton.Get());
#pragma endregion

#pragma region create Solid configuration callback
	vtkSmartPointer<LayersConfiguration::vtkSolidConfigCallback> _solidCallbackButton = LayersConfiguration::vtkSolidConfigCallback::New();
	_solidCallbackButton->_volumeProperty = _callbacksData._volumeProperty;
	_solidCallbackButton->_sliderWidget_W = _callbacksData._sliders->_sliderWidget_W;
	_solidCallbackButton->_sliderWidget_L = _callbacksData._sliders->_sliderWidget_L;
	_solidCallbackButton->_currentSetup = _callbacksData._sliders->_setupWLWWConfig.get();
	_vectorCallbacks.push_back(_solidCallbackButton.Get());
#pragma endregion

#pragma region create  Teeth configuration button callback
	vtkSmartPointer<LayersConfiguration::vtkTeethConfigCallback> _teethCallbackButton = LayersConfiguration::vtkTeethConfigCallback::New();
	_teethCallbackButton->_volumeProperty = _callbacksData._volumeProperty;
	_teethCallbackButton->_sliderWidget_W = _callbacksData._sliders->_sliderWidget_W;
	_teethCallbackButton->_sliderWidget_L = _callbacksData._sliders->_sliderWidget_L;
	_teethCallbackButton->_currentSetup = _callbacksData._sliders->_setupWLWWConfig.get();
	_vectorCallbacks.push_back(_teethCallbackButton.Get());
#pragma endregion

#pragma region create Jittering callback
	vtkSmartPointer<vtkButtonJitteringModeCallback> _jitteringModeCallbackButton = vtkButtonJitteringModeCallback::New();
	_jitteringModeCallbackButton->_volume = _callbacksData._volume;
	_vectorCallbacks.push_back(_jitteringModeCallbackButton.Get());
#pragma endregion

#pragma region create Drill move callback
	_drillMovedClickCallback = vtkCallbackCommand::New();
    _drillMovedClickCallback->SetCallback(Drill::DrillMovedClickCallbackFunction);
	_drillMovedClickCallback->SetClientData(_callbacksData._drill);
	_callbacksData._interactor->AddObserver(vtkCommand::LeftButtonPressEvent, _drillMovedClickCallback);
#pragma endregion

#pragma region create interactor style
	_interactorStyleCallback = KeyPressInteractorStyle::New();
    _interactorStyleCallback->SetImageCurrentData(_callbacksData._reader->GetOutput());
    _interactorStyleCallback->SetImagePreData(_callbacksData._preReader->GetOutput());
    _interactorStyleCallback->SetVolume(_callbacksData._volume);
    _interactorStyleCallback->SetDrill(_callbacksData._drill);
    _interactorStyleCallback->SetBoxCallback(_boxCallback);
    _interactorStyleCallback->SetBoxWidget(_callbacksData._representation->_boxWidget);
	_interactorStyleCallback->SetCurrentRenderer(_callbacksData._renderer);
	_callbacksData._interactor->SetInteractorStyle(_interactorStyleCallback);
#pragma endregion

}

void Callbacks::DisconnectCallbacks()
{
	for(int i = (int)_vectorCallbacks.size() - 1; i >= 0; --i)
	{
		_vectorCallbacks[i]->Delete();
		_vectorCallbacks.pop_back();
	}
}
