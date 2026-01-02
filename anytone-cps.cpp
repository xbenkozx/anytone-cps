#include <QApplication>
#include <QFont>
#include "main_window.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/icons/d878_icon_64.ico"));

    QFont font = qApp->font();
    font.setPointSize(10);
    qApp->setFont(font);

    MainWindow widget;
    widget.setWindowIcon(QIcon(":/icons/d878_icon_64.ico"));
    widget.show();

    return app.exec();
}