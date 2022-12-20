#ifndef MYVTKDATA_H
#define MYVTKDATA_H

#include "Src/DicomRenderModule/Callbacks.h"
#include "Src/DicomRenderModule/Representation.h"

#include <QString.h>

#include <vtkObject.h>
#include <vtkObjectFactory.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkVolumeProperty.h>
#include <vtkImageReader2.h>
#include <vtkDICOMReader.h>

struct MyVtkData : vtkObject
{
public:
    // represents the common properties for rendering a volume
    vtkNew<vtkVolumeProperty> _volumeProperty;
    // represents a volume (data & properties) in a rendered scene
    vtkNew<vtkVolume> _volume;
    // app callbacks
    std::shared_ptr<Callbacks> _callbacks;

    // reader for first buffer
    vtkSmartPointer<vtkImageReader2> _reader;

    vtkNew<vtkRenderer> _renderer;

    vtkSmartPointer<vtkRenderWindow> _renderWindow;

public:
    static MyVtkData* New();

    vtkTypeMacro(MyVtkData, vtkObject);
    MyVtkData();

    /// <summary>
    /// Add a data set to the scene
    /// </summary>
    /// <param name="param[in] dataSet The data set to add"></param>
    void AddDataSet(vtkSmartPointer<vtkImageReader2> dataSet);
    /// <summary>
    /// Setup m_ptrRenderer, m_ptrRenderWindow, m_ptrInterator
    /// </summary>
    void SetupRender();
    /// <summary>
    /// Setup vtkGPUVolumeRayCastMapper, vtkColorTransferFunction, vtkPiecewiseFunction
    /// </summary>
    void SetupGPU();
    /// <summary>
    /// Remove the data set from the scene
    /// </summary>
    void RemoveDataSet();
    /// <summary>
    /// Setup readers parameters for m_ptrReader and m_ptrPreReader
    /// </summary>
    /// <param name="reader"></param>
    void SetupReader(vtkSmartPointer<vtkImageReader2> reader);
    /// <summary>
    /// Open single DICOM file
    /// </summary>
    /// <param name="singleFile"></param>
    /// <returns>Error value code</returns>
    [[nodiscard]] bool OpenSingleFile(QString singleFile);
    /// <summary>
    /// Directory with DICOM files
    /// </summary>
    /// <param name="directory"></param>
    /// <returns>Error value code</returns>
    [[nodiscard]] bool OpenDirectory(QString directory);

    [[nodiscard]] bool CheckReader(vtkSmartPointer<vtkDICOMReader> reader, vtkSmartPointer<vtkImageReader2> dataSet);


    /// <summary>
    /// Zoom to the extent of the data set in the scene
    /// </summary>
    void ZoomToExtent();
};

#endif // MYVTKDATA_H
