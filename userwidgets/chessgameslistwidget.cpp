#include "chessgameslistwidget.h"

#include <QDebug>
#include <QStringList>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QHeaderView>

ChessGamesListWidget::ChessGamesListWidget(FormWidget *parent):
    FormWidget{parent} {
    formHeader = new FormHeader();
    formHeader->setTitle("Chess games list");

    date = new QLineEdit();
    whiteName = new QLineEdit();
    blackName = new QLineEdit();
    format = new QLineEdit();
    timeControl = new QLineEdit();
    opening = new QLineEdit();

    whiteRating = new QSpinBox;
    blackRating = new QSpinBox;

    moves = new QTextBrowser();

    ratingDifs = new QTableView;
    ratingDifs->setMinimumHeight(300);

    layout = new QGridLayout(this);

    layout->addWidget(formHeader);
    layout->addWidget(new QLabel("Date:"));
    layout->addWidget(date);
    layout->addWidget(new QLabel("White:"));
    layout->addWidget(new QLabel("Name:"));
    layout->addWidget(whiteName);
    layout->addWidget(new QLabel("Rating:"));
    layout->addWidget(whiteRating);
    layout->addWidget(new QLabel("Black:"));
    layout->addWidget(new QLabel("Name:"));
    layout->addWidget(blackName);
    layout->addWidget(new QLabel("Rating:"));
    layout->addWidget(blackRating);
    layout->addWidget(new QLabel("Format:"));
    layout->addWidget(format);
    layout->addWidget(new QLabel("Time control:"));
    layout->addWidget(timeControl);
    layout->addWidget(new QLabel("Played opening:"));
    layout->addWidget(opening);
    layout->addWidget(new QLabel("Moves:"));
    layout->addWidget(moves);
    layout->addWidget(new QLabel("Rating differences in games:"));
    layout->addWidget(ratingDifs);

    connectFormHeader();

    loadPage();
    
}

ChessGamesListWidget::~ChessGamesListWidget() {
    
}

void ChessGamesListWidget::loadPage() {
    QString queryString = "SELECT game_date, white.name, white.elo_rating, black.name, black.elo_rating, format,"
    " time_control, opening.name, chess_games.moves"
    " FROM chess_games"
    " INNER JOIN chessplayers AS white ON white_id = white.chessplayer_id"
    " INNER JOIN chessplayers AS black ON black_id = black.chessplayer_id"
    " INNER JOIN openings AS opening ON opening_id = opening.eco_id";
    queryString += " WHERE game_id = " + QString::number(curInd);

    QSqlQuery query(queryString);
    while(query.next()) {
        date->setText(query.value(0).toString());
        whiteName->setText(query.value(1).toString());
        whiteRating->setValue(query.value(2).toInt());
        blackName->setText(query.value(3).toString());
        blackRating->setValue(query.value(4).toInt());
        format->setText(query.value(5).toString());
        timeControl->setText(query.value(6).toString());
        opening->setText(query.value(7).toString());
        moves->setText(query.value(8).toString());
    }

    queryString = "SELECT name FROM chessplayers";
    query = QSqlQuery(queryString);
    QStringList names;
    while (query.next()) {
        names.push_back(query.value(0).toString());
    }

    QStandardItemModel *model = new QStandardItemModel();
    model->setRowCount(names.size());
    model->setColumnCount(names.size() + 2);
    model->setHeaderData(1, Qt::Horizontal, tr("Сумма"));

    for (int i = 1; i <= names.size(); ++i) {
        model->setHeaderData(i+1, Qt::Horizontal, QString(names[i-1]));
        int ind = 0;
        model->setData(model->index(i-1, ind++), names[i-1]);
        QString str = QString::number(i);
        queryString = "SELECT chessplayers.name, me.elo_rating-chessplayers.elo_rating"
        " FROM chess_games"
        " INNER JOIN chessplayers on white_id = chessplayers.chessplayer_id"
        " INNER JOIN chessplayers AS me ON black_id = me.chessplayer_id "
        " WHERE black_id = " + str;
        queryString += " UNION DISTINCT"
        " SELECT chessplayers.name, me.elo_rating-chessplayers.elo_rating"
        " FROM chess_games"
        " INNER JOIN chessplayers on black_id = chessplayers.chessplayer_id"
        " INNER JOIN chessplayers AS me ON white_id = me.chessplayer_id "
        " WHERE white_id = " + str;
        //qDebug() << queryString;

        ++++ind;
        query = QSqlQuery(queryString);
        //qDebug() << names[i-1];
        int sum = 0;
        while(query.next()) {
            ind = names.indexOf(query.value(0).toString());
            model->setData(model->index(i-1, ind + 2), query.value(1));
            sum += query.value(1).toInt();
        }
        model->setData(model->index(i-1, 1), QVariant(sum));
    }

    model->setHeaderData(0, Qt::Horizontal, tr("Шахматист"));

    ratingDifs->setModel(model);
    ratingDifs->show();


}
