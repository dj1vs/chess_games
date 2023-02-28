#ifndef CHESSGAMESLISTWIDGET_H
#define CHESSGAMESLISTWIDGET_H

#include <QWidget>

class ChessGamesListWidget : public QWidget {
    Q_OBJECT
public:
    explicit ChessGamesListWidget(QWidget *parent = nullptr);
    ~ChessGamesListWidget();
};
#endif //CHESSGAMESLISTWIDGET_H