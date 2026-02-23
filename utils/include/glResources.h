#ifndef GLRESOURCES_H
#define GLRESOURCES_H

// #include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QVector>

class GLResources
{
public:
    struct VertexAttribute {
        GLuint index;
        GLint size;
        GLenum type;
        GLboolean normalized;
        GLsizei stride;
        size_t offset;
    };

    struct TextureBinding {
        QOpenGLTexture* texture;  // 原始指针，类内管理生命周期
        GLuint unit;
        QString uniformName;
    };

public:
    explicit GLResources();
    ~GLResources();

    // 禁止拷贝和移动
    GLResources(const GLResources&) = delete;
    GLResources& operator=(const GLResources&) = delete;
    GLResources(GLResources&&) = delete;
    GLResources& operator=(GLResources&&) = delete;

    void initialize(QOpenGLFunctions_4_5_Core* glFunc);
    void destroy();

    void bind();
    void release();

    void createVAO();
    void createVBO(GLsizeiptr size, const void* data, QOpenGLBuffer::UsagePattern usage);
    void createEBO(GLsizeiptr size, const void* data, QOpenGLBuffer::UsagePattern usage);
    void setAttributeBuffer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
    void enableAttributeArray(GLuint index);
    void drawElements(GLenum mode, GLsizei count, GLenum type, const void *indices);

    bool createTexture2D(const QString& name, const QString& imagePath,
                         QOpenGLTexture::WrapMode wrapMode = QOpenGLTexture::Repeat,
                         QOpenGLTexture::Filter minFilter = QOpenGLTexture::Linear,
                         QOpenGLTexture::Filter magFilter = QOpenGLTexture::Linear);
    bool bindTexture(const QString& name, int textureUnit = 0);
    void releaseTexture(const QString& name, int textureUnit = 0);
    QOpenGLTexture* getTexture(const QString& name);
    void deleteTexture(const QString& name);
    void deleteAllTextures();
    bool hasTexture(const QString& name) const;
    int textureCount() const { return m_textures.size(); }
    void setActiveTextureUnit(int unit);
    void generateMipmaps(const QString& name);

private:
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo{QOpenGLBuffer::VertexBuffer};
    QOpenGLBuffer m_ebo{QOpenGLBuffer::IndexBuffer};
    QMap<QString, QOpenGLTexture*> m_textures;
    QOpenGLFunctions_4_5_Core* m_glFunc = nullptr;
};

#endif