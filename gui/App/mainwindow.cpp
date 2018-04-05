#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralWidget->setMouseTracking(true);
    installEventFilter(this);
    setMouseTracking(true);

<<<<<<< HEAD
    initMenu();
    initGraph();
    initVar();
=======
    m_graph = new Graph();
    m_graph->setOnDestroyNodeData(onDeleteNode);
    m_graph->setOnDestroyEdgeData(onDeleteEdge);
    m_graph->setOnSerializeNodeData(onSerializeNode);
    m_graph->setOnSerializeEdgeData(onSerializeEdge);
    m_graph->setOnDeserializeNodeData(onDeserializeNode);
    m_graph->setOnDeserializeEdgeData(onDeserializeEdge);

    m_selectedNode = nullptr;
    m_drag = false;
>>>>>>> 5c0b17156589dce552c5467fae2617bc230c5bd9

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

void MainWindow::initMenu(){
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));
}

<<<<<<< HEAD
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
=======
    std::vector<Edge*> edges = m_graph->getEdges();
    for(const auto& v : edges){
        Node* start = v->getStartNode();
        NodeAttr* sa = (NodeAttr*) start->getData();
        NodeGuiAttr* sgui = sa->m_gui;

        Node* end = v->getEndNode();
        NodeAttr* ea = (NodeAttr*) end->getData();
        NodeGuiAttr* egui = ea->m_gui;
>>>>>>> 5c0b17156589dce552c5467fae2617bc230c5bd9

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
    m_linking = false;
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
    for(unsigned int i=0 ; i<m_gnodes.size() ; i++){
        if(m_gnodes[i]->m_node->getUid()==node->getUid()){
            delete m_gnodes[i];
            m_gnodes.erase(m_gnodes.begin() + i);
        }
    }
    m_graph->removeNode(node);
    update();
}

void MainWindow::paintEvent(QPaintEvent *event){    
    QPainter painter(this);

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

            // line
            QPointF pStart(sgui->m_x+sgui->m_width/2, sgui->m_y+sgui->m_height/2);
            QPointF pEnd(egui->m_x+egui->m_width/2, egui->m_y+egui->m_height/2);
            painter.setPen(QPen(Qt::black, 3, Qt::DashLine, Qt::RoundCap));
            painter.drawLine(pStart, pEnd);

            // arrow
            float h = 20, w = 10;
            QPointF pMiddle = (pStart+pEnd)/2;
            QPointF U = (pEnd-pStart)/(pEnd-pStart).manhattanLength();
            QPointF V = QPointF(-U.y(), U.x());
            QPointF P1 = pMiddle - h*U + w*V;
            QPointF P2 = pMiddle - h*U - w*V;
            painter.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap));
            painter.drawLine(pMiddle, P1);
            painter.drawLine(pMiddle, P2);
        }
    }

    if(m_linking){
        QPoint pos = mapFromGlobal(QCursor::pos());
        painter.setPen(QPen(Qt::blue, 3, Qt::DashLine, Qt::RoundCap));
        Animal* attr = (Animal*) m_startNode->m_node->getData();
        NodeGuiAttr* gui = attr->m_gui;
        painter.drawLine(gui->m_x+gui->m_width/2, gui->m_y+gui->m_height/2, pos.x(), pos.y());
    }
    else if(!m_linking && m_endNode!=nullptr){
        m_graph->connect(m_startNode->m_node, m_endNode->m_node);
        m_startNode = nullptr;
        m_endNode = nullptr;
        update();
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
    if (event->type() == QEvent::MouseMove){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

        if(m_drag && m_selectedNode!=nullptr){
            m_selectedNode->m_attr->m_x += mouseEvent->pos().x()-m_mousePos.x();
            m_selectedNode->m_attr->m_y += mouseEvent->pos().y()-m_mousePos.y();
            m_mousePos = QPoint(mouseEvent->pos().x(), mouseEvent->pos().y());
            m_selectedNode->update();
            update();
        }

        if(m_linking){
            update();
        }
    }
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event){
    if (event->type()==QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if (key->key()==Qt::Key_Control) {
            QPoint pos = mapFromGlobal(QCursor::pos());
            m_startNode = gnodeAt(pos);
            m_linking = (m_startNode!=nullptr);
            return true;
        }
    }
    else if(event->type()==QEvent::KeyRelease){
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if (key->key()==Qt::Key_Control) {
            QPoint pos = mapFromGlobal(QCursor::pos());
            m_endNode = gnodeAt(pos);
            m_linking = false;
            update();
            return true;
        }
    }
    return QObject::eventFilter(obj, event);
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
