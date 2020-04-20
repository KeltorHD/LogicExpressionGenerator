#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QStackedWidget *stWidget, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu), stWidget(stWidget)
{
    ui->setupUi(this);

    connect(ui->generate, &QPushButton::clicked, this, &Menu::generate);
    connect(ui->settings, &QPushButton::clicked, this, &Menu::settings);
    connect(ui->quit, &QPushButton::clicked, qApp, &QApplication::quit);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::generate()
{
    stWidget->setCurrentIndex(int(screen::GENERATE));
}

void Menu::settings()
{
    stWidget->setCurrentIndex(int(screen::SETTINGS));
}
