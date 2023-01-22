
#include <QGridLayout>
#include <QKeyEvent>
#include <QLabel>

#include "AboutWidget.h"

AboutWidget::AboutWidget(QWidget *parent): QWidget(parent)
{
    auto layout = new QGridLayout;

    auto title = new QLabel("About Masyu Game");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("QLabel { font: bold; font-size: 72px }");

    auto aboutLabel = new QLabel;
    aboutLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    aboutLabel->setStyleSheet("QLabel { font: bold; font-size: 32px }");
    aboutLabel->setText("Qt 6.4/C++ open source project\n"
                        "created by Aleksey Khaleev 22.01.2023\n\n\n"
                        "NIZHNY NOVGOROD STATE TECHNICAL UNIVERSITY\n"
                        "Institute of Radioelectronics and Information Technologies\n"
                        "Department of Informatics and Control Systems\n\n"
                        "Algorithms and data structures course work\n\n"
                        "\"Recursive algorithms\"\n\n"
                        "version 1.0\n\n\n"
                        "https://github.com/AlekseyKhaleev/MasyuGame.git");

    layout->addWidget(title,0,0,1,1);
    layout->addWidget(aboutLabel,1,0,4,1);
    setLayout(layout);
}

void AboutWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        emit returnClicked();
    }
}

AboutWidget::~AboutWidget()=default;
