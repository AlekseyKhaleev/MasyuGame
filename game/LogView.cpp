

#include "LogView.h"

#include <QTime>
#include <QVBoxLayout>
#include <utility>


LogView::LogView(Robot::Model targetModel, QWidget *parent): RobotView(std::move(targetModel), parent), m_logs(new QListWidget)

{
    m_logs->setItemAlignment(Qt::AlignHCenter);
    m_logs->setStyleSheet("border: 6px solid white; font: bold; font-size: 14px");

    m_logs->addItem(QTime::currentTime().toString() + "   -   " + m_viewModel.state);
    m_logs->setFocusPolicy(Qt::NoFocus);
    m_logs->setWindowFlag(Qt::FramelessWindowHint);
    m_logs->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored);

    auto layout = new QVBoxLayout;
    layout->addWidget(m_logs);
    setLayout(layout);
}

void LogView::updateModel(Robot::Model model) {
    if(model.state != m_viewModel.state) {
        m_viewModel = model;
       if(m_viewModel.state == "init") { m_logs->clear(); }
        m_logs->addItem(QTime::currentTime().toString() + "   -   " + m_viewModel.state);
        m_logs->scrollToBottom();
    }
}


LogView::~LogView()=default;
