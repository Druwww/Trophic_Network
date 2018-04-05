#ifndef NODEGUIATTR
#define NODEGUIATTR

#include <iostream>

struct NodeGuiAttr{
    std::string m_imageFilepath;
    int m_width;
    int m_height;
    int m_x;
    int m_y;

    NodeGuiAttr(std::string imageFilepath="", int width=100, int height=100){
        m_imageFilepath = imageFilepath;
        m_width = width;
        m_height = height;
        m_x = 0;
        m_y = 0;
    }

    void write(std::ostream& os) const{
        os << m_imageFilepath << " ";
        os << m_width << " " << m_height << " ";
        os << m_x << " " << m_y;
    }

    void read(std::istream& is){
        is >> m_imageFilepath;
        is >> m_width >> m_height;
        is >> m_x >> m_y;
    }
};

#endif // NODEGUIATTR

