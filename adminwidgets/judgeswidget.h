#ifndef JUDGESWIDGET_H
#define JUDGESWIDGET_H

#include "../formwidget.h"
#include <QLineEdit>
#include <QTableView>
#include <QFormLayout>
#include <QComboBox>

#include <QWidget>

class JudgesWidget : public FormWidget {
    Q_OBJECT
public:
    explicit JudgesWidget(FormWidget *parent = nullptr);
    ~JudgesWidget();
private:
    void loadPage() {}
    QComboBox *id;
    QLineEdit *name, *mail;
    QTableView *tournaments;

    QFormLayout *layout;
};
#endif //JUDGESWIDGET_H
