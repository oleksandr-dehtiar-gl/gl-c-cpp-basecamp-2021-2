#include "grid.h"

Grid::Grid(const uint32_t& pixmapWidth, QObject* parent) : QObject(parent)
{
        m_pixmap.reset(new QPixmap(pixmapWidth, pixmapWidth));
        m_painter.reset(new QPainter);
}


void Grid::setPixmapWidth(const uint32_t& pixmapWidth)
{
    *m_pixmap = m_pixmap->scaled(pixmapWidth, pixmapWidth);
}

const QPixmap & Grid::getDrawPattern()
{

    m_pixmap->fill(Qt::transparent);
    m_painter->begin(m_pixmap.get());
    m_painter->setPen(Qt::gray);
    m_painter->setBrush(Qt::gray);

    uint32_t pixmapWidth = m_pixmap->width();

    int pointRadius = 1;
    int diameter = pointRadius * 2;

    m_painter->drawEllipse(-pointRadius, -pointRadius, diameter, diameter);
    m_painter->drawEllipse(pixmapWidth - pointRadius, -pointRadius, diameter, diameter);
    m_painter->drawEllipse(pixmapWidth - pointRadius, pixmapWidth - pointRadius, diameter, diameter);
    m_painter->drawEllipse(-pointRadius, pixmapWidth - pointRadius, diameter, diameter);



    return *m_pixmap;

}
