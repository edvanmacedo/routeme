#include "routememap.h"
#include "serviceprovider.h"

RouteMeMap::RouteMeMap(QDeclarativeItem *parent)
    : QDeclarativeItem(parent)
    , m_map(0)
    , m_mapManager(0)
    , m_zoomLevel(0)
    , m_coordinate(0)
    , m_route(0)
{
    init();
}

RouteMeMap::~RouteMeMap()
{
    m_mapManager->deleteLater();
}

void RouteMeMap::init()
{
    m_mapManager = ServiceProvider::instance()->mappingManager();
    m_map = new QGraphicsGeoMap(m_mapManager, this);
}

RouteMeCoordinate* RouteMeMap::coordinate()
{
    return m_coordinate;
}

void RouteMeMap::setCoordinate(RouteMeCoordinate *coordinate)
{
    m_coordinate = coordinate;
    QGeoCoordinate center = m_map->center();
    center.setLatitude(m_coordinate->latitude());
    center.setLongitude(m_coordinate->longitude());

    m_map->setCenter(center);

    emit coordinateChanged();
}

void RouteMeMap::setZoomLevel(qreal zoom)
{
    if (zoom < 0)
        return;

    if (zoom == m_zoomLevel)
        return;

    m_zoomLevel = zoom;

    m_map->setZoomLevel(m_zoomLevel);

    emit zoomLevelChanged();
}

void RouteMeMap::setProviderName(const QString &providerName)
{
    if (providerName.isEmpty())
        return;

    if (providerName == m_providerName)
        return;

    m_providerName = providerName;

    emit providerNameChanged();
}

void RouteMeMap::componentComplete()
{
    m_map->setGeometry(0, 0, boundingRect().width(), boundingRect().height());
}

RouteMeRouteMapObject* RouteMeMap::route()
{
    return m_route;
}

void RouteMeMap::setRoute(RouteMeRouteMapObject *route)
{
    m_route = route;
    m_map->addMapObject(m_route->geoMapRouteObject());
    emit routeChanged();
}

void RouteMeMap::setCurrentPixmapLocation(RouteMePixmapObject *pixmap)
{
    m_currentPixmapLocation = pixmap;
    m_map->addMapObject(m_currentPixmapLocation->pixmapObject());
    emit currentPixmapLocationChanged();
}

void RouteMeMap::pan(int dx, int dy)
{
    m_map->pan(dx, dy);
}

RouteMeCoordinate* RouteMeMap::screenPositionToCoordinate(const QPoint &point)
{
    QPointF pointf(point);
    QGeoCoordinate coord = m_map->screenPositionToCoordinate(pointf);
    RouteMeCoordinate *coordinate = new RouteMeCoordinate(this);
    coordinate->setLatitude(coord.latitude());
    coordinate->setLongitude(coord.longitude());

    return coordinate;
}
