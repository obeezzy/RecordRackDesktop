import "../../rrui" as RRUi
import Fluid.Controls 1.0 as FluidControls
import QtQuick 2.12
import QtQuick.Controls 2.12 as QQC2
import com.gecko.rr.models 1.0 as RRModels

RRUi.SubView {
    id: userDetailSubView

    readonly property bool isExistingUser: userId > 0
    property int userId: 0
    property string imageUrl: ""
    property string firstName: ""
    property string lastName: ""
    property string userName: ""
    property string password: ""
    property string passwordConfirmation: ""
    property string phoneNumber: ""
    property string emailAddress: ""

    implicitWidth: 800
    implicitHeight: 800

    RRModels.UserDetailRecord {
        id: userDetailRecord

        userId: userDetailSubView.userId
    }

    contentItem: FocusScope {
        QQC2.ScrollView {
            id: scrollView

            anchors {
                top: parent.top
                bottom: parent.bottom
                topMargin: 24
            }

            Row {
                id: mainRow

                spacing: 84

                anchors {
                    left: parent.left
                    leftMargin: 64
                }

                Column {
                    id: imageColumn

                    width: 160
                    spacing: 4

                    RRUi.LetterCircleImage {
                        id: userImage

                        height: width
                        font.pixelSize: 30
                        name: userNameTextField.text

                        anchors {
                            left: parent.left
                            right: parent.right
                        }

                        FluidControls.Icon {
                            anchors.centerIn: parent
                            visible: userImage.name === ""
                            color: "white"
                            source: FluidControls.Utils.iconUrl("image/photo_camera")
                        }

                    }

                    Row {
                        anchors.horizontalCenter: parent.horizontalCenter

                        RRUi.ToolButton {
                            id: takePhotoButton

                            icon.source: FluidControls.Utils.iconUrl("image/photo_camera")
                            text: qsTr("Take a photo")
                        }

                        RRUi.ToolButton {
                            id: selectPhotoButton

                            icon.source: FluidControls.Utils.iconUrl("image/photo")
                            text: qsTr("Select image")
                        }

                        RRUi.ToolButton {
                            id: deviceSearchButton

                            icon.source: FluidControls.Utils.iconUrl("hardware/phonelink")
                            text: qsTr("Start DeviceLink")
                        }

                    }

                }

                Column {
                    id: detailColumn

                    width: 300

                    RRUi.IconTextField {
                        id: userNameTextField

                        enabled: !userDetailSubView.isExistingUser
                        icon.source: FluidControls.Utils.iconUrl("social/person")
                        textField.placeholderText: qsTr("User name")
                        text: userDetailRecord.userName

                        anchors {
                            left: parent.left
                            right: parent.right
                        }

                        Connections {
                            target: userNameTextField.textField
                            onTextEdited: userDetailSubView.userName = userNameTextField.textField.text
                        }

                    }

                    RRUi.IconTextField {
                        id: firstNameTextField

                        enabled: !userDetailSubView.isExistingUser
                        textField.placeholderText: qsTr("First name")
                        text: userDetailRecord.firstName

                        anchors {
                            left: parent.left
                            right: parent.right
                        }

                        Connections {
                            target: firstNameTextField.textField
                            onTextEdited: userDetailSubView.firstName = firstNameTextField.textField.text
                        }

                    }

                    RRUi.IconTextField {
                        id: lastNameTextField

                        enabled: !userDetailSubView.isExistingUser
                        textField.placeholderText: qsTr("Last name")
                        text: userDetailRecord.lastName

                        anchors {
                            left: parent.left
                            right: parent.right
                        }

                        Connections {
                            target: lastNameTextField.textField
                            onTextEdited: userDetailSubView.lastName = lastNameTextField.textField.text
                        }

                    }

                    RRUi.IconTextField {
                        id: passwordTextField

                        visible: !userDetailSubView.isExistingUser
                        icon.source: FluidControls.Utils.iconUrl("action/lock")
                        textField.placeholderText: qsTr("Password")
                        textField.echoMode: TextInput.Password
                        textField.passwordCharacter: "⚫"

                        anchors {
                            left: parent.left
                            right: parent.right
                        }

                        Connections {
                            target: passwordTextField.textField
                            onTextEdited: userDetailSubView.password = passwordTextField.textField.text
                        }

                    }

                    RRUi.IconTextField {
                        id: confirmPasswordTextField

                        visible: !userDetailSubView.isExistingUser
                        textField.placeholderText: qsTr("Confirm password")
                        textField.echoMode: TextInput.Password
                        textField.passwordCharacter: "⚫"

                        anchors {
                            left: parent.left
                            right: parent.right
                        }

                        Connections {
                            target: confirmPasswordTextField.textField
                            onTextEdited: userDetailSubView.passwordConfirmation = confirmPasswordTextField.textField.text
                        }

                    }

                    RRUi.IconTextField {
                        id: phoneNumberTextField

                        enabled: !userDetailSubView.isExistingUser
                        icon.source: FluidControls.Utils.iconUrl("communication/phone")
                        textField.placeholderText: qsTr("Phone number")
                        text: userDetailRecord.phoneNumber

                        anchors {
                            left: parent.left
                            right: parent.right
                        }

                        Connections {
                            target: phoneNumberTextField.textField
                            onTextEdited: userDetailSubView.phoneNumber = phoneNumberTextField.textField.text
                        }

                    }

                    RRUi.IconTextField {
                        id: emailTextField

                        enabled: !userDetailSubView.isExistingUser
                        icon.source: FluidControls.Utils.iconUrl("communication/email")
                        textField.placeholderText: qsTr("Email address")
                        text: userDetailRecord.emailAddress

                        anchors {
                            left: parent.left
                            right: parent.right
                        }

                        Connections {
                            target: emailTextField.textField
                            onTextEdited: userDetailSubView.emailAddress = emailTextField.textField.text
                        }

                    }

                }

            }

        }

    }

}
