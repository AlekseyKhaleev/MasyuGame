#pragma once

#include "MenuWidget.h"

#include <QFile>
#include <QLabel>
#include <QMap>
#include <QWidget>
#include <utility>

namespace Highscores{
    struct Line{
        QString NAME;
        int SCORE;
        Line(QString name, int score){
            NAME = std::move(name);
            SCORE = score;
        }
    };
    static bool compareLines(const Line &first, const Line &second){
        return first.SCORE > second.SCORE;
    }
}

using namespace Highscores;
class HighscoresWidget : public QWidget {

Q_OBJECT

public:
    explicit HighscoresWidget(QWidget *parent= nullptr);
    ~HighscoresWidget() override;
signals:
    void returnClicked(int button=Menu::RETURN);

public slots:
    void keyPressEvent(QKeyEvent *event) override;
    void readHighscores();

private:
   QVector<Line> m_FileLines;
   QVector<QLabel> m_LayLines;
   QFile *m_HSFile;
   QGridLayout *m_layout;


   static QLabel *createLabel(const QString &text);
   void createLayLines();


};

