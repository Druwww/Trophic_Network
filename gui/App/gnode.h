#ifndef GNODE_H
#define GNODE_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QPainter>

#include "../../entities/graph/include/Node.h"
#include "../../entities/data/include/NodeAttr.h"
#include "nodeguiattr.h"

struct GNode : public QWidget{
    Node* m_node;
    NodeAttr* m_attr;
    NodeGuiAttr* m_gui;

    QPixmap* m_image;

    GNode(Node* node, NodeGuiAttr* gui, QWidget* parent=0) : QWidget(parent){
        setMouseTracking(true);

        m_node = node;
        m_gui = gui;
        m_attr = (NodeAttr*) m_node->getData();
        m_attr->m_gui = m_gui;

        m_image = new QPixmap;

        updateImage();
        updatePos();
    }

    virtual ~GNode(){
        delete m_image;
    }

    void painEvent(QPainter& painter){
        int margin = 6;
        QString str = "Q = "+QString::number(m_attr->m_quantity)
                + " | BR = "+QString::number(m_attr->m_birthRate);
        painter.setPen(QPen(Qt::blue, 3, Qt::SolidLine, Qt::RoundCap));
        painter.drawText(m_gui->m_x, m_gui->m_y-margin, str);
        painter.drawPixmap(m_gui->m_x, m_gui->m_y, m_gui->m_width, m_gui->m_height, *m_image);
    }

    void updateImage(){
        m_image->load(QString::fromStdString(m_gui->m_imageFilepath));
        *m_image = m_image->scaled(m_gui->m_width, m_gui->m_height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        resize(m_gui->m_width, m_gui->m_height);
    }

    void updatePos(){
        move(m_gui->m_x, m_gui->m_y);
    }
};

#endif // GNODE_H
