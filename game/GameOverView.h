
#pragma once

#include <QMessageBox>
#include <QPushButton>


class GameOverView : public QMessageBox {

    Q_OBJECT

public:
    explicit GameOverView(QMessageBox *parent = nullptr);

    ~GameOverView() override;

signals:
    void gameStarted();
    void gameEnded();

public slots:
    void levelDone(bool success);

private:

   QPushButton *m_accept;
   QPushButton *m_exit;

   static QPushButton* createButton(const QString &text);
};
