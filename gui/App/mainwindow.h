#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QPoint>
#include <QTreeWidget>
#include <QAction>

#include "gnode.h"
#include "nodeguiattr.h"
#include "graphhelper.h"
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

        GNode* getGNode(Node* node);
        GNode* m_selectedNode;
        QPoint m_nodePos;
        QPoint m_mousePos;
        bool m_drag;

        GNode* m_startNode;
        GNode* m_endNode;
        bool m_linking;

        void initMenu();
        void initGraph();
        void initVar();
        GNode* gnodeAt(const QPoint& pos);

    private slots:
        void addNode();
        void removeNode();
        void showContextMenu(const QPoint& pos);

};

#endif // MAINWINDOW_H
