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
    explicit GamesWidget(FormWidget *parent = nullptr);
    ~GamesWidget();
private:
    void loadPage();
    inline void loadLists();
    void loadChessplayers();
    void loadOpenings();
    void loadTournaments();

    void saveChanges();

    QString getOpeningID();
    quint32 getTournamentID();
    quint32 getChessplayerID(QString name);
    
    QSpinBox *id;
    QLineEdit *format, *timeControl, *date, *white, *black, *result, *opening, *tournament;
    QTextEdit *moves;
    QPushButton *save;

    QCompleter *chessplayersCompleter, *openingsCompleter, *tournamentsCompleter;

    QStringList chessplayers, openings, tournaments;

};
#endif //GAMESWIDGET_H
