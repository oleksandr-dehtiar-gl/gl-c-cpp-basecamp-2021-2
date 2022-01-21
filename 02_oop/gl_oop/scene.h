#ifndef SCENE_H
#define SCENE_H


#include <QGraphicsScene>
#include <QPainter>
#include <QPen>
#include <QObject>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(const QPen & pen, const uint32_t & gridSize = 8, QObject* parent = nullptr);
    void drawBackground(QPainter * painter, const QRectF & rect) override;
    const uint32_t getGridSize();
private:
    QPen m_pen;
    uint32_t m_gridSize;


};

#endif // SCENE_H
