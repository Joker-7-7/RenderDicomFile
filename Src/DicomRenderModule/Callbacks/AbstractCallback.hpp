#ifndef ABSTRACTCALLBACK_H
#define ABSTRACTCALLBACK_H

#include <vtkCommand.h>

/// <summary>
/// Abstract callbacks class for all callbacks in the project
/// </summary>
class AbstractCallback : public vtkCommand
{
public:
	/// <summary>
	/// Main function where described what does the callback do
	/// </summary>
	virtual void Execute(vtkObject* caller, unsigned long eventId, void* callData) = 0;
};

#endif