#ifndef GNODE_H
#define GNODE_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>

#include "../../entities/graph/include/Node.h"
#include "nodeguiattr.h"

struct GNode : public QWidget{
    Node *m_node;
    QLabel *m_label;
    QVBoxLayout *m_layout;
    NodeGuiAttr* m_attr;

    GNode(Node* node, NodeGuiAttr* attr, QWidget* parent=0) : QWidget(parent){
        setMouseTracking(true);

        m_node = node;
        m_attr = attr;
        m_layout = new QVBoxLayout();
        m_label = new QLabel(this);
        m_label->setScaledContents(true);
        m_layout->addWidget(m_label);
        setLayout(m_layout);

        update();
    }

    virtual ~GNode(){
        delete m_label;
        delete m_layout;
    }

    void update(){
        QImage tmp(QString::fromStdString(m_attr->m_imageFilepath));
        QImage img = tmp.scaled(m_attr->m_width, m_attr->m_width, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        m_label->setPixmap(QPixmap::fromImage(img));
        resize(m_attr->m_width, m_attr->m_height);
        move(m_attr->m_x, m_attr->m_y);
    }
};

#endif // GNODE_H
