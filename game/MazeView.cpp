#include "MazeView.h"

#include <QPainter>
#include <QKeyEvent>
#include <QVector>
#include <QtGui>
#include <QMessageBox>
#include <QStyleOption>
#include <utility>

//#include "Utils.h"

using namespace utils;
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
    drawMaze();
    drawTmpWalls();
    drawNodes();
}

void MazeView::drawTmpWalls(){
    QPainter qp(this);
    for(auto &w:qAsConst(m_viewModel.tmpWalls)){
        qp.setBrush(Qt::red);
        if(!m_viewModel.walls.contains(w))
        qp.drawRect(w.x()*DOT_SIDE, w.y()*DOT_SIDE, DOT_SIDE, DOT_SIDE);
    }
}

void MazeView::drawMaze(){
    QPainter qp(this);
    for(auto &c:qAsConst(m_viewModel.cells)){
        qp.setBrush(Qt::white);
        qp.drawRect(c.x() * DOT_SIDE, c.y() * DOT_SIDE, DOT_SIDE, DOT_SIDE);
    }
}

void MazeView::drawNodes(){
    QPainter qp(this);
    for (auto &b : m_viewModel.blackPoints) {
        qp.drawImage(QRect(b.x() * DOT_SIDE, b.y() * DOT_SIDE, DOT_SIDE,DOT_SIDE), m_blackImage);
    }
    for (auto &b : m_viewModel.whitePoints) {
        qp.drawImage(QRect(b.x() * DOT_SIDE, b.y() * DOT_SIDE, DOT_SIDE,DOT_SIDE), m_whiteImage);
    }
}

void MazeView::updateModel(const Maze::Model &model) {
    m_viewModel = model;
    repaint();
}




