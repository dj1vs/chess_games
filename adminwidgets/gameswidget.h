#ifndef GAMESWIDGET_H
#define GAMESWIDGET_H

#include "../form/formwidget.h"

#include <QWidget>

#include <QLineEdit>
#include <QSpinBox>
#include <QTextBrowser>
#include <QCompleter>


class GamesWidget : public FormWidget {
    Q_OBJECT
public:
    explicit GamesWidget(FormWidget *parent = nullptr);
    ~GamesWidget();
private:
    void loadPage();
    inline void loadLists();

    void loadChessplayers();
    void loadOpenings();
    void loadTournaments();
    
    QSpinBox *id;
    QLineEdit *format, *timeControl, *date, *white, *black, *result, *opening, *tournament;
    QTextBrowser *moves;

    QCompleter *chessplayersCompleter, *openingsCompleter, *tournamentsCompleter;

    QStringList chessplayers, openings, tournaments;

};
#endif //GAMESWIDGET_H
