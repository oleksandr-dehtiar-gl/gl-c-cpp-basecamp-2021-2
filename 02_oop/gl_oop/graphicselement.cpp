#include "graphicselement.h"
#include "scene.h"
#include <QApplication>
#include <QtMath>
#include <QStyleOptionGraphicsItem>
GraphicsElement::GraphicsElement(QGraphicsItem* parent) : QGraphicsObject(parent)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsGeometryChanges);
    m_pixmap.reset(new QPixmap(64, 64));
    setPos(32, 32);


}
GraphicsElement::~GraphicsElement()
{}

void GraphicsElement::addInputs(const int& inputAmount)
{
    if(inputAmount > 0 && inputAmount <= 8)
    {
        if(m_inputs.empty())
        {
            m_inputs.resize(inputAmount);
        }

        int yPos = -4;
        int step = 0;
        if(m_inputs.size() > 1)
        {
            step = ((m_pixmap->height() - (m_inputs.size() * 8)) / (m_inputs.size() - 1)) + 8;
            yPos = -32;
        }

        for(auto ind = 0; ind < inputAmount; ind++)
        {
            InPort * newPort = new InPort(this);
            m_inputs[ind] = newPort;
            m_inputs[ind]->setPos(-32, yPos);
            m_inputs[ind]->update();
            m_inputs[ind]->setIndex(ind);
            yPos += step;
        }
    }

}

void GraphicsElement::addOutput(const int8_t& initial_state)
{
    if(!m_output)
    {
        OutPort * newPort = new OutPort(this, initial_state);
        m_output = newPort;
        m_output->setPos(m_pixmap->width() / 2  + 8, -4);
        m_output->update();
    }
}

std::vector<InPort *>& GraphicsElement::getInputs()
{
    return m_inputs;
}

OutPort* GraphicsElement::getOutputPort()
{
    return m_output;
}


QVariant GraphicsElement::itemChange(GraphicsItemChange change, const QVariant &value)
{

    if (change == ItemPositionChange && scene())
    {
        QPointF newPos = value.toPointF();
        if (qobject_cast<Scene*> (scene()))
        {

            int gridSize = qobject_cast<Scene*> (scene())->getGridSize();
            qreal xV = round(newPos.x()/gridSize)*gridSize;
            qreal yV = round(newPos.y()/gridSize)*gridSize;

            return QPointF(xV, yV);
        }
        else
        {
            return newPos;
        }
    }

    return QGraphicsItem::itemChange(change, value);
}

QRectF GraphicsElement::boundingRect() const
{
    return QRectF(-40,-40,80,80);
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
    painter->setClipRect(option->exposedRect);
    if (isSelected()) {
        painter->setBrush(QColor(0,0,255,127));
        painter->setPen(QPen(Qt::red, 0.5, Qt::SolidLine));
        painter->drawRoundedRect(QRectF(-40,-40,80,80), 5, 5);
    }
    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(QBrush(Qt::white));
    painter->drawRect(-32,-32, 64,64);
    painter->drawText(QRect(-32, -32 ,64,64), Qt::AlignCenter, QString(m_type_strs[static_cast<int>(m_type)].c_str()));
}
