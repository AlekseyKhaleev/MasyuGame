
#include "Controller.h"


#include <QCoreApplication>
#include <QKeyEvent>
#include <QTextStream>
#include <QTime>
#include <utility>

#include "../HighscoresWidget.h"


using namespace Highscores;

void Controller::keyEventAction(int eventKey) {
    switch (eventKey) {
        case Qt::Key_Left: {
            if(m_robotModel.robotDestination!=Robot::Directions::LEFT){
                emit robotRotated(Robot::Directions::LEFT);
            }
            break;
        }
        case Qt::Key_Right:{
            if(m_robotModel.robotDestination!=Robot::Directions::RIGHT){
                emit robotRotated(Robot::Directions::RIGHT);
            }
            break;
        }
        case Qt::Key_Up:{
            if(m_robotModel.robotDestination!=Robot::Directions::UP){
                emit robotRotated(Robot::Directions::UP);
            }
            break;
        }
        case Qt::Key_Down:{
            if(m_robotModel.robotDestination!=Robot::Directions::DOWN){
                emit robotRotated(Robot::Directions::DOWN);
            }
            break;
        }
        case Qt::Key_Space:{
            moveRobot();
            break;
        }
        case Qt::Key_Backspace:{
           emit stepBack();
           break;
        }
        case Qt::Key_Escape:{
            emit returnClicked();
            break;
        }

        default:break;
    }
//    if(m_robotModel.steps == m_mazeModel.maxEnergy) { emit levelDone(false); }
}


void Controller::updateMazeModel(Maze::Model model) {
    m_mazeModel = std::move(model);
}


void Controller::updateRobotModel(Robot::Model model) {
    m_robotModel = std::move(model);
    if(m_robotModel.state == "init"){ m_animationTimer.start(300); }
    if(m_robotModel.state == "exit"){ m_animationTimer.stop(); }
//    if(getPercentEnergy() || (m_robotModel.steps == m_mazeModel.maxEnergy)){ emit energyChanged(getPercentEnergy()); }
}


Controller::Controller(Robot::Model robotModel, Maze::Model mazeModel, QObject *parent) :
    QObject(parent), m_robotModel(std::move(robotModel)), m_mazeModel(std::move(mazeModel))
{
   m_scoreIncrease = true;
    m_animationTimer.start(300);
    connect(&m_animationTimer, SIGNAL(timeout()), this,  SIGNAL(skinAnimated()));
}


Controller::~Controller()=default;


bool Controller::checkWall(QPoint dest) const{
    return !(m_mazeModel.walls.contains(dest)||m_robotModel.way.contains(dest)||m_mazeModel.tmpWalls.contains(dest));
}


int Controller::updateScore() const
{
    if (m_scoreIncrease)
        return (m_robotModel.score + 1);
    else if (m_robotModel.score) {
        return (m_robotModel.score - 1);
    }
    else {return (m_robotModel.score);}
}

void Controller::checkPoint()
{
#define pos m_robotModel.robotPosition
#define way m_robotModel.way
#define tmpWalls m_mazeModel.tmpWalls
#define dest m_robotModel.robotDestination

    //удаляем диаганальные клетки из ограничений на движения
    QVector<QPoint> oldTmpWalls{
            QPoint{pos.rx() - 1, pos.ry() - 1},
            QPoint{pos.rx() + 1, pos.ry() + 1},
            QPoint{pos.rx() - 1, pos.ry() + 1},
            QPoint{pos.rx() + 1, pos.ry() - 1}
    };
    for(auto &p:oldTmpWalls){
        tmpWalls.remove(p);
    }

    if (m_mazeModel.whitePoints.contains(pos)) {
        //для белых точек
        if ((dest == Robot::UP) || (dest == Robot::DOWN)) {
            tmpWalls.insert(QPoint{pos.rx() - 1, pos.ry()}); //запрет левой клетки
            tmpWalls.insert(QPoint{pos.rx() + 1, pos.ry()}); //запрет правой клетки
        } else {
            tmpWalls.insert(QPoint{pos.rx(), pos.ry() - 1}); //запрет верхней клетки
            tmpWalls.insert(QPoint{pos.rx(), pos.ry() + 1}); //запрет нижней клетки
        }

        for (auto &p: oldTmpWalls) {  //если перед попаданием был поворот
            if (way.contains(p)) {
                emit TmpWallsUpdated(tmpWalls);
                return;
            }
        }
        //если поворота не было
        switch (dest) {
            //запрет прямого движения через ход
            case Robot::UP:
                tmpWalls.insert(QPoint{pos.rx(), pos.ry() - 2});
                break;
            case Robot::DOWN:
                tmpWalls.insert(QPoint{pos.rx(), pos.ry() + 2});
                break;
            case Robot::LEFT:
                tmpWalls.insert(QPoint{pos.rx() - 2, pos.ry()});
                break;
            case Robot::RIGHT:
                tmpWalls.insert(QPoint{pos.rx() + 2, pos.ry()});
                break;
            default:
                break;
        }
        emit TmpWallsUpdated(tmpWalls);
        return;
    }
    if(m_mazeModel.blackPoints.contains(pos)){
        switch (dest) {
            //запрет прямого движения через ход
            case Robot::UP:
                tmpWalls.insert(QPoint{pos.rx(), pos.ry() - 1});
                break;
            case Robot::DOWN:
                tmpWalls.insert(QPoint{pos.rx(), pos.ry() + 1});
                break;
            case Robot::LEFT:
                tmpWalls.insert(QPoint{pos.rx() - 1, pos.ry()});
                break;
            case Robot::RIGHT:
                tmpWalls.insert(QPoint{pos.rx() + 1, pos.ry()});
                break;
            default:
                break;
        }
    }
    emit TmpWallsUpdated(tmpWalls);
#undef pos
#undef way
#undef tmpWalls
#undef dest
}

//void Controller::checkBattery()
//{
//    if (m_mazeModel.batteries.contains(m_robotModel.robotPosition)) {
//       m_scoreIncrease = false;
//        emit batteryFound(m_robotModel.robotPosition);
//        emit energyChanged(getPercentEnergy());
//
//    }
//}


//void Controller::checkTarget(){
//    if (m_robotModel.robotPosition == m_mazeModel.targetPosition) {
//       m_scoreIncrease = true;
//       emit levelDone(true);
//    }
//}

void Controller::writeHighscore() const{
   auto *HSFile = new QFile("../resources/highscores.txt");
   if (!HSFile->open(QIODevice::ReadOnly | QIODevice::Text)){return;}
   QVector<Line> lines;
   while(!HSFile->atEnd()) {
      QString lineName = HSFile->readLine();
      lineName.remove('\n');
      QString lineScore = HSFile->readLine();
      lineName.remove('\n');
      lines.push_back(Line(lineName, lineScore.toInt()));
   }
   lines.push_back(Line(m_robotModel.name, m_robotModel.highScore));

   std::sort(lines.begin(), lines.end(), compareLines);

   HSFile->close();
   if (HSFile->open(QIODevice::WriteOnly | QIODevice::Text))
   {
      QTextStream out(HSFile);
      if (lines.size() < 10)
      {
         for (auto &i: lines) { out << i.NAME << '\n' << i.SCORE << '\n'; }
      } else
      {
         for (int i = 0; i < 10; i++) { out << lines[i].NAME << '\n' << lines[i].SCORE << '\n'; }
      }
      HSFile->close();
   }
}

//void Controller::locateBattery(){
//    QPoint battery;
//    do{
//        battery = getRandDot();
//    } while ((m_robotModel.robotPosition == battery) || (m_mazeModel.targetPosition == battery)
//             || (abs(battery.x() - m_robotModel.robotPosition.x()) > m_mazeModel.fieldWidth / 4)
//             || (abs(battery.y() - m_robotModel.robotPosition.y()) > m_mazeModel.fieldHeight / 2));
//    emit batteryLocated(battery);
//}


void Controller::moveRobot(){
#define pos m_robotModel.robotPosition

    QPoint tar_pos = m_robotModel.robotPosition;
    switch (m_robotModel.robotDestination) {
        case Robot::LEFT: {
            tar_pos.rx()-=1;
            if (checkWall(tar_pos)) {
                emit robotMoved(tar_pos);
                checkPoint();
            }
            break;
        }
        case Robot::RIGHT:{
            tar_pos.rx()+=1;
            if (checkWall(tar_pos)) {
                emit robotMoved(tar_pos);
                checkPoint();
            }
            break;
        }
        case Robot::UP:{
            tar_pos.ry()-=1;
            if (checkWall(tar_pos)) {
                emit robotMoved(tar_pos);
                checkPoint();
            }
            break;
        }
        case Robot::DOWN:{
            tar_pos.ry()+=1;
            if (checkWall(tar_pos)) {
                emit robotMoved(tar_pos);
                checkPoint();
            }
            break;
        }
        default: break;
    }

    for(auto &p:QVector<QPoint>{
        QPoint{pos.rx()+1,pos.ry()},
        QPoint{pos.rx()-1,pos.ry()},
        QPoint{pos.rx(),pos.ry()+1},
        QPoint{pos.rx(),pos.ry()-1}
        }){
        if(!(m_mazeModel.tmpWalls.contains(p)||m_mazeModel.walls.contains(p)||m_robotModel.way.contains(p))) return;
    }
    emit levelDone(false);
#undef pos
}


void Controller::exit()
{
   writeHighscore();
   emit returnClicked(Menu::END_GAME);
}


