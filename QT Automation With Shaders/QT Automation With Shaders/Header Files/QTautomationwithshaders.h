#pragma once

#include <QtWidgets/QMainWindow>
#include "OpenGLWindow.h"

class OpenGLWindow;

class QTAutomationWithShaders : public QMainWindow
{
    Q_OBJECT

public:
    QTAutomationWithShaders(QWidget *parent = nullptr);
    ~QTAutomationWithShaders();


public:
    QVector<QVector2D> mPixelVertices;
    QVector<GLfloat>   mVertices;
    QVector<GLfloat>   mColors;


private:
    void setupUi();

private slots:
    void addGrid();
    void rotationAngle();
private:
    OpenGLWindow* mRenderer;

    QPushButton* gridInputButton;
    QPushButton* mColorSelector;
    QPushButton* mRotationAngle;


    QLineEdit* gridInput;
    QLineEdit* mAngleInput;

    QLabel* gridLabel;
    QLabel* mAngleInputLabel;
};
