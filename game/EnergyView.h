#pragma once

#include <QLabel>
#include <QObject>
#include <QWidget>


class EnergyView : public QWidget {

Q_OBJECT

public:
    explicit EnergyView(QWidget *parent = nullptr);

    ~EnergyView() override;

public slots:

    void updateModel(int percEnergy);

private:

    void paintEvent(QPaintEvent *event) override;

    enum Energy {
        en_0, en_10, en_30, en_50, en_70, en_80, en_90
    } m_enStatus;

    QVector<QImage*> m_enStatusImgs;

    void drawStatus();
};

