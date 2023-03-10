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
    void setMaxInd() {curInd = worker->getMaxGameID();};

    void saveChanges();
    
    QSpinBox *id;
    QLineEdit *format, *timeControl, *date, *white, *black, *result, *opening, *tournament;
    QTextEdit *moves;
    QPushButton *save;

    QCompleter *chessplayersCompleter, *openingsCompleter, *tournamentsCompleter;

    QStringList chessplayers, openings, tournaments;

};
#endif //GAMESWIDGET_H
