#ifndef JUDGESWIDGET_H
#define JUDGESWIDGET_H

#include "../form/formwidget.h"
#include <QLineEdit>
#include <QTableView>
#include <QFormLayout>
#include <QSpinBox>

#include <QWidget>

class JudgesWidget : public FormWidget {
    Q_OBJECT
public:
    explicit JudgesWidget(SQLWorker *w, FormWidget *parent = nullptr);
    ~JudgesWidget();
private:
    void loadPage();
    void setMaxInd() {curInd = worker->getMaxJudgeID();};
    void saveChanges();
    QSpinBox *id;
    QLineEdit *name, *mail;
    QPushButton *save;
    QTableView *tournaments;
};
#endif //JUDGESWIDGET_H
