#include "mainwindow.h"

#include "userwidget.h"
#include "adminwidget.h"

#include "sqlworker.h"
#include "userwidgets/chessgameslistwidget.h"
#include "userwidgets/chessplayersstatswidget.h"
#include "userwidgets/openingsstatswidget.h"
#include "userwidgets/tournamentsstatswidget.h"
#include "adminwidgets/chessplayerswidget.h"
#include "adminwidgets/gameswidget.h"
#include "adminwidgets/judgeswidget.h"
#include "adminwidgets/openingswidget.h"
#include "adminwidgets/placeswidget.h"
#include "adminwidgets/tournamentswidget.h"

#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    
    setupMenu();

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

    this->setMinimumSize(1000, 500);

    
}

MainWindow::~MainWindow() {
}

void MainWindow::processAuthorization(QPair <QString, QString> authorizationParams) {
    const QString login = authorizationParams.first;
    const QString pass = authorizationParams.second;

    SQLWorker *worker = new SQLWorker;
    bool t = worker->authSuccess(login, pass);


    if (t) {
        qDebug() << "Successfully logged in as " + login;
    } else {
        QMessageBox msg;
        msg.setWindowTitle("Error");
        msg.setText("Auth failed!");
        msg.setIcon(QMessageBox::Critical);
        msg.exec();
        return;
    }

    if (login == "admin") {
        setupAdmin();
        
    } else if (login == "user") {
        setupUser();
    }

}

void MainWindow::setupMenu() {
    LoginWidget *loginWidget = new LoginWidget;
    setCentralWidget(loginWidget);

    connect(loginWidget, &LoginWidget::authorize, this, [this, loginWidget] {
        processAuthorization(loginWidget->getUserInputs());
        });
    
}

void MainWindow::setupUser() {
    UserWidget *user = new UserWidget();
    setCentralWidget(user);

    connect(user, &UserWidget::chessplayers, this, [this] {
        ChessplayersStatsWidget *w = new ChessplayersStatsWidget();
        setScrollWidget(w);

        connect(w, &ChessplayersStatsWidget::exit, this, [this] {
            setupUser();
        });
    });
    connect(user, &UserWidget::games, this, [this] {
        ChessGamesListWidget *w = new ChessGamesListWidget();
        setScrollWidget(w);
        connect(w, &ChessGamesListWidget::exit, this, [this] {
            setupUser();
        });
    });
    connect(user, &UserWidget::openings, this, [this] {
        OpeningsStatsWidget *w = new OpeningsStatsWidget();
        setScrollWidget(w);
        connect(w, &OpeningsStatsWidget::exit, this, [this] {
            setupUser();
        });
    });
    connect(user, &UserWidget::tournaments, this, [this] {
        TournamentsStatsWidget *w = new TournamentsStatsWidget();
        setScrollWidget(w);
        connect(w, &TournamentsStatsWidget::exit, this, [this] {
            setupUser();
        });
    });
    connect(user, &UserWidget::back, this, [this] {
        setupMenu();
    });
}

void MainWindow::setupAdmin() {
    AdminWidget *admin = new AdminWidget();
    setCentralWidget(admin);

    connect(admin, &AdminWidget::chessplayers, this, [this] {
        ChessplayersWidget *w = new ChessplayersWidget;
        setScrollWidget(w);
        connect(w, &ChessplayersWidget::exit, this, [this] {
            setupAdmin();
        });
    });
    connect(admin, &AdminWidget::openings, this, [this] {
        OpeningsWidget *w = new OpeningsWidget;
        setScrollWidget(w);
        connect(w, &OpeningsWidget::exit, this, [this] {
            setupAdmin();
        });
    });
    connect(admin, &AdminWidget::tournaments, this, [this] {
        TournamentsWidget *w = new TournamentsWidget;
        setScrollWidget(w);
        connect(w, &TournamentsWidget::exit, this, [this] {
            setupAdmin();
        });
    });
    connect(admin, &AdminWidget::places, this, [this] {
        PlacesWidget *w = new PlacesWidget;
        setScrollWidget(w);
        connect(w, &PlacesWidget::exit, this, [this] {
            setupAdmin();
        });
    });
    connect(admin, &AdminWidget::judges, this, [this] {
        JudgesWidget *w = new JudgesWidget;
        setScrollWidget(w);
        connect(w, &JudgesWidget::exit, this, [this] {
            setupAdmin();
        });
    });
    connect(admin, &AdminWidget::games, this, [this] {
        GamesWidget *w = new GamesWidget;
        setScrollWidget(w);
        connect(w, &GamesWidget::exit, this, [this] {
            setupAdmin();
        });
    });
    connect(admin, &AdminWidget::back, this, [this] {
        setupMenu();
    });

}

inline void MainWindow::setScrollWidget(QWidget *w) {
    QScrollArea *mw = new QScrollArea();
    mw->setWidget(w);
    mw->setWidgetResizable(1);
    setCentralWidget(mw);
}
