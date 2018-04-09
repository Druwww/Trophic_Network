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


/**
 * @brief La classe principal qui gère l'interface utilisateur
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    protected:
        void paintEvent(QPaintEvent *event);            //!< evenement appelé lorsque l'interface est redessiné
        void mousePressEvent(QMouseEvent *event);       //!< evenement appelé lorsqu'un bouton de la souris est pressé
        void mouseReleaseEvent(QMouseEvent *event);     //!< evenement appelé lorsqu'un bouton de la souris est relaché
        void mouseMoveEvent(QMouseEvent *event);        //!< evenement appelé lorsque la souris se déplace sur l'écran
        bool eventFilter(QObject* obj, QEvent* event);  //!< evenement appelé lorsqu'un evenement quelquonque apparait

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        Ui::MainWindow* ui;

        /**
         * @brief Objet Graph contenant toute les données "brut"
         */
        Graph* m_graph;

        /**
         * @brief Vecteur de GNode présent à l'écran
         */
        std::vector<GNode*> m_gnodes;

        /**
         * @brief Pointe vers le GNode séléctionné lors des drag & drop des sommets à l'écran
         */
        GNode* m_selectedNode;

        /**
         * @brief Position de la souris au début du drag & drop
         */
        QPoint m_mousePos;

        /**
         * @brief true s'il y a un drag & drop, false sinon
         */
        bool m_drag;

        /**
         * @brief Pointe vers le sommet de départ lors d'une connexion entre 2 sommets
         */
        GNode* m_startNode;

        /**
         * @brief Pointe vers le sommet d'e départ d'arrivé lors d'une connexion entre 2 sommets
         */
        GNode* m_endNode;

        /**
         * @brief Renvoie le GNode associé au Node en paramètre
         * @param Node
         * @return GNode
         */
        GNode* getGNode(Node* node);

        /**
         * @brief Renvoie le GNode présent à la position passée en paramètre
         * @param Position sur l'écran
         * @return GNode
         */
        GNode* gnodeAt(const QPoint& pos);

        /**
         * @brief Renvoie l'objet Edge présent à la position passéeen paramètre
         * @param Position sur l'écran
         * @return Edge
         */
        Edge* edgeAt(const QPoint& pos);

        /**
         * @brief Objet contenant les différents algorithmes de la théorie des graphes
         */
        Algorithm m_algorithm;

        /**
         * @brief Objet contenant les algorithmes de simulations concernant le projet trophic network
         */
        Simulation m_simulation;

        /**
         * @brief Initialise la barre de menu
         */
        void initMenuBar();

        /**
         * @brief Initialise le menu du clique gauche de la souris
         */
        void initContextMenu();

        /**
         * @brief Initialise le Graph
         */
        void initGraph();

        /**
         * @brief Initialise les différentes variables de la class MainWindow
         */
        void initVar();

        /**
         * @brief Reset le paramètre concernant les groupes de connexité des sommets de m_graph
         */
        void resetGroups();

    private slots:
        /**
         * @brief Lance l'algorithme "Forte Connexité"
         */
        void algo1();

        /**
         * @brief Lance l'algorithme "K Min Connexité Sommet"
         */
        void algo2();

        /**
         * @brief Lance l'algorithme "K Min Connexité Arête"
         */
        void algo3();

        /**
         * @brief Lance l'algorithme "DFS Influence"
         */
        void algo4();

        /**
         * @brief Démarre la simulation
         */
        void startSimulation();

        /**
         * @brief Arrête la simulation
         */
        void stopSimulation();

        /**
         * @brief Avance la simulation d'une étape
         */
        void nextStepSimulation();

        /**
         * @brief Affiche les résultats de la simulation sur un graphique
         */
        void chartSimulation();

        /**
         * @brief Crée un sommet à la position de la souris
         */
        void addNode();

        /**
         * @brief Supprime le sommet présent à la position de la souris
         */
        void removeNode();

        /**
         * @brief Edite un sommet présent à la position de la souris
         */
        void editNode();

        /**
         * @brief Supprime une arête présente à la position de la souris
         */
        void removeEdge();

        /**
         * @brief Edite une arête présente à la position de la souris
         */
        void editEdge();

        /**
         * @brief Affiche une fenêtre qui permet de séléctionner un nouveau graphe à charger
         */
        void openGraph();

        /**
         * @brief Affiche une fenêtre qui permet de sauvegarder le graphe courant
         */
        void saveGraph();

        /**
         * @brief Efface l'écran et crée un graphe vierge
         */
        void newGraph();

        /**
         * @brief Affiche le menu clique droit
         * @param Position de la souris
         */
        void showContextMenu(const QPoint& pos);

};

#endif // MAINWINDOW_H
