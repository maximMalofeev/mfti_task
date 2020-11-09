import QtQuick 2.12
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import Backend 1.0

ApplicationWindow {
  id: root
  width: 600
  maximumWidth: 600
  height: 400
  maximumHeight: 400
  visible: true
  title: "Chart"

  property int chartElementWidth: 10

  RowLayout {
    anchors.fill: parent
    spacing: 0

    Rectangle {
      id: scene
      Layout.preferredWidth: (root.width * 2) / 3
      Layout.preferredHeight: root.height
      color: "lightgrey"

      Canvas {
        id: canvas
        anchors.fill: parent

        onPaint: {
          var ctx = getContext("2d")
          ctx.reset()

          ctx.lineWidth = 3;
          ctx.strokeStyle = "dimgrey"
          ctx.beginPath()


          let model = repeater.model
          let count = model.rowCount()
          if(count > 1) {
            let point = model.point(0)
            point.x += root.chartElementWidth / 2
            point.y += root.chartElementWidth / 2
            ctx.moveTo(point.x, point.y)
            for(let i = 1; i < count; i++) {
              let nextPoint = model.point(i)
              nextPoint.x += root.chartElementWidth / 2
              nextPoint.y += root.chartElementWidth / 2
              ctx.lineTo(nextPoint.x, nextPoint.y)
              ctx.moveTo(nextPoint.x, nextPoint.y)
              ctx.stroke()
              point = nextPoint
            }
          }
        }
      }

      Repeater {
        id: repeater
        model: Backend {}
        delegate: Rectangle {
          x: model.X
          y: model.Y
          width: root.chartElementWidth
          height: width
          radius: width / 2
          color: "blue"

          onXChanged: {
            model.X = x
            canvas.requestPaint()
          }

          onYChanged: {
            model.Y = y
            canvas.requestPaint()
          }

          MouseArea {
            anchors.fill: parent
            drag.target: parent
            drag.axis: Drag.XAndYAxis
            drag.minimumX: 0
            drag.maximumX: scene.width - parent.width
            drag.minimumY: 0
            drag.maximumY: scene.height - parent.width
          }
        }
      }
    }

    ListView {
      id: list
      Layout.preferredWidth: root.width / 3
      Layout.preferredHeight: root.height
      model: repeater.model;
      delegate: Rectangle {
        property alias xVal: xField.text
        property alias yVal: yField.text
        xVal: model.X
        yVal: model.Y
        width: xField.width + yField.width
        height: Math.max(xField.implicitHeight, yField.implicitHeight)
        TextField {
          id: xField
          anchors.left: parent.left
          width: 100
          validator: IntValidator {
            top: (root.width * 2) / 3
            bottom: 0
          }

          onTextChanged: {
            model.X = text
          }
        }
        TextField {
          id: yField
          anchors.right: parent.right
          width: 100
          validator: IntValidator {
            top: root.height
            bottom: 0
          }

          onTextChanged: {
            model.Y = text
          }
        }
      }
    }
  }
}
