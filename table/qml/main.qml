import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import Backend 1.0

ApplicationWindow {
  id: root
  width: 600
  minimumWidth: 400
  height: 400
  minimumHeight: 200
  visible: true
  title: "Table"

  background: Rectangle {
    color: "lightgrey"
  }

  ScrollView{
    anchors.fill: parent
    clip: true

    TableView {
      id: table
      anchors.fill: parent

      model: Backend{}
      delegate: Rectangle {
        implicitWidth: 100
        implicitHeight: 50
        border.color: "black"
        border.width: 1
        TextInput {
          anchors.centerIn: parent
          clip: true
          text: backendData
          onAccepted: {
            model.edit = text
          }
        }
      }
    }
  }
}
