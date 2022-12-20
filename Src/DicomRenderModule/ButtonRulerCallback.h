#pragma once

#include "AbstractCallback.h"

#include <vtkDistanceWidget.h>
#include <vtkDistanceRepresentation3D.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCellPicker.h>
#include <vtkCallbackCommand.h>
#include <vtkSmartPointer.h>

namespace RulerOptions
{
	/// <summary>
	/// Flag second point for demon ruler
	/// </summary>
	static bool secondPoint = false;

	/// <summary>
	/// Click callback function for choice two ruler point
	/// </summary>
	/// <param name="caller"></param>
	/// <param name="eventId"></param>
	/// <param name="clientData"></param>
	/// <param name="vtkNotUsed"></param>
	void clickCallbackFunction(vtkObject* caller_, long unsigned int eventId_, void* clientData_,
	                           void* vtkNotUsed(callData));

	/// <summary>
	/// Callback for ruler button
	/// </summary>
	class vtkButtonRulerCallback final : public AbstractCallback
	{
	public:
		vtkButtonRulerCallback();

        vtkSmartPointer<vtkDistanceWidget> _distanceWidget;

        vtkSmartPointer<vtkDistanceWidget> _tempDistanceWidget;

		bool _modeOn;

		vtkRenderWindowInteractor* _lIren;

		static vtkButtonRulerCallback* New();

		void Execute(vtkObject* caller_, unsigned long, void*) override;

		 ~vtkButtonRulerCallback() override;
	};
}
