//
// Created by kristofer on 24.12.22.
//

#include "AuthWidget.h"

#include <QLabel>
#include <QKeyEvent>

AuthWidget::AuthWidget(QWidget *parent) :QWidget(parent), m_layout(new QVBoxLayout), m_auth(new QLineEdit)
{
    connect(m_auth, SIGNAL(returnPressed()), this, SLOT(changeName()));

    auto authLabel = new QLabel("Enter your name, robot: ");
    authLabel->setStyleSheet("font: bold; font-size: 72px; color: white; background-color: black");


    m_auth->setMaxLength(12);
    m_auth->setStyleSheet("border: 6px solid white; border-radius: 30px; font: bold; font-size: 48px; "
                       "color: white; background-color: black; width: 360px");
    m_auth->setTextMargins(12,0,0,0);


    m_layout->addWidget(authLabel,1, Qt::AlignCenter);
    m_layout->addWidget(m_auth,1, Qt::AlignTop|Qt::AlignHCenter);

    setLayout(m_layout);
}

void AuthWidget::changeName() {

    emit nameChanged(m_auth->text());
    m_auth->clear();
}

AuthWidget::~AuthWidget()=default;
