#ifndef GNODE_H
#define GNODE_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>

#include "../../entities/graph/include/Node.h"
#include "../../entities/data/include/NodeAttr.h"
#include "nodeguiattr.h"

struct GNode : public QWidget{
    Node* m_node;
    NodeAttr* m_attr;
    NodeGuiAttr* m_gui;

    QLabel* m_imageLabel;
    QLabel* m_quantityLabel;
    QVBoxLayout* m_mainLayout;
    QVBoxLayout* m_imageLayout;

    GNode(Node* node, NodeGuiAttr* gui, QWidget* parent=0) : QWidget(parent){
        setMouseTracking(true);

        m_node = node;
        m_gui = gui;
        m_attr = (NodeAttr*) m_node->getData();
        m_gui = m_gui;

        createView();
        updateImage();
        updateData();
        updatePos();
    }

    virtual ~GNode(){
        delete m_imageLayout;
        delete m_mainLayout;
        delete m_quantityLabel;
        delete m_imageLabel;
    }

    void createView(){
        m_imageLayout = new QVBoxLayout;
        m_mainLayout = new QVBoxLayout;
        m_quantityLabel = new QLabel;
        m_imageLabel = new QLabel;

        m_imageLabel->setScaledContents(true);
        m_imageLayout->addWidget(m_imageLabel);

//        m_mainLayout->addWidget(m_quantityLabel);
        m_mainLayout->addLayout(m_imageLayout);
        setLayout(m_mainLayout);
    }

    void updateData(){
        NodeAttr* data = (NodeAttr*) m_node->getData();
        m_quantityLabel->setText(QString::number(data->m_quantity));
    }

    void updateImage(){
        QImage tmp(QString::fromStdString(m_gui->m_imageFilepath));
        QImage img = tmp.scaled(m_gui->m_width, m_gui->m_height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        m_imageLabel->setPixmap(QPixmap::fromImage(img));
        resize(m_gui->m_width, m_gui->m_height);
    }

    void updatePos(){
        move(m_gui->m_x, m_gui->m_y);
    }
};

#endif // GNODE_H
