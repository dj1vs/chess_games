#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include <QVBoxLayout>

class AdminWidget : public QWidget {
    Q_OBJECT
public:
    explicit AdminWidget(QWidget *parent = nullptr);
    ~AdminWidget();


private:
    QLabel *title;
    QPushButton *chessplayers;
    QPushButton *openings;
    QPushButton *tournaments;
    QPushButton *places;
    QPushButton *judges;
    QPushButton *games;
    QPushButton *back;

    QVBoxLayout *layout;

};


#endif //ADMINWIDGET_H