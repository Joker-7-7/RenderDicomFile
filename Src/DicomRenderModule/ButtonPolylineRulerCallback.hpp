#ifndef BUTTONPOLYLINERULERCALLBACK_H
#define BUTTONPOLYLINERULERCALLBACK_H

#include "AbstractCallback.hpp"
#include "PolylineRulerWidget.hpp"
#include "KeyPressInteractorStyle.hpp"

/// <summary>
/// Callback for polyline button
/// </summary>
class vtkButtonPolylineRulerCallback final : public AbstractCallback
{
public:
    PolylineRulerWidget* _widget;
    vtkRenderWindowInteractor* _lIren;
    bool _modeOn;

public:
	vtkButtonPolylineRulerCallback();
    ~vtkButtonPolylineRulerCallback() override;

	static vtkButtonPolylineRulerCallback* New();
	void Execute(vtkObject* caller_, unsigned long, void*) override;
};

#endif