#ifndef BUTTONREVERSEDRILLCALLBACK_H
#define BUTTONREVERSEDRILLCALLBACK_H

#include "AbstractCallback.hpp"
#include "Drill.hpp"

/// <summary>
/// Callback for drill mode button
/// </summary>
class vtkButtonReverseDrillCallback final : public AbstractCallback
{
public:
    Drill* _drill;

public:
	vtkButtonReverseDrillCallback();

	static vtkButtonReverseDrillCallback* New();
	void Execute(vtkObject* caller_, unsigned long, void*) override;
};

#endif