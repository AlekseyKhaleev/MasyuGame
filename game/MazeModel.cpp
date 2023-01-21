#include "MazeModel.h"

#include <QGuiApplication>
#include <qpoint.h>
#include <qset.h>
#include <QVector>
#include <QWidget>

using namespace Maze;

//************************************************


MazeModel::MazeModel(QObject *parent): QObject(parent)
{
    initMaze();
}

MazeModel::~MazeModel()=default;

//******************************************************

void MazeModel::initMaze(){
    initDefaultMazeMap();
    locateNodes();
    m_model.tmpWalls.clear();
    m_model.level ++;
    emit modelChanged(m_model);
}



void MazeModel::locateNodes() {
    m_model.blackPoints.clear();
    m_model.whitePoints.clear();
    utils::Screen screen;
    for(int i=0; i< (screen.HEIGHT * screen.HEIGHT) / 16; i++){
        QPoint dot;
        do{
            dot = utils::getRandDot();
        }while(m_model.blackPoints.contains(dot) || m_model.whitePoints.contains(dot));
        m_model.blackPoints.insert(dot);
        do{
            dot = utils::getRandDot();
        }while(m_model.blackPoints.contains(dot) || m_model.whitePoints.contains(dot));
        m_model.whitePoints.insert(dot);
    }
}


void MazeModel::initDefaultMazeMap(){
    using namespace utils;
    m_model.cells.clear();
    m_model.walls.clear();
    QPoint dot;
    Screen screen;
    for(int y=0; y < screen.HEIGHT; y++){
        for(int x=0; x < screen.WIDTH; x++){
            if ((y>0 &&x>=((screen.WIDTH - screen.HEIGHT) / 2)) && (y < screen.HEIGHT - 1 && x < screen.WIDTH - ((screen.WIDTH - screen.HEIGHT) / 2))) {
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
    if(!m_memory.isEmpty()){
        Model lastModel = m_memory.pop();
        if(lastModel.tmpWalls == m_model.tmpWalls){
            stepBack();
        }
        else
        {
            m_model.tmpWalls = lastModel.tmpWalls;
            emit modelChanged(m_model);
        }
        if(m_memory.isEmpty()){
            m_memory.push(m_model);
        }
    }
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

void MazeModel::updateTmpWalls(QSet<QPoint> tmpWalls) {
    m_model.tmpWalls = tmpWalls;
    emit modelChanged(m_model);
}


