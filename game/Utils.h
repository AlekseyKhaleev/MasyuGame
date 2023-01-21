#pragma ones

#include <QSet>
#include <QPoint>

inline uint qHash(const QPoint &key) { return (key.x() << 16) + key.y(); }
