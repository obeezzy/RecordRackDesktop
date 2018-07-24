#include "abstractdetailrecord.h"
#include "database/databasethread.h"

AbstractDetailRecord::AbstractDetailRecord(QObject *parent) :
    QObject(parent),
    m_autoQuery(true),
    m_busy(false)
{
    connect(this, &AbstractDetailRecord::executeRequest, &DatabaseThread::instance(), &DatabaseThread::execute);
    connect(&DatabaseThread::instance(), &DatabaseThread::resultReady, this, &AbstractDetailRecord::processResult);
}

AbstractDetailRecord::~AbstractDetailRecord()
{

}

bool AbstractDetailRecord::autoQuery() const
{
    return m_autoQuery;
}

void AbstractDetailRecord::setAutoQuery(bool autoQuery)
{
    if (m_autoQuery == autoQuery)
        return;

    m_autoQuery = autoQuery;
    emit autoQueryChanged();
}

bool AbstractDetailRecord::isBusy() const
{
    return m_busy;
}

void AbstractDetailRecord::classBegin()
{

}

void AbstractDetailRecord::componentComplete()
{
    if (m_autoQuery)
        tryQuery();
}

void AbstractDetailRecord::setBusy(bool busy)
{
    if (m_busy == busy)
        return;

    m_busy = busy;
    emit busyChanged();
}