#pragma once

#include <QListWidget>
#include <QWidget>

#include "RobotView.h"

class LogView : public RobotView{

    Q_OBJECT

public:
    explicit LogView(Robot::Model targetModel, QWidget *parent= nullptr);
    ~LogView() override;

public slots:
    void updateModel(Robot::Model model) override;
private:
    QListWidget *m_logs;

};

