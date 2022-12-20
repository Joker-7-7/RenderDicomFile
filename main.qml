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

    Vtk.MyVtkItem {
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
                text: "Zoom camera"
                onClicked: { scene.OnClickButtonResetCamera()}
            }

            Button {
                text: "Open directory"
                onClicked: function() {
                    indicator.running = true;
                    folderDialog.open();
                }
            }
        }
    }

}
