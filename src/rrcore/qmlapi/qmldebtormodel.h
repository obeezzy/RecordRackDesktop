#ifndef QMLDEBTORMODEL_H
#define QMLDEBTORMODEL_H

#include <QObject>
#include <QVariantList>
#include "models/abstractvisuallistmodel.h"

class QMLDebtorModel : public AbstractVisualListModel
{
    Q_OBJECT
public:
    enum SuccessCodes {
        DebtorsFetched = 1,
        UndoDebtorRemoved,
        DebtorRemoved
    }; Q_ENUM(SuccessCodes)

    enum ErrorCodes {
        InvalidDebtor = 1
    }; Q_ENUM(ErrorCodes)

    enum Roles {
        ClientIdRole = Qt::UserRole,
        DebtorIdRole,
        ImageSourceRole,
        PreferredNameRole,
        TotalDebtRole,
        NoteRole,
        CreatedRole,
        LastEditedRole,
        UserRole
    };

    enum Column {
        PreferredNameColumn, TotalDebtColumn
    }; Q_ENUM(Column)

    explicit QMLDebtorModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override final;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override final;
    QHash<int, QByteArray> roleNames() const override final;

protected:
    void tryQuery() override final;
    void processResult(const QueryResult result) override final;
    void filter() override final;
public slots:
    void refresh();
    void removeDebtor(int debtorId);
private:
    QVariantList m_records;

    int debtorRowFromId(int debtorId);

    void removeItemFromModel(int debtorId);
    void undoRemoveItemFromModel(int row, int debtorId, const QVariantMap &debtorInfo);
};

#endif // QMLDEBTORMODEL_H
