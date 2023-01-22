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
    void levelDone(bool success=true);
    void resetMaze();
    void resetRobot();
    void returnClicked(int button=Menu::RETURN);
    void robotMoved(QPoint position);
    void robotRotated(Robot::Directions dir);
    void skinAnimated();
    void stepBack();
    void TmpWallsUpdated(QSet<QPoint> tmpWalls);

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
    QStack<QPoint> m_trueWay;
    bool m_scoreIncrease;
    QTimer m_animationTimer;
    Robot::Model m_robotModel;
    Maze::Model m_mazeModel;

    [[nodiscard]] bool checkWall(QPoint dest) const;
    [[nodiscard]] int updateScore() const;

    void moveRobot(bool solver=false);
    void checkPoints();
    bool checkTarget();

    bool solve();

    QSet<QPoint> getNeighbours();

    void rotate(QPoint dest);
};


