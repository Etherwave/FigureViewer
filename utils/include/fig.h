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

class FieldGeometry2D {
public:
    FieldGeometry2D();
    ~FieldGeometry2D();
    void createTriangle(size_t num);
    void createSimpleCase();
    void createRectangle(size_t rowNum, size_t colNum);

    float m_minX, m_minY, m_maxX, m_maxY;
    float m_minVal, m_maxVal;
    QVector3D m_minColor, m_maxColor;

    QVector<GLfloat> m_vertexData;      // 顶点数据（位置+值+颜色/或位置+值，颜色实时算）
    QVector<GLuint> m_elementTri;       // Element Buffer for Triangles
    QVector<GLuint> m_elementLine;      // Element Buffer for Lines
};


#endif //FIG_H
