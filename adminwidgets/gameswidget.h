#ifndef GAMESWIDGET_H
#define GAMESWIDGET_H

#include "../form/formwidget.h"

#include <QWidget>

#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QCompleter>
#include <QDateEdit>

#include <QGroupBox>
#include <QRadioButton>


class GamesWidget : public FormWidget {
    Q_OBJECT
public:
    explicit GamesWidget(SQLWorker *w, FormWidget *parent = nullptr);
    ~GamesWidget();
public slots:
    void load(const DMap &map);
    void loadChessplayers(QStringList names);
    void loadOpenings(QStringList names);
    void loadTournaments(QStringList names);
private:
    void loadPage();
    //void setMaxInd() {curInd = worker->getMaxGameID();};
    
    void connectWorker();
    
    QSpinBox *id;
    QDateEdit *date;
    QLineEdit *format, *timeControl, *white, *black, *opening, *tournament;
    QTextEdit *moves;
    QPushButton *save;

    QGroupBox *result;
    QRadioButton *win, *lose, *draw;


    QCompleter *chessplayersCompleter, *openingsCompleter, *tournamentsCompleter;

    QStringList chessplayers, openings, tournaments;
signals:
    void getGame(quint32 ind);
    void getChessplayers();
    void getOpenings();
    void getTournaments();

    void setGame(DMap map);
};
#endif //GAMESWIDGET_H
