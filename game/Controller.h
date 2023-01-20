#pragma once

#include <QKeyEvent>
#include <QObject>
#include <QTimer>

#include "RobotModel.h"
#include "MazeModel.h"
#include "../MenuWidget.h"

class Controller: public QObject {

    Q_OBJECT

signals:
    void batteryFound(QPoint batPos);
    void batteryLocated(QPoint value);
    void energyChanged(int percEnergy);
    void levelDone(bool success=true);
    void resetMaze();
    void resetRobot();
    void returnClicked(int button=Menu::RETURN);
    void robotMoved(QPoint position, int score, Robot::Colors curColor);
    void robotRotated(Robot::Directions dir, Robot::Colors curColor);
    void skinAnimated();
    void stepBack();

public slots:
    void exit();
    void keyEventAction(int eventKey);
    void updateMazeModel(Maze::Model model);
    void updateRobotModel(Robot::Model model);
    void writeHighscore() const;



public:
    Controller(Robot::Model robotModel, Maze::Model mazeModel, QObject *parent= nullptr);
    ~Controller() override;

private:

    bool m_scoreIncrease;
    QTimer m_animationTimer;
    Robot::Model m_robotModel;
    Maze::Model m_mazeModel;

    [[nodiscard]] bool checkWall(QPoint dest) const;

    [[nodiscard]] int getPercentEnergy() const;
    [[nodiscard]] int updateScore() const;

    void checkBattery();
    void checkTarget();
    void locateBattery();
    void moveRobot();


    [[nodiscard]] QPoint getRandDot() const;

    Robot::Colors checkEnergy();
};


