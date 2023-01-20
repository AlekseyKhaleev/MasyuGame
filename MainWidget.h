#pragma once

#include <QMainWindow>

#include <QStackedLayout>

#include "AboutWidget.h"
#include "AuthWidget.h"
#include "MenuWidget.h"
#include "GameWidget.h"
#include "ControlsWidget.h"
#include "HighscoresWidget.h"

namespace {

}
class MainWidget: public QWidget {
Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget() override;
private:

    MenuWidget *m_menu;
    GameWidget *m_game;
    ControlsWidget *m_controls;
    QStackedLayout *m_layout;
    AuthWidget *m_auth;
    AboutWidget *m_about;
    HighscoresWidget *m_highscores;

public slots:
    void changeWidgets(int button);
    void initNewGame(QString name);
};


