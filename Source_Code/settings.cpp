#include "settings.h"
#include "ui_settings.h"

Settings::Settings(State *state,
                   QStackedWidget *stWidget,
                   QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings), state(state), stWidget(stWidget)
{
    ui->setupUi(this);

}

Settings::~Settings()
{
    delete ui;
}
