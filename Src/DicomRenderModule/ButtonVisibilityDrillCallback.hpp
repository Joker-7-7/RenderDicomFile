#ifndef BUTTONVISIBILITYCALLBACK_H
#define BUTTONVISIBILITYCALLBACK_H

#include "AbstractCallback.hpp"
#include "Drill.hpp"

/// <summary>
/// Callback for drill visibility button
/// </summary>
class vtkButtonVisibilityDrillCallback final : public AbstractCallback
{
public:
	vtkButtonVisibilityDrillCallback();

	Drill* _drill;

	static vtkButtonVisibilityDrillCallback* New();

	void Execute(vtkObject* caller_, unsigned long, void*) override;
};

#endif