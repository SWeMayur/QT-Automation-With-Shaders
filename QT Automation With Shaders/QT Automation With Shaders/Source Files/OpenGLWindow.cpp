#include "stdafx.h"
#include "OpenGLWindow.h"
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include "Grid.h"

using namespace GeometricEntity;
using namespace PixelGrid;

OpenGLWindow::OpenGLWindow(const QColor& background, QMainWindow* parent) : mBackground(background)
{
    setParent(parent);
    setMinimumSize(720, 550);
    const QStringList list = { "vertexShader.glsl" , "fragmentShader.glsl" };
    mShaderWatcher = new QFileSystemWatcher(list, this);
    connect(mShaderWatcher, &QFileSystemWatcher::fileChanged, this, &OpenGLWindow::shaderWatcher);
}

OpenGLWindow::~OpenGLWindow()
{
    reset();
}

void OpenGLWindow::reset()
{
    // And now release all OpenGL resources.
    makeCurrent();
    delete mProgram;
    mProgram = nullptr;
    delete mVshader;
    mVshader = nullptr;
    delete mFshader;
    mFshader = nullptr;
    mVbo.destroy();
    doneCurrent();

    QObject::disconnect(mContextWatchConnection);
}

void OpenGLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    mProgram->bind();

    QMatrix4x4 matrix;
    matrix.ortho(-3.0f - (gridSize / 2), 3.0f + (gridSize / 2), -3.0f - (gridSize / 2), 3.0f + (gridSize / 2), 0.1f, 100.0f);
    matrix.translate(0, 0, -2);
    mProgram->setUniformValue(m_matrixUniform, matrix);
    Grid grid(vertices, colors, gridSize);

    mProgram->setUniformValue("r", r);
    mProgram->setUniformValue("g", g);
    mProgram->setUniformValue("b", b);
    mProgram->setUniformValue("angle", angle);

    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices.data());
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors.data());


    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glDrawArrays(GL_LINES, 0, vertices.size() / 2);

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);

}

void OpenGLWindow::initializeGL()
{
    QString vertexShaderSource = readShader("vertexShader.glsl");
    QString fragmentShaderSource = readShader("fragmentShader.glsl");

    initializeOpenGLFunctions();

    mProgram = new QOpenGLShaderProgram(this);

    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->link();
    m_posAttr = mProgram->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colAttr = mProgram->attributeLocation("colAttr");
    Q_ASSERT(m_colAttr != -1);
    m_matrixUniform = mProgram->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);
}

QString OpenGLWindow::readShader(QString filePath) {
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "Invalid file";

    QTextStream stream(&file);
    QString line = stream.readLine();

    while (!stream.atEnd()) {
        line.append(stream.readLine());
    }
    file.close();
    return line;
}

void OpenGLWindow::shaderWatcher()
{
    QString vertexShaderSource = readShader("vertexShader.glsl");
    QString fragmentShaderSource = readShader("fragmentShader.glsl");

    mProgram->release();
    mProgram->removeAllShaders();
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->link();
}
void OpenGLWindow::selectColor()
{
    QColorDialog colorDialog(this);
    QColor selectedColor = colorDialog.getColor();

    if (selectedColor.isValid()) {
        // Set the selected color to the curves or store it for later use
        r = selectedColor.redF();
        g = selectedColor.greenF();
        b = selectedColor.blueF();
        emit shapeUpdate();  // Trigger an update to redraw the curves with the new color
    }
}

void OpenGLWindow::addGrid(int size)
{
    gridSize = size;
    emit shapeUpdate();
}

void OpenGLWindow::rotateObject(GLfloat rotationAngle)
{
    angle = rotationAngle;
    emit shapeUpdate();
}