#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class UserWidget : public QWidget {
    Q_OBJECT
public:
    explicit UserWidget(QWidget *parent = nullptr);
    ~UserWidget();
private:
    QLabel *title;
    QPushButton *chessplayersStats;
    QPushButton *openingsStats;
    QPushButton *tournamentsStats;
    QPushButton *gamesList;
    QPushButton *back;
    QVBoxLayout *layout;
};
#endif //USERWIDGET_H