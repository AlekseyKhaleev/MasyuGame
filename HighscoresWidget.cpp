
#include "HighscoresWidget.h"

#include <QFile>
#include <QKeyEvent>
#include <QLabel>


HighscoresWidget::HighscoresWidget(QWidget *parent)
: QWidget(parent), m_HSFile(new QFile("../resources/highscores.txt"))
{
   m_layout = new QGridLayout;
   setLayout(m_layout);
}

void HighscoresWidget::readHighscores(){
   m_FileLines.clear();

    if (m_HSFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
       while (!m_HSFile->atEnd()){
          QString lineName = m_HSFile->readLine();
          lineName.remove('\n');
          QString lineScore = m_HSFile->readLine();
          lineName.remove('\n');
          m_FileLines.push_back(Line(lineName, lineScore.toInt()));
       }
       m_HSFile->close();
       createLayLines();
    }
}

void HighscoresWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        emit returnClicked();
    }
}

QLabel *HighscoresWidget::createLabel(const QString &text) {
    auto *label = new QLabel(text);
    label->setStyleSheet("QLabel { font: bold; font-size: 32px }");
    label->setAlignment(Qt::AlignLeft);
    label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    return label;
}

void HighscoresWidget::createLayLines()
{
   QLayoutItem *item;
   while((item = m_layout->takeAt(0)) != nullptr){
      delete item->widget();
      delete item;
   }
   auto title = new QLabel("Highscores :");
   title->setAlignment(Qt::AlignCenter);
   title->setStyleSheet("QLabel { font: bold; font-size: 72px }");

   m_layout->addWidget(title, 0, 0, 2, 5);
   for (int i=0; (i<10) && (i < m_FileLines.size()); i++){
      m_layout->addWidget(createLabel(QString::number(i+1) + ". "), 2+i, 1,1,1, Qt::AlignRight);
      m_layout->addWidget(createLabel(m_FileLines[i].NAME), 2 + i, 2, 1, 1);
      m_layout->addWidget(createLabel(QString::number(m_FileLines[i].SCORE)), 2 + i, 3, 1, 1);
   }
}

HighscoresWidget::~HighscoresWidget()=default;