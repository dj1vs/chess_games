#include "mainwindow.h"

#include "userwidget.h"
#include "adminwidget.h"

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
#include <QMap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qRegisterMetaType<DTable>();
    qRegisterMetaType<QVector <QPair<QString, quint32>>>();
    
    setupMenu();

    about = new QAction(tr("О создателе"));
    quit = new QAction(tr("Выход"));


    menu = new QMenuBar;

    menu->addAction(about);
    menu->addAction(quit);

    this->setMenuBar(menu);
    this->setWindowTitle("АСС \"Шахматные партии\"");

    connect(about, &QAction::triggered, this, [this] {
        QMessageBox msg;
        msg.setWindowTitle("О создателе");
        msg.setText("(c) Трифонов Дмитрий, ИУ5-45б 2023\ngithub.com/Djivs");
        msg.setIcon(QMessageBox::Information);
        msg.exec();
    });
    connect(quit, &QAction::triggered, this, [this] {
        this->close();
    });

    workerThread = new QThread;
    worker = new SQLWorker;
    
    connect(worker, SIGNAL(destroyed()), workerThread, SLOT(quit()));
    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
    connect(workerThread, &QThread::started, worker, &SQLWorker::connectToDB);
    connect(this, &MainWindow::getAuthResult, worker, &SQLWorker::authSuccess);
    connect(worker, &SQLWorker::authResultReady, this, &MainWindow::processAuthResults);

    worker->moveToThread(workerThread);
    workerThread->start();



    this->setMinimumSize(1000, 500);

    
}

MainWindow::~MainWindow() {
}

void MainWindow::processAuthResults(bool result) {
    if (result) {
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
        auto strings = loginWidget->getUserInputs();
        login = strings.first;
        pass = strings.second;

        emit getAuthResult(login, pass);
        });
    
}

void MainWindow::setupUser() {
    UserWidget *user = new UserWidget();
    setCentralWidget(user);

    connect(user, &UserWidget::chessplayers, this, [this] {
        ChessplayersStatsWidget *w = new ChessplayersStatsWidget(worker);
        setScrollWidget(w);

        connect(w, &ChessplayersStatsWidget::exit, this, [this] {
            setupUser();
        });
    });
    connect(user, &UserWidget::games, this, [this] {
        ChessGamesListWidget *w = new ChessGamesListWidget(worker);
        setScrollWidget(w);
        connect(w, &ChessGamesListWidget::exit, this, [this] {
            setupUser();
        });
    });
    connect(user, &UserWidget::openings, this, [this] {
        OpeningsStatsWidget *w = new OpeningsStatsWidget(worker);
        setScrollWidget(w);
        connect(w, &OpeningsStatsWidget::exit, this, [this] {
            setupUser();
        });
    });
    connect(user, &UserWidget::tournaments, this, [this] {
        TournamentsStatsWidget *w = new TournamentsStatsWidget(worker);
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
        ChessplayersWidget *w = new ChessplayersWidget(worker);
        setScrollWidget(w);
        connect(w, &ChessplayersWidget::exit, this, [this] {
            setupAdmin();
        });
    });
    connect(admin, &AdminWidget::openings, this, [this] {
        OpeningsWidget *w = new OpeningsWidget(worker);
        setScrollWidget(w);
        connect(w, &OpeningsWidget::exit, this, [this] {
            setupAdmin();
        });
    });
    connect(admin, &AdminWidget::tournaments, this, [this] {
        TournamentsWidget *w = new TournamentsWidget(worker);
        setScrollWidget(w);
        connect(w, &TournamentsWidget::exit, this, [this] {
            setupAdmin();
        });
    });
    connect(admin, &AdminWidget::places, this, [this] {
        PlacesWidget *w = new PlacesWidget(worker);
        setScrollWidget(w);
        connect(w, &PlacesWidget::exit, this, [this] {
            setupAdmin();
        });
    });
    connect(admin, &AdminWidget::judges, this, [this] {
        JudgesWidget *w = new JudgesWidget(worker);
        setScrollWidget(w);
        connect(w, &JudgesWidget::exit, this, [this] {
            setupAdmin();
        });
    });
    connect(admin, &AdminWidget::games, this, [this] {
        GamesWidget *w = new GamesWidget(worker);
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

void MainWindow::initWorker() {
    workerThread = new QThread;
    worker = new SQLWorker;
    
    worker->moveToThread(workerThread);
    connect(worker, SIGNAL(destroyed()), workerThread, SLOT(quit()));
    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
    workerThread->start();
}
