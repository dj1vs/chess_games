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
signals:
    void chessplayers();
    void openings();
    void tournaments();
    void places();
    void judges();
    void games();
    void back();


private:
    QLabel *title;
    QPushButton *chessplayersButton;
    QPushButton *openingsButton;
    QPushButton *tournamentsButton;
    QPushButton *placesButton;
    QPushButton *judgesButton;
    QPushButton *gamesButton;
    QPushButton *backButton;

    QVBoxLayout *layout;

};


#endif //ADMINWIDGET_H