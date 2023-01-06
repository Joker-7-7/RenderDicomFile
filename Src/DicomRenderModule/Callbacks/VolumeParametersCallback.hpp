#ifndef VOLUMEPARAMETERSCALLBACK_H
#define VOLUMEPARAMETERSCALLBACK_H

#include "AbstractCallback.hpp"

#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkVolume.h>

/// <summary>
/// Callback for Jittering mode button
/// </summary>
class vtkButtonJitteringModeCallback final : public AbstractCallback
{
public:
    vtkVolume* volume;
    bool isJitteringMode;
    
public:
	vtkButtonJitteringModeCallback();

	static vtkButtonJitteringModeCallback* New();
	void Execute(vtkObject* caller, unsigned long, void*) override;
};

#endif