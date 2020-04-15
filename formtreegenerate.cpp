#include "formtreegenerate.h"
#include "ui_formtreegenerate.h"

#include <QApplication>
#include <QObject>
#include <QDebug>

FormTreeGenerate::FormTreeGenerate(std::vector<Node*>& _his, std::vector<Node*>& _head, QStackedWidget *stWidget, QWidget *parent) :
    QWidget(parent), ui(new Ui::FormTreeGenerate), his(_his), head(_head)
{
    ui->setupUi(this);
    this->stWidget = stWidget;

    for (int var = 0; var < VARIABLE_COUNT; ++var)
    {
        masX[var] = 0;
    }

    masOp[0] = masOp[1] = masOp[2] = true;
    for (int var = 3; var < 8; ++var)
    {
        masOp[var] = false;
    }

    for (int var = 0; var < 2; ++var)
    {
        masLg[var] = false;
    }

    checkGenerate(); /*проверка на возможность генерации*/

    connect(ui->quitBtn, &QPushButton::clicked, qApp, &QApplication::quit); /*кнопка выход*/
    connect(ui->X, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &FormTreeGenerate::spinBoxChanged); /*изменение значений переменных*/
    connect(ui->Y, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &FormTreeGenerate::spinBoxChanged); /*изменение значений переменных*/
    connect(ui->Z, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &FormTreeGenerate::spinBoxChanged); /*изменение значений переменных*/
    connect(ui->T, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &FormTreeGenerate::spinBoxChanged); /*изменение значений переменных*/
    connect(ui->K, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &FormTreeGenerate::spinBoxChanged); /*изменение значений переменных*/
    connect(ui->L, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &FormTreeGenerate::spinBoxChanged); /*изменение значений переменных*/
    connect(ui->M, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &FormTreeGenerate::spinBoxChanged); /*изменение значений переменных*/
    connect(ui->N, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &FormTreeGenerate::spinBoxChanged); /*изменение значений переменных*/
    connect(ui->P, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &FormTreeGenerate::spinBoxChanged); /*изменение значений переменных*/
    connect(ui->S, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &FormTreeGenerate::spinBoxChanged); /*изменение значений переменных*/

    connect(ui->AND, &QCheckBox::stateChanged, this, &FormTreeGenerate::checkBoxOPChanged); /*иземенение количества операций*/
    connect(ui->OR, &QCheckBox::stateChanged, this, &FormTreeGenerate::checkBoxOPChanged); /*иземенение количества операций*/
    connect(ui->NOT, &QCheckBox::stateChanged, this, &FormTreeGenerate::checkBoxOPChanged); /*иземенение количества операций*/
    connect(ui->IMPLICATION, &QCheckBox::stateChanged, this, &FormTreeGenerate::checkBoxOPChanged); /*иземенение количества операций*/
    connect(ui->EKV, &QCheckBox::stateChanged, this, &FormTreeGenerate::checkBoxOPChanged); /*иземенение количества операций*/
    connect(ui->HATCH, &QCheckBox::stateChanged, this, &FormTreeGenerate::checkBoxOPChanged); /*иземенение количества операций*/
    connect(ui->PIERCE, &QCheckBox::stateChanged, this, &FormTreeGenerate::checkBoxOPChanged); /*иземенение количества операций*/
    connect(ui->XOR, &QCheckBox::stateChanged, this, &FormTreeGenerate::checkBoxOPChanged); /*иземенение количества операций*/

    connect(ui->lgTrue, &QCheckBox::stateChanged, this, &FormTreeGenerate::checkBoxLgChanged); /*изменение наличия логических констант*/
    connect(ui->lgFalse, &QCheckBox::stateChanged, this, &FormTreeGenerate::checkBoxLgChanged); /*изменение наличия логических констант*/

    connect(ui->generateBtn, &QPushButton::clicked, this, &FormTreeGenerate::generateClick); /*нажатие на кнопку генерировать*/
    connect(ui->sCountFormula, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &FormTreeGenerate::spinBoxFormulaChanged); /*изменение числа формул*/
}

FormTreeGenerate::~FormTreeGenerate()
{
    delete ui;
}

void FormTreeGenerate::spinBoxChanged(int var)
{
    int count;
    QString str = QObject::sender()->objectName();

    if (str == "X")
        count = 0;
    else if (str == "Y")
        count = 1;
    else if (str == "Z")
        count = 2;
    else if (str == "T")
        count = 3;
    else if (str == "K")
        count = 4;
    else if (str == "L")
        count = 5;
    else if (str == "M")
        count = 6;
    else if (str == "N")
        count = 7;
    else if (str == "P")
        count = 8;
    else if (str == "S")
        count = 9;
    else
        count = VARIABLE_COUNT;

    if (count != VARIABLE_COUNT)
    {
        int sum = 0;
        for (int i = 0; i < VARIABLE_COUNT; i++)
        {
            if (i == count)
                sum += var;
            else
                sum += masX[i];
        }
        if (sum <= VARIABLE_COUNT && sum >= 0)
        {
            masX[count] = var;
            ui->lCounter->setText(QString::number(sum));
        }
        else
        {
            switch (count)
            {
            case 0:
                ui->X->setValue(masX[0]);
                break;
            case 1:
                ui->Y->setValue(masX[1]);
                break;
            case 2:
                ui->Z->setValue(masX[2]);
                break;
            case 3:
                ui->T->setValue(masX[3]);
                break;
            case 4:
                ui->K->setValue(masX[4]);
                break;
            case 5:
                ui->L->setValue(masX[5]);
                break;
            case 6:
                ui->M->setValue(masX[6]);
                break;
            case 7:
                ui->N->setValue(masX[7]);
                break;
            case 8:
                ui->P->setValue(masX[8]);
                break;
            case 9:
                ui->S->setValue(masX[9]);
                break;
            }
        }
    }

    checkGenerate(); /*проверка на возможность генерации*/
}

void FormTreeGenerate::checkBoxOPChanged(int state)
{
    int count;
    QString str = QObject::sender()->objectName();

    if (str == "AND")
        count = 0;
    else if (str == "OR")
        count = 1;
    else if (str == "NOT")
        count = 2;
    else if (str == "IMPLICATION")
        count = 3;
    else if (str == "XOR")
        count = 4;
    else if (str == "EKV")
        count = 5;
    else if (str == "HATCH")
        count = 6;
    else if (str == "PIERCE")
        count = 7;
    else
        count = 8;

    if (count != 8)
    {
        if (state == Qt::Checked)
        {
            masOp[count] = true;
        }
        else
        {
            masOp[count] = false;
        }
    }

    checkGenerate(); /*проверка на возможность генерации*/
}

void FormTreeGenerate::checkBoxLgChanged(int state)
{
    int count;
    QString str = QObject::sender()->objectName();

    if (str == "lgFalse")
        count = 0;
    else if (str == "lgTrue")
        count = 1;
    else
        count = 2;

    if (count != 2)
    {
        if (state == Qt::Checked)
        {
            masLg[count] = true;
        }
        else
        {
            masLg[count] = false;
        }
    }

    checkGenerate(); /*проверка на возможность генерации*/
}

void FormTreeGenerate::spinBoxFormulaChanged(int var)
{
    qDebug() << var;
    checkGenerate(); /*проверка на возможность генерации*/
}

void FormTreeGenerate::generateClick()
{
    int countVar = 0;
    int countOp = 0;
    for (int i = 0; i < VARIABLE_COUNT; ++i)
    {
        for (int j = 0; j < masX[i]; j++)
        {
            countVar++;
        }
    }
    for (int i = 0; i < 8; ++i)
    {
        if (masOp[i])
            countOp++;
    }
    if (ui->sCountFormula->value() >= 1 && countVar >= 2 && countOp >= 1)
    {
        /*Генерация формул*/
        for (int i = 0; i < VARIABLE_COUNT; i++) /*переменные*/
        {
            for (int j = 0; j < masX[i]; j++)
            {
                his.push_back(new Node({ typeNode::VAR, variable(i) }, nullptr, nullptr));
            }
        }
        for (int i = 0; i <2; i++) /*логические константы*/
        {
            if (masLg[i])
                his.push_back(new Node({ typeNode::LOG_CONST, log_const(i) }, nullptr, nullptr));
        }
        /*операции*/
        std::vector<operation> oper;
        bool isNot = false;
        for (int i = 0; i < 8; i++)
        {
            if (i != 2)
            {
                if (masOp[i])
                oper.push_back(operation(i >=3 ? i - 1 : i));
            }
            else
            {
                if (masOp[i])
                    isNot = true;
            }
        }

        /*генерация*/
        generateNode(his, head, oper, isNot, static_cast<size_t>(ui->sCountFormula->value()));

        /*восстановление прежнего состояния*/
        for (int var = 0; var < VARIABLE_COUNT; ++var)
        {
            masX[var] = 0;
        }
        ui->X->setValue(masX[0]);
        ui->Y->setValue(masX[1]);
        ui->Z->setValue(masX[2]);
        ui->T->setValue(masX[3]);
        ui->K->setValue(masX[4]);
        ui->L->setValue(masX[5]);
        ui->M->setValue(masX[6]);
        ui->N->setValue(masX[7]);
        ui->P->setValue(masX[8]);
        ui->S->setValue(masX[9]);

        masOp[0] = masOp[1] = masOp[2] = true;
        for (int var = 3; var < 8; ++var)
        {
            masOp[var] = false;
        }
        ui->OR->setChecked(true);
        ui->NOT->setChecked(true);
        ui->AND->setChecked(true);
        ui->IMPLICATION->setChecked(false);
        ui->XOR->setChecked(false);
        ui->HATCH->setChecked(false);
        ui->EKV->setChecked(false);
        ui->PIERCE->setChecked(false);

        for (int var = 0; var < 2; ++var)
        {
            masLg[var] = false;
        }
        ui->lgTrue->setChecked(false);
        ui->lgFalse->setChecked(false);

        ui->sCountFormula->setValue(0);
        stWidget->setCurrentIndex(1);
    }
}

void FormTreeGenerate::checkGenerate()
{
    int countVar = 0;
    int countOp = 0;
    for (int i = 0; i < VARIABLE_COUNT; ++i)
    {
        for (int j = 0; j < masX[i]; j++)
        {
            countVar++;
        }
    }
    for (int i = 0; i < 8; ++i)
    {
        if (masOp[i])
            countOp++;
    }

    if (ui->sCountFormula->value() >= 1 && countVar >= 2 && countOp >= 1)
    {
        ui->generateBtn->setDisabled(false);
    }
    else
    {
        ui->generateBtn->setDisabled(true);
    }
}
