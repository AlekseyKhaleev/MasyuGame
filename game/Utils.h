#pragma ones

#include <QGuiApplication>
#include <QSet>
#include <QPoint>
#include <QScreen>
#include <QSize>
#include <QTime>

namespace utils {
    const int DOT_SIDE{68};

    struct Screen {
        int WIDTH;
        int HEIGHT;
        Screen() {
            static auto const rec = QGuiApplication::primaryScreen()->size();
            WIDTH = rec.width() / DOT_SIDE;
            HEIGHT = rec.height() * 0.8 / DOT_SIDE;
        }
    };

    QPoint getRandDot();
}

inline uint qHash(const QPoint &key) { return (key.x() << 16) + key.y(); }

