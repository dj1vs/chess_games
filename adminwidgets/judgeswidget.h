#ifndef JUDGESWIDGET_H
#define JUDGESWIDGET_H

#include "../form/formwidget.h"
#include <QLineEdit>
#include <QTableView>
#include <QFormLayout>
#include <QSpinBox>
#include <QStandardItemModel>

#include <QWidget>

class JudgesWidget : public FormWidget {
    Q_OBJECT
public:
    explicit JudgesWidget(SQLWorker *w, FormWidget *parent = nullptr);
    ~JudgesWidget();
public slots:
    void loadJudge(const DMap &map);
    void loadJudgesTournaments(DTable table);
private:
    void loadPage();
    void connectWorker();


    QSpinBox *id;
    QLineEdit *name, *mail;
    QPushButton *save;
    QTableView *tournaments;
signals:
    void getJudge(quint32 ind);
    void getJudgesTournaments(quint32 ind);
    void setJudge(DMap map);
};
#endif //JUDGESWIDGET_H
