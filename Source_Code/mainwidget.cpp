#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QDebug>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    this->init();

    connect(ui->stackedWidget, &QStackedWidget::currentChanged, this, &MainWidget::update);
}

MainWidget::~MainWidget()
{
    delete ui;
    delete menu;
    delete settings;
    delete formTreeGenerate;
    delete fromTreeManipulation;
}

void MainWidget::update()
{
    if (ui->stackedWidget->currentIndex() == int(screen::MANIPULATION))
        fromTreeManipulation->updateTree();
    if (ui->stackedWidget->currentIndex() == int(screen::GENERATE))
        formTreeGenerate->setVarText();
}

void MainWidget::init()
{
    state = new State();

    menu = new Menu(ui->stackedWidget);
    settings = new Settings(state, ui->stackedWidget);
    formTreeGenerate = new FormTreeGenerate(his, head, state, ui->stackedWidget);
    fromTreeManipulation = new FromTreeManipulation(his, head, state, ui->stackedWidget);

    ui->stackedWidget->insertWidget(int(screen::MENU), menu);
    ui->stackedWidget->insertWidget(int(screen::SETTINGS), settings);
    ui->stackedWidget->insertWidget(int(screen::GENERATE), formTreeGenerate);
    ui->stackedWidget->insertWidget(int(screen::MANIPULATION), fromTreeManipulation);

    ui->stackedWidget->setCurrentIndex(int(screen::MENU));
}
