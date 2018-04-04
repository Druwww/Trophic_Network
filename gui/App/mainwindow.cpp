#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initMenu();
    initGraph();
    initVar();

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

void MainWindow::initMenu(){
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));
}

void MainWindow::showContextMenu(const QPoint& pos){
    QMenu contextMenu(this);
    GNode* gnode = gnodeAt(pos);

    QAction *action;
    if(gnode==nullptr){
        action = new QAction("Add Node", this);
        action->setData(QVariant(pos));
        connect(action, SIGNAL(triggered()), this, SLOT(addNode()));
        contextMenu.addAction(action);
    }
    else{
        QVariant var = qVariantFromValue((void *) gnode);
        action = new QAction("Remove Node", this);
        action->setData(var);
        connect(action, SIGNAL(triggered()), this, SLOT(removeNode()));
        contextMenu.addAction(action);
    }

    contextMenu.exec(mapToGlobal(pos));
    delete action;
}

void MainWindow::initGraph(){
    m_graph = new Graph();
    m_graph->setOnDestroyNodeData(onDeleteNode);
    m_graph->setOnDestroyEdgeData(onDeleteEdge);
    m_graph->setOnSerializeNodeData(onSerializeNode);
    m_graph->setOnSerializeEdgeData(onSerializeEdge);
    m_graph->setOnDeserializeNodeData(onDeserializeNode);
    m_graph->setOnDeserializeEdgeData(onDeserializeEdge);
}

void MainWindow::initVar(){
    m_selectedNode = nullptr;
    m_drag = false;
}

void MainWindow::addNode(){
    QAction *action = qobject_cast<QAction *>(sender());
    QVariant variant = action->data();
    QPoint pos = variant.toPoint();

    std::string path = "/home/omar/Desktop/Trophic_Network/gui/App/image.png";
    Node* node = new Node();
    Animal* animal = new Animal();
    animal->m_gui = new NodeGuiAttr(path);
    animal->m_gui->m_x = pos.x()-animal->m_gui->m_width/2;
    animal->m_gui->m_y = pos.y()-animal->m_gui->m_height/2;
    node->setData(animal);
    m_graph->addNode(node);
    update();
}

void MainWindow::removeNode(){
    QAction *action = qobject_cast<QAction *>(sender());
    QVariant variant = action->data();
    GNode *gnode = (GNode*) variant.value<void *>();
    Node* node = gnode->m_node;
    for(int i=0 ; i<m_gnodes.size() ; i++){
        if(m_gnodes[i]->m_node->getUid()==node->getUid()){
            delete m_gnodes[i];
            m_gnodes.erase(m_gnodes.begin() + i);
        }
    }
    m_graph->removeNode(node);
    update();
    // rm gnode
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 3, Qt::DashLine, Qt::RoundCap));

    for(int i=0 ; i<m_graph->size() ; i++){
        std::pair<Node*, std::pair<std::vector<Edge*>, std::vector<Edge*> > > p = m_graph->get(i);

        Node* end = p.first;
        Animal* ea = (Animal*) end->getData();
        NodeGuiAttr* egui = ea->m_gui;
        GNode *egnode = getGNode(end);
        if(egnode==nullptr){
            egnode = new GNode(end, egui, this);
            m_gnodes.push_back(egnode);
        }
        egnode->show();

        std::vector<Edge*> in = p.second.first;
        for(auto const& e : in){
            Node* start = e->getStartNode();
            Animal* sa = (Animal*) start->getData();
            NodeGuiAttr* sgui = sa->m_gui;

            painter.drawLine(sgui->m_x+sgui->m_width/2, sgui->m_y+sgui->m_height/2,
                egui->m_x+egui->m_width/2, egui->m_y+egui->m_height/2);
        }
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

GNode* MainWindow::gnodeAt(const QPoint& pos){
    for(const auto& gnode : m_gnodes){
        if(gnode->geometry().contains(pos)){
            return gnode;
        }
    }
    return nullptr;
}
