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
    void setChessplayer(DMap map);
private:
    void loadPage();
    void connectWorker();
    void setMaxInd() {curInd = worker->getMaxChessplayerID();};
    void saveChanges();

    QLineEdit *name, *id;
    QSpinBox *rating, *birthYear;
    QPushButton *save;
signals:
    void getChessplayer(quint32 ind);
};
#endif //CHESSPLAYERSWIDGET_H
