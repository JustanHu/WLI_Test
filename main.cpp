#include "mainwindow.h"

#include <QApplication>
#include <QSurfaceFormat>
#include <QTextCodec>

int main(int argc, char *argv[])
{
//适配高清屏幕
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif
// 设置字符编码为UTF-8
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
