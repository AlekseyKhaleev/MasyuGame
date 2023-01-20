#pragma once

#include <QLCDNumber>
#include <QWidget>

#include "MazeModel.h"
#include "RobotModel.h"


class LCDView : public QLCDNumber{

Q_OBJECT

public:
    explicit LCDView(const Maze::Model& model, QWidget *parent = nullptr);
    explicit LCDView(const Robot::Model& model, QWidget *parent = nullptr);

    ~LCDView() override;

public slots:
    void updateModel(const Maze::Model& model);
    void updateModel(const Robot::Model& model);

private:
    static int getRange(int value);
};
