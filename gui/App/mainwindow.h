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

#include <fstream>

#include "gnode.h"
#include "nodeguiattr.h"
#include "graphhelper.h"
#include "editnodedialog.h"
#include "editedgedialog.h"
#include "../../entities/graph/include/Graph.h"

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

        void initMenuBar();
        void initContextMenu();
        void initGraph();
        void initVar();

    private slots:
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
