#include "MazeView.h"

#include <QPainter>
#include <QKeyEvent>
#include <QVector>
#include <QtGui>
#include <QMessageBox>
#include <QStyleOption>
#include <utility>

using namespace Maze;

MazeView::MazeView(Model targetModel, QWidget *parent)
    : QWidget(parent), m_viewModel(std::move(targetModel)),m_blackImage(QImage(":/images/black.png")),
    m_whiteImage(QImage(":/images/white.png"))
{
    repaint();
}

MazeView::~MazeView()=default;



void MazeView::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)

//    QStyleOption opt;
//    opt.initFrom(this);
//    QPainter p(this);
//    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    drawMaze();
    drawNodes();

}

void MazeView::drawMaze(){
    QPainter qp(this);
    for(auto &w:qAsConst(m_viewModel.cells)){
        qp.setBrush(Qt::white);
        qp.drawRect(w.x()*Maze::Model::DOT_SIDE, w.y()*Maze::Model::DOT_SIDE, Maze::Model::DOT_SIDE, Maze::Model::DOT_SIDE);
    }
}

void MazeView::drawNodes(){
    QPainter qp(this);
    for (auto &b : m_viewModel.blackPoints) {
        qp.drawImage(QRect(b.x() * Maze::Model::DOT_SIDE, b.y() * Maze::Model::DOT_SIDE, Maze::Model::DOT_SIDE,
                           Maze::Model::DOT_SIDE), m_blackImage);
    }
    for (auto &b : m_viewModel.whitePoints) {
        qp.drawImage(QRect(b.x() * Maze::Model::DOT_SIDE, b.y() * Maze::Model::DOT_SIDE, Maze::Model::DOT_SIDE,
                           Maze::Model::DOT_SIDE), m_whiteImage);
    }
}

void MazeView::updateModel(const Maze::Model &model) {
    m_viewModel = model;
    repaint();
}




