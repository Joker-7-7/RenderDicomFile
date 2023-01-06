#include "ButtonBoxCallback.hpp"

vtkButtonBoxCallback::vtkButtonBoxCallback() {
    box = nullptr;
    modeOn = false;
}

vtkButtonBoxCallback* vtkButtonBoxCallback::New() {
    return new vtkButtonBoxCallback;
}

void vtkButtonBoxCallback::Execute(vtkObject* caller, unsigned long, void*) {
    modeOn = !modeOn;
    box->SetEnabled(modeOn);
}

vtkButtonBoxCallback::~vtkButtonBoxCallback() {
    box->SetEnabled(false);
}
