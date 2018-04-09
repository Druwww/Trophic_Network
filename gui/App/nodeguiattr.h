#ifndef NODEGUIATTR
#define NODEGUIATTR

#include <iostream>

/**
 * @brief Struct qui contient les attributs graphique d'un sommet
 */
struct NodeGuiAttr{
    /**
     * @brief Chemin vers l'image affichée pour le sommet
     */
    std::string m_imageFilepath;

    /**
     * @brief Longueur de l'image affichée
     */
    int m_width;

    /**
     * @brief Largeur de l'image affichée
     */
    int m_height;

    /**
     * @brief Abscisse du sommet sur la fenêtre
     */
    int m_x;

    /**
     * @brief Ordonnée du sommet sur la fenêtre
     */
    int m_y;

    NodeGuiAttr(std::string imageFilepath="", int width=100, int height=100){
        m_imageFilepath = imageFilepath;
        m_width = width;
        m_height = height;
        m_x = 0;
        m_y = 0;
    }

    NodeGuiAttr(const NodeGuiAttr& attr){
        m_imageFilepath = attr.m_imageFilepath;
        m_width = attr.m_width;
        m_height = attr.m_height;
        m_x = attr.m_x;
        m_y = attr.m_y;
    }

    /**
     * @brief Ecrit l'objet dans un flux
     * @param Le flux de sortie
     */
    void write(std::ostream& os) const{
        os << m_imageFilepath << " ";
        os << m_width << " " << m_height << " ";
        os << m_x << " " << m_y;
    }

    /**
     * @brief Lis l'objet à partir d'un flux
     * @param Le flux d'entrée
     */
    void read(std::istream& is){
        is >> m_imageFilepath;
        is >> m_width >> m_height;
        is >> m_x >> m_y;
    }
};

#endif // NODEGUIATTR
