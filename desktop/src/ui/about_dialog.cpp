
#include "about_dialog.h"
#include "ui_about_dialog.h"
#include "constants.h"
#include <QFile>
#include <QUrl>
#include <QDesktopServices>
#include <QTextBrowser>
#include <QTextDocument>
#include <QRegularExpression>


AboutDialog::AboutDialog(QWidget *parent):
    QDialog(parent),
    ui(std::make_unique<Ui_AboutDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    ui->iconLabel->setStyleSheet("background-image: url(:/icons/d878_icon.png);background-repeat: no-repeat;");

    ui->aboutLabel->setMarkdown(
        "# Anytone CPS\n"
        "Version: **" + Constants::CPS_VERISON + "**\n\r"
        "Supported Models:\n"
        "- D878UVII (FW4.00)\n"
        "- D890UV (FW1.03)"
    );
    ui->aboutLabel->setFixedWidth(250);

    // CHANGELOG.md is compiled into the application (desktop/resources.qrc), so the text shown
    // here is the one in the repository and its newest version is the one in the VERSION file.
    ui->changelogView->setStyleSheet(
        "QTextBrowser { background: palette(base); border: 1px solid palette(mid);"
        " border-radius: 6px; padding: 6px; }");
    ui->changelogView->document()->setDefaultStyleSheet(
        "h1 { font-size: 17pt; }"
        "h2 { font-size: 12pt; margin-top: 16px; margin-bottom: 2px; }"
        "h3 { font-size: 10pt; margin-top: 6px; margin-bottom: 0px; }"
        "li { margin-bottom: 3px; }"
        "code { font-family: monospace; }");
    QFile changelog(":/CHANGELOG.md");
    if(changelog.open(QIODevice::ReadOnly)){
        QString text = QString::fromUtf8(changelog.readAll());
        // show only the list of versions: skip the introduction and stop at the separator
        // before the incident write-ups, which are meant for the repository
        const int first = text.indexOf(QRegularExpression("^## \\[", QRegularExpression::MultilineOption));
        const int last = text.indexOf(QRegularExpression("^---$", QRegularExpression::MultilineOption));
        if(first >= 0) text = text.mid(first, last > first ? last - first : -1);
        text.replace(QRegularExpression("^## \\[([0-9.]+)\\]", QRegularExpression::MultilineOption), "## \\1");
        ui->changelogView->setMarkdown("# What's new\n\n" + text);
        ui->changelogView->moveCursor(QTextCursor::Start);
    }else{
        ui->changelogView->setPlainText("The changelog is not available in this build.");
    }
    // only real web links are opened; links to other files or to a place in the file are ignored
    connect(ui->changelogView, &QTextBrowser::anchorClicked, this, [](const QUrl &url){
        if(url.scheme() == "http" || url.scheme() == "https") QDesktopServices::openUrl(url);
    });
}
AboutDialog::~AboutDialog(){
    
}
