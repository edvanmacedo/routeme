#include "routemepositioninfo.h"
#include "serviceprovider.h"

RouteMePositionInfo::RouteMePositionInfo(QObject *parent)
    : QObject(parent)
    , m_infoSourceSatellite(0)
    , m_infoSourceCellId(0)
{
    init();
}

RouteMePositionInfo::~RouteMePositionInfo()
{
}

void RouteMePositionInfo::init()
{
    m_infoSourceSatellite = QGeoPositionInfoSource::createDefaultSource(this);
    if (m_infoSourceSatellite) {
        m_infoSourceSatellite->setPreferredPositioningMethods(QGeoPositionInfoSource::SatellitePositioningMethods);
        connect(m_infoSourceSatellite, SIGNAL(positionUpdated(const QGeoPositionInfo &)),
            this, SLOT(onPositionUpdated(const QGeoPositionInfo &)));
        connect(m_infoSourceSatellite, SIGNAL(updateTimeout()),
                this, SLOT(onUpdateTimeout()));
    }

    m_infoSourceCellId = QGeoPositionInfoSource::createDefaultSource(this);
    if (m_infoSourceCellId) {
        m_infoSourceCellId->setPreferredPositioningMethods(QGeoPositionInfoSource::NonSatellitePositioningMethods);
        connect(m_infoSourceCellId, SIGNAL(positionUpdated(const QGeoPositionInfo &)),
            this, SLOT(onPositionUpdated(const QGeoPositionInfo &)));
        connect(m_infoSourceCellId, SIGNAL(updateTimeoute()),
                this, SLOT(onUpdateTimeout()));
    }

}

void RouteMePositionInfo::onPositionUpdated(const QGeoPositionInfo &info)
{
    if (!info.isValid() || !info.coordinate().isValid())
        return;

    QGeoCoordinate coordinate = info.coordinate();
    m_currentCoordinate.setGeoCoordinate(coordinate);

    emit currentCoordinateAvailable();

    stopUpdates();
}

void RouteMePositionInfo::startUpdates()
{
    if (!m_infoSourceSatellite || !m_infoSourceCellId) {
        //XXX Just to run on Desktop...
        onUpdateTimeout();
        return;
    }


    m_infoSourceSatellite->startUpdates();
    m_infoSourceCellId->startUpdates();
}

void RouteMePositionInfo::stopUpdates()
{
    if (!m_infoSourceSatellite || !m_infoSourceCellId)
        return;

    m_infoSourceSatellite->stopUpdates();
    m_infoSourceCellId->stopUpdates();
}

RouteMeCoordinate* RouteMePositionInfo::currentCoordinate()
{
    return &m_currentCoordinate;
}

void RouteMePositionInfo::onUpdateTimeout()
{
    QGeoCoordinate coordinate;
    coordinate.setLatitude(-3.014554);
    coordinate.setLongitude(-60.029321);
    m_currentCoordinate.setGeoCoordinate(coordinate);

    emit currentCoordinateAvailable();

    stopUpdates();
}
