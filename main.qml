import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Dialogs

import Vtk 1.0 as Vtk

Window {
    id: root
    width: 640
    height: 480
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

    FolderDialog {
        id: folderDialog
        onAccepted: function() {
            scene.OnClickButtonOpenDirectory(selectedFolder);
        }
    }


    ToolBar {
        RowLayout {
            Button {
                text: "Zoom camera"
                onClicked: { }
            }

            Button {
                text: "Open directory"
                onClicked: function() {
                    folderDialog.open();
                }
            }
        }
    }

}
