#ifndef FIG_H
#define FIG_H

#include <QVector3D>
#include <QPointF>
#include <QVector2D>
#include <GL/gl.h>
#include <QVector>


// struct Vertex {
//     QVector3D pos;
//     QVector3D color;
//     QVector2D texCoord;
// };

class Figures2D {
public:
    Figures2D();
    ~Figures2D();
    void createTriangle(size_t num);
    void createSimpleCase();

    float m_minX, m_minY, m_maxX, m_maxY;
    float m_minVal, m_maxVal;
    QVector3D m_minColor, m_maxColor;
    QVector<GLfloat> m_vertices;
    QVector<GLuint> m_indices;
};


#endif //FIG_H
