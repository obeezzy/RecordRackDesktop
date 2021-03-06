import "../rrui" as RRUi
import Fluid.Controls 1.0 as FluidControls
import QtQuick 2.12
import QtQuick.Controls 2.12 as QQC2
import QtQuick.Layouts 1.3 as QQLayouts

QQC2.Dialog {
    id: suspendTransactionDialog

    property int transactionId: 0
    property string note: ""

    x: (QQC2.ApplicationWindow.contentItem.width - width) / 2
    y: (QQC2.ApplicationWindow.contentItem.height - height) / 2
    parent: QQC2.ApplicationWindow.contentItem
    implicitWidth: 600
    focus: true
    modal: true
    title: qsTr("Suspend transaction")

    Column {
        id: column

        anchors {
            left: parent.left
            right: parent.right
        }

        FluidControls.SubheadingLabel {
            id: label

            wrapMode: Text.Wrap
            text: qsTr("Add a description of this transaction below, if you wish to.")

            anchors {
                left: parent.left
                right: parent.right
            }

        }

        RRUi.TextField {
            id: noteField

            placeholderText: qsTr("Add short description (optional)")
            focus: true

            anchors {
                left: parent.left
                right: parent.right
            }

        }

        Row {
            spacing: 8
            anchors.right: parent.right

            QQC2.Button {
                flat: true
                text: qsTr("Cancel")
                onClicked: suspendTransactionDialog.reject()
            }

            QQC2.Button {
                text: qsTr("Suspend")
                onClicked: {
                    suspendTransactionDialog.note = noteField.text;
                    suspendTransactionDialog.accept();
                }
            }

        }

    }

}
