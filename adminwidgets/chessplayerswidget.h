#ifndef CHESSPLAYERSWIDGET_H
#define CHESSPLAYERSWIDGET_H

#include "../form/formwidget.h"

#include <QWidget>
#include <QSpinBox>

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

    QLineEdit *name, *id;
    QSpinBox *rating, *birthYear;
    QPushButton *save;
};
#endif //CHESSPLAYERSWIDGET_H
