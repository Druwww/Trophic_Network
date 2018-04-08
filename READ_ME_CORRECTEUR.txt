Bonjour cher correcteur.

Voici le guide d’utilisation du code afin de pouvoir le compiler, lancer l’exécuteur et utiliser l’application.
Le reste du livrable se trouvent dans le dossier Documents


### Compilation + Exécuter

Pour ce code, nous avons utilisé pour la partie graphique de la bibliothèque QT. Pour pouvoir compiler notre code, il faut installer l’IDE QT AVEC l’extension : QTCharts
-	Pour linux regarder le READ ME
-	Pour Windows : https://www.qt.io/download
        !! Lors de l’installation, sélectionnez Charts lors de l’installation des Tools !!
Ensuite, ouvrez l’IDE, ouvrez un projet et sélectionnez le fichier : Gui/App/App.pro
Cliquez sur la flèche verte en bas a gauche pour compiler/lancer le code

###Guide d’utilisation
Lors du lancement, on vous propose de charger une sauvegarde, on vous en a préparer quelques-uns dans Gui/raws/ .
Vous pouvez en charger/créer/sauvegarder dans le menu File
Dans le menu Algorithms, ont peut lancer les algorithmes (seul le premier fonctionne pour l’instant). Il permet de donner les numéros de groupe de forte connexité.
Pour ajouter un sommet/Animal, faite un click droit -> add Node.
Pour modifier l’image, valeur d’un sommet ou autres paramètres : clic droit sur le sommet -> edit Node
Pour supprimer un sommet : clic droit sur le sommet -> remove node
Pour créer une liaison : mettre la souris sur un sommet -> maintenir Ctrl -> glisser la souris sur le sommet à lier avec -> lâcher la touche ctrl
Pour modifier une liaison : click droit sur la liaison
Il est aussi possible de lancer une simulation en appuyant sur start simulation, puis voir l’évolution étape par étape. On peut aussi lancer une simulation sur un nombre de tour définie sans affecter les données dans le graphe.

L'équation de la simultion est la suivante : la population au prochain tours est égale dans un premier temps au nombre de population + ceux qui sont nait, on elève ceux qui sont manger, puis on garde ceux qui peuvent survivre en mangeant ce qu'il y a
Tout ces parametres peuvent être modifier dans les noeud ou arêtes


Il y a d'autre algorithmes qui ont été préparer qui n'ont pas eu le temps d'être affiché
    Kmin pour les sommet et arêtes
    K connexité pour les sommets et arêtes

Bonne lecture du code !
