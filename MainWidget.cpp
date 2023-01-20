//
// Created by kristofer on 22.12.22.
//

#include "MainWidget.h"

#include <QCoreApplication>
#include <QStackedLayout>
#include <QWidget>
#include <utility>

#include "AboutWidget.h"

using namespace Menu;

MainWidget::MainWidget(QWidget *parent):
        QWidget(parent), m_menu(new MenuWidget), m_layout(new QStackedLayout), m_controls(new ControlsWidget),
        m_auth(new AuthWidget), m_about(new AboutWidget), m_highscores(new HighscoresWidget)
{
    this->setStyleSheet("QWidget {background-color: black; color: WHITE;}");

    connect(m_menu, SIGNAL(newGameClicked(int)), this, SLOT(changeWidgets(int)));
    connect(m_menu, SIGNAL(controlsClicked(int)), this, SLOT(changeWidgets(int)));
    connect(m_menu, SIGNAL(highscoresClicked(int)), this, SLOT(changeWidgets(int)));
    connect(m_menu, SIGNAL(aboutClicked(int)), this, SLOT(changeWidgets(int)));
    connect(m_menu, SIGNAL(exitClicked(int)), this, SLOT(changeWidgets(int)));
    connect(m_menu, SIGNAL(returnClicked(int)), this, SLOT(changeWidgets(int)));
    connect(m_controls, SIGNAL(returnClicked(int)), this, SLOT(changeWidgets(int)));
    connect(m_about, SIGNAL(returnClicked(int)), this, SLOT(changeWidgets(int)));
    connect(m_auth, SIGNAL(nameChanged(QString)), this, SLOT(initNewGame(QString)));
    connect(m_highscores, SIGNAL(returnClicked(int)), this, SLOT(changeWidgets(int)));


    m_layout->setStackingMode(QStackedLayout::StackOne);

    m_layout->addWidget(m_menu);
    m_layout->addWidget(m_controls);
    m_layout->addWidget(m_auth);
    m_layout->addWidget(m_about);
    m_layout->addWidget(m_highscores);

    setLayout(m_layout);
}


void MainWidget::initNewGame(QString name){
   if(m_game != nullptr) {
      m_layout->removeWidget(m_game);
      delete m_game;
      m_game = nullptr;
   }
    m_game = new GameWidget(std::move(name));
    connect(m_game, SIGNAL(returnClicked(int)), this, SLOT(changeWidgets(int)));
    connect(m_menu, SIGNAL(exitClicked(int)), m_game, SIGNAL(writeHighscore()));

    m_layout->addWidget(m_game);
    m_layout->setCurrentWidget(m_game);
}


void MainWidget::changeWidgets(int button) {
    switch(button){
        case Menu::NEW_GAME:{
            m_layout->setCurrentWidget(m_auth);
            break;
        }
        case Menu::RETURN:{
            if((m_layout->currentWidget() == m_menu) && (m_game != nullptr)){ m_layout->setCurrentWidget(m_game); }
            else{ m_layout->setCurrentWidget(m_menu); }
            break;
        }
        case Menu::CONTROLS:  { m_layout->setCurrentWidget(m_controls); break; }
        case Menu::HIGHSCORES:{
           m_highscores->readHighscores();
           m_layout->setCurrentWidget(m_highscores);
           break;
        }
        case Menu::ABOUT:     { m_layout->setCurrentWidget(m_about); break;    }
        case Menu::EXIT:      { QCoreApplication::quit(); break; }
        case Menu::END_GAME:
        {
           m_layout->setCurrentWidget(m_menu);
           m_layout->removeWidget(m_game);
           delete m_game;
           m_game = nullptr;
           break;
        }
        default:break;
    }

}


MainWidget::~MainWidget()=default;
