#include "RobotModel.h"


#include <QKeyEvent>
#include <QStyleOption>
#include <QtGui>
#include <QVector>
#include <utility>

#include "Utils.h"


using namespace Robot;

//*****************************************************

//Constructor
RobotModel::RobotModel(QString name, QObject *parent): QObject(parent)
{
    m_model.name = std::move(name);
    initRobot();
}

//Destructor
RobotModel::~RobotModel()=default;


//*****************************************************
QPoint RobotModel::locateRobot(){
    auto const rec = QGuiApplication::primaryScreen()->size();
    QPoint pos;
    pos.rx() = rec.width() / (Robot::Model::DOT_SIDE*2);
    pos.ry() = rec.height() * 0.8 / (Robot::Model::DOT_SIDE*2);
    return pos;
}
void RobotModel::initRobot(){
    m_model.state = "init";
    m_model.robotDestination = UP;
    m_model.robotPosition = locateRobot();
    m_model.way.insert(m_model.robotPosition);
    m_model.curColor = GREEN;
    m_model.tmpColor = WHITE;
    m_model.steps = 0;
    m_memory.clear();
    m_memory.push(m_model);
    if(m_model.score){ m_model.score += 100; }
    emit modelChanged(m_model);
}



void RobotModel::stepBack(){

   if(!m_memory.isEmpty()){
      Model lastModel = m_memory.pop();
      if(lastModel.steps == m_model.steps){
         stepBack();
      }
      else
      {
         m_model.robotPosition = lastModel.robotPosition;
         m_model.robotDestination = lastModel.robotDestination;
         m_model.score = lastModel.score;
         m_model.steps = lastModel.steps;
         m_model.way = lastModel.way;
         m_model.curColor = lastModel.curColor;
         m_model.tmpColor = lastModel.tmpColor;
         m_model.state = "step back";
         emit modelChanged(m_model);
      }
      if(m_memory.isEmpty()){
         m_memory.push(m_model);
      }
   }
}


void RobotModel::rotate(Robot::Directions dir) {
    m_model.state = "rotate";
    m_model.robotDestination = dir;
    m_model.steps++;
    m_memory.push(m_model);
    emit modelChanged(m_model);
}

void RobotModel::move(QPoint tar_pos) {
    m_model.state = "move";
    m_model.steps++;
    m_model.robotPosition = tar_pos;
    m_model.way.insert(tar_pos);
    m_memory.push(m_model);
    emit modelChanged(m_model);
}

void RobotModel::wait() {
    m_model.state = "wait";
    qSwap(m_model.curColor, m_model.tmpColor);
    emit modelChanged(m_model);
}


Robot::Model RobotModel::getModel() {
    return m_model;
}

void RobotModel::replaceBattery(QPoint batPos) {
    Q_UNUSED(batPos)
    m_model.state = "replace battery";
    m_model.steps = 0;
    m_model.score += 50;
    m_model.curColor = Robot::GREEN;
    m_model.tmpColor = Robot::WHITE;
    m_memory.push(m_model);
    emit modelChanged(m_model);

}

void RobotModel::exit(bool success) {
   m_model.state = "exit";
    if(!success){
       m_model.score = 0;
       m_model.highScore = 0;
       m_model.curColor = Robot::WHITE;
       m_model.tmpColor = Robot::WHITE;
    } else
    {
       m_model.highScore += m_model.score;
    }
    emit modelChanged(m_model);
}






