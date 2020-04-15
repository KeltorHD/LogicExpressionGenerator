#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    formTreeGenerate = new FormTreeGenerate(his, head, ui->stackedWidget);
    fromTreeManipulation = new FromTreeManipulation(his, head, ui->stackedWidget);

    ui->stackedWidget->insertWidget(1, fromTreeManipulation);
    ui->stackedWidget->insertWidget(2, formTreeGenerate);

    ui->stackedWidget->setCurrentIndex(2);

    connect(ui->stackedWidget, &QStackedWidget::currentChanged, this, &MainWidget::update);
}

MainWidget::~MainWidget()
{
    delete ui;
    delete formTreeGenerate;
    delete fromTreeManipulation;
}

void MainWidget::update()
{
    if (ui->stackedWidget->currentIndex() == 1)
        fromTreeManipulation->updateTree();
}
