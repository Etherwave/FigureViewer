#include "shader_s.h"

Shader::Shader(): _program(nullptr) {

}

Shader::~Shader() {
    if (_program) {
        qDebug() << "Error::SHADER::~Shader: need destroy manually";
    }
}

bool Shader::initialize(const QString& vertexPath, const QString& fragmentPath) {
    if (!checkContextValid()) {
        qCritical() << "ERROR::SHADER::NOT_INITIALIZED, checkContextValid() failed";
        return false;
    }
    if (_program) destroy();
    _program = new QOpenGLShaderProgram();

    // 1. 读取并编译顶点着色器
    QString vertexCode = loadShaderSource(vertexPath);
    if (vertexCode.isEmpty()) {
        qCritical() << "ERROR::SHADER::VERTEX_FILE_NOT_READ:" << vertexPath;
        return false;
    }

    if (!_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexCode)) {
        qCritical() << "ERROR::SHADER::VERTEX_COMPILATION\n" << _program->log();
        return false;
    }

    // 2. 读取并编译片段着色器
    QString fragmentCode = loadShaderSource(fragmentPath);
    if (fragmentCode.isEmpty()) {
        qCritical() << "ERROR::SHADER::FRAGMENT_FILE_NOT_READ:" << fragmentPath;
        return false;
    }

    if (!_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentCode)) {
        qCritical() << "ERROR::SHADER::FRAGMENT_COMPILATION\n" << _program->log();
        return false;
    }

    // 3. 链接着色器程序
    if (!_program->link()) {
        qCritical() << "ERROR::SHADER::PROGRAM_LINKING\n" << _program->log();
        return false;
    }
    return true;
}

void Shader::destroy() {
    if (!checkContextValid()) {
        qCritical() << "ERROR::SHADER::NOT_INITIALIZED, checkContextValid() failed";
        return;
    }
    if (_program) {
        delete _program;
        _program = nullptr;
    }
}

bool Shader::bind() {
    if (_program && _program->isLinked()) {
        _program->bind();
        return true;
    }
    qWarning() << "WARNING::SHADER::USE_FAILED - Program not valid";
    return false;
}
void Shader::release() {
    if (_program) {
        _program->release();
    }
}

GLuint Shader::getProgramID() const {
    return _program ? _program->programId() : 0;
}

bool Shader::isValid() const {
    return _program && _program->isLinked();
}

bool Shader::checkProgramValid()
{
    if (!_program || !_program->isLinked()) {
        qWarning() << "WARNING::SHADER::PROGRAM_NOT_VALID";
        return false;
    }
    return true;
}

bool Shader::checkContextValid() const {
    return QOpenGLContext::currentContext() != nullptr;
}

QString Shader::loadShaderSource(const QString& path) const {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open shader file:" << path << "Error:" << file.errorString();
        return QString();
    }

    QTextStream stream(&file);
    QString content = stream.readAll();
    file.close();
    return content;
}

int Shader::uniformLocation(const QString& name) const {
    if (!_program) return -1;

    // 实时查询，不缓存（避免 glGetActiveUniform 调用）
    int loc = _program->uniformLocation(name);
    if (loc == -1) {
        static QSet<QString> warned;  // 避免重复警告
        if (!warned.contains(name)) {
            qWarning() << "WARNING::SHADER::UNIFORM_NOT_FOUND:" << name;
            warned.insert(name);
        }
    }
    return loc;
}
