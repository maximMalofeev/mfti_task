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
  title: "Random array"

  background: Rectangle {
    color: "lightgrey"
  }

  ListView {
    id: chart

    property var arr: []
    function setArr(newArr) {
      arr = newArr
      update()
    }

    signal update()

    anchors {
      top: parent.top
      left: parent.left
      right: parent.right
      bottom: controlButtonsRow.top
      margins: 4
    }
    orientation: ListView.Horizontal
    model: arr.length
    spacing: 2

    delegate: Rectangle {
      id: chartItem
      width: chart.width / chart.model - chart.spacing
      height: width
      radius: width / 2
      color: "blue"

      ToolTip.text: modelData + ", " + chart.arr[modelData]
      ToolTip.visible: mouseArea.containsMouse
      MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
      }

      Connections {
        target: chart
        function onUpdate() {
          y = (chart.height - chartItem.height) * chart.arr[modelData]
        }
      }
      Behavior on y {
        NumberAnimation {
          duration: 50
        }
      }
    }
  }

  Row {
    id: controlButtonsRow
    anchors.bottom: parent.bottom
    anchors.horizontalCenter: parent.horizontalCenter
    spacing: 4

    Button {
      id: startButton
      text: "Start"

      onClicked: {
        backend.start()
      }
    }
    Button {
      id: pauseButton
      text: "Pause"

      onClicked: {
        backend.pause()
      }
    }
    Button {
      id: stopButton
      text: "Stop"

      onClicked: {
        backend.stop()
        chart.arr = []
      }
    }
  }

  Backend {
    id: backend
    onUpdate: {
      chart.setArr(arr)
    }
  }
}
