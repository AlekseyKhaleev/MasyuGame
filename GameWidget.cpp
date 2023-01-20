#include "GameWidget.h"

#include <QCoreApplication>
#include <QLayout>
#include <QLCDNumber>
#include <QStackedLayout>
#include <QString>
#include <utility>

#include "game/EnergyView.h"
#include "game/LogView.h"
#include "game/MazeModel.h"
#include "game/RobotModel.h"


GameWidget::GameWidget(QString name, QWidget *parent)
    : QWidget{parent}, m_robotModel(new Robot::RobotModel(std::move(name))), m_mazeModel(new Maze::MazeModel(this)),
    m_energyView(new EnergyView), m_gameOverView(new GameOverView)
{
    m_controller = new Controller(m_robotModel->getModel(), m_mazeModel->getMazeModel());
    m_robotView  = new RobotView(m_robotModel->getModel());
    m_mazeView   = new MazeView(m_mazeModel->getMazeModel());
    m_levelView  = new LCDView(m_mazeModel->getMazeModel());
    m_scoreView  = new LCDView(m_robotModel->getModel());
    m_logView    = new LogView(m_robotModel->getModel());

    this->setStyleSheet("QWidget {background-color: black; color: WHITE;}");

    m_robotView->setFocusPolicy(Qt::StrongFocus);

    m_mazeView->setStyleSheet("MazeView {background-color: WHITE; color: black;}");


    //****************************************** CONNECTIONS *********************************************************

    //********* m_gameOverView sender **********
    connect(m_gameOverView, SIGNAL(gameStarted()),m_controller, SIGNAL(resetMaze()));
    connect(m_gameOverView, SIGNAL(gameStarted()),m_controller, SIGNAL(resetRobot()));
    connect(m_gameOverView, SIGNAL(gameEnded()),  m_controller, SLOT(exit()));

    //********* m_mazeModel sender ***********
    connect(m_mazeModel, SIGNAL(modelChanged(Maze::Model)),m_controller,SLOT(updateMazeModel(Maze::Model)));
    connect(m_mazeModel, SIGNAL(modelChanged(Maze::Model)),m_mazeView,  SLOT(updateModel(Maze::Model)));
    connect(m_mazeModel, SIGNAL(modelChanged(Maze::Model)),m_levelView, SLOT(updateModel(Maze::Model)));

    //********* m_robotModel sender ************
    connect(m_robotModel, SIGNAL(modelChanged(Robot::Model)),m_controller,SLOT(updateRobotModel(Robot::Model)));
    connect(m_robotModel, SIGNAL(modelChanged(Robot::Model)),m_robotView, SLOT(updateModel(Robot::Model)));
    connect(m_robotModel, SIGNAL(modelChanged(Robot::Model)),m_scoreView, SLOT(updateModel(Robot::Model)));
    connect(m_robotModel, SIGNAL(modelChanged(Robot::Model)),m_logView,   SLOT(updateModel(Robot::Model)));

    //********* m_robotView sender *************
    connect(m_robotView, SIGNAL(keyHandled(int)), m_controller, SLOT(keyEventAction(int)));

    //********* m_controller sender ************
    connect(m_controller, SIGNAL(levelDone(bool)),m_robotModel,  SLOT(exit(bool)));
    connect(m_controller, SIGNAL(levelDone(bool)),m_mazeModel,   SLOT(resetLevel(bool)));
    connect(m_controller, SIGNAL(levelDone(bool)),m_gameOverView,SLOT(levelDone(bool)));

    connect(m_controller, SIGNAL(resetMaze()),    m_mazeModel,   SLOT(initMaze()));
    connect(m_controller, SIGNAL(resetRobot()),   m_robotModel,  SLOT(initRobot()));

    connect(m_controller, SIGNAL(batteryFound(QPoint)),  m_mazeModel, SLOT(delBattery(QPoint)));
    connect(m_controller, SIGNAL(batteryFound(QPoint)),  m_robotModel,SLOT(replaceBattery(QPoint)));
    connect(m_controller, SIGNAL(batteryLocated(QPoint)),m_mazeModel, SLOT(addBattery(QPoint)));
    connect(m_controller, SIGNAL(stepBack()),            m_mazeModel, SLOT(stepBack()));

    connect(m_controller, SIGNAL(energyChanged(int)),                   m_energyView, SLOT(updateModel(int)));
    connect(m_controller, SIGNAL(stepBack()),                           m_robotModel, SLOT(stepBack()));
    connect(m_controller, SIGNAL(skinAnimated()),                       m_robotModel, SLOT(wait()));
    connect(m_controller, SIGNAL(robotRotated(Robot::Directions, Robot::Colors)),m_robotModel, SLOT(rotate(Robot::Directions, Robot::Colors)));
    connect(m_controller, SIGNAL(robotMoved(QPoint, int, Robot::Colors)),m_robotModel, SLOT(move(QPoint, int, Robot::Colors)));
    connect(m_controller, SIGNAL(returnClicked(int)),                   this, SIGNAL(returnClicked(int)));

    connect(this, SIGNAL(writeHighscore()), m_controller, SLOT(writeHighscore()));

    auto gameLay = new QStackedLayout;
    gameLay->setStackingMode(QStackedLayout::StackAll);
    gameLay->addWidget(m_mazeView);
    gameLay->addWidget(m_robotView);

    auto *layout = new QGridLayout;
    layout->addWidget(createLabel( m_robotModel->getModel().name + " ENERGY"), 0, 0, 2, 1);
    layout->addWidget(m_energyView,2,0,3,1);
    layout->addWidget(createLabel( "STATE LOG"), 0, 1, 2, 1);
    layout->addWidget(m_logView,2,1,3,1, Qt::AlignHCenter);
    layout->addWidget(createLabel("LEVEL"), 0, 2, 2, 1);
    layout->addWidget(m_levelView, 2, 2, 3, 1);
    layout->addWidget(createLabel("SCORE"), 0, 3, 2, 1);
    layout->addWidget(m_scoreView, 2, 3, 3, 1);
    layout->addLayout(gameLay, 6, 0, 20, 4);


    setLayout(layout);

}

QLabel *GameWidget::createLabel(const QString &text){
    auto *label = new QLabel(text);
    label->setStyleSheet("QLabel { font: bold; font-size: 30px; }");
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    return label;
}

GameWidget::~GameWidget()=default;
