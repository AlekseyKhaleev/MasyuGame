#pragma once

#include <QImage>
#include <QMap>
#include <QObject>
#include <QPoint>
#include <QStack>
#include <QSet>

#include <iostream>
#include <memory>




namespace Robot {

    enum Directions {
        LEFT, RIGHT, UP, DOWN
    };

    enum Colors {
        WHITE, GREEN, YELLOW, RED
    };

    struct Model {

        int score{0}, highScore{0}, steps{};

        QSet<QPoint> way;

        QString name, state;

        QPoint robotPosition, startPosition;

        Colors curColor{}, tmpColor{};

        Directions robotDestination{};

    };


    class RobotModel : public QObject {
    Q_OBJECT
    signals:
        void modelChanged(Robot::Model model);

    public slots:
        void initRobot();                                             // state "init"

        void wait();                                                  //state "wait"

        void rotate(Robot::Directions dir);   // state "rotate"

        void move(QPoint tar_pos); // state "move"

        void stepBack();                                              // state "step back"

        void replaceBattery(QPoint batPos);                           // state "replace battery"

        void exit(bool success);                                      // state "exit"

    public:
        explicit RobotModel(QString name="Robot", QObject *parent = nullptr);
        ~RobotModel() override;
        Robot::Model getModel();

    private:
        Model m_model;
        QStack<Model> m_memory;

        QPoint locateRobot();
    };
}

