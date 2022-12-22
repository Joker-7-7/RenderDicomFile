#ifndef BUTTONBOXCALLBACK_H
#define BUTTONBOXCALLBACK_H

#include "AbstractCallback.hpp"

#include <vtkBoxWidget2.h>

/// <summary>
/// Callback for clipping Box button
/// </summary>
class vtkButtonBoxCallback final : public AbstractCallback
{
public:
	vtkBoxWidget2* _box;
	bool _modeOn;

public:
	vtkButtonBoxCallback();
	~vtkButtonBoxCallback() override;

	static vtkButtonBoxCallback* New();
	void Execute(vtkObject* caller_, unsigned long, void*) override;
};

#endif