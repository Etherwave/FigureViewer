#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QOpenGLContext>
#include <QOpenGLFunctions_4_5_Core>

class Shader {
public:
    explicit Shader();
    ~Shader();

    bool initialize(const QString& vertexPath, const QString& fragmentPath);
    void destroy();
    bool bind();
    void release();
    GLuint getProgramID() const;
    bool isValid() const;

    template<typename... Args>
    void setUniformValue(const QString& name, Args&&... args) {
        _program->setUniformValue(name.toStdString().c_str(), std::forward<Args>(args)...);
    }

    template<typename T>
    void setUniformValueArray(const QString& name, const T* values, int count) {
        _program->setUniformValueArray(name.toStdString().c_str(), values, count);
    }

private:
    bool checkProgramValid();
    bool checkContextValid() const;
    QString loadShaderSource(const QString& path) const;
    int uniformLocation(const QString& name) const;

private:
    QOpenGLShaderProgram* _program;
};

#endif // SHADER_H