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
    locateWalls();
    if (!m_model.batteries.empty()) {
        m_model.batteries.clear();
    }
    m_model.batteries.push_back(QPoint{-1, -1});
    m_model.targetPosition = QPoint(m_model.fieldWidth - 2, m_model.fieldHeight - 2);
    setMaxEnergy();
    m_model.level ++;
    emit modelChanged(m_model);
}

QPoint MazeModel::getRandDot(){
    QTime time = QTime::currentTime();
    srand((uint) time.msec());
    QPoint dot;
    do{
        dot.rx() = rand() % m_model.fieldWidth;
        dot.ry() = rand() % m_model.fieldHeight;
    }while(m_model.walls.contains(dot));
    return dot;
}

void MazeModel::locateWalls(){
    QSet<QPoint> cells;
    for (auto &k: qAsConst(m_model.cells)){
        cells.insert(k);
    }
    QPoint current = getRandDot();
    QPoint next;
    QVector<QPoint> neighbours;
    QStack<QPoint> way;
    do{
        neighbours = getMazeNeighbours(current, cells);
        if(!neighbours.isEmpty()){
            next = neighbours[rand()%neighbours.size()];
            way.push(current);
            QPoint toDel = current;
            if(current.y() == next.y()){
                toDel.rx() = current.x()+((next.x()-current.x())/std::abs(next.x()-current.x()));
            }else{
            toDel.ry() = current.y()+((next.y()-current.y())/std::abs(next.y()-current.y()));
            }
            m_model.walls.remove(toDel);
            m_model.cells.insert(toDel);
            current = next;
            cells.remove(current);
        } else if(!way.empty()){
            current = way.pop();
        }
        else{
            QPoint key;
            for (auto &k: qAsConst(cells)){
                key = k;
                break;
            }
            current = key;
        }
    }while(!cells.empty());
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
            if ((x % 2 != 0 && y % 2 != 0) && (y < m_model.fieldHeight - 1 && x < m_model.fieldWidth - 1)) {
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

void MazeModel::addBattery(QPoint value) {
    m_model.batteries.push_back(value);
    emit modelChanged(m_model);
}

void MazeModel::delBattery(QPoint value) {
    m_model.batteries.removeAll(value);
    emit modelChanged(m_model);
}

Model MazeModel::getMazeModel(){
    return m_model;

}

void MazeModel::stepBack(){
   m_model.batteries.clear();
   emit modelChanged(m_model);
}


void MazeModel::setMaxEnergy() {
    m_model.maxEnergy = 2;
    QSet<QPoint> cells;
    for (auto k: qAsConst(m_model.cells)){
        cells.insert(k);
    }
    QPoint current{1,1};
    QVector<QPoint> neighbours;
    QStack<QPoint> way;
    cells.remove(current);
    while (current != m_model.targetPosition) {
        neighbours = getWayNeighbours(current, cells);
        if(!neighbours.empty()){
            way.push(current);
            current = neighbours[rand()%neighbours.size()];
            cells.remove(current);
        }
        else if(!way.isEmpty()){
            current = way.pop();
        }
        else{break;}
    }
    m_model.maxEnergy += way.size();
    for(int i=1;i<way.size()-1;i++){
        if((way[i-1].x()==way[i].x()&&way[i+1].y()==way[i].y())||(way[i-1].y()==way[i].y()&&way[i+1].x()==way[i].x())){
            m_model.maxEnergy++;
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


