
#include "MenuWidget.h"

#include<QPushButton>
#include <QWidget>
#include <QGridLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QFont>
#include <QStyle>


MenuWidget::MenuWidget(QWidget *parent):
QWidget(parent), m_newGame(createButton(tr("New Game"))), m_controls(createButton("Control keys")),
m_highscores(createButton("Highscores")), m_about(createButton("About")), m_exit(createButton("Exit"))
{
    connect(m_newGame, SIGNAL(clicked()), this, SIGNAL(newGameClicked()));
    connect(m_controls, SIGNAL(clicked()), this, SIGNAL(controlsClicked()));
    connect(m_highscores, SIGNAL(clicked()), this, SIGNAL(highscoresClicked()));
    connect(m_about, SIGNAL(clicked()), this, SIGNAL(aboutClicked()));
    connect(m_exit,SIGNAL(clicked()), this, SIGNAL(exitClicked()));

    auto menuLabel = new QLabel(tr("Cleaner Adventures"));
    menuLabel->setStyleSheet("font: bold; font-size: 72px; height: 120px; width: 120px;");
    menuLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    auto layout = new QGridLayout;
    layout->addWidget(menuLabel,0,0,4,5);
    layout->addWidget(m_newGame,4,2,2,1);
    layout->addWidget(m_controls,6,2,2,1);
    layout->addWidget(m_highscores,8,2,2,1);
    layout->addWidget(m_about,10,2,2,1);
    layout->addWidget(m_exit,12,2,2,1);

    setLayout(layout);

}

void MenuWidget::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Escape){
        emit returnClicked();
    }

}

QPushButton *MenuWidget::createButton(const QString &text) {
    auto *button = new QPushButton(text);
    button->setDefault(true);

    button->setStyleSheet("QPushButton { font: bold; border: 3px solid darkgrey; border-radius: 20px;"
                          "outline-radius: 20px; font-size: 32px; height: 60px; width: 120px; }"
                          "QPushButton:focus { font: bold; border: 10px solid white; border-radius: 20px;"
                          "outline-radius: 20px; font-size: 32px }");

    return button;
}


MenuWidget::~MenuWidget()=default;

