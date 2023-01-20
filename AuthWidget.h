#pragma once

#include <QInputDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>

class AuthWidget: public QWidget {

Q_OBJECT

public:
    explicit AuthWidget(QWidget *parent = nullptr);
    ~AuthWidget() override;

signals:
    void nameChanged(QString name);

private:
    QVBoxLayout *m_layout;
    QLineEdit *m_auth;

private slots:
    void changeName();
};
