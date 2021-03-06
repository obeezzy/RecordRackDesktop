#ifndef VIEWPURCHASEREPORT_H
#define VIEWPURCHASEREPORT_H

#include "purchaseexecutor.h"

namespace Utility {
class DateTimeSpan;
}

namespace Query {
namespace Purchase {
class ViewPurchaseReport : public PurchaseExecutor
{
    Q_OBJECT
public:
    static inline const QString COMMAND =
        QStringLiteral("view_purchase_report");

    explicit ViewPurchaseReport(const Utility::DateTimeSpan& dateTimeSpan,
                                QObject* receiver);
    QueryResult execute() override;
};
}  // namespace Purchase
}  // namespace Query

#endif  // VIEWPURCHASEREPORT_H
