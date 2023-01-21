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
        int level{0};
        QSet<QPoint> walls, tmpWalls, cells, blackPoints, whitePoints;
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

        void updateTmpWalls(QSet<QPoint> tmpWalls);

        Model getMazeModel();

    private:
        Model m_model;

        QStack<Model> m_memory;

        void initDefaultMazeMap();

        static QVector<QPoint> getMazeNeighbours(QPoint current, const QSet<QPoint> &cells);

        static QVector<QPoint> getWayNeighbours(QPoint current, const QSet<QPoint> &cells);

        void locateNodes();
    };
}

