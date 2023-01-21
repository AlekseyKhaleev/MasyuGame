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

#include "Utils.h"

namespace Maze {

    struct Model {
        static const int DOT_SIDE{68};
        int level{0}, fieldWidth{}, fieldHeight{};

        QSet<QPoint> walls, cells, blackPoints, whitePoints;
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

        void stepBack();

        void initMaze();

        void resetLevel(bool success);

        Model getMazeModel();

    private:
        Model m_model;

        void initFieldSize();

        void initDefaultMazeMap();

        QPoint getRandDot();

        static QVector<QPoint> getMazeNeighbours(QPoint current, const QSet<QPoint> &cells);

        static QVector<QPoint> getWayNeighbours(QPoint current, const QSet<QPoint> &cells);

        void locateNodes();
    };
}

