#ifndef QMLPURCHASEREPORTMODEL_H
#define QMLPURCHASEREPORTMODEL_H

#include "models/abstractreportmodel.h"
#include "utility/purchase/purchasereporttransaction.h"

class QMLPurchaseReportModel : public AbstractReportModel
{
    Q_OBJECT
public:
    enum Roles
    {
        CategoryRole = Qt::UserRole,
        ProductRole,
        QuantityBoughtRole,
        TotalExpenditureRole,
        UnitRole
    };

    enum Columns
    {
        CategoryColumn,
        ProductColumn,
        QuantityBoughtColumn,
        TotalAmountColumn,
        ColumnCount
    };
    Q_ENUM(Columns)

    explicit QMLPurchaseReportModel(QObject* parent = nullptr);
    explicit QMLPurchaseReportModel(DatabaseThread& thread,
                                    QObject* parent = nullptr);

    QVariant data(const QModelIndex& index,
                  int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

protected:
    void tryQuery() override;
    bool canProcessResult(const QueryResult& result) const override final;
    void processResult(const QueryResult& result) override final;

private:
    Utility::Purchase::PurchaseReportTransactionList m_transactions;
};

#endif  // QMLPURCHASEREPORTMODEL_H
