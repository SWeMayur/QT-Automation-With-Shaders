#include "stdafx.h"
#include "QTAutomationWithShaders.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTAutomationWithShaders w;
    w.show();
    return a.exec();
}
