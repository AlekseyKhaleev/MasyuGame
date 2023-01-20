#pragma once

#include <QGuiApplication>
#include <QMap>
#include <QObject>
#include <QPoint>
#include <QScreen>
#include <QSet>
#include <QStack>
#include <QVector>
#include <QWidget>

inline uint qHash(const QPoint &key) { return (key.x() << 16) + key.y(); }

namespace Maze {

    struct Model {
        static const int DOT_SIDE{34};
        int level{0}, fieldWidth{}, fieldHeight{}, maxEnergy{};

        QSet<QPoint> walls, cells;
        QVector<QPoint> batteries;
        QPoint targetPosition;
        Model() = default;
    };

    class MazeModel : public QObject {

    Q_OBJECT

    public:
        explicit MazeModel(QObject *parent = nullptr);
        ~MazeModel() override;

    signals:
        void modelChanged(Maze::Model model);

    public slots:
        void addBattery(QPoint value);

        void delBattery(QPoint value);

        void stepBack();

        void initMaze();

        void resetLevel(bool success);

        Model getMazeModel();

    private:
        Model m_model;

        void initFieldSize();

        void initDefaultMazeMap();

        void locateWalls();

        QPoint getRandDot();

        void setMaxEnergy();

        static QVector<QPoint> getMazeNeighbours(QPoint current, const QSet<QPoint> &cells);

        static QVector<QPoint> getWayNeighbours(QPoint current, const QSet<QPoint> &cells);
    };
}

