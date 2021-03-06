import "../common"
import "../rrui" as RRUi
import "../sales"
import Fluid.Controls 1.0 as FluidControls
import Fluid.Core 1.0 as FluidCore
import QtQuick 2.12
import QtQuick.Controls 2.12 as QQC2
import QtQuick.Controls.Material 2.3
import com.gecko.rr.models 1.0 as RRModels

RRUi.SubView {
    id: saleReportSubView

    objectName: "reports/saleReportSubView"

    RRUi.ViewPreferences {
        id: viewPreferences

        filterModel: ["Filter by product", "Filter by category"]
        sortColumnModel: ["Sort by product", "Sort by category"]
    }

    QQC2.BusyIndicator {
        anchors.centerIn: parent
        visible: saleReportTableView.busy
    }

    //********************* ON-DEMAND ITEMS ****************************
    FluidControls.Placeholder {
        visible: saleReportTableView.rows === 0 && searchBar.text !== ""
        anchors.centerIn: parent
        icon.source: FluidControls.Utils.iconUrl("action/search")
        text: qsTr("No results for this search query.")
    }

    FluidControls.Placeholder {
        visible: saleReportTableView.rows === 0 && searchBar.text === ""
        anchors.centerIn: parent
        icon.source: Qt.resolvedUrl("qrc:/icons/coin.svg")
        text: qsTr("No transactions were made on this day.")
    }

    Connections {
        target: saleReportSubView.QQC2.SwipeView.view
        onCurrentIndexChanged: {
            if (saleReportSubView.QQC2.SwipeView.view.currentIndex === saleReportSubView.QQC2.SwipeView.index)
                saleReportTableView.refresh();

        }
    }

    contentItem: FocusScope {
        RRUi.Card {
            anchors.fill: parent
            Material.elevation: 0
            topPadding: 4
            bottomPadding: 0
            leftPadding: 4
            rightPadding: 4

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
                    model: viewPreferences.model

                    anchors {
                        top: searchBar.bottom
                        left: parent.left
                        right: parent.right
                    }

                }

                SaleReportTableView {
                    id: saleReportTableView

                    autoQuery: saleReportSubView.QQC2.SwipeView.index === 0

                    anchors {
                        top: filterChipListView.bottom
                        left: parent.left
                        right: parent.right
                        bottom: parent.bottom
                    }

                }

            }

        }

    }

}
