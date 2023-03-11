#ifndef GAMESWIDGET_H
#define GAMESWIDGET_H

#include "../form/formwidget.h"

#include <QWidget>

#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QCompleter>


class GamesWidget : public FormWidget {
    Q_OBJECT
public:
    explicit GamesWidget(SQLWorker *w, FormWidget *parent = nullptr);
    ~GamesWidget();
public slots:
    void load(const DMap &map);
private:
    void loadPage();
    void setMaxInd() {curInd = worker->getMaxGameID();};
    
    void connectWorker();
    
    QSpinBox *id;
    QLineEdit *format, *timeControl, *date, *white, *black, *result, *opening, *tournament;
    QTextEdit *moves;
    QPushButton *save;

    QCompleter *chessplayersCompleter, *openingsCompleter, *tournamentsCompleter;

    QStringList chessplayers, openings, tournaments;
signals:
    void getGame(quint32 ind);
    void setGame(DMap map);
};
#endif //GAMESWIDGET_H
