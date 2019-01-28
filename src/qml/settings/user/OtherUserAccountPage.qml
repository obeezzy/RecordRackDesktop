import QtQuick 2.12
import QtQuick.Controls 2.12 as QQC2
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3 as QQLayouts
import Fluid.Controls 1.0 as FluidControls
import com.gecko.rr.models 1.0 as RRModels
import "../../rrui" as RRUi
import "../../common"
import ".."

RRUi.Page {
    id: otherUserAccountPage

    title: qsTr("Manage other user accounts")

    QtObject {
        id: privateProperties

        property int filterIndex: 0
        property int sortIndex: 0
        property var filterModel: ["Search by item name", "Search by category name"]
        property var sortModel: ["Sort in ascending order", "Sort in descending order"]
    }

    contentItem: FocusScope {
        focus: true

        RRUi.Card {
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                bottom: parent.bottom
            }

            topPadding: 4
            bottomPadding: 0
            leftPadding: 4
            rightPadding: 4

            width: 800

            contentItem: FocusScope {
                focus: true

                RRUi.SearchBar {
                    id: searchBar
                    focus: true
                    anchors {
                        top: parent.top
                        left: parent.left
                        right: parent.right
                    }
                }

                RRUi.ChipListView {
                    id: filterChipListView
                    height: 30
                    anchors {
                        top: searchBar.bottom
                        left: parent.left
                        right: parent.right
                    }

                    model: [
                        privateProperties.filterModel[privateProperties.filterIndex],
                        privateProperties.sortModel[privateProperties.sortIndex]
                    ]
                }

                UserTableView {
                    id: userTableView
                    anchors {
                        top: filterChipListView.bottom
                        left: parent.left
                        right: parent.right
                        bottom: parent.bottom
                        topMargin: 20
                    }

                    filterText: searchBar.text
                    filterColumn: RRModels.SaleTransactionModel.CustomerNameColumn

                    onSuccess: {
                        switch (successCode) {
                        case RRModels.UserModel.RemoveUserSuccess:
                            otherUserAccountPage.RRUi.ApplicationWindow.window.snackBar.show(qsTr("User deleted."), qsTr("Undo"));
                            userTableView.refresh();
                            break;
                        case RRModels.UserModel.UndoRemoveUserSuccess:
                            otherUserAccountPage.RRUi.ApplicationWindow.window.snackBar.show(qsTr("Undo successful"));
                            userTableView.refresh();
                            break;
                        }
                    }

                    onError: {
                        switch (errorCode) {
                        case RRModels.UserModel.InsufficientPrivilegeError:
                            break;
                        }
                    }

                    buttonRow: Row {
                        spacing: 0

                        RRUi.ToolButton {
                            icon.source: FluidControls.Utils.iconUrl("image/remove_red_eye")
                            text: qsTr("View user details")
                        }

                        RRUi.ToolButton {
                            icon.source: FluidControls.Utils.iconUrl("image/edit")
                            text: qsTr("Edit user privileges")
                            onClicked: otherUserAccountPage.push(Qt.resolvedUrl("NewUserPage.qml"), { userId: parent.parent.modelData.user_id });
                        }

                        RRUi.ToolButton {
                            icon.source: FluidControls.Utils.iconUrl("action/delete")
                            text: qsTr("Delete user")
                            onClicked: deleteConfirmationDialog.show(parent.parent.modelData);
                        }
                    }
                }

                RRUi.FloatingActionButton {
                    anchors {
                        right: parent.right
                        bottom: parent.bottom
                        margins: 24
                    }

                    icon.source: FluidControls.Utils.iconUrl("content/add")
                    text: qsTr("Add user")
                    onClicked: otherUserAccountPage.push(Qt.resolvedUrl("NewUserPage.qml"));
                }

                FluidControls.BottomSheetList {
                    id: bottomSheet
                    title: qsTr("What would you like to do?")

                    actions: [
                        FluidControls.Action {
                            icon.source: FluidControls.Utils.iconUrl("content/add")
                            text: qsTr("Add user.")
                        },

                        FluidControls.Action {
                            icon.source: FluidControls.Utils.iconUrl("image/edit")
                            text: qsTr("Manage income transactions.")
                        }
                    ]
                }
            }
        }

        RRUi.AlertDialog {
            id: deleteConfirmationDialog

            property var modelData: null

            width: 300
            text: qsTr("Are you sure you want to remove this user?");
            standardButtons: RRUi.AlertDialog.Yes | RRUi.AlertDialog.No
            onAccepted: {
                userTableView.removeUser(modelData.user);
                deleteConfirmationDialog.modelData = null;
            }

            function show(modelData) {
                if (Object(modelData).hasOwnProperty("user")) {
                    text = qsTr("Are you sure you want to delete \"<b>%1</b>\" from the list?").arg(modelData.user);
                    deleteConfirmationDialog.modelData = modelData;
                    open();
                }
            }
        }

        //UserDetailDialog { id: userDetailDialog }
    }

    QQC2.StackView.onActivating: {
        searchBar.clear();
        userTableView.refresh();
    }
}
