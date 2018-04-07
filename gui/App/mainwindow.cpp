#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralWidget->setMouseTracking(true);
    installEventFilter(this);
    setMouseTracking(true);

    initVar();
    initGraph();
    initMenuBar();
    initContextMenu();

    std::ifstream file("../raws/v1.graph");
    if(file){
        m_graph->read(file);
        file.close();
        update();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_graph;
}

void MainWindow::initMenuBar(){
    QAction* openGraph = new QAction("Open Graph", this);
    openGraph->setShortcuts(QKeySequence::Open);
    connect(openGraph, SIGNAL(triggered(bool)), this, SLOT(openGraph()));

    QAction* saveGraph = new QAction("Save Graph", this);
    saveGraph->setShortcuts(QKeySequence::Save);
    connect(saveGraph, SIGNAL(triggered(bool)), this, SLOT(saveGraph()));

    QMenu* fileMenu = menuBar()->addMenu(tr("File"));
    QList<QAction*> actions({openGraph, saveGraph});
    fileMenu->addActions(actions);
}

void MainWindow::initContextMenu(){
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));
}

void MainWindow::showContextMenu(const QPoint& pos){
    QMenu contextMenu(this);
    GNode* gnode = gnodeAt(pos);

    if(gnode==nullptr){
        QAction* addAction = new QAction("Add Node", this);
        addAction->setData(QVariant(pos));
        connect(addAction, SIGNAL(triggered()), this, SLOT(addNode()));
        contextMenu.addAction(addAction);

        Edge* edge = edgeAt(pos);
        if(edge!=nullptr){
            QVariant var = qVariantFromValue((void *) edge);

            QAction* editEdgeAction = new QAction("Edit Edge", this);
            editEdgeAction->setData(var);
            connect(editEdgeAction, SIGNAL(triggered()), this, SLOT(editEdge()));
            contextMenu.addAction(editEdgeAction);

            QAction* removeEdgeAction = new QAction("Remove Edge", this);
            removeEdgeAction->setData(var);
            connect(removeEdgeAction, SIGNAL(triggered()), this, SLOT(removeEdge()));
            contextMenu.addAction(removeEdgeAction);
        }
    }
    else{
        QVariant var = qVariantFromValue((void *) gnode);

        QAction* rmAction = new QAction("Remove Node", this);
        rmAction->setData(var);
        connect(rmAction, SIGNAL(triggered()), this, SLOT(removeNode()));
        contextMenu.addAction(rmAction);

        QAction* editAction = new QAction("Edit Node", this);
        editAction->setData(var);
        connect(editAction, SIGNAL(triggered()), this, SLOT(editNode()));
        contextMenu.addAction(editAction);
    }

    contextMenu.exec(mapToGlobal(pos));
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
    m_startNode = nullptr;
    m_endNode = nullptr;
    m_drag = false;
}

void MainWindow::addNode(){
    QAction *action = qobject_cast<QAction *>(sender());
    QVariant variant = action->data();
    QPoint pos = variant.toPoint();

    std::string path = "../images/eth.png";
    Node* node = new Node();
    NodeAttr* attr = new NodeAttr();
    attr->m_gui = new NodeGuiAttr(path);
    attr->m_gui->m_x = pos.x()-attr->m_gui->m_width/2;
    attr->m_gui->m_y = pos.y()-attr->m_gui->m_height/2;
    node->setData(attr);
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

void MainWindow::editNode(){
    QAction *action = qobject_cast<QAction *>(sender());
    QVariant variant = action->data();
    GNode *gnode = (GNode*) variant.value<void *>();

    EditNodeDialog dialog(gnode);
    if (dialog.exec() == QDialog::Accepted) {
        NodeAttr* attr = (NodeAttr*) gnode->m_node->getData();
        NodeGuiAttr* gui = attr->m_gui;

        QString filePath = dialog.getNodeImageFilepath();
        if(!filePath.isEmpty()){
            gui->m_imageFilepath = filePath.toStdString();
            gnode->updateImage();
        }

        attr->m_quantity = dialog.getNodeQuantity();
        attr->m_birthRate = dialog.getNodeBirthRate();

        update();
    }
}

void MainWindow::removeEdge(){
    QAction* action = qobject_cast<QAction *>(sender());
    QVariant variant = action->data();
    Edge* edge = (Edge*) variant.value<void *>();

    // remove edge
}

void MainWindow::editEdge(){
    QAction* action = qobject_cast<QAction *>(sender());
    QVariant variant = action->data();
    Edge* edge = (Edge*) variant.value<void *>();

    EditEdgeDialog dialog(edge);
    if(dialog.exec() == QDialog::Accepted){
        EdgeAttr* attr = (EdgeAttr*) edge->getData();
        edge->setWeight(dialog.getEdgeWeight());
        attr->m_importance = dialog.getEdgeImportance();
        attr->m_survivalRate = dialog.getEdgeSurvivalRate();
        update();
    }
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    for(int i=0 ; i<m_graph->size() ; i++){
        std::pair<Node*, std::pair<std::vector<Edge*>, std::vector<Edge*> > > p = m_graph->get(i);
        Node* end = p.first;
        NodeAttr* ea = (NodeAttr*) end->getData();
        NodeGuiAttr* egui = ea->m_gui;

        // edges
        std::vector<Edge*> in = p.second.first;
        for(auto const& e : in){
            Node* start = e->getStartNode();
            NodeAttr* sa = (NodeAttr*) start->getData();
            NodeGuiAttr* sgui = sa->m_gui;

            // line
            QPointF pStart(sgui->m_x+sgui->m_width/2, sgui->m_y+sgui->m_height/2);
            QPointF pEnd(egui->m_x+egui->m_width/2, egui->m_y+egui->m_height/2);
            painter.setPen(QPen(Qt::black, 3, Qt::DashLine, Qt::RoundCap));
            painter.drawLine(pStart, pEnd);

            // arrow
            float h = 20, w = 10, k = 50;
            QPointF U = (pEnd-pStart)/(pEnd-pStart).manhattanLength();
            QPointF V = QPointF(-U.y(), U.x());
            QPointF pMiddle = (pStart+pEnd)/2 + k*U;
            QPointF P1 = pMiddle - h*U + w*V;
            QPointF P2 = pMiddle - h*U - w*V;
            painter.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap));
            painter.drawLine(pMiddle, P1);
            painter.drawLine(pMiddle, P2);

            // data
            EdgeAttr* e_attr = (EdgeAttr*) e->getData();
            if(e_attr!=nullptr){
                QString str = "W = " + QString::number(e->getWeight())
                        + " | I = " + QString::number(e_attr->m_importance)
                        + " | SR = " + QString::number(e_attr->m_survivalRate);
                painter.setPen(QPen(Qt::magenta, 3, Qt::SolidLine, Qt::RoundCap));
                painter.drawText(pMiddle+20*V, str);
            }
        }
    }

    // nodes
    for(int i=0 ; i<m_graph->size() ; i++){
        Node* node = m_graph->get(i).first;
        NodeAttr* attr = (NodeAttr*) node->getData();
        NodeGuiAttr* gui = attr->m_gui;
        GNode *gnode = getGNode(node);
        if(gnode==nullptr){
            gnode = new GNode(node, gui, this);
            m_gnodes.push_back(gnode);
        }
        gnode->show();
        gnode->painEvent(painter);
    }

    if(m_startNode!=nullptr){
        QPoint pos = mapFromGlobal(QCursor::pos());
        NodeAttr* attr = (NodeAttr*) m_startNode->m_node->getData();
        NodeGuiAttr* gui = attr->m_gui;
        painter.setPen(QPen(Qt::blue, 3, Qt::DashLine, Qt::RoundCap));
        painter.drawLine(gui->m_x+gui->m_width/2, gui->m_y+gui->m_height/2, pos.x(), pos.y());
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        for(const auto& gnode : m_gnodes){
            if(gnode->geometry().contains(event->pos())) {
                m_selectedNode = gnode;
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
            m_selectedNode->m_gui->m_x += mouseEvent->pos().x()-m_mousePos.x();
            m_selectedNode->m_gui->m_y += mouseEvent->pos().y()-m_mousePos.y();
            m_mousePos = QPoint(mouseEvent->pos().x(), mouseEvent->pos().y());
            m_selectedNode->updatePos();
            update();
        }

        if(m_startNode!=nullptr){
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
            return true;
        }
    }
    else if(event->type()==QEvent::KeyRelease){
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if (key->key()==Qt::Key_Control) {
            QPoint pos = mapFromGlobal(QCursor::pos());
            m_endNode = gnodeAt(pos);

            if(m_startNode!=nullptr && m_endNode!=nullptr){
                if(!m_graph->areConnected(m_startNode->m_node, m_endNode->m_node)){
                    m_graph->connect(m_startNode->m_node, m_endNode->m_node);
                }
                else{
                    statusBar()->showMessage("Nodes already connected !", 3000);
                }
            }

            m_startNode = nullptr;
            m_endNode = nullptr;

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

Edge* MainWindow::edgeAt(const QPoint& pos){
    for(int i=0 ; i<m_graph->size() ; i++){
        Node* start = m_graph->get(i).first;
        IO io = m_graph->get(i).second;

        NodeAttr* sattr = (NodeAttr*) start->getData();
        NodeGuiAttr* sgui = sattr->m_gui;
        QPointF pStart(sgui->m_x+sgui->m_width/2, sgui->m_y+sgui->m_height/2);

        for(const auto& e : io.second){
            Node* end = e->getEndNode();
            NodeAttr* eattr = (NodeAttr*) end->getData();
            NodeGuiAttr* egui = eattr->m_gui;
            QPointF pEnd(egui->m_x+egui->m_width/2, egui->m_y+egui->m_height/2);

            // check if pos lies between pStart and pEnd
            double length = sqrt(pow(pStart.x()-pEnd.x(), 2) + pow(pStart.y()-pEnd.y(), 2));
            double length2 = sqrt(pow(pStart.x()-pos.x(), 2) + pow(pStart.y()-pos.y(), 2))
                     + sqrt(pow(pos.x()-pEnd.x(), 2) + pow(pos.y()-pEnd.y(), 2));

            double diff = qAbs(length-length2);

            if(diff<2){
                return e;
            }
        }

    }
    return nullptr;
}

void MainWindow::openGraph(){
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Graph"), "",
            tr("Graph (*.graph);;All Files (*)"));

    if(!fileName.isEmpty()){
        std::ifstream file(fileName.toStdString().c_str());
        if(file){
            for(unsigned int i=0 ; i<m_gnodes.size() ; i++){
                delete m_gnodes[i];
            }
            m_gnodes.clear();
            m_graph->read(file);
            file.close();
            update();
        }
        else{
            QMessageBox::critical(this, "Error !", "Could not open file : "+fileName);
        }
    }
}

void MainWindow::saveGraph(){
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Graph"), "",
            tr("Graph (*.graph);;All Files (*)"));

    if(!fileName.isEmpty()){
        if(!fileName.endsWith(".graph")){
            fileName.append(".graph");
        }
        std::ofstream file(fileName.toStdString().c_str());
        if(file){
            m_graph->write(file);
            file.close();
            statusBar()->showMessage("File saved !", 3000);
        }
        else{
            QMessageBox::critical(this, "Error !", "Could not save file to : "+fileName);
        }
    }
}
