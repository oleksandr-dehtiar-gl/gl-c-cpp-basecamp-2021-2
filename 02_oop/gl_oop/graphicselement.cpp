#include "graphicselement.h"
#include "scene.h"
#include <QApplication>
#include <QtMath>
GraphicsElement::GraphicsElement(QGraphicsItem* parent) : QGraphicsObject(parent)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsGeometryChanges);
    m_pixmap.reset(new QPixmap(64, 64));

}
GraphicsElement::~GraphicsElement()
{}

void GraphicsElement::addInputs(Port * input)
{
    if(m_inputs.size() <= 8)
    {

        m_inputs.push_back(input);
        int yPos = 0;
        int step = 0;
        if(m_inputs.size() > 1)
        {
            step = ((64 - (m_inputs.size() * 8)) / (m_inputs.size() - 1)) + 8;
        }

        for(auto ind = 0; ind < m_inputs.size(); ind++)
        {
            m_inputs[ind]->setPos(0, yPos);
            yPos += step;

        }
    }
}

void GraphicsElement::addOutputs(Port * output)
{
    if(m_outputs.empty())
    {
        m_outputs.push_back(output);
    }
}

QVariant GraphicsElement::itemChange(GraphicsItemChange change, const QVariant &value)
{

    if (change == ItemPositionChange && scene()) {
        QPointF newPos = value.toPointF();
        if(QApplication::mouseButtons() == Qt::LeftButton &&
                qobject_cast<Scene*> (scene())){

            int gridSize = qobject_cast<Scene*> (scene())->getGridSize();
            qreal xV = round(newPos.x()/gridSize)*gridSize;
            qreal yV = round(newPos.y()/gridSize)*gridSize;
            return QPointF(xV, yV);
        }
        else
            return newPos;
    }
    else
        return QGraphicsItem::itemChange(change, value);
}

QRectF GraphicsElement::boundingRect() const
{
    return m_pixmap->rect();
}

ElementType GraphicsElement::getType() const
{
    return m_type;
}

void GraphicsElement::setType(ElementType type)
{
    m_type = type;
}




void GraphicsElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    QPainter tempPainter;
    tempPainter.begin(m_pixmap.get());
    tempPainter.setPen(QPen(Qt::black, 2));
    tempPainter.setBrush(Qt::black);
    tempPainter.drawRect(0, 0, m_pixmap->rect().width(), m_pixmap->height());
    tempPainter.setPen(QPen(Qt::white, 2));
    tempPainter.drawText(QRect(m_pixmap->rect()), Qt::AlignCenter, QString(m_type_strs[static_cast<int>(m_type)].c_str()));
    tempPainter.end();
    painter->drawPixmap(QPoint(0,0), *m_pixmap.get());

}
