#ifndef CHESSPLAYERSWIDGET_H
#define CHESSPLAYERSWIDGET_H

#include "../form/formwidget.h"

#include <QWidget>
#include <QSpinBox>

#include <QLineEdit>
class ChessplayersWidget : public FormWidget {
    Q_OBJECT
public:
    explicit ChessplayersWidget(SQLWorker *w, FormWidget *parent = nullptr);
    ~ChessplayersWidget();
public slots:
    void load(DMap map);
private:
    void loadPage();
    void connectWorker();
    //void setMaxInd() {curInd = worker->getMaxChessplayerID();};

    QLineEdit *name, *id;
    QSpinBox *rating, *birthYear;
    QPushButton *save;
signals:
    void getChessplayer(quint32 ind);
    void setChessplayer(DMap player);
};
#endif //CHESSPLAYERSWIDGET_H
