#include "Callbacks.hpp"


void Callbacks::SetupCallbacks() {
#pragma region create box rep callback
    vtkSmartPointer<vtkBoxCallback> boxCallback = vtkBoxCallback::New();
    boxCallback->volume = callbacksData.volume;
    boxCallback->planes = callbacksData.representation->planes;
    boxCallback->imageCurrentData = callbacksData.reader->GetOutput();
    boxCallback->imagePreData = callbacksData.preReader->GetOutput();
    callbacksData.representation->boxWidget->AddObserver(vtkCommand::EndInteractionEvent, boxCallback);
    vectorCallbacks.push_back(boxCallback.Get());
#pragma endregion

#pragma region create ruler button callback
    vtkSmartPointer<RulerOptions::vtkButtonRulerCallback> distanceCallbackButton = RulerOptions::vtkButtonRulerCallback::New();
    distanceCallbackButton->interactor = callbacksData.interactor;
    vectorCallbacks.push_back(distanceCallbackButton.Get());
#pragma endregion

#pragma region create box button callback
    vtkSmartPointer<vtkButtonBoxCallback> boxCallbackButton = vtkButtonBoxCallback::New();
    boxCallbackButton->box = callbacksData.representation->boxWidget;
    vectorCallbacks.push_back(boxCallbackButton.Get());
#pragma endregion

#pragma region create  Skin Configuration callback
    vtkSmartPointer<LayersConfiguration::vtkSkinConfigCallback> skinCallbackButton = LayersConfiguration::vtkSkinConfigCallback::New();
    skinCallbackButton->volumeProperty = callbacksData.volumeProperty;
    vectorCallbacks.push_back(skinCallbackButton.Get());
#pragma endregion

#pragma region create Default configuration callback
    vtkSmartPointer<LayersConfiguration::vtkDefaultConfigCallback> defaultCallbackButton = LayersConfiguration::vtkDefaultConfigCallback::New();
    defaultCallbackButton->volumeProperty = callbacksData.volumeProperty;
    vectorCallbacks.push_back(defaultCallbackButton.Get());
#pragma endregion

#pragma region create Solid configuration callback
    vtkSmartPointer<LayersConfiguration::vtkSolidConfigCallback> solidCallbackButton = LayersConfiguration::vtkSolidConfigCallback::New();
    solidCallbackButton->volumeProperty = callbacksData.volumeProperty;
    vectorCallbacks.push_back(solidCallbackButton.Get());
#pragma endregion

#pragma region create  Teeth configuration button callback
    vtkSmartPointer<LayersConfiguration::vtkTeethConfigCallback> teethCallbackButton = LayersConfiguration::vtkTeethConfigCallback::New();
    teethCallbackButton->volumeProperty = callbacksData.volumeProperty;
    vectorCallbacks.push_back(teethCallbackButton.Get());
#pragma endregion

#pragma region create Jittering callback
    vtkSmartPointer<vtkButtonJitteringModeCallback> jitteringModeCallbackButton = vtkButtonJitteringModeCallback::New();
    jitteringModeCallbackButton->volume = callbacksData.volume;
    vectorCallbacks.push_back(jitteringModeCallbackButton.Get());
#pragma endregion

#pragma region create interactor style
    interactorStyleCallback = KeyPressInteractorStyle::New();
    interactorStyleCallback->SetImageCurrentData(callbacksData.reader->GetOutput());
    interactorStyleCallback->SetImagePreData(callbacksData.preReader->GetOutput());
    interactorStyleCallback->SetBoxCallback(boxCallback);
    interactorStyleCallback->SetBoxWidget(callbacksData.representation->boxWidget);
    interactorStyleCallback->SetCurrentRenderer(callbacksData.renderer);
    callbacksData.interactor->SetInteractorStyle(interactorStyleCallback);
#pragma endregion
}

void Callbacks::DisconnectCallbacks() {
    for (int i = (int) vectorCallbacks.size() - 1; i >= 0; --i) {
        vectorCallbacks[i]->Delete();
        vectorCallbacks.pop_back();
    }
}
