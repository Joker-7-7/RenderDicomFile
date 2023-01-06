#include "KeyPressInteractorStyle.hpp"

KeyPressInteractorStyle::KeyPressInteractorStyle() {
    _imageCurrentData = nullptr;
    _imagePreData = nullptr;
    _boxCallback = nullptr;
    _boxWidget = nullptr;
}

KeyPressInteractorStyle* KeyPressInteractorStyle::New() {
    return new KeyPressInteractorStyle;
}

void KeyPressInteractorStyle::SetImageCurrentData(vtkImageData* imageCurrentData) noexcept {
    _imageCurrentData = imageCurrentData;
}

void KeyPressInteractorStyle::SetImagePreData(vtkImageData* imagePreData) noexcept {
    _imagePreData = imagePreData;
}

void KeyPressInteractorStyle::SetBoxCallback(vtkBoxCallback* boxCallback) noexcept {
    _boxCallback = boxCallback;
}

void KeyPressInteractorStyle::SetBoxWidget(vtkBoxWidget2* boxWidget) noexcept {
    _boxWidget = boxWidget;
}