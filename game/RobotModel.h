#pragma once

#include <QImage>
#include <QMap>
#include <QObject>
#include <QPoint>
#include <QStack>

#include <iostream>
#include <memory>


//inline uint qHash(const QPoint &key) { return (key.x() << 16) + key.y(); }


namespace Robot {
    enum Directions {
        LEFT, RIGHT, UP, DOWN
    };

    enum Colors {
        WHITE, GREEN, YELLOW, RED
    };

    struct Model {
        static const int DOT_SIDE{34};

        int score{0}, highScore{0}, steps{};

        QString name, state;

        QPoint robotPosition;

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

        void rotate(Robot::Directions dir, Robot::Colors curColor);   // state "rotate"

        void move(QPoint tar_pos, int score, Robot::Colors curColor); // state "move"

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
    };
}

