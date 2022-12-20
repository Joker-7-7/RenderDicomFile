#include "SceneVtkData.h"

#include "DicomRenderModule/LayersConfiguration.h"

#include <vtkNew.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkGPUVolumeRayCastMapper.h>


#include <vtkGlobFileNames.h>
#include <vtkDICOMDirectory.h>
#include <vtkDICOMImageReader.h>

SceneVtkData::SceneVtkData() : _backgroundColor{0.3, 0.3, 0.3}, _desiredUpdateRate(30){
    SetupRender();
    SetupGPU();

    CreateDrill();
    CreateRepresentations();
    CreateCallbacks();
}

void SceneVtkData::SetupRender() {

    _renderer->SetBackground(_backgroundColor);

    _iren->SetRenderWindow(_renderWindow);
}

void SceneVtkData::SetupGPU() {

    // Setup Volume property
    vtkNew<vtkColorTransferFunction> m_ptrColorFunction;
    vtkNew<vtkPiecewiseFunction> m_ptrOpacityFunction;
    _volumeProperty->SetColor(m_ptrColorFunction);
    _volumeProperty->SetScalarOpacity(m_ptrOpacityFunction);
    _volumeProperty->SetInterpolationTypeToLinear();
    _volumeProperty->ShadeOn();
    _volumeProperty->SetAmbient(0.15);
    _volumeProperty->SetDiffuse(0.8);
    _volumeProperty->SetSpecular(0.25);
    _volumeProperty->SetSpecularPower(40);

    int wl = 900;
    int ww = 300;
    LayersConfiguration::setColorAndOpacityFunction(_volumeProperty,_slidersValue.Slider_L, _slidersValue.Slider_W);

    _volume->SetProperty(_volumeProperty);
}

void SceneVtkData::AddDataSet(vtkSmartPointer<vtkImageReader2> reader) {
    RemoveDataSet();

    SetupReader(reader);

    // Mapper
    vtkNew<vtkGPUVolumeRayCastMapper> mapper;
    mapper->SetInputConnection(reader->GetOutputPort());
    mapper->SetMaximumImageSampleDistance(1.0);
    mapper->UseJitteringOn();


    _volume->SetProperty(_volumeProperty);
    _volume->SetMapper(mapper);

    _renderer->AddVolume(_volume);
    _renderer->ResetCamera();
}

void SceneVtkData::RemoveDataSet() {
    vtkProp* volume = _renderer->GetVolumes()->GetLastProp();
    if (volume != nullptr) {
        _renderer->RemoveVolume(volume);
    }
}

void SceneVtkData::SetupReader(vtkSmartPointer<vtkImageReader2> reader) {
    _reader = reader;
}

bool SceneVtkData::OpenDirectory(QString directory)
{
    vtkSmartPointer<vtkImageReader2> dataSet = nullptr;
    QString directoryName = directory.remove(0, 8);

    // Open directory
    vtkSmartPointer<vtkGlobFileNames> globFileNames =
            vtkSmartPointer<vtkGlobFileNames>::New();
    globFileNames->SetDirectory(directoryName.toStdString().c_str());
    globFileNames->AddFileNames("*.dcm");

    vtkSmartPointer<vtkDICOMDirectory> directoryReader =
            vtkSmartPointer<vtkDICOMDirectory>::New();
    directoryReader->RequirePixelDataOn();
    directoryReader->SetInputFileNames(globFileNames->GetFileNames());
    directoryReader->Update();

    if (directoryReader->GetNumberOfSeries() == 0)
    {

        return false;
    }

    vtkNew<vtkDICOMReader> reader;
    reader->SetFileNames(directoryReader->GetFileNamesForSeries(0));
    reader->SetMemoryRowOrderToFileNative();
    reader->Update();

    return CheckReader(reader, dataSet);
}
bool SceneVtkData::OpenSingleFile(QString singleFile)
{
    vtkSmartPointer<vtkImageReader2> dataSet = nullptr;
    // Open file
    QString fileName = singleFile.remove(0,8);

    vtkNew<vtkDICOMReader> fileReader;
    fileReader->SetFileName(fileName.toStdString().c_str());
    fileReader->SetMemoryRowOrderToFileNative();
    fileReader->Update();

    return CheckReader(fileReader, dataSet);
}


bool SceneVtkData::CheckReader(vtkSmartPointer<vtkDICOMReader> reader, vtkSmartPointer<vtkImageReader2> dataSet) {

    if (reader->GetErrorCode() == 0)
        dataSet = reader;

    // Add data set to 3D view
    if (dataSet){
        AddDataSet(dataSet);
        return true;
    }

    return false;
}

void SceneVtkData::ZoomToExtent() {
    _renderer->ResetCamera();
}

void SceneVtkData::CreateRepresentations() {
    _representation = std::make_shared<Representation>(_iren, _renderer);
}

void SceneVtkData::CreateDrill() {
    _drill = std::make_shared<Drill>(_renderer);
}

void SceneVtkData::CreateCallbacks() {
    _callbacks = std::make_shared<Callbacks>();
}

void SceneVtkData::SetupCallbacks() {
    _callbacks->_callbacksData._volume = _volume.Get();
    _callbacks->_callbacksData._representation = _representation.get();
    _callbacks->_callbacksData._sliders = _sliders.get();
    _callbacks->_callbacksData._drill = _drill.get();
    _callbacks->_callbacksData._reader = _reader.Get();
    _callbacks->_callbacksData._preReader = _preReader.Get();
    _callbacks->_callbacksData._volumeProperty = _volumeProperty.Get();
    _callbacks->_callbacksData._interactor = _renderWindow->GetInteractor();
    _callbacks->_callbacksData._renderer = _renderer.Get();

    _callbacks->setupCallbacks();
}
