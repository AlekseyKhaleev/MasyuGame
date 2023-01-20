#pragma once

#include <QLabel>
#include <QLCDNumber>
#include <QMessageBox>
#include <QObject>
#include <QWidget>

#include "game/Controller.h"
#include "game/GameOverView.h"
#include "game/EnergyView.h"
#include "game/LCDView.h"
#include "game/LogView.h"
#include "game/MazeModel.h"
#include "game/MazeView.h"
#include "game/RobotModel.h"
#include "game/RobotView.h"
#include "MenuWidget.h"


class GameWidget : public QWidget
{
    Q_OBJECT

signals:
    void returnClicked(int button=Menu::RETURN);
    void writeHighscore();

public:
    explicit GameWidget(QString name, QWidget *parent = nullptr);
    ~GameWidget() override;

private:
    Controller *m_controller;
    EnergyView *m_energyView;
    GameOverView *m_gameOverView;
    LCDView *m_levelView;
    LCDView *m_scoreView;
    LogView *m_logView;
    MazeView *m_mazeView;
    Maze::MazeModel *m_mazeModel;
    RobotView *m_robotView;
    Robot::RobotModel *m_robotModel;


    QLabel *createLabel(const QString &text);
};

