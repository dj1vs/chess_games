#ifndef GAMESWIDGET_H
#define GAMESWIDGET_H
    
#include <QWidget>

class GamesWidget : public QWidget {
    Q_OBJECT
public:
    explicit GamesWidget(QWidget *parent = nullptr);
    ~GamesWidget();
};
#endif //GAMESWIDGET_H