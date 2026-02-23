#include "glResources.h"

#include <iostream>
#include <ostream>


GLResources::GLResources() {
    std::cout << "GLResources::GLResources()" << std::endl;
}

GLResources::~GLResources() {
    std::cout << "~GLResources::GLResources()" << std::endl;
    destroy();  // 确保资源释放
}

void GLResources::initialize(QOpenGLFunctions_4_5_Core* glFunc) {
    std::cout << "GLResources::initialize()" << std::endl;
    m_glFunc = glFunc;
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_ebo.setUsagePattern(QOpenGLBuffer::StaticDraw);
}

void GLResources::destroy() {
    deleteAllTextures();  // 确保删除所有纹理
    // 添加保护：已经清理过就不再执行
    if (!m_vao.isCreated()) {
        return;
    }
    // 2. 释放EBO（必须在VAO之前，但VAO不"拥有"EBO，只是记录绑定状态）
    if (m_ebo.isCreated()) {
        m_ebo.destroy();
    }
    // 3. 释放VBO
    if (m_vbo.isCreated()) {
        m_vbo.destroy();
    }
    // 4. 最后释放VAO
    if (m_vao.isCreated()) {
        m_vao.destroy();
    }
}

void GLResources::bind() {
    qDebug() << "GLResources::bind()";
    if (m_vao.isCreated()) {
        m_vao.bind();
    }
    qDebug() << "GLResources::bind() done";
}

void GLResources::release() {
    if (m_vao.isCreated()) {
        m_vao.release();
    }
}

void GLResources::createVAO() {
    std::cout << "GLResources::createVAO()" << std::endl;
    if (!m_vao.isCreated()) {
        m_vao.create();
    }
}

void GLResources::createVBO(GLsizeiptr size, const void* data, QOpenGLBuffer::UsagePattern usage) {
    std::cout << "GLResources::createVBO()" << std::endl;
    if (!m_vbo.isCreated()) {
        m_vbo.create();
        m_vbo.setUsagePattern(usage);
    }
    m_vbo.bind();
    m_vbo.allocate(data, size);
}

void GLResources::createEBO(GLsizeiptr size, const void* data, QOpenGLBuffer::UsagePattern usage) {
    std::cout << "GLResources::createEBO()" << std::endl;
    if (!m_ebo.isCreated()) {
        m_ebo.create();
        m_ebo.setUsagePattern(usage);
    }
    m_ebo.bind();
    m_ebo.allocate(data, size);
}

void GLResources::setAttributeBuffer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) {
    m_glFunc->glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void GLResources::enableAttributeArray(GLuint index) {
    m_glFunc->glEnableVertexAttribArray(index);
}

void GLResources::drawElements(GLenum mode, GLsizei count, GLenum type, const void *indices) {
    m_glFunc->glDrawElements(mode, count, type, indices);
}

bool GLResources::createTexture2D(const QString& name, const QString& imagePath,
                                  QOpenGLTexture::WrapMode wrapMode,
                                  QOpenGLTexture::Filter minFilter,
                                  QOpenGLTexture::Filter magFilter) {
    // 检查是否已存在同名纹理
    if (m_textures.contains(name)) {
        qWarning() << "Texture" << name << "already exists!";
        return false;
    }

    // 加载图片
    QImage image(imagePath);
    if (image.isNull()) {
        qWarning() << "Failed to load image:" << imagePath;
        return false;
    }

    // 转换为OpenGL格式（RGBA）
    image = image.convertToFormat(QImage::Format_RGBA8888);

    // 创建纹理
    QOpenGLTexture* texture = new QOpenGLTexture(image.mirrored());
    if (!texture->isCreated()) {
        qWarning() << "Failed to create texture:" << name;
        delete texture;
        return false;
    }

    // 设置纹理参数
    texture->setWrapMode(wrapMode);
    texture->setMinificationFilter(minFilter);
    texture->setMagnificationFilter(magFilter);

    // 生成mipmap
    texture->generateMipMaps();

    // 存储纹理
    m_textures[name] = texture;

    qDebug() << "Texture created:" << name << "from" << imagePath;
    return true;
}

bool GLResources::bindTexture(const QString& name, int textureUnit) {
    if (!m_textures.contains(name)) {
        qWarning() << "Texture not found:" << name;
        return false;
    }

    QOpenGLTexture* texture = m_textures[name];
    if (texture && texture->isCreated()) {
        // 设置活动纹理单元
        if (m_glFunc) {
            m_glFunc->glActiveTexture(GL_TEXTURE0 + textureUnit);
        }
        texture->bind();
        return true;
    }

    return false;
}

void GLResources::releaseTexture(const QString& name, int textureUnit) {
    if (m_textures.contains(name)) {
        QOpenGLTexture* texture = m_textures[name];
        if (texture) {
            texture->release();
        }
    }
}

QOpenGLTexture* GLResources::getTexture(const QString& name) {
    return m_textures.value(name, nullptr);
}

void GLResources::deleteTexture(const QString& name) {
    if (m_textures.contains(name)) {
        QOpenGLTexture* texture = m_textures[name];
        if (texture) {
            delete texture;
        }
        m_textures.remove(name);
        qDebug() << "Texture deleted:" << name;
    }
}

void GLResources::deleteAllTextures() {
    qDebug() << "Deleting all textures, count:" << m_textures.size();

    for (auto it = m_textures.begin(); it != m_textures.end(); ++it) {
        if (it.value()) {
            delete it.value();
        }
    }
    m_textures.clear();
}

bool GLResources::hasTexture(const QString& name) const {
    return m_textures.contains(name);
}

void GLResources::setActiveTextureUnit(int unit) {
    if (m_glFunc) {
        m_glFunc->glActiveTexture(GL_TEXTURE0 + unit);
    }
}

void GLResources::generateMipmaps(const QString& name) {
    if (m_textures.contains(name)) {
        QOpenGLTexture* texture = m_textures[name];
        if (texture) {
            texture->generateMipMaps();
        }
    }
}

