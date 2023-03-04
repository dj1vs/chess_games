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
    QSpinBox *id;
    QLineEdit *name, *mail;
    QTableView *tournaments;
};
#endif //JUDGESWIDGET_H
