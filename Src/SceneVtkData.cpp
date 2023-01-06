#include "SceneVtkData.hpp"
#include "Src/DicomRenderModule/SceneInteractionParameters/LayersConfiguration.hpp"

#include <vtkNew.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkGlobFileNames.h>
#include <vtkDICOMDirectory.h>
#include <vtkDICOMImageReader.h>

SceneVtkData::SceneVtkData() :
    _backgroundColor{0.3, 0.3, 0.3}
{
}

void SceneVtkData::InitSceneVTKData(vtkRenderWindow* renderWindow) {
#ifdef _DEBUG
#else
    vtkObject::GlobalWarningDisplayOff();
#endif

    _renderWindow = renderWindow;
    SetupRender();
    SetupGPU();

    CreateRepresentations();
    CreateCallbacks();
}

void SceneVtkData::SetupRender() {
    vtkNew<vtkInteractorStyleTrackballCamera> style;
    style->SetDefaultRenderer(_renderer);

    _renderWindow->GetInteractor()->SetInteractorStyle(style);
    _renderWindow->SetSize(_renderWindow->GetScreenSize());
    _renderWindow->AddRenderer(_renderer);
    _renderWindow->SetWindowName("MainWindow");

    _renderer->SetBackground(_backgroundColor);
}

void SceneVtkData::SetupGPU() const noexcept {
    // Setup Volume property
    vtkNew<vtkColorTransferFunction> m_ptrColorFunction;
    vtkNew<vtkPiecewiseFunction> m_ptrOpacityFunction;
    volumeProperty->SetColor(m_ptrColorFunction);
    volumeProperty->SetScalarOpacity(m_ptrOpacityFunction);
    volumeProperty->SetInterpolationTypeToLinear();
    volumeProperty->ShadeOn();
    volumeProperty->SetAmbient(0.15);
    volumeProperty->SetDiffuse(0.8);
    volumeProperty->SetSpecular(0.25);
    volumeProperty->SetSpecularPower(40);

    LayersConfiguration::SetColorAndOpacityFunction(volumeProperty, viewSettings.lLevel, viewSettings.wLevel);
    _volume->SetProperty(volumeProperty);
}

void SceneVtkData::AddDataSet(vtkSmartPointer<vtkImageReader2> reader) {
    RemoveDataSet();
    RemoveCallbacks();

    SetupReader(reader);
    SetupCallbacks();

    // Mapper
    vtkNew<vtkGPUVolumeRayCastMapper> mapper;
    mapper->SetInputConnection(reader->GetOutputPort());
    mapper->SetMaximumImageSampleDistance(1.0);
    mapper->UseJitteringOn();

    _volume->SetProperty(volumeProperty);
    _volume->SetMapper(mapper);

    _renderer->AddVolume(_volume);
    _renderer->ResetCamera();
}

void SceneVtkData::RemoveDataSet() const {
    vtkProp *volume = _renderer->GetVolumes()->GetLastProp();
    if (volume != nullptr) {
        _renderer->RemoveVolume(volume);
    }
}

void SceneVtkData::SetupReader(vtkSmartPointer<vtkImageReader2> reader) {
    _representation->SetReader(reader);
    // save reader in first buffer
    _reader = reader;
    // create new reader for second buffer
    vtkNew<vtkImageReader2> newReaderCopy;
    newReaderCopy->GetOutput()->DeepCopy(reader->GetOutput());
    _preReader = newReaderCopy;
}

bool SceneVtkData::OpenDirectory(QString directory) {
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

    if (directoryReader->GetNumberOfSeries() == 0) {
        return false;
    }

    vtkNew<vtkDICOMReader> reader;
    reader->SetFileNames(directoryReader->GetFileNamesForSeries(0));
    reader->SetMemoryRowOrderToFileNative();
    reader->Update();

    return CheckReader(reader, dataSet);
}

bool SceneVtkData::OpenSingleFile(QString singleFile) {
    vtkSmartPointer<vtkImageReader2> dataSet = nullptr;
    // Open file
    QString fileName = singleFile.remove(0, 8);

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
    if (dataSet) {
        AddDataSet(dataSet);
        return true;
    }

    return false;
}

void SceneVtkData::ZoomToExtent() const noexcept {
    _renderer->ResetCamera();
}

void SceneVtkData::CreateRepresentations() noexcept {
    _representation = std::make_shared<Representation>(_renderWindow->GetInteractor(), _renderer.Get());
}

void SceneVtkData::CreateCallbacks() noexcept {
    _callbacks = std::make_shared<Callbacks>();
}


void SceneVtkData::SetupCallbacks() {
    _callbacks->callbacksData.volume = _volume.Get();
    _callbacks->callbacksData.representation = _representation.get();
    _callbacks->callbacksData.reader = _reader.Get();
    _callbacks->callbacksData.preReader = _preReader.Get();
    _callbacks->callbacksData.volumeProperty = volumeProperty.Get();
    _callbacks->callbacksData.interactor = _renderWindow->GetInteractor();
    _callbacks->callbacksData.renderer = _renderer.Get();

    _callbacks->SetupCallbacks();
}

void SceneVtkData::RemoveCallbacks() const {
    _representation->boxWidget->RemoveAllObservers();
    _callbacks->DisconnectCallbacks();
}



