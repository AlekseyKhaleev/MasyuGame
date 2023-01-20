#pragma once

#include <QWidget>

#include "MazeModel.h"


class MazeView : public QWidget{

    Q_OBJECT
public:
    explicit MazeView(Maze::Model targetModel, QWidget *parent= nullptr);
    ~MazeView() override;
public slots:
    void paintEvent(QPaintEvent *event) override;
    virtual void updateModel(const Maze::Model &model);

protected:
    Maze::Model m_viewModel;
private:

    QImage m_batteryImage;
    QImage m_targetImage;

    void drawMaze();
    void drawTarget();
    void drawBattery();
};



