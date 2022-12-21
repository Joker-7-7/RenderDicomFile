import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Dialogs

import Vtk 1.0 as Vtk

Window {
    id: root
    width: 1280
    height: 861
    visible: true
    title: qsTr("DicomRender")


    Rectangle {
      anchors.fill: parent
      color: "#272727"
    }

    Vtk.SceneVtkItem {
        id: scene
        anchors.fill: parent
        anchors.margins: 30
    }

    BusyIndicator {
        id: indicator
        anchors.centerIn: parent
        width: 100
        height: 80
        visible: true
        running: false
    }

    FileDialog {
        id: fileDialog
        nameFilters: ["*.dcm"]
        onAccepted: function() {
            scene.OnClickButtonOpenFile(selectedFile);
            indicator.running = false;
        }
        onRejected: indicator.running = false;
    }

    FolderDialog {
        id: folderDialog
        onAccepted: function() {
            scene.OnClickButtonOpenDirectory(selectedFolder);
            indicator.running = false;
        }
        onRejected: indicator.running = false;
    }

   MessageDialog
    {
        id: msgDialog
        title: "Error"
        text: "Cannot confirm"
        informativeText: "The directory does not contain the correct files or the files are corrupted."
        visible: false
        onAccepted: console.log("client clicked ok")
    }
        Connections{
            target: scene
            function onShowMessageBox(){ msgDialog.visible = true;}
        }

    ToolBar {
        RowLayout {

            Button {
                text: "Open directory"
                onClicked: function() {
                    indicator.running = true;
                    folderDialog.open();
                }
            }

            Button {
                text: "Open single"
                onClicked: function() {
                    indicator.running = true;
                    fileDialog.open();
                }
            }

            Button {
                onClicked: { scene.OnClickButtonRuler()}
                 icon.source: "qrc:/Assets/ruler.png"
            }

            Button {
                onClicked: { scene.OnClickButtonBoxRep()}
                 icon.source: "qrc:/Assets/cube.png"
            }

            Button {
                onClicked: { scene.OnClickButtonTeethConfig()}
                 icon.source: "qrc:/Assets/jaw.png"
            }

            Button {
                onClicked: { scene.OnClickButtonSolidConfig()}
                 icon.source: "qrc:/Assets/skull.png"
            }

            Button {
                onClicked: { scene.OnClickButtonSkinConfig()}
                 icon.source: "qrc:/Assets/face.png"
            }

            Button {
                onClicked: { scene.OnClickButtonJitteringMode()}
                 icon.source: "qrc:/Assets/smoothing.png"
            }

            Button {
                text: "Zoom camera"
                onClicked: { scene.OnClickButtonResetCamera()}
                 icon.source: "qrc:/Assets/arrow.png"
            }
        }
    }

}
