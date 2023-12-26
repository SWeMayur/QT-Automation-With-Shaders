#include "stdafx.h"
#include "QTautomationwithshaders.h"

QTAutomationWithShaders::QTAutomationWithShaders(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    connect(gridInputButton, &QPushButton::clicked, this, &QTAutomationWithShaders::addGrid);
    connect(mRotationAngle, &QPushButton::clicked, this, &QTAutomationWithShaders::rotationAngle);
    connect(mColorSelector, &QPushButton::clicked, mRenderer, &OpenGLWindow::selectColor);
    connect(mRenderer, SIGNAL(shapeUpdate()), mRenderer, SLOT(update()));
}

QTAutomationWithShaders::~QTAutomationWithShaders()
{}

void QTAutomationWithShaders::setupUi()
{
    resize(1530, 785);
    gridLabel = new QLabel(this);
    gridLabel->setObjectName("label");
    gridLabel->setText("Grid Size");
    gridLabel->setGeometry(QRect(160, 0, 85, 20));

    gridInput = new QLineEdit(this);
    gridInput->setObjectName("lineEdit_6");
    gridInput->setGeometry(QRect(140, 25, 85, 20));

    gridInputButton = new QPushButton(this);
    gridInputButton->setObjectName("pushButton");
    gridInputButton->setText("Draw Grid");
    gridInputButton->setGeometry(QRect(240, 0, 100, 50));

    mAngleInputLabel = new QLabel(this);
    mAngleInputLabel->setObjectName("label");
    mAngleInputLabel->setText("angle");
    mAngleInputLabel->setGeometry(QRect(535, 0, 85, 20));

    mAngleInput = new QLineEdit(this);
    mAngleInput->setObjectName("lineEdit_6");
    mAngleInput->setGeometry(QRect(505, 25, 85, 20));

    mRotationAngle = new QPushButton(this);
    mRotationAngle->setObjectName("pushButton");
    mRotationAngle->setText("Enter angle");
    mRotationAngle->setGeometry(QRect(600, 0, 85, 50));

    mColorSelector = new QPushButton(this);
    mColorSelector->setObjectName("pushButton");
    mColorSelector->setText("Select color");
    mColorSelector->setGeometry(QRect(340, 0, 85, 50));

    mRenderer = new OpenGLWindow(QColor(0, 0, 0), this);
    mRenderer->setGeometry(QRect(90, 140, 1000, 600));

    setWindowTitle(QCoreApplication::translate("QT shaders automation", "QT shaders automation", nullptr));
}

void QTAutomationWithShaders::addGrid()
{
    int gridSize = gridInput->text().toInt();
    mRenderer->addGrid(gridSize);
}

void QTAutomationWithShaders::rotationAngle()
{
    GLfloat angle = mAngleInput->text().toFloat();
    mRenderer->rotateObject(angle);
}