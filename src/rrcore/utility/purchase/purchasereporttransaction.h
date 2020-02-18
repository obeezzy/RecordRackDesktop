#ifndef PURCHASEREPORTTRANSACTION_H
#define PURCHASEREPORTTRANSACTION_H

#include <QVariantList>
#include "utility/stock/stockproductcategory.h"
#include "utility/stock/stockproduct.h"

namespace Utility {
struct PurchaseReportTransaction
{
    StockProductCategory category;
    StockProduct product;
    qreal quantityBought {0.0};
    qreal totalAmount {0.0};

    explicit PurchaseReportTransaction() = default;
    explicit PurchaseReportTransaction(const QVariantMap &map);

    QVariantMap toVariantMap() const;
};

class PurchaseReportTransactionList : public QList<PurchaseReportTransaction>
{
public:
    explicit PurchaseReportTransactionList() = default;
    PurchaseReportTransactionList(std::initializer_list<PurchaseReportTransaction> transactions) :
        QList<PurchaseReportTransaction>(transactions) { }
    explicit PurchaseReportTransactionList(const QVariantList &list) :
        QList<PurchaseReportTransaction>() {
        for (const auto &variant : list)
            append(PurchaseReportTransaction{ variant.toMap() });
    }

    QVariantList toVariantList() const {
        QVariantList list;
        for (const auto &transaction : *this)
            list.append(transaction.toVariantMap());
        return list;
    }
};
}
Q_DECLARE_TYPEINFO(Utility::PurchaseReportTransaction, Q_PRIMITIVE_TYPE);

#endif // PURCHASEREPORTTRANSACTION_H