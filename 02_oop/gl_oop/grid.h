#ifndef GRID_H
#define GRID_H

#include <QObject>
#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <memory>


class Grid : public QObject
{
    Q_OBJECT
public:
    explicit Grid(const uint32_t& pixmapWidth, QObject* parent = nullptr);
    void setPixmapWidth(const uint32_t& pixmapWidth);
    const QPixmap & getDrawPattern();

private:


    std::unique_ptr<QPixmap> m_pixmap;
    std::unique_ptr<QPainter> m_painter;
};

#endif // GRID_H
