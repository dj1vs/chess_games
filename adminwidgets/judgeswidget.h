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
    explicit JudgesWidget(FormWidget *parent = nullptr);
    ~JudgesWidget();
private:
    void loadPage();
    void setMaxInd() {QSqlQuery query("SELECT MAX(judge_id) FROM judges");
    if (query.next()) {
        curInd = query.value(0).toInt();
    }};
    void saveChanges();
    QSpinBox *id;
    QLineEdit *name, *mail;
    QPushButton *save;
    QTableView *tournaments;
};
#endif //JUDGESWIDGET_H
