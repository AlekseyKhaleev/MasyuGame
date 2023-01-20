#include "LCDView.h"

#include <QLCDNumber>
#include <QWidget>



LCDView::LCDView(const Maze::Model& model, QWidget *parent )
        :QLCDNumber(parent)
{
    this->setSegmentStyle(QLCDNumber::Filled);
    this->setDigitCount(getRange(model.level));
    this->display(model.level);
}


LCDView::LCDView(const Robot::Model& model, QWidget *parent )
    :QLCDNumber(parent)
{
    this->setSegmentStyle(QLCDNumber::Filled);
    this->setDigitCount(getRange(model.score));
    this->display(model.score);
}

void LCDView::updateModel(const Maze::Model& model) {
    this->setDigitCount(getRange(model.level));
    this->display(model.level);
}

void LCDView::updateModel(const Robot::Model& model) {

    this->setDigitCount(getRange(model.score));
    this->display(model.score);
}

int LCDView::getRange(int value) {
    int range{0};
    while(value !=0){
        range++;
        value /= 10;
    }
    return (range != 0? range: 1);
}

LCDView::~LCDView()=default;
