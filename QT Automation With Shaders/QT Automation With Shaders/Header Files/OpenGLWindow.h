#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include "Line.h"
#include <vector>
#include "Point.h"

class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;
class QOpenGLPaintDevice;

class OpenGLWindow :public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
signals:
    void shapeUpdate();
public:
    OpenGLWindow(const QColor& background, QMainWindow* parent);
    ~OpenGLWindow();

public:
    void addGrid(int gridSize);
    void rotateObject(GLfloat angle);

protected:
    void paintGL() override;
    void initializeGL() override;

private:
    void reset();
    QString readShader(QString filePath);
    

public slots:
    void selectColor();

private slots:
    void shaderWatcher();

private:
    QOpenGLShader* mVshader = nullptr;
    QOpenGLShader* mFshader = nullptr;
    QOpenGLShaderProgram* mProgram = nullptr;
    QOpenGLBuffer mVbo;
    int gridSize = 0;
    QColor mBackground;
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;
    std::vector<float> vertices;
    std::vector<float> colors;
    GLfloat r = 1, g = 1, b = 1, angle = 0;
    
    QFileSystemWatcher* mShaderWatcher;

    QMetaObject::Connection mContextWatchConnection;
};