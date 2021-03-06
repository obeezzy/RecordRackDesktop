#include "viewpurchasehome.h"
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "database/databaseexception.h"
#include "utility/common/datetimespan.h"

using namespace Query::Purchase;

ViewPurchaseHome::ViewPurchaseHome(const Utility::DateTimeSpan& dateTimeSpan,
                                   QObject* receiver)
    : PurchaseExecutor(
          COMMAND,
          {{"from", dateTimeSpan.from}, {"to", dateTimeSpan.to}, {"limit", 5}},
          receiver)
{}

QueryResult ViewPurchaseHome::execute()
{
    QueryResult result{request()};
    result.setSuccessful(true);

    QSqlDatabase connection = QSqlDatabase::database(connectionName());
    QSqlQuery q(connection);
    QVariantList homeRecords;

    try {
        fetchLastPurchasedProducts(homeRecords);

        result.setOutcome(QVariantMap{{"records", homeRecords},
                                      {"record_count", homeRecords.count()}});
        return result;
    } catch (const DatabaseException&) {
        throw;
    }
}

void ViewPurchaseHome::fetchLastPurchasedProducts(QVariantList& homeRecords)
{
    const QVariantMap& params = request().params();

    const QList<QSqlRecord>& records(
        callProcedure("FetchLastPurchasedProducts",
                      {ProcedureArgument{ProcedureArgument::Type::In, "from",
                                         params.value("from")},
                       ProcedureArgument{ProcedureArgument::Type::In, "to",
                                         params.value("to")},
                       ProcedureArgument{ProcedureArgument::Type::In, "limit",
                                         params.value("limit")}}));

    QVariantList lastPurchasedProducts;
    for (const auto& record : records)
        lastPurchasedProducts.append(recordToMap(record));

    QVariantMap lastPurchasedProductsInfo;
    lastPurchasedProductsInfo.insert("chart_type", "last_purchased_products");
    lastPurchasedProductsInfo.insert("chart_model", lastPurchasedProductsInfo);

    if (!lastPurchasedProducts.isEmpty())
        homeRecords.append(lastPurchasedProducts);
}
