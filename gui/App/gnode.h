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

        QImage tmp(QString::fromStdString(attr->m_imageFilepath));
        QImage img = tmp.scaled(attr->m_width, attr->m_width, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        m_label->setPixmap(QPixmap::fromImage(img));
        m_layout->addWidget(m_label);
        setLayout(m_layout);
        move(attr->m_x, attr->m_y);
        resize(attr->m_width, attr->m_height);
    }

    virtual ~GNode(){
        delete m_label;
        delete m_layout;
    }

    void update(){
        move(m_attr->m_x, m_attr->m_y);
    }
};

#endif // GNODE_H
