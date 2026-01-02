
#include "contact_selection_dialog.h"
#include "ui_contact_selection_dialog.h"
#include "channel_edit_dialog.h"
#include "memory/memory.h"
#include "memory/talkgroup.h"
#include "constants.h"
#include "ui_channel_settings.h"
#include <QStandardItemModel>

constexpr int TG_ROLE = Qt::UserRole + 1;

ContactSelectionDialog::ContactSelectionDialog(ChannelEditDialog *parent, QString text, QString title) :
    QDialog(parent),
    ui(std::make_unique<Ui_ContactSelectDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    ced = parent;

    setupUI();
    
}
ContactSelectionDialog::~ContactSelectionDialog(){}

void ContactSelectionDialog::setupUI(){
    QStandardItemModel *model = new QStandardItemModel();
    QVector<Anytone::Talkgroup*> sorted_tg_list = Anytone::Memory::talkgroups;

    std::stable_sort(sorted_tg_list.begin(), sorted_tg_list.end(),
          [](const Anytone::Talkgroup* a, const Anytone::Talkgroup* b) {
              return a->name < b->name;
          });

    int i = 0;
    for(Anytone::Talkgroup *tg : sorted_tg_list){
        if(tg->dmr_id != 0){
            QStandardItem *item = new QStandardItem(tg->name);
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            item->setData(QVariant::fromValue(tg), Qt::UserRole + 1);
            model->setItem(int(i/6), i%6, item);
            i++;
        }
    }

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(model);
    connect(ui->tableView, &QTableView::clicked, this, &ContactSelectionDialog::onTableClicked);
    connect(ui->tableView, &QTableView::doubleClicked, this, &ContactSelectionDialog::onTableDblClicked);
}
void ContactSelectionDialog::onTableClicked(QModelIndex index){
    if (last_selected_tg_item) {
        auto *prevTg = last_selected_tg_item->data(TG_ROLE).value<Anytone::Talkgroup*>();
        if (prevTg) {
            last_selected_tg_item->setText(prevTg->name);
        }
    }

    auto *model = qobject_cast<QStandardItemModel*>(const_cast<QAbstractItemModel*>(index.model()));
    if (!model)
        return;

    QStandardItem *item = model->item(index.row(), index.column());
    if (!item)
        return;

    auto *tg = item->data(TG_ROLE).value<Anytone::Talkgroup*>();
    if (!tg)
        return;

    // Build display text: name(id)(calltype)
    const QString callTypeStr = Constants::CALL_TYPE.at(tg->call_type);
    item->setText(QString("%1(%2)(%3)")
                      .arg(tg->name)
                      .arg(tg->dmr_id)
                      .arg(callTypeStr));

    last_selected_tg_item = item;
}
void ContactSelectionDialog::onTableDblClicked(QModelIndex index){
    auto *tg = index.data(TG_ROLE).value<Anytone::Talkgroup*>();

    ced->channel->contact = tg;
    ced->channel->contact_idx = tg->id;

    ced->ui->digitalContactBtn->setText(ced->channel->contact->name);
    close();
}