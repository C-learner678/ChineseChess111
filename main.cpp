#include "Chinese_chess2.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Chinese_chess2 w;
	w.setFixedSize(w.width(), w.height());
    w.show();
    return a.exec();
}

