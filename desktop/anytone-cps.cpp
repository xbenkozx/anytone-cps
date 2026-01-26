#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QFont>
#include "main_window.h"
#include <QDebug>

// TODO: Create Satellite UI
// TODO: Create AM Air UI
// TODO: Create AM Air Table
// TODO: Create AM Zone UI
// TODO: Create AM Zone Table

int main(int argc, char *argv[]){

    QApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("AnyTone CPS");
    parser.addHelpOption();
    parser.addVersionOption();

    // Options
    QCommandLineOption debugOption(
        {"d", "debug"},
        "Enable Debug"
    );

    parser.addOption(debugOption);

    parser.process(app);

    bool debug = parser.isSet(debugOption);

    app.setWindowIcon(QIcon(":/icons/d878_icon_64.ico"));

    QFont font = qApp->font();
    font.setPointSize(10);
    qApp->setFont(font);

    MainWindow widget;
    widget.debug = debug;
    widget.setWindowIcon(QIcon(":/icons/d878_icon_64.ico"));
    widget.show();

    return app.exec();
}