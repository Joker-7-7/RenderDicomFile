#include "MyVtkData.h"

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

MyVtkData::MyVtkData() {
    SetupRender();
    SetupGPU();


}

void MyVtkData::SetupRender() {

    _renderer->SetBackground(0.3, 0.3, 0.3);
}

void MyVtkData::SetupGPU() {

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
    LayersConfiguration::setColorAndOpacityFunction(_volumeProperty, wl, ww);

    _volume->SetProperty(_volumeProperty);
}

void MyVtkData::AddDataSet(vtkSmartPointer<vtkImageReader2> reader) {
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

void MyVtkData::RemoveDataSet() {
    vtkProp* volume = _renderer->GetVolumes()->GetLastProp();
    if (volume != nullptr) {
        _renderer->RemoveVolume(volume);
    }
}

void MyVtkData::SetupReader(vtkSmartPointer<vtkImageReader2> reader) {
    _reader = reader;
}

bool MyVtkData::OpenDirectory(QString directory)
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
bool MyVtkData::OpenSingleFile(QString singleFile)
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


bool MyVtkData::CheckReader(vtkSmartPointer<vtkDICOMReader> reader, vtkSmartPointer<vtkImageReader2> dataSet) {

    if (reader->GetErrorCode() == 0)
        dataSet = reader;

    // Add data set to 3D view
    if (dataSet){
        AddDataSet(dataSet);
        return true;
    }

    return false;
}

void MyVtkData::ZoomToExtent() {
    _renderer->ResetCamera();
}
