#pragma once

#include <QWidget>
#include <QTableView>
#include <QLabel>

#include "MenuWidget.h"

class ControlsWidget: public QWidget {

    Q_OBJECT

public:

    explicit ControlsWidget(QWidget *parent=nullptr);
    ~ControlsWidget() override;

signals:
    void returnClicked(int button=Menu::RETURN);

public slots:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QLabel *createLabel(const QString &text);
};
