#pragma once

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

namespace Menu{
    enum{
        RETURN, NEW_GAME, CONTROLS, HIGHSCORES, ABOUT, EXIT, END_GAME
    };
}

class MenuWidget: public QWidget {
Q_OBJECT

public:
    explicit MenuWidget(QWidget *parent = nullptr);

    ~MenuWidget() override;

signals:
    void returnClicked(int button=Menu::RETURN);
    void newGameClicked(int button=Menu::NEW_GAME);
    void controlsClicked(int button=Menu::CONTROLS);
    void highscoresClicked(int button=Menu::HIGHSCORES);
    void aboutClicked(int button=Menu::ABOUT);
    void exitClicked(int button=Menu::EXIT);

public slots:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QPushButton *m_newGame;
    QPushButton *m_controls;
    QPushButton *m_highscores;
    QPushButton *m_about;
    QPushButton *m_exit;

    QPushButton *createButton(const QString &text);


};
