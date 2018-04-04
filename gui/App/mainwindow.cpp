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

    std::string path = "/home/omar/Desktop/Trophic_Network/gui/App/image.png";

    Node* n1 = new Node("Omar");
    Node* n2 = new Node("Fred");
    Node* n3 = new Node("Quentin");

    Animal* an1 = new Animal();
    an1->m_gui = new NodeGuiAttr(path);
    an1->m_gui->m_x = 0;
    an1->m_gui->m_y = 0;
    n1->setData(an1);

    Animal* an2 = new Animal();
    an2->m_gui = new NodeGuiAttr(path);
    an2->m_gui->m_x = 400;
    an2->m_gui->m_y = 300;
    n2->setData(an2);

    Animal* an3 = new Animal();
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
        Node* end = v->getEndNode();
        Animal* sa = (Animal*) start->getData();
        Animal* ea = (Animal*) end->getData();
        NodeGuiAttr* sgui = sa->m_gui;
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
//    if (event->button() == Qt::LeftButton){
//        for(unsigned int i=0 ; i<m_graph->size() ; i++){
//            data d = m_graph->get(i);

//            if(iconLabel->geometry().contains(event->pos())) {

//                QDrag *drag = new QDrag(this);
//                QMimeData *mimeData = new QMimeData;

//                mimeData->setText(commentEdit->toPlainText());
//                drag->setMimeData(mimeData);
//                drag->setPixmap(iconPixmap);

//                Qt::DropAction dropAction = drag->exec();
//            }
//        }

//    }
}

GNode* MainWindow::getGNode(Node* node){
    for(const auto& gn : m_gnodes){
        if(gn->m_node->getUid()==node->getUid()){
            return gn;
        }
    }
    return nullptr;
}

void onDeleteNode(void* data){
    Animal* animal = (Animal*) data;
    delete animal;
}

void onDeleteVertex(void* data){
    NaturalLaw* law = (NaturalLaw*) data;
    delete law;
}

void onSerializeNode(std::ostream& os, void* data){
    Animal* animal = (Animal*) data;
    animal->write(os);
}

void onSerializeVertex(std::ostream& os, void* data){
    NaturalLaw* law = (NaturalLaw*) data;
    law->write(os);
}

void onDeserializeNode(std::istream& is, void** data){
    Animal* animal = new Animal();
    animal->read(is);
    *data = animal;
}

void onDeserializeVertex(std::istream& is, void** data){
    NaturalLaw* law = new NaturalLaw();
    law->read(is);
    *data = law;
}
