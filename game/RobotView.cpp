
#include "RobotView.h"

#include <QCoreApplication>

#include <QKeyEvent>
#include <QMessageBox>
#include <QPainter>
#include <QStyleOption>
#include <QTimerEvent>
#include <utility>

#include "Utils.h"

using namespace utils;



RobotView::RobotView(Robot::Model targetModel, QWidget *parent):
QWidget(parent),
m_viewModel(std::move(targetModel)),
m_white(QVector<QImage>{
        QImage(":/images/VC_wt_lt"),
        QImage(":/images/VC_wt_rt"),
        QImage(":/images/VC_wt_up"),
        QImage(":/images/VC_wt_dn")
}),
m_green(QVector<QImage>{
        QImage(":/images/VC_gr_lt"),
        QImage(":/images/VC_gr_rt"),
        QImage(":/images/VC_gr_up"),
        QImage(":/images/VC_gr_dn")
}),
m_yellow(QVector<QImage>{
        QImage(":/images/VC_yw_lt"),
        QImage(":/images/VC_yw_rt"),
        QImage(":/images/VC_yw_up"),
        QImage(":/images/VC_yw_dn")
}),
m_red(QVector<QImage>{
        QImage(":/images/VC_rd_lt"),
        QImage(":/images/VC_rd_rt"),
        QImage(":/images/VC_rd_up"),
        QImage(":/images/VC_rd_dn")
}),
m_way(QImage(":/images/way")),
m_start(QImage(":/images/start"))
{
//    repaint();
}

void RobotView::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)
    drawWay();
    drawStartPoint();
    drawRobot();
}
void RobotView::keyPressEvent(QKeyEvent *event){

    emit keyHandled(event->key());
}

void RobotView::drawWay(){
    QPainter qp(this);
    for(auto &el: qAsConst(m_viewModel.way)) {
        qp.drawImage(QRect(el.x() * DOT_SIDE,el.y() * DOT_SIDE,DOT_SIDE,DOT_SIDE),m_way);
    }
}

void RobotView::drawStartPoint(){
    QPainter qp(this);
    qp.drawImage(QRect(m_viewModel.startPosition.x() * DOT_SIDE,m_viewModel.startPosition.y() * DOT_SIDE,
                       DOT_SIDE,DOT_SIDE),m_start);
}


void RobotView::drawRobot(){
    QPainter qp(this);

    qp.drawImage(QRect(m_viewModel.robotPosition.x() * DOT_SIDE,m_viewModel.robotPosition.y() * DOT_SIDE,
                       DOT_SIDE,DOT_SIDE),m_robotSkin[m_viewModel.curColor][m_viewModel.robotDestination]);
}

void RobotView::updateModel(Robot::Model model) {
    m_viewModel = std::move(model);
    repaint();
}

RobotView::~RobotView()=default;


