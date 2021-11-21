#include "scene.h"
#include <assert.h>
Scene::Scene(const QPen & pen, const uint32_t & gridSize, QObject* parent): QGraphicsScene(parent)
{
    m_pen = pen;
    m_gridSize = gridSize;
}

void Scene::drawBackground(QPainter * painter, const QRectF & rect)
{
    assert(painter);

    painter->setPen(m_pen);
    painter->setBrush(Qt::yellow);

    int left = int(rect.left()) - (int(rect.left()) % m_gridSize);
    int top = int(rect.top()) - (int(rect.top()) % m_gridSize);

    QVector<QPointF> points;
    for (int x = left; x < rect.right(); x += m_gridSize)
    {
        for(int y = top; y < rect.bottom(); y += m_gridSize)
        {
            points.append(QPointF(x,y));
        }
    }

    painter->drawPoints(points.data(), points.size());
}

const uint32_t Scene::getGridSize()
{
    return m_gridSize;
}
