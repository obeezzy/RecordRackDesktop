#include "qmlapi/qmlincomereportmodel.h"
#include "mockdatabasethread.h"
#include <QtTest>
#include <QCoreApplication>

class QMLIncomeReportModelTest : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void cleanup();
    void testModel();
private:
    QMLIncomeReportModel *m_incomeReportModel;
    MockDatabaseThread *m_thread;
    QueryResult m_result;
};

void QMLIncomeReportModelTest::init()
{
    m_thread = new MockDatabaseThread(this);
    m_incomeReportModel = new QMLIncomeReportModel(*m_thread, this);
}

void QMLIncomeReportModelTest::cleanup()
{
    m_incomeReportModel->deleteLater();
    m_thread->deleteLater();
}

void QMLIncomeReportModelTest::testModel()
{
    QAbstractItemModelTester(m_incomeReportModel,
                             QAbstractItemModelTester::FailureReportingMode::Fatal,
                             this);
}

QTEST_MAIN(QMLIncomeReportModelTest)

#include "tst_qmlincomereportmodeltest.moc"
