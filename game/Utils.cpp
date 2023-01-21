#include "Utils.h"

QPoint utils::getRandDot() {
    QTime time = QTime::currentTime();
    srand((uint) time.msec());
    QPoint dot;
    Screen screen;
    dot.rx() = (rand() % (screen.HEIGHT - 2)) + ((screen.WIDTH - screen.HEIGHT) / 2);
    dot.ry() = (rand() % (screen.HEIGHT - 2)) + 1;
    return dot;
}
