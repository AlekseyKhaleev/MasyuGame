#include "EnergyView.h"

#include <QPainter>
#include <QWidget>


EnergyView::EnergyView(QWidget *parent) :
        QWidget(parent), m_enStatusImgs(QVector<QImage*>{
        new QImage(":/images/en_0"),
        new QImage(":/images/en_10"),
        new QImage(":/images/en_30"),
        new QImage(":/images/en_50"),
        new QImage(":/images/en_70"),
        new QImage(":/images/en_80"),
        new QImage(":/images/en_90")
})
{
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Ignored);
    m_enStatus = en_90;
    repaint();
}

EnergyView::~EnergyView() = default;

void EnergyView::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)
    drawStatus();
}


void EnergyView::updateModel(int percEnergy) {
    if (percEnergy == 0) { m_enStatus = en_0; }
    else if (percEnergy <= 10) { m_enStatus = en_10; }
    else if (percEnergy <= 30) { m_enStatus = en_30; }
    else if (percEnergy <= 50) { m_enStatus = en_50; }
    else if (percEnergy <= 70) { m_enStatus = en_70; }
    else if (percEnergy <= 80) { m_enStatus = en_80; }
    else { m_enStatus = en_90; }
    repaint();
}


void EnergyView::drawStatus() {
    QPainter qp(this);
    qp.drawImage(QRect(this->width() / 2 - this->width() * 0.3, 0, this->width() * 0.6, this->height()),
                 *m_enStatusImgs[m_enStatus]);
}

