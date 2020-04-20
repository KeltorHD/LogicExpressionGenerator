#include "fromtreemanipulation.h"
#include "ui_fromtreemanipulation.h"

#include <QFileDialog>
#include <QTextStream>
#include <QDebug>

FromTreeManipulation::FromTreeManipulation(std::vector<const Node*>& _his,
                                           std::vector<const Node*>& _head,
                                           State *state,
                                           QStackedWidget *stWidget,
                                           QWidget *parent) :
    QWidget(parent), ui(new Ui::FromTreeManipulation), his(_his), head(_head), state(state)
{
    ui->setupUi(this);
    this->stWidget = stWidget;

    /*Кнопки из левого ряда по-умолчанию выключены*/
    ui->del->setDisabled(true);
    ui->sdnf->setDisabled(true);
    ui->sknf->setDisabled(true);
    ui->table->setDisabled(true);
    ui->save->setDisabled(true);

    connect(ui->listWidget, &QListWidget::itemClicked, this, &FromTreeManipulation::itemChanged); /*если нажать на формулу, станут доступны кнопки*/
    connect(ui->del, &QPushButton::clicked, this, &FromTreeManipulation::deleteItem); /*нажатие на кнопку Удалить*/
    connect(ui->delAll, &QPushButton::clicked, this, &FromTreeManipulation::deleteAllItem); /*нажатие на кнопку Удалить все*/
    connect(ui->save, &QPushButton::clicked, this, &FromTreeManipulation::saveItem); /*нажатие на кнопку сохранить*/
    connect(ui->saveAll, &QPushButton::clicked, this, &FromTreeManipulation::saveAllItem); /*нажатие на кнопку сохранить все*/

    connect(ui->generate, &QPushButton::clicked, this, &FromTreeManipulation::generateAnother); /*нажатие на кнопку генерировать другие*/

    connect(ui->sdnfAll, &QPushButton::clicked, this, &FromTreeManipulation::sdnfAllItem); /*построение сднф*/
    connect(ui->sdnf, &QPushButton::clicked, this, &FromTreeManipulation::sdnfItem); /*построение сднф*/

    connect(ui->sknfAll, &QPushButton::clicked, this, &FromTreeManipulation::sknfAllItem); /*построение скнф*/
    connect(ui->sknf, &QPushButton::clicked, this, &FromTreeManipulation::sknfItem); /*построение скнф*/

    connect(ui->table, &QPushButton::clicked, this, &FromTreeManipulation::tableItem); /*таблица истинности*/
    connect(ui->tableAll, &QPushButton::clicked, this, &FromTreeManipulation::tableAllItem); /*таблица истинности*/
}

FromTreeManipulation::~FromTreeManipulation()
{
    delete ui;
}

void FromTreeManipulation::itemChanged()
{
    QListWidgetItem *curitem = ui->listWidget->currentItem();

    int r = ui->listWidget->row(curitem);

    if (r != -1)
    {
        ui->del->setDisabled(false);
        ui->sdnf->setDisabled(false);
        ui->sknf->setDisabled(false);
        ui->table->setDisabled(false);
        ui->save->setDisabled(false);
    }
}

void FromTreeManipulation::deleteItem()
{
    QListWidgetItem *curitem = ui->listWidget->currentItem();

    int r = ui->listWidget->row(curitem);

    if (r != -1)
    {
        deleteNode(head[r]);
        head.erase(head.begin() + r);
        delete ui->listWidget->takeItem(r);
        for (int i = 0; i < ui->listWidget->count() - r; ++i)
        {
            QString str = ui->listWidget->item(r + i)->text().split(".")[1];
            str.prepend(QString::number(r + i + 1) + ".");
            ui->listWidget->item(r + i)->setText(str);
        }
    }
    if (!ui->listWidget->count())
    {
        ui->del->setDisabled(true);
        ui->sdnf->setDisabled(true);
        ui->sknf->setDisabled(true);
        ui->table->setDisabled(true);
        ui->save->setDisabled(true);
        ui->delAll->setDisabled(true);
        ui->sdnfAll->setDisabled(true);
        ui->sknfAll->setDisabled(true);
        ui->tableAll->setDisabled(true);
        ui->saveAll->setDisabled(true);
    }
}

void FromTreeManipulation::deleteAllItem()
{
    for (int i = 0; i < ui->listWidget->count(); i++)
    {
        deleteNode(head[i]);
        delete ui->listWidget->item(i);
    }
    head.clear();
    /*очищение переменных и логических коснтант*/
    for (size_t i = 0; i < his.size(); i++)
    {
        deleteNode(his[i]);
    }
    his.clear();
    if (ui->listWidget->count() != 0)
    {
        ui->listWidget->clear();
    }
    ui->del->setDisabled(true);
    ui->sdnf->setDisabled(true);
    ui->sknf->setDisabled(true);
    ui->table->setDisabled(true);
    ui->save->setDisabled(true);
    ui->delAll->setDisabled(true);
    ui->sdnfAll->setDisabled(true);
    ui->sknfAll->setDisabled(true);
    ui->tableAll->setDisabled(true);
    ui->saveAll->setDisabled(true);
}

void FromTreeManipulation::saveItem()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt)"));

    QListWidgetItem *curitem = ui->listWidget->currentItem();
    int r = ui->listWidget->row(curitem);

    if (!fileName.isNull())
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            file.close();
            // error message
        }
        else if (r != -1)
        {
            QTextStream stream(&file);
            stream << curitem->text();
            stream.flush();
            file.close();
        }
    }
}

void FromTreeManipulation::saveAllItem()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt)"));

    if (!fileName.isNull())
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            file.close();
            // error message
        }
        else
        {
            QTextStream stream(&file);
            for (int i = 0; i < ui->listWidget->count(); i++)
                stream << ui->listWidget->item(i)->text() << endl;
            stream.flush();
            file.close();
        }
    }
}

void FromTreeManipulation::sdnfItem()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt)"));

    QListWidgetItem *curitem = ui->listWidget->currentItem();
    int r = ui->listWidget->row(curitem);

    if (!fileName.isNull())
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            file.close();
            // error message
        }
        else if (r != -1)
        {
            QTextStream stream(&file);
            std::vector<const Node*> headOne;
            headOne.push_back(head[r]);
            outputSdnf(his, headOne, stream);
            stream.flush();
            file.close();
        }
    }
}

void FromTreeManipulation::sdnfAllItem()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt)"));

    if (!fileName.isNull())
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            file.close();
            // error message
        }
        else
        {
            QTextStream stream(&file);
            outputSdnf(his, head, stream);
            stream.flush();
            file.close();
        }
    }
}

void FromTreeManipulation::sknfItem()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt)"));

    QListWidgetItem *curitem = ui->listWidget->currentItem();
    int r = ui->listWidget->row(curitem);

    if (!fileName.isNull())
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            file.close();
            // error message
        }
        else if (r != -1)
        {
            QTextStream stream(&file);
            std::vector<const Node*> headOne;
            headOne.push_back(head[r]);
            outputSknf(his, headOne, stream);
            stream.flush();
            file.close();
        }
    }
}

void FromTreeManipulation::sknfAllItem()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt)"));

    if (!fileName.isNull())
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            file.close();
            // error message
        }
        else
        {
            QTextStream stream(&file);
            outputSknf(his, head, stream);
            stream.flush();
            file.close();
        }
    }
}

void FromTreeManipulation::tableItem()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt)"));

    QListWidgetItem *curitem = ui->listWidget->currentItem();
    int r = ui->listWidget->row(curitem);

    if (!fileName.isNull())
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            file.close();
            // error message
        }
        else if (r != -1)
        {
            QTextStream stream(&file);
            std::vector<const Node*> headOne;
            headOne.push_back(head[r]);
            buildTableTruth(his, headOne, stream);
            stream.flush();
            file.close();
        }
    }
}

void FromTreeManipulation::tableAllItem()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt)"));

    if (!fileName.isNull())
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            file.close();
            // error message
        }
        else
        {
            QTextStream stream(&file);
            buildTableTruth(his, head, stream);
            stream.flush();
            file.close();
        }
    }
}

void FromTreeManipulation::generateAnother()
{
    /*восстановление исходного состояния*/
    ui->del->setDisabled(true);
    ui->sdnf->setDisabled(true);
    ui->sknf->setDisabled(true);
    ui->table->setDisabled(true);
    ui->save->setDisabled(true);
    ui->delAll->setDisabled(false);
    ui->sdnfAll->setDisabled(false);
    ui->sknfAll->setDisabled(false);
    ui->tableAll->setDisabled(false);
    ui->saveAll->setDisabled(false);
    /*очищение памяти всех деревьев*/
    for (size_t i = 0; i < head.size(); i++)
    {
        deleteNode(head[i]);
    }
    /*очищение переменных и логических коснтант*/
    for (size_t i = 0; i < his.size(); i++)
    {
        deleteNode(his[i]);
    }
    his.clear();
    head.clear();
    for (int i = 0; i < ui->listWidget->count(); i++)
    {
        delete ui->listWidget->item(i);
    }
    if (ui->listWidget->count() != 0)
    {
        ui->listWidget->clear();
    }
    stWidget->setCurrentIndex(2);
}

void FromTreeManipulation::updateTree()
{
    for (size_t i = 0; i < head.size(); ++i)
    {
        QString s;
        QTextStream os(&s);
        os<<"%1.";
        head[i]->qStringDisplay(0, os);
        ui->listWidget->addItem(s.arg(i+1));
    }
}
