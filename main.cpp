#include <QtGui/QApplication>
#include "imageshow.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("gb18030"));
    ImageShow w;
    w.show();
    
    return a.exec();
}
