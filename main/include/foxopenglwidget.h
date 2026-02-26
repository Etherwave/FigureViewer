#ifndef FOXOPENGLWIDGET_H
#define FOXOPENGLWIDGET_H

#include <QOpenGLWidget>  // 相当于GLFW
#include <QOpenGLFunctions_4_5_Core>  // 相当于 GLAD
// #include <QOpenGLFunctions_3_3_Core>  // 相当于 GLAD

#include "glResources.h"
#include "shader_s.h"

class FoxOpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_4_5_Core
// class FoxOpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit FoxOpenGLWidget(QWidget *parent = nullptr);
    ~FoxOpenGLWidget();

protected:
    /* 需要重载的 QOpenGLWidget 中的三个函数 */
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    /* 鼠标事件处理 */
    virtual void wheelEvent(QWheelEvent *event);  // 滚轮缩放
    virtual void mousePressEvent(QMouseEvent *event);  // 鼠标按下事件
    virtual void mouseMoveEvent(QMouseEvent *event);  // 鼠标移动事件
    virtual void mouseReleaseEvent(QMouseEvent *event);  // 鼠标释放事件

    signals:

    public slots:

private:
    /* 根据鼠标位置计算缩放后的偏移，实现以鼠标为中心缩放 */
    QPointF screenToWorld(const QPoint &screenPos);
    void applyZoomAtPoint(float delta, const QPoint &mousePos);
    QMatrix4x4 getViewMatrix();     // 获取包含缩放的视图矩阵
private:
    /* 缩放相关参数 */
    QPointF _cameraOffset{0, 0};  // 相机偏移，用于实现以鼠标为中心缩放
    float _zoomLevel = 1.0f;        // 当前缩放级别
    float _zoomSensitivity = 0.1f;  // 缩放灵敏度 (0.0 - 1.0)
    float _minZoom = 0.1f;          // 最小缩放限制
    float _maxZoom = 10.0f;         // 最大缩放限制
    /* 鼠标拖动相关参数 */
    bool m_isDragging = false;  // 是否正在拖动
    QPointF m_lastMousePos;      // 上次鼠标位置

    Shader _shader;
    GLResources _glResources;
};

#endif // FOXOPENGLWIDGET_H
