import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
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

  footer: Rectangle {
    id: footer
    color: "darkgrey"
    height: pushButton.implicitHeight + 4
    Button {
      id: pushButton
      anchors.centerIn: parent
      text: "Push"
      onClicked: {
        table.model.insertRows(table.model.rowCount(), 1)
      }
    }
  }

  TableView {
    id: table
    anchors{
      top: parent.top
      left: parent.left
      right: parent.right
      bottom: footer.top
    }
    ScrollBar.horizontal: ScrollBar{}
    ScrollBar.vertical: ScrollBar{}

    model: Backend{}

    Menu {
      id: tableContextMenu
      property int row

      MenuItem {
        text: "Copy"
        onTriggered: {
          table.model.copyRow(tableContextMenu.row)
        }
      }
      MenuItem {
        text: "Paste"
        enabled: table.model.hasCache
        onTriggered: {
          table.model.insertRows(tableContextMenu.row, 1)
        }
      }
      MenuItem {
        text: "Remove"
        onTriggered: {
          table.model.removeRows(tableContextMenu.row, 1)
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
          if(event.button === Qt.RightButton) {
            let coords = mapToItem(table, event.x, event.y)
            tableContextMenu.x = coords.x
            tableContextMenu.y = coords.y
            tableContextMenu.row = model.row
            tableContextMenu.open()
          }
        }
      }
    }
  }
}
