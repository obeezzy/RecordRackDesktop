#include "mockdatabasethread.h"
#include "qmlapi/qmlmostsoldproductmodel.h"
#include <QtTest>
#include <QCoreApplication>

class QMLMostSoldProductModelTest : public QObject
{
    Q_OBJECT
public:
    QMLMostSoldProductModelTest() = default;
private slots:
    void init();
    void cleanup();
    void testViewMostSoldProducts();
    void testError();
private:
    QMLMostSoldProductModel *m_mostSoldProductModel;
    MockDatabaseThread *m_thread;
    QueryResult m_result;
};

void QMLMostSoldProductModelTest::init()
{
    m_thread = new MockDatabaseThread(&m_result, this);
    m_mostSoldProductModel = new QMLMostSoldProductModel(*m_thread, this);
}

void QMLMostSoldProductModelTest::cleanup()
{
    m_mostSoldProductModel->deleteLater();
    m_thread->deleteLater();
}

void QMLMostSoldProductModelTest::testViewMostSoldProducts()
{
    const QVariantList products {
        QVariantMap {
            { "product_category_id", 1 },
            { "product_category", QStringLiteral("Category1") },
            { "product_id", 1 },
            { "product", QStringLiteral("Product1") },
            { "total_revenue", 2004.42 },
            { "total_quantity", 3 },
            { "product_unit_id", 1 },
            { "product_unit", "product(s)" }
        },
        QVariantMap {
            { "product_category_id", 1 },
            { "product_category", QStringLiteral("Category1") },
            { "product_id", 2 },
            { "product", QStringLiteral("Product2") },
            { "total_revenue", 3567.42 },
            { "total_quantity", 389.4532 },
            { "product_unit_id", 1 },
            { "product_unit", "product(s)" }
        },
        QVariantMap {
            { "product_category_id", 2 },
            { "product_category", QStringLiteral("Category2") },
            { "product_id", 3 },
            { "product", QStringLiteral("Product3") },
            { "total_revenue", 3455.42 },
            { "total_quantity", 3334 },
            { "product_unit_id", 1 },
            { "product_unit", "product(s)" }
        }
    };
    auto databaseWillReturn = [this](const QVariantList &products) {
        m_result.setSuccessful(true);
        m_result.setOutcome(QVariantMap { { "products", products } });
    };
    QSignalSpy busyChangedSpy(m_mostSoldProductModel, &QMLMostSoldProductModel::busyChanged);
    QSignalSpy errorSpy(m_mostSoldProductModel, &QMLMostSoldProductModel::error);
    QSignalSpy successSpy(m_mostSoldProductModel, &QMLMostSoldProductModel::success);

    QCOMPARE(m_mostSoldProductModel->rowCount(), 0);

    databaseWillReturn(products);

    m_mostSoldProductModel->componentComplete();
    QCOMPARE(m_mostSoldProductModel->rowCount(), 3);
    QCOMPARE(m_mostSoldProductModel->columnCount(), 3);
    QCOMPARE(busyChangedSpy.count(), 2);
    QCOMPARE(errorSpy.count(), 0);
    QCOMPARE(successSpy.count(), 1);

    enum Roles {
        ProductCategoryIdRole = Qt::UserRole,
        ProductCategoryRole,
        ProductIdRole,
        ProductRole,
        TotalRevenueRole,
        TotalQuantityRole,
        UnitIdRole,
        UnitRole
    };

    enum Columns {
        ProductColumn,
        TotalQuantityColumn,
        TotalRevenueColumn,
        ColumnCount
    };

    QCOMPARE(products.count(), 3);
    // Rows with columns
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(0, QMLMostSoldProductModel::ProductColumn),
                                          Qt::DisplayRole).toString(),
             products[0].toMap()["product"].toString());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(0, QMLMostSoldProductModel::TotalQuantityColumn),
                                          Qt::DisplayRole).toDouble(),
             products[0].toMap()["total_quantity"].toDouble());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(0, QMLMostSoldProductModel::TotalRevenueColumn),
                                          Qt::DisplayRole).toDouble(),
             products[0].toMap()["total_revenue"].toDouble());

    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(1, QMLMostSoldProductModel::ProductColumn),
                                          Qt::DisplayRole).toString(),
             products[1].toMap()["product"].toString());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(1, QMLMostSoldProductModel::TotalQuantityColumn),
                                          Qt::DisplayRole).toDouble(),
             products[1].toMap()["total_quantity"].toDouble());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(1, QMLMostSoldProductModel::TotalRevenueColumn),
                                          Qt::DisplayRole).toDouble(),
             products[1].toMap()["total_revenue"].toDouble());

    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(2, QMLMostSoldProductModel::ProductColumn),
                                          Qt::DisplayRole).toString(),
             products[2].toMap()["product"].toString());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(2, QMLMostSoldProductModel::TotalQuantityColumn),
                                          Qt::DisplayRole).toDouble(),
             products[2].toMap()["total_quantity"].toDouble());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(2, QMLMostSoldProductModel::TotalRevenueColumn),
                                          Qt::DisplayRole).toDouble(),
             products[2].toMap()["total_revenue"].toDouble());

    // All rows
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(0, 0),
                                          QMLMostSoldProductModel::ProductCategoryIdRole).toInt(),
             products[0].toMap()["product_category_id"].toInt());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(0, 0),
                                          QMLMostSoldProductModel::ProductCategoryRole).toString(),
             products[0].toMap()["product_category"].toString());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(0, 0),
                                          QMLMostSoldProductModel::ProductIdRole).toInt(),
             products[0].toMap()["product_id"].toInt());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(0, 0),
                                          QMLMostSoldProductModel::ProductRole).toString(),
             products[0].toMap()["product"].toString());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(0, 0),
                                          QMLMostSoldProductModel::TotalRevenueRole).toDouble(),
             products[0].toMap()["total_revenue"].toDouble());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(0, 0),
                                          QMLMostSoldProductModel::TotalQuantityRole).toDouble(),
             products[0].toMap()["total_quantity"].toDouble());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(0, 0),
                                          QMLMostSoldProductModel::ProductUnitIdRole).toInt(),
             products[0].toMap()["product_unit_id"].toInt());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(0, 0),
                                          QMLMostSoldProductModel::ProductUnitRole).toString(),
             products[0].toMap()["product_unit"].toString());

    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(1, 0),
                                          QMLMostSoldProductModel::ProductCategoryIdRole).toInt(),
             products[1].toMap()["product_category_id"].toInt());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(1, 0),
                                          QMLMostSoldProductModel::ProductCategoryRole).toString(),
             products[1].toMap()["product_category"].toString());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(1, 0),
                                          QMLMostSoldProductModel::ProductIdRole).toInt(),
             products[1].toMap()["product_id"].toInt());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(1, 0),
                                          QMLMostSoldProductModel::ProductRole).toString(),
             products[1].toMap()["product"].toString());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(1, 0),
                                          QMLMostSoldProductModel::TotalRevenueRole).toDouble(),
             products[1].toMap()["total_revenue"].toDouble());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(1, 0),
                                          QMLMostSoldProductModel::TotalQuantityRole).toDouble(),
             products[1].toMap()["total_quantity"].toDouble());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(1, 0),
                                          QMLMostSoldProductModel::ProductUnitIdRole).toInt(),
             products[1].toMap()["product_unit_id"].toInt());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(1, 0),
                                          QMLMostSoldProductModel::ProductUnitRole).toString(),
             products[1].toMap()["product_unit"].toString());

    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(2, 0),
                                          QMLMostSoldProductModel::ProductCategoryIdRole).toInt(),
             products[2].toMap()["product_category_id"].toInt());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(2, 0),
                                          QMLMostSoldProductModel::ProductCategoryRole).toString(),
             products[2].toMap()["product_category"].toString());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(2, 0),
                                          QMLMostSoldProductModel::ProductIdRole).toInt(),
             products[2].toMap()["product_id"].toInt());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(2, 0),
                                          QMLMostSoldProductModel::ProductRole).toString(),
             products[2].toMap()["product"].toString());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(2, 0),
                                          QMLMostSoldProductModel::TotalRevenueRole).toDouble(),
             products[2].toMap()["total_revenue"].toDouble());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(2, 0),
                                          QMLMostSoldProductModel::TotalQuantityRole).toDouble(),
             products[2].toMap()["total_quantity"].toDouble());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(2, 0),
                                          QMLMostSoldProductModel::ProductUnitIdRole).toInt(),
             products[2].toMap()["product_unit_id"].toInt());
    QCOMPARE(m_mostSoldProductModel->data(m_mostSoldProductModel->index(2, 0),
                                          QMLMostSoldProductModel::ProductUnitRole).toString(),
             products[2].toMap()["product_unit"].toString());
}

void QMLMostSoldProductModelTest::testError()
{
    auto databaseWillReturnError = [this]() {
        m_result.setSuccessful(false);
    };
    QSignalSpy busyChangedSpy(m_mostSoldProductModel, &QMLMostSoldProductModel::busyChanged);
    QSignalSpy errorSpy(m_mostSoldProductModel, &QMLMostSoldProductModel::error);
    QSignalSpy successSpy(m_mostSoldProductModel, &QMLMostSoldProductModel::success);

    QCOMPARE(m_mostSoldProductModel->rowCount(), 0);

    databaseWillReturnError();

    m_mostSoldProductModel->componentComplete();
    QCOMPARE(m_mostSoldProductModel->rowCount(), 0);
    QCOMPARE(busyChangedSpy.count(), 2);
    QCOMPARE(errorSpy.count(), 1);
    QCOMPARE(successSpy.count(), 0);
}

QTEST_MAIN(QMLMostSoldProductModelTest)

#include "tst_qmlmostsoldproductmodeltest.moc"
