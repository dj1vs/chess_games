#include "mainwindow.h"

#include "userwidget.h"
#include "adminwidget.h"

#include "userwidgets/chessgameslistwidget.h"
#include "userwidgets/chessplayersstatswidget.h"
#include "userwidgets/openingsstatswidget.h"
#include "userwidgets/tournamentsstatswidget.h"

#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    LoginWidget *loginWidget = new LoginWidget;
    setCentralWidget(loginWidget);

    about = new QAction(tr("About"));
    quit = new QAction(tr("Exit"));


    menu = new QMenuBar;

    menu->addAction(about);
    menu->addAction(quit);

    this->setMenuBar(menu);
    this->setWindowTitle("Chess games");

    connect(about, &QAction::triggered, this, [this] {
        QMessageBox msg;
        msg.setWindowTitle("About");
        msg.setText("(c) Djivs 2023\ngithub.com/Djivs");
        msg.setIcon(QMessageBox::Information);
        msg.exec();
    });
    connect(quit, &QAction::triggered, this, [this] {
        this->close();
    });
    connect(loginWidget, &LoginWidget::authorize, this, [this, loginWidget] {
        processAuthorization(loginWidget->getUserInputs());
        });

    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("chess_games");
    db.setUserName("postgres");
    db.setPassword("123");

    if (db.open()) {
        qDebug() << "Database successfully opened";
    } else {
        qDebug() << "Can't connect to database";
    }

    this->setMinimumSize(700, 300);
    this->setMaximumSize(1000, 600);

    
}

MainWindow::~MainWindow() {
    delete about, quit;
    delete menu;
}

void MainWindow::processAuthorization(QPair <QString, QString> authorizationParams) {
    const QString login = authorizationParams.first;
    const QString pass = authorizationParams.second;

    QSqlQuery query("SELECT pass FROM users WHERE login = \'" + login + "\';");
    int count = 0;
    bool isAuthorized = false;
    while(query.next()) {
        if (query.value(0).toString() == pass) {
            ++count;
            isAuthorized = true;
        }
    }

    if (isAuthorized && count == 1) {
        qDebug() << "Successfully logged in as " + login;
    } else {
        qDebug() << "Auth failed";
        return;
    }

    if (login == "admin") {
        AdminWidget *adminWidget = new AdminWidget();
        setCentralWidget(adminWidget);
        
    } else if (login == "user") {
        UserWidget *userWidget = new UserWidget();
        setCentralWidget(userWidget);

        connect(userWidget, &UserWidget::chessplayers, this, [this] {
            ChessplayersStatsWidget *chessplayersStatsWidget = new ChessplayersStatsWidget();
            QScrollArea *mw = new QScrollArea();
            mw->setWidget(chessplayersStatsWidget);

            setCentralWidget(mw);
        });
        connect(userWidget, &UserWidget::games, this, [this] {
            ChessGamesListWidget *chessGamesListWidget = new ChessGamesListWidget();
            setCentralWidget(chessGamesListWidget);;
        });
        connect(userWidget, &UserWidget::openings, this, [this] {
            OpeningsStatsWidget *openingsStatsWidget = new OpeningsStatsWidget();
            setCentralWidget(openingsStatsWidget);;
        });
        connect(userWidget, &UserWidget::tournaments, this, [this] {
            TournamentsStatsWidget *tournamentsStatsWidget = new TournamentsStatsWidget();
            setCentralWidget(tournamentsStatsWidget);;
        });
        
    }

}

