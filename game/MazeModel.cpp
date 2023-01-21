#include "MazeModel.h"

#include <QGuiApplication>
#include <qpoint.h>
#include <qset.h>
#include <QStack>
#include <QTime>
#include <QVector>
#include <QWidget>

using namespace Maze;

//************************************************


MazeModel::MazeModel(QObject *parent): QObject(parent)
{
    initFieldSize();
    initMaze();
}

MazeModel::~MazeModel()=default;

//******************************************************

void MazeModel::initMaze(){
    initDefaultMazeMap();
    locateNodes();
    m_model.level ++;
    emit modelChanged(m_model);
}

QPoint MazeModel::getRandDot(){
    QTime time = QTime::currentTime();
    srand((uint) time.msec());
    QPoint dot;
    do{
        dot.rx() = (rand() % m_model.fieldWidth)+(m_model.fieldWidth-m_model.fieldHeight)/2;
        dot.ry() = rand() % m_model.fieldHeight;
    }while(m_model.walls.contains(dot));
    return dot;
}

void MazeModel::locateNodes() {
    for(int i=0; i<(m_model.fieldHeight*m_model.fieldHeight)/8;i++){
        QPoint dot;
        do{
            dot = getRandDot();
        }while(m_model.blackPoints.contains(dot) || m_model.whitePoints.contains(dot));
        m_model.blackPoints.insert(dot);
        do{
            dot = getRandDot();
        }while(m_model.blackPoints.contains(dot) || m_model.whitePoints.contains(dot));
        m_model.whitePoints.insert(dot);
    }
}


void MazeModel::initFieldSize(){
    auto const rec = QGuiApplication::primaryScreen()->size();
    m_model.fieldWidth = rec.width() / Maze::Model::DOT_SIDE;
    m_model.fieldHeight = rec.height() * 0.8 / Maze::Model::DOT_SIDE;

}

void MazeModel::initDefaultMazeMap(){
    m_model.cells.clear();
    m_model.walls.clear();
    QPoint dot;
    for(int y=0; y < m_model.fieldHeight; y++){
        for(int x=0; x < m_model.fieldWidth; x++){

            if ((y>0 &&x>=((m_model.fieldWidth - m_model.fieldHeight)/2)) && (y < m_model.fieldHeight - 1 && x < m_model.fieldWidth - ((m_model.fieldWidth - m_model.fieldHeight)/2))) {
                dot.rx() = x;
                dot.ry()= y;
                m_model.cells.insert(dot);
            } else {
                dot.rx() = x;
                dot.ry()= y;
                m_model.walls.insert(dot);
            }
        }
    }
}

Model MazeModel::getMazeModel(){
    return m_model;

}

void MazeModel::stepBack(){

   emit modelChanged(m_model);
}


QVector<QPoint> MazeModel::getMazeNeighbours(QPoint current, const QSet<QPoint>& cells){
    QVector<QPoint> curNeighbours;
    current.rx()+=2;
    if(cells.contains(current)){
        curNeighbours.push_back(current);
    }
    current.rx()-=4;
    if(cells.contains(current)){
        curNeighbours.push_back(current);
    }
    current.rx()+=2;
    current.ry()+=2;
    if(cells.contains(current)){
        curNeighbours.push_back(current);
    }
    current.ry()-=4;
    if(cells.contains(current)){
        curNeighbours.push_back(current);
    }
    return curNeighbours;
}


QVector<QPoint> MazeModel::getWayNeighbours(QPoint current, const QSet<QPoint> &cells) {
    QVector<QPoint> curNeighbours;
    current.rx()+=1;
    if(cells.contains(current)){
        curNeighbours.push_back(current);
    }
    current.rx()-=2;
    if(cells.contains(current)){
        curNeighbours.push_back(current);
    }
    current.rx()+=1;
    current.ry()+=1;
    if(cells.contains(current)){
        curNeighbours.push_back(current);
    }
    current.ry()-=2;
    if(cells.contains(current)){
        curNeighbours.push_back(current);
    }
    return curNeighbours;
}

void MazeModel::resetLevel(bool success) {
    if(!success){ m_model.level = 0; }
}


