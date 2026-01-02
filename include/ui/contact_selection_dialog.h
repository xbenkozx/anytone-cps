#ifndef CONTACT_SELECTION_DIALOG_H
#define CONTACT_SELECTION_DIALOG_H

#include <QDialog>
#include <QString>
#include <QStandardItem>

class Ui_ContactSelectDialog;
class ChannelEditDialog;

class ContactSelectionDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit ContactSelectionDialog(ChannelEditDialog *parent = nullptr, QString text = "", QString title = "");
    ~ContactSelectionDialog();

    void setupUI();

private:
    std::unique_ptr<Ui_ContactSelectDialog> ui;
    ChannelEditDialog *ced;
    QStandardItem *last_selected_tg_item = nullptr;

private slots:
    void onTableClicked(QModelIndex index);
    void onTableDblClicked(QModelIndex index);
};

#endif