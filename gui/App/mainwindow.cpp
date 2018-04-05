#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_graph = new Graph();
    m_graph->setOnDestroyNodeData(onDeleteNode);
    m_graph->setOnDestroyVertexData(onDeleteVertex);
    m_graph->setOnSerializeNodeData(onSerializeNode);
    m_graph->setOnSerializeVertexData(onSerializeVertex);
    m_graph->setOnDeserializeNodeData(onDeserializeNode);
    m_graph->setOnDeserializeVertexData(onDeserializeVertex);

    m_selectedNode = nullptr;
    m_drag = false;

    std::string path = "/home/omar/Desktop/Trophic_Network/gui/App/image.png";

    Node* n1 = new Node("Omar");
    Node* n2 = new Node("Fred");
    Node* n3 = new Node("Quentin");

    NodeAttr* an1 = new NodeAttr();
    an1->m_gui = new NodeGuiAttr(path);
    an1->m_gui->m_x = 0;
    an1->m_gui->m_y = 0;
    n1->setData(an1);

    NodeAttr* an2 = new NodeAttr();
    an2->m_gui = new NodeGuiAttr(path);
    an2->m_gui->m_x = 400;
    an2->m_gui->m_y = 300;
    n2->setData(an2);

    NodeAttr* an3 = new NodeAttr();
    an3->m_gui = new NodeGuiAttr(path);
    an3->m_gui->m_x = 800;
    an3->m_gui->m_y = 200;
    n3->setData(an3);

    m_graph->connect(n1, n2);
    m_graph->connect(n3, n2);
    m_graph->connect(n2, n1);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_graph;
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 3, Qt::DashLine, Qt::RoundCap));

    std::vector<Vertex*> vertices = m_graph->getVertices();
    for(const auto& v : vertices){
        Node* start = v->getStartNode();
        NodeAttr* sa = (NodeAttr*) start->getData();
        NodeGuiAttr* sgui = sa->m_gui;

        Node* end = v->getEndNode();
        NodeAttr* ea = (NodeAttr*) end->getData();
        NodeGuiAttr* egui = ea->m_gui;

        GNode *sgnode = getGNode(start);
        if(sgnode==nullptr){
            sgnode = new GNode(start, sgui, this);
            m_gnodes.push_back(sgnode);
        }

        GNode *egnode = getGNode(end);
        if(egnode==nullptr){
            egnode = new GNode(end, egui, this);
            m_gnodes.push_back(egnode);
        }

        sgnode->show();
        egnode->show();
        painter.drawLine(sgui->m_x+sgui->m_width/2, sgui->m_y+sgui->m_height/2,
            egui->m_x+egui->m_width/2, egui->m_y+egui->m_height/2);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        for(const auto& gnode : m_gnodes){
            if(gnode->geometry().contains(event->pos())) {
                m_selectedNode = gnode;
                m_nodePos = QPoint(gnode->pos().x(), gnode->pos().y());
                m_mousePos = QPoint(event->pos().x(), event->pos().y());
                m_drag = true;
                break;
            }
        }

    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        for(const auto& gnode : m_gnodes){
            if(gnode->geometry().contains(event->pos())) {
                m_selectedNode = nullptr;
                m_drag = false;
            }
        }

    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if (event->type() == QEvent::MouseMove && m_drag && m_selectedNode!=nullptr){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        m_selectedNode->m_attr->m_x += mouseEvent->pos().x()-m_mousePos.x();
        m_selectedNode->m_attr->m_y += mouseEvent->pos().y()-m_mousePos.y();
        m_mousePos = QPoint(mouseEvent->pos().x(), mouseEvent->pos().y());
        m_selectedNode->update();
        update();
    }
}

GNode* MainWindow::getGNode(Node* node){
    for(const auto& gn : m_gnodes){
        if(gn->m_node->getUid()==node->getUid()){
            return gn;
        }
    }
    return nullptr;
}
