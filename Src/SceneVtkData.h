#ifndef SCENEVTKDATA_H
#define SCENEVTKDATA_H

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

struct SlidersValue{
    int Slider_L = 900;
    int Slider_W = 300;
};

struct SceneVtkData : vtkObject
{
public:
    // Sliders value
    SlidersValue _slidersValue;
    // Window background color
    const double _backgroundColor[3];
    // Represents a volume (data & properties) in a rendered scene
    vtkNew<vtkVolume> _volume;
    // Represents the common properties for rendering a volume
    vtkNew<vtkVolumeProperty> _volumeProperty;
    // Reader for first buffer
    vtkSmartPointer<vtkImageReader2> _reader;
    // Reader for second buffer
    vtkSmartPointer<vtkImageReader2> _preReader;
    // Scene view elements
    std::shared_ptr<Representation> _representation;
    // App sliders
    std::shared_ptr<Sliders> _sliders;
    // App callbacks
    std::shared_ptr<Callbacks> _callbacks;
    // Twin of the drill
    std::shared_ptr<Drill> _drill;
    // Is an object that controls the rendering process for objects
    vtkNew<vtkRenderer> _renderer;
    // A window in a graphical user interface where renderers draw their images
    vtkSmartPointer<vtkRenderWindow> _renderWindow;

public:
    vtkTypeMacro(SceneVtkData, vtkObject);

    static SceneVtkData* New();

    SceneVtkData();

    void InitSceneVTKData(vtkRenderWindow *renderWindow);
    /// <summary>
    /// Add a data set to the scene
    /// </summary>
    /// <param name="param[in] dataSet The data set to add"></param>
    void AddDataSet(vtkSmartPointer<vtkImageReader2> dataSet);
    /// <summary>
    /// Setup _renderer, _renderWindow, _interactor
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
    /// Create all representations un the app
    /// </summary>
    void CreateRepresentations();
    /// <summary>
    /// Create twin of the drill
    /// </summary>
    void CreateDrill();
    /// <summary>
    /// Remove all callbacks in the app
    /// </summary>
    void RemoveCallbacks();
    /// <summary>
    /// Create all sliders in the app
    /// </summary>
    void CreateSliders();
    /// <summary>
    /// Create all callbacks in the app
    /// </summary>
    void CreateCallbacks();
    /// <summary>
    /// Setup all callbacks in the app
    /// </summary>
    void SetupCallbacks();
    /// <summary>
    /// Zoom to the extent of the data set in the scene
    /// </summary>
    void ZoomToExtent() const;
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

    /**
     * Сheck the validity of the reader and add data to the scene if successful
     * @param reader Reader with selected file
     * @param dataSet Dataset for render
     * @return Error code: true - success, false - error
     */
    [[nodiscard]] bool CheckReader(vtkSmartPointer<vtkDICOMReader> reader, vtkSmartPointer<vtkImageReader2> dataSet);

public:
    template<class T>
    void Execute()
    {
        if(_callbacks) {
            AbstractCallback* callback_ = _callbacks->getCallback<T>();
            if (callback_) {
                callback_->Execute(nullptr, NULL, nullptr);
            }
        }
    }
};

#endif
