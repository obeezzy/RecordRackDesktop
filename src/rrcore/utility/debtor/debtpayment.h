#ifndef DEBTPAYMENT_H
#define DEBTPAYMENT_H

#include <QDateTime>
#include <QDebug>
#include <QString>
#include <QVariantList>
#include "debtormonies.h"
#include "singletons/settings.h"
#include "utility/common/note.h"
#include "utility/common/recordgroup.h"
#include "utility/common/recordtimestamp.h"

namespace Utility {
namespace Debtor {
struct DebtPayment
{
private:
    Q_GADGET
public:
    enum class State
    {
        Clean,
        Dirty,
        Fresh,
        Trash
    };
    Q_ENUM(State)
    int id{0};
    int debtTransactionId{0};
    DebtorMonies monies;
    QDateTime dueDateTime;
    RecordGroup::Flags flags;
    Note note;
    RecordTimestamp timestamp;
    State state{State::Fresh};
    static int temporaryId;

    explicit DebtPayment(const DebtorMonies& monies,
                         const QDateTime& dueDateTime,
                         const Note& note = Note());
    explicit DebtPayment(int id, const DebtorMonies& monies,
                         const QDateTime& dueDateTime,
                         const RecordGroup::Flags& flags, State state,
                         const Note& note = Note());

    explicit DebtPayment(const QVariantMap& map);
    QVariantMap toVariantMap() const;

    bool operator==(const DebtPayment& other) { return id == other.id; }

    friend QDebug operator<<(QDebug debug, const DebtPayment& debtPayment)
    {
        debug.nospace() << "DebtPayment("
                        << "id=" << debtPayment.id
                        << ", debt=" << debtPayment.monies.debt
                        << ", amountPaid=" << debtPayment.monies.amountPaid
                        << ", balance=" << debtPayment.monies.balance
                        << ", state=" << debtPayment.state << ")";

        return debug.nospace();
    }
};

class DebtPaymentList : public QList<DebtPayment>
{
public:
    explicit DebtPaymentList() = default;
    explicit DebtPaymentList(std::initializer_list<DebtPayment> payments)
        : QList<DebtPayment>(payments)
    {}
    explicit DebtPaymentList(const QVariantList& list) : QList<DebtPayment>()
    {
        for (const auto& variant : list)
            append(DebtPayment{variant.toMap()});
    }

    QVariantList toVariantList() const
    {
        QVariantList list;
        for (const auto& payment : *this)
            list.append(payment.toVariantMap());
        return list;
    }
};
}  // namespace Debtor
}  // namespace Utility
Q_DECLARE_TYPEINFO(Utility::Debtor::DebtPayment, Q_PRIMITIVE_TYPE);

#endif  // DEBTPAYMENT_H
