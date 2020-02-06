import QtQuick 2.12
import QtQuick.Controls 2.12 as QQC2
import QtQuick.Controls.Material 2.3
import "../singletons"
import Fluid.Controls 1.0 as FluidControls
import "../rrui" as RRUi
import com.gecko.rr.models 1.0 as RRModels

ListView {
    id: cartListView

    readonly property bool busy: model.busy
    property alias customerName: purchaseCartModel.customerName
    property alias customerPhoneNumber: purchaseCartModel.customerPhoneNumber
    property alias transactionId: purchaseCartModel.transactionId
    property alias note: purchaseCartModel.note
    readonly property real totalCost: model.totalCost
    property real amountPaid: model.amountPaid

    signal viewRequested(int productId)
    signal editRequested(var product)
    signal success(int successCode)
    signal error(int errorCode)

    function addProduct(product) { cartListView.model.addProduct(product); }
    function submitTransaction(payment) { cartListView.model.submitTransaction(payment); }
    function suspendTransaction(params) { cartListView.model.suspendTransaction(params); }
    function undoLastTransaction() { cartListView.model.undoLastCommit(); }
    function clearAll() { cartListView.model.clearAll(); }
    function updateItem(productId, product) { cartListView.model.updateItem(productId, product); }
    function addPayment(amount, method) { cartListView.model.addPayment(amount, method); }
    function clearPayments() { cartListView.model.clearPayments(); }

    spacing: 10
    clip: true

    topMargin: 4
    bottomMargin: 10

    model: RRModels.PurchaseCartModel {
        id: purchaseCartModel
        onSuccess: cartListView.success(successCode);
        onError: cartListView.error(errorCode);
    }

    delegate: Item {
        width: ListView.view.width
        height: delegateColumn.height + quantitySpinBox.height + 10

        Column {
            id: delegateColumn
            anchors {
                left: parent.left
                top: parent.top
            }

            spacing: 2

            FluidControls.HeadlineLabel {
                text: product
            }

            FluidControls.SubheadingLabel {
                text: "From <i>" + category + "</i><br/>"
                      + available_quantity + " "
                      + unit + " left<br/>Costs "
                      + Number(unit_price).toLocaleCurrencyString(Qt.locale(GlobalSettings.currencyLocaleName)) + " each"
            }
        }

        Row {
            spacing: 0
            anchors {
                right: parent.right
                top: parent.top
            }

            RRUi.ToolButton {
                id: viewButton
                icon.source: FluidControls.Utils.iconUrl("image/remove_red_eye")
                text: qsTr("View details")
                onClicked: cartListView.viewRequested(product_id);
            }

            RRUi.ToolButton {
                id: editButton
                icon.source: FluidControls.Utils.iconUrl("image/edit")
                text: qsTr("Edit ")
                onClicked: cartListView.editRequested({ "product_index": index,
                                                          "product_id": product_id,
                                                          "product": product,
                                                          "quantity": quantity,
                                                          "unit_price": unit_price,
                                                          "cost": cost,
                                                          "available_quantity": available_quantity,
                                                          "unit": unit });
            }

            RRUi.ToolButton {
                id: deleteButton
                icon.source: FluidControls.Utils.iconUrl("action/delete")
                text: qsTr("Delete product")
                onClicked: cartListView.model.removeItem(product_id);
            }
        }

        FluidControls.SubheadingLabel {
            anchors {
                right: parent.right
                bottom: parent.bottom
            }

            text: Number(cost).toLocaleCurrencyString(Qt.locale("en_NG"))
        }

        RRUi.QuantitySpinBox {
            id: quantitySpinBox
            quantity: model.quantity
            maximumQuantity: 100000000
            unit: model.unit
            anchors {
                bottomMargin: 4
                bottom: parent.bottom
            }

            onQuantityUpdated: cartListView.model.setItemQuantity(model.product_id, newQuantity);
        }

        Rectangle {
            anchors {
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
            color: "lightgray"
            height: 1
            visible: index < cartListView.count - 1
        }
    }

    FluidControls.Placeholder {
        anchors.centerIn: parent
        visible: cartListView.count == 0
        icon.source: Qt.resolvedUrl("qrc:/icons/cart-outline.svg")
        text: qsTr("Your cart is empty.\nAdd items from the view in the left to get started.");
    }
}
