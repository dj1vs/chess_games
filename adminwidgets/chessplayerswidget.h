#ifndef CHESSPLAYERSWIDGET_H
#define CHESSPLAYERSWIDGET_H

#include "../form/formwidget.h"

#include <QWidget>

#include <QLineEdit>
class ChessplayersWidget : public FormWidget {
    Q_OBJECT
public:
    explicit ChessplayersWidget(FormWidget *parent = nullptr);
    ~ChessplayersWidget();
private:
    void loadPage();
    void setMaxInd() {curInd = worker->getMaxChessplayerID();};
    void saveChanges();
    inline bool checkIfRecordExists();

    QLineEdit *name, *id, *rating, *birthYear;
    QPushButton *save;
};
#endif //CHESSPLAYERSWIDGET_H
