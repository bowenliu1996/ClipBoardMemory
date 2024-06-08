#include "clipboardmemory.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClipBoardMemory w;
    w.show();
    return a.exec();
}
