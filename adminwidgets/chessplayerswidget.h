#ifndef CHESSPLAYERSWIDGET_H
#define CHESSPLAYERSWIDGET_H

#include <QWidget>

class ChessplayersWidget : public QWidget {
    Q_OBJECT
public:
    explicit ChessplayersWidget(QWidget *parent = nullptr);
    ~ChessplayersWidget();
};
#endif //CHESSPLAYERSWIDGET_H