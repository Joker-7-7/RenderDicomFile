#ifndef BUTTONREVERSEDRILLCALLBACK_H
#define BUTTONREVERSEDRILLCALLBACK_H

#include "AbstractCallback.h"
#include "Drill.h"

/// <summary>
/// Callback for drill mode button
/// </summary>
class vtkButtonReverseDrillCallback final : public AbstractCallback
{
public:
	vtkButtonReverseDrillCallback();

	Drill* _drill;

	static vtkButtonReverseDrillCallback* New();

	void Execute(vtkObject* caller_, unsigned long, void*) override;
};

#endif