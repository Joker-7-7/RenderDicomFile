#pragma once

#include "AbstractCallback.h"

#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkVolume.h>

/// <summary>
/// Callback for Jittering mode button
/// </summary>
class vtkButtonJitteringModeCallback final : public AbstractCallback
{
public:
	vtkButtonJitteringModeCallback();

	vtkVolume* _volume;

	bool _isJitteringMode;

	static vtkButtonJitteringModeCallback* New();

	void Execute(vtkObject* caller_, unsigned long, void*) override;
};
