#include <QDebug>
#include "foxopenglwidget.h"

#include <iostream>

#include "shader_s.h"
#include "fig.h"

Figures2D fig2D;
// const int num = 1e3;
const int num = 4;

FoxOpenGLWidget::FoxOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
    std::cout << "FoxOpenGLWidget::FoxOpenGLWidget()" << std::endl;
}

FoxOpenGLWidget::~FoxOpenGLWidget() {
    std::cout << "FoxOpenGLWidget::~FoxOpenGLWidget()" << std::endl;
    makeCurrent();
    _glResources.destroy();
    _shader.release();
    _shader.destroy();
    doneCurrent();
}

/* 首要要执行初始化过程，将函数指针指向显卡内的函数 */
void FoxOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();  // 【重点】初始化OpenGL函数，将 Qt 里的函数指针指向显卡的函数（头文件 QOpenGLFunctions_X_X_Core）
    _glResources.initialize(this);

    // 顶点数据结构
    // struct Vertex {
    //     QVector3D pos;
    //     QVector3D color;
    //     QVector2D texCoord;
    // };
    //
    // QVector<Vertex> vertices = {
    //     {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    //     {{ 0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    //     {{ 0.5f,  0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
    //     {{-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}
    // };
    // QVector<GLuint> indices = {
    //     0, 1, 2,
    //     0, 2, 3
    // };
    // // 2. 配置顶点属性
    // QVector<GLResources::VertexAttribute> attrs = {
    //     {0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, pos)},
    //     {1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, color)},
    //     {2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, texCoord)}
    // };
    // size_t oneElementSize = sizeof(QVector3D) + sizeof(QVector3D) + sizeof(QVector2D);
    // size_t bias1 = 0;
    // size_t bias2 = sizeof(QVector3D);
    // size_t bias3 = sizeof(QVector3D) + sizeof(QVector3D);



    fig2D.createTriangle(num);
    // fig2D.createSimpleCase();
    qDebug() << "fig2D.minX = " << fig2D.m_minX;
    qDebug() << "fig2D.maxX = " << fig2D.m_maxX;
    qDebug() << "fig2D.minY = " << fig2D.m_minY;
    qDebug() << "fig2D.maxY = " << fig2D.m_maxY;
    qDebug() << "fig2D.minVal = " << fig2D.m_minVal;
    qDebug() << "fig2D.maxVal = " << fig2D.m_maxVal;
    qDebug() << "fig2D.m_minColor = " << fig2D.m_minColor;
    qDebug() << "fig2D.m_maxColor = " << fig2D.m_maxColor;
    qDebug() << "fig2D.m_vertices.size() = " << fig2D.m_vertices.size();
    qDebug() << "fig2D.m_indices.size() = " << fig2D.m_indices.size();
    // for (size_t i = 0; i < fig2D.m_vertices.size(); i++)
    // {
    //     qDebug() << "fig2D.m_vertices[" << i << "] = " << fig2D.m_vertices[i];
    // }
    // for (size_t i = 0; i < fig2D.m_indices.size(); i++)
    // {
    //     qDebug() << "fig2D.m_indices[" << i << "] = " << fig2D.m_indices[i];
    // }
    // 2. 配置顶点属性
    GLsizei oneElementSize = sizeof(float) * (2 + 1);
    size_t bias1 = 0;
    size_t bias2 = sizeof(float) * 2;
    QVector<GLResources::VertexAttribute> attrs = {
        {0, 2, GL_FLOAT, GL_FALSE, oneElementSize, bias1},
        {1, 1, GL_FLOAT, GL_FALSE, oneElementSize, bias2},
    };

    _glResources.createVAO();
    _glResources.bind();
    _glResources.createVBO(fig2D.m_vertices.size() * sizeof(float), fig2D.m_vertices.data(), QOpenGLBuffer::UsagePattern::StaticDraw);
    _glResources.createEBO(fig2D.m_indices.size() * sizeof(GLuint), fig2D.m_indices.data(), QOpenGLBuffer::UsagePattern::StaticDraw);  // EBO/IBO 是储存顶点【索引】的
    // _glResources.createVBO(vertices.size() * sizeof(Vertex), vertices.data(), QOpenGLBuffer::UsagePattern::StaticDraw);
    // _glResources.createEBO(indices.size() * sizeof(GLuint), indices.data(), QOpenGLBuffer::UsagePattern::StaticDraw);  // EBO/IBO 是储存顶点【索引】的


    // _glResources.setAttributeBuffer(0, 3, GL_FLOAT, GL_FALSE, oneElementSize, (void*)bias1);
    // _glResources.setAttributeBuffer(1, 3, GL_FLOAT, GL_FALSE, oneElementSize, (void*)bias2);
    // _glResources.setAttributeBuffer(2, 2, GL_FLOAT, GL_FALSE, oneElementSize, (void*)bias3);
    // _glResources.enableAttributeArray(0);
    // _glResources.enableAttributeArray(1);
    // _glResources.enableAttributeArray(2);
    for (const auto& attr : attrs) {
        _glResources.setAttributeBuffer(attr.index, attr.size, attr.type, attr.normalized, oneElementSize, ((void*)attr.offset));
        _glResources.enableAttributeArray(attr.index);
    }
    _glResources.release();

    // 创建纹理
    // QString texturePath = "D:/code/openglData/pics/container.jpg";
    // if (!_glResources.createTexture2D("container", texturePath)) {
    //     qWarning() << "Failed to create texture!";
    // }

    // 5. 初始化shader (你的已有类)
    // std::string shaderVs = "D:/code/c/FigureViewer/shaders/shader.vs";
    // std::string shaderFs = "D:/code/c/FigureViewer/shaders/shader.fs";
    std::string shaderVs = "D:/code/c/FigureViewer/shaders/tri.vs";
    std::string shaderFs = "D:/code/c/FigureViewer/shaders/tri.fs";
    _shader.initialize(shaderVs.c_str(), shaderFs.c_str());
    _shader.bind();
    _shader.setUniformValue("minX", fig2D.m_minX);
    _shader.setUniformValue("maxX", fig2D.m_maxX);
    _shader.setUniformValue("minY", fig2D.m_minY);
    _shader.setUniformValue("maxY", fig2D.m_maxY);
    _shader.setUniformValue("minValue", fig2D.m_minVal);
    _shader.setUniformValue("maxValue", fig2D.m_maxVal);
    _shader.setUniformValue("minColor", fig2D.m_minColor);
    _shader.setUniformValue("maxColor", fig2D.m_maxColor);
    _shader.release();
    std::cout << "FoxOpenGLWidget::initializeGL() done" << std::endl;
}

void FoxOpenGLWidget::resizeGL(int w, int h)
{
    // Q_UNUSED(w);
    // Q_UNUSED(h);
    // 添加视口设置
    glViewport(0, 0, w, h);
    qDebug() << "resize " << w << " " << h;
}

void FoxOpenGLWidget::paintGL()
{
    std::cout << "FoxOpenGLWidget::paintGL()" << std::endl;
    /* 设置 OpenGLWidget 控件背景颜色为深青色 */
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  // set方法【重点】如果没有 initializeGL，目前是一个空指针状态，没有指向显卡里面的函数，会报错
    glClear(GL_COLOR_BUFFER_BIT);  // use方法
    qDebug() << "clear done";
    // 检查资源是否有效
    if (!_shader.isValid()) {
        qWarning() << "Shader not valid!";
        return;
    }

    // _glResources.bindTexture("container", 0);
    // _shader.setUniformValue("texture1", 0);

    _glResources.bind();
    _shader.bind();
    qDebug() << "bind done";
    qDebug() << "fig2D.m_indices.size() = " << fig2D.m_indices.size();
    _glResources.drawElements(GL_TRIANGLES, fig2D.m_indices.size(), GL_UNSIGNED_INT, 0);
    // _glResources.drawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    qDebug() << "draw done";
    // _glResources.releaseTexture("container", 0);
    _glResources.release();
}
