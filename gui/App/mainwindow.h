#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

#include "../../entities/animal/include/Animal.h"
#include "../../entities/animal/include/NaturalLaw.h"
#include "../../entities/graph/include/Graph.h"
#include "gnode.h"
#include "nodeguiattr.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *event);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Graph* m_graph;
};

void onDeleteNode(void* data);
void onDeleteVertex(void* data);
void onSerializeNode(std::ostream& os, void* data);
void onSerializeVertex(std::ostream& os, void* data);
void onDeserializeNode(std::istream& is, void** data);
void onDeserializeVertex(std::istream& is, void** data);

#endif // MAINWINDOW_H
