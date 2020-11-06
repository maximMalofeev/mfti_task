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

  onClosing: {
    table.focus = false
  }

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

      Menu {
        id: tableContextMenue
        property int row

        MenuItem {
          text: "Copy"
          onTriggered: {
            table.model.copyRow(tableContextMenue.row)
          }
        }
        MenuItem {
          text: "Paste"
          enabled: table.model.hasCache
          onTriggered: {
            table.model.insertRows(tableContextMenue.row, 1)
          }
        }
        MenuItem {
          text: "Remove"
          onTriggered: {
            table.model.removeRows(tableContextMenue.row, 1)
          }
        }
      }

      Component{
        id: rowIndex
        Label {
          id: label
          width: 30
          anchors.centerIn: parent
          text: index
          horizontalAlignment: Text.AlignHCenter
          verticalAlignment: Text.AlignVCenter
        }
      }

      delegate: Rectangle {
        implicitWidth: textInput.implicitWidth + rowIndexLoader.width
        implicitHeight: textInput.implicitHeight

        Loader {
          id: rowIndexLoader
          property int index: model.row

          width: item ? item.width : 0
          anchors{
            top: parent.top
            bottom: parent.bottom
          }

          sourceComponent: model.column === 0 ? rowIndex : undefined
        }

        TextField {
          id: textInput
          anchors.right: parent.right
          clip: true
          text: model.display
          onEditingFinished: {
            model.edit = text
          }
          onPressed: {
            if(event.button == Qt.RightButton) {
              let coords = mapToItem(table, event.x, event.y)
              tableContextMenue.x = coords.x
              tableContextMenue.y = coords.y
              tableContextMenue.row = model.row
              tableContextMenue.open()
            }
          }
        }
      }
    }
  }
}