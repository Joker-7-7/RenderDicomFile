#ifndef BUTTONDRILLCALLBACK_H
#define BUTTONDRILLCALLBACK_H

#include "AbstractCallback.hpp"
#include "Drill.hpp"

/// <summary>
/// Callback for drill visibility button
/// </summary>
class vtkButtonDrillCallback final : public AbstractCallback
{
public:
    Drill* _drill;
    bool _modeOn;

public:
	vtkButtonDrillCallback();

	static vtkButtonDrillCallback* New();
	void Execute(vtkObject* caller_, unsigned long, void*) override;
};

#endif