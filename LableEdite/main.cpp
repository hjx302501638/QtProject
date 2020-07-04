#include "LabelEdit.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LabelEdit w;
    w.show();
    return a.exec();
}
