#ifndef ROUTEMEPIXMAPOBJECT_H
#define ROUTEMEPIXMAPOBJECT_H

#include <QtCore/QObject>
#include <QtCore/QPoint>

#include "routemecoordinate.h"

#include <qgeomappixmapobject.h>

using namespace QtMobility;

class RouteMePixmapObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(RouteMeCoordinate* coordinate READ coordinate WRITE setCoordinate NOTIFY coordinateChanged)
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(int offsetX READ offsetX WRITE setOffsetX NOTIFY offsetXChanged)
    Q_PROPERTY(int offsetY READ offsetY WRITE setOffsetY NOTIFY offsetYChanged)

public:
    RouteMePixmapObject(QObject *parent = 0);
    ~RouteMePixmapObject();

    RouteMeCoordinate* coordinate();
    void setCoordinate(RouteMeCoordinate* coordinate);

    QString source() const;
    void setSource(const QString &source);

    int offsetX();
    void setOffsetX(int offsetX);

    int offsetY();
    void setOffsetY(int offsetY);

    QGeoMapPixmapObject* pixmapObject() { return m_pixmapObject; }

signals:
    void coordinateChanged();
    void sourceChanged();
    void offsetXChanged();
    void offsetYChanged();

private:
    QGeoMapPixmapObject *m_pixmapObject;
    QString m_source;
    QPoint m_offset;
};

#endif
