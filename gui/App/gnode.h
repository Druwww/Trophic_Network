#ifndef GNODE_H
#define GNODE_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QPainter>
#include <QList>

#include "../../entities/graph/include/Node.h"
#include "../../entities/data/include/NodeAttr.h"
#include "nodeguiattr.h"

/**
 * @brief Version graphique d'un Node
 */
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

    /**
     * @brief Dessine l'objet et ses paramètres à l'écran
     * @param painter
     */
    void painEvent(QPainter& painter){
        int margin = 6;
        QString str = "Q = "+QString::number(m_attr->m_quantity)
                + " | BR = "+QString::number(m_attr->m_birthRate);

        enableUnderline(painter, false);
        painter.setOpacity(m_attr->m_quantity==0?0.2:1);
        painter.setPen(QPen(Qt::blue, 3, Qt::SolidLine, Qt::RoundCap));
        painter.drawText(m_gui->m_x, m_gui->m_y-margin, str);
        painter.drawPixmap(m_gui->m_x, m_gui->m_y, m_gui->m_width, m_gui->m_height, *m_image);

        int group = m_node->getGroup();
        if(group>0){
            QString str = QString::number(group);
            enableUnderline(painter, true);
            painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
            painter.drawText(m_gui->m_x+m_gui->m_width+margin, m_gui->m_y+m_gui->m_height+margin, str);
        }
        else if(m_node->isProcessed()){
            painter.setPen(QPen(Qt::blue, 2, Qt::DotLine, Qt::RoundCap));
            painter.drawRect(m_gui->m_x, m_gui->m_y, m_gui->m_width, m_gui->m_height);
        }
    }

    /**
     * @brief Met à jour l'image du sommet
     */
    void updateImage(){
        m_image->load(QString::fromStdString(m_gui->m_imageFilepath));
        *m_image = m_image->scaled(m_gui->m_width, m_gui->m_height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        resize(m_gui->m_width, m_gui->m_height);
    }

    /**
     * @brief Met à jour la position du sommet
     */
    void updatePos(){
        move(m_gui->m_x, m_gui->m_y);
    }

    /**
     * @brief Active l'option de soulignage de texte
     * @param painter
     * @param enabled
     */
    void enableUnderline(QPainter& painter, const bool& enabled){
        QFont f = font();
        f.setUnderline(enabled);
        painter.setFont(f);
    }
};

#endif // GNODE_H
