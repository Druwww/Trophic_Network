#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QPoint>
#include <QTreeWidget>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>

#include <QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

#include <fstream>

#include "gnode.h"
#include "nodeguiattr.h"
#include "editnodedialog.h"
#include "editedgedialog.h"

#include "../../algorithm/include/algorithm.h"
#include "../../entities/graph/include/Graph.h"
#include "../../simulation/include/Simulation.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    protected:
        void paintEvent(QPaintEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        bool eventFilter(QObject* obj, QEvent* event);

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        Ui::MainWindow* ui;

        Graph* m_graph;
        std::vector<GNode*> m_gnodes;

        GNode* m_selectedNode;
        QPoint m_mousePos;
        bool m_drag;

        GNode* m_startNode;
        GNode* m_endNode;

        GNode* getGNode(Node* node);
        GNode* gnodeAt(const QPoint& pos);
        Edge* edgeAt(const QPoint& pos);

        Algorithm m_algorithm;
        Simulation m_simulation;

        void initMenuBar();
        void initContextMenu();
        void initGraph();
        void initVar();

    private slots:
        void algo1();
        void algo2();
        void algo3();
        void algo4();

        void startSimulation();
        void stopSimulation();
        void nextStepSimulation();
        void chartSimulation();

        void addNode();
        void removeNode();
        void editNode();
        void removeEdge();
        void editEdge();
        void openGraph();
        void saveGraph();
        void showContextMenu(const QPoint& pos);

};

#endif // MAINWINDOW_H
