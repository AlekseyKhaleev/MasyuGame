#pragma once

#include <QWidget>

#include "MenuWidget.h"
class AboutWidget: public QWidget {
    Q_OBJECT
public:
    explicit AboutWidget(QWidget *parent= nullptr);
    ~AboutWidget() override;

signals:
    void returnClicked(int button=Menu::RETURN);

public slots:
    void keyPressEvent(QKeyEvent *event) override;

};


