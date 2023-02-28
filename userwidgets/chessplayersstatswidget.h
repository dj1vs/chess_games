#ifndef CHESSPLAYERSSTATSWIDGET_H
#define CHESSPLAYERSSTATSWIDGET_H

#include <QWidget>

class ChessplayersStatsWidget : public QWidget {
    Q_OBJECT
public:
    explicit ChessplayersStatsWidget(QWidget *parent = nullptr);
    ~ChessplayersStatsWidget();
};
#endif //CHESSPLAYERSSTATSWIDGET_H