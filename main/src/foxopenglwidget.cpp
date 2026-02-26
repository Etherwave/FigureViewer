#include <QDebug>
#include <QWheelEvent>
#include "foxopenglwidget.h"

#include <iostream>

#include "shader_s.h"
#include "fig.h"

FieldGeometry2D fg2d;
// const int num = 1e3;
//const int num = 4;
const size_t rowNum = 10;
const size_t colNum = 10;
// const size_t rowNum = 1e2;
// const size_t colNum = 1e2;
// const size_t rowNum = 1e3;
// const size_t colNum = 1e3;

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
    // 【重点】初始化OpenGL函数，将 Qt 里的函数指针指向显卡的函数（头文件 QOpenGLFunctions_X_X_Core）
    if (!initializeOpenGLFunctions()) {
        qDebug() << "initializeOpenGLFunctions failed!";
    }
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



//    fg2d.createTriangle(num);
    // fg2d.createSimpleCase();
    fg2d.createRectangle(rowNum, colNum);
    qDebug() << "fg2d.minX = " << fg2d.m_minX;
    qDebug() << "fg2d.maxX = " << fg2d.m_maxX;
    qDebug() << "fg2d.minY = " << fg2d.m_minY;
    qDebug() << "fg2d.maxY = " << fg2d.m_maxY;
    qDebug() << "fg2d.minVal = " << fg2d.m_minVal;
    qDebug() << "fg2d.maxVal = " << fg2d.m_maxVal;
    qDebug() << "fg2d.m_minColor = " << fg2d.m_minColor;
    qDebug() << "fg2d.m_maxColor = " << fg2d.m_maxColor;
    qDebug() << "fg2d.m_vertexData.size() = " << fg2d.m_vertexData.size();
    qDebug() << "fg2d.m_elementTri.size() = " << fg2d.m_elementTri.size();
    // for (size_t i = 0; i < fg2d.m_vertexData.size(); i++)
    // {
    //     qDebug() << "fg2d.m_vertexData[" << i << "] = " << fg2d.m_vertexData[i];
    // }
    // for (size_t i = 0; i < fg2d.m_elementTri.size(); i++)
    // {
    //     qDebug() << "fg2d.m_elementTri[" << i << "] = " << fg2d.m_elementTri[i];
    // }
    // 2. 配置顶点属性
    GLsizei oneElementSize = sizeof(float) * (2 + 1);
    size_t bias1 = 0;
    size_t bias2 = sizeof(float) * 2;
    QVector<GLResources::VertexAttribute> attrs = {
        {0, 2, GL_FLOAT, GL_FALSE, oneElementSize, bias1},
        {1, 1, GL_FLOAT, GL_FALSE, oneElementSize, bias2},
    };

    _glResources.createTriVAO();
    _glResources.bindTriVAO();
    _glResources.createVBO(fg2d.m_vertexData.size() * sizeof(float), fg2d.m_vertexData.data(), QOpenGLBuffer::UsagePattern::StaticDraw);
    qDebug() << "start set attr";
    for (const auto& attr : attrs) {
        _glResources.setAttributeBuffer(attr.index, attr.size, attr.type, attr.normalized, oneElementSize, ((void*)attr.offset));
        _glResources.enableAttributeArray(attr.index);
    }
    _glResources.createTriEBO(fg2d.m_elementTri.size() * sizeof(GLuint), fg2d.m_elementTri.data(), QOpenGLBuffer::UsagePattern::StaticDraw);  // EBO/IBO 是储存顶点【索引】的
    // _glResources.createVBO(vertices.size() * sizeof(Vertex), vertices.data(), QOpenGLBuffer::UsagePattern::StaticDraw);
    // _glResources.createEBO(indices.size() * sizeof(GLuint), indices.data(), QOpenGLBuffer::UsagePattern::StaticDraw);  // EBO/IBO 是储存顶点【索引】的


    // _glResources.setAttributeBuffer(0, 3, GL_FLOAT, GL_FALSE, oneElementSize, (void*)bias1);
    // _glResources.setAttributeBuffer(1, 3, GL_FLOAT, GL_FALSE, oneElementSize, (void*)bias2);
    // _glResources.setAttributeBuffer(2, 2, GL_FLOAT, GL_FALSE, oneElementSize, (void*)bias3);
    // _glResources.enableAttributeArray(0);
    // _glResources.enableAttributeArray(1);
    // _glResources.enableAttributeArray(2);

    _glResources.createLineVAO();
    _glResources.bindLineVAO();
    _glResources.bindVBO();
    qDebug() << "start set attr";
    for (const auto& attr : attrs) {
        _glResources.setAttributeBuffer(attr.index, attr.size, attr.type, attr.normalized, oneElementSize, ((void*)attr.offset));
        _glResources.enableAttributeArray(attr.index);
    }
    _glResources.createLineEBO(fg2d.m_elementLine.size() * sizeof(GLuint), fg2d.m_elementLine.data(), QOpenGLBuffer::UsagePattern::StaticDraw);  // EBO/IBO 是储存顶点【索引】的
    _glResources.release();

    // 创建纹理
    // QString texturePath = "D:/code/openglData/pics/container.jpg";
    // if (!_glResources.createTexture2D("container", texturePath)) {
    //     qWarning() << "Failed to create texture!";
    // }
    qDebug() << "start init shader";
    // 5. 初始化shader (你的已有类)
    // std::string shaderVs = "D:/code/c/FigureViewer/shaders/shader.vs";
    // std::string shaderFs = "D:/code/c/FigureViewer/shaders/shader.fs";
    std::string shaderVs = "D:/code/c/FigureViewer/shaders/tri.vs";
    std::string shaderFs = "D:/code/c/FigureViewer/shaders/tri.fs";
    _shader.initialize(shaderVs.c_str(), shaderFs.c_str());
    _shader.bind();
    _shader.setUniformValue("minX", fg2d.m_minX);
    _shader.setUniformValue("maxX", fg2d.m_maxX);
    _shader.setUniformValue("minY", fg2d.m_minY);
    _shader.setUniformValue("maxY", fg2d.m_maxY);
    _shader.setUniformValue("minValue", fg2d.m_minVal);
    _shader.setUniformValue("maxValue", fg2d.m_maxVal);
    _shader.setUniformValue("minColor", fg2d.m_minColor);
    _shader.setUniformValue("maxColor", fg2d.m_maxColor);
    _shader.setUniformValue("paintMode", 0);
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

    QMatrix4x4 projection = getViewMatrix();
    _shader.bind();
    _shader.setUniformValue("projection", projection);
    // qDebug() << "projection = " << projection;

    qDebug() << "start bindTriVAO";
    _glResources.bindTriVAO();

    // _shader.setUniformValue("projection", projection);
    _shader.setUniformValue("paintMode", 0);
    qDebug() << "bind done";
    qDebug() << "fg2d.m_elementTri.size() = " << fg2d.m_elementTri.size();
    _glResources.drawElements(GL_TRIANGLES, fg2d.m_elementTri.size(), GL_UNSIGNED_INT, 0);

//    _glResources.drawElements(GL_LINES, fg2d.m_indices.size(), GL_UNSIGNED_INT, 0);
//    _glResources.drawElements(GL_LINE_LOOP, fg2d.m_indices.size(), GL_UNSIGNED_INT, 0);
//    _glResources.drawElements(GL_RECTANGLE, fg2d.m_indices.size(), GL_UNSIGNED_INT, 0);
    // _glResources.drawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    qDebug() << "start bindLineVAO";
    _glResources.bindLineVAO();
    // _shader.bind();
    // _shader.setUniformValue("projection", projection);
    _shader.setUniformValue("paintMode", 1);
    qDebug() << "bind done";
    qDebug() << "fg2d.m_elementLine.size() = " << fg2d.m_elementLine.size();
    _glResources.drawElements(GL_LINES, fg2d.m_elementLine.size(), GL_UNSIGNED_INT, 0);
    qDebug() << "draw done";

    // _glResources.releaseTexture("container", 0);
    _glResources.release();
}

/* ============================================
 * 核心功能：鼠标滚轮缩放
 * ============================================ */

void FoxOpenGLWidget::wheelEvent(QWheelEvent *event)
{
    // 获取滚轮增量，向上滚动为正值，向下为负值
    float delta = event->angleDelta().y() / 120.0f;  // 标准化为步数

    // 应用缩放
    applyZoomAtPoint(delta, event->position().toPoint());

    // 触发重绘
    update();

    // 接受事件，阻止传递给父控件
    event->accept();
}
// 替换 applyZoomAtPoint 函数：
void FoxOpenGLWidget::applyZoomAtPoint(float delta, const QPoint &mousePos)
{
    float zoomFactor = 1.0f + (delta * _zoomSensitivity);
    float newZoom = qBound(_minZoom, _zoomLevel * zoomFactor, _maxZoom);

    if (qFuzzyCompare(newZoom, _zoomLevel)) return;

    // 将鼠标位置转换为世界坐标（考虑当前缩放和偏移）
    QPointF mouseWorldBefore = screenToWorld(mousePos);

    // 更新缩放
    _zoomLevel = newZoom;

    // 将同一屏幕位置转换为新的世界坐标
    QPointF mouseWorldAfter = screenToWorld(mousePos);

    // 调整偏移，使鼠标指向的世界坐标保持不变
    _cameraOffset += (mouseWorldAfter - mouseWorldBefore);

    update();
}

QPointF FoxOpenGLWidget::screenToWorld(const QPoint &screenPos)
{
    int w = width();
    int h = height();

    // 屏幕坐标 -> NDC (-1 到 1)
    float ndcX = (2.0f * screenPos.x()) / w - 1.0f;
    float ndcY = 1.0f - (2.0f * screenPos.y()) / h;

    // NDC -> 世界坐标 (逆变换)
    QPointF worldPos;
    worldPos.setX(ndcX / _zoomLevel - _cameraOffset.x());
    worldPos.setY(ndcY / _zoomLevel - _cameraOffset.y());

    return worldPos;
}

QMatrix4x4 FoxOpenGLWidget::getViewMatrix()
{
    QMatrix4x4 view;
    view.setToIdentity();
    view.translate(_cameraOffset.x(), _cameraOffset.y());
    view.scale(_zoomLevel);
    return view;
}


// 实现三个鼠标事件处理函数
void FoxOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isDragging = true;
        m_lastMousePos = screenToWorld(event->pos());;
        event->accept();
    }
}

void FoxOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isDragging) {
        QPointF currentMousePos = screenToWorld(event->pos());
        // QPointF delta = currentMousePos - m_lastMousePos;
        _cameraOffset += (currentMousePos - m_lastMousePos);

        m_lastMousePos = currentMousePos;
        update();
        event->accept();
    }
}

void FoxOpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isDragging = false;
        event->accept();
    }
}
