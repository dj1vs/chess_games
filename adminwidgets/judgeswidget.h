#ifndef JUDGESWIDGET_H
#define JUDGESWIDGET_H

#include "../formheader.h"
#include <QLineEdit>
#include <QTableView>
#include <QFormLayout>
#include <QComboBox>

#include <QWidget>

class JudgesWidget : public QWidget {
    Q_OBJECT
public:
    explicit JudgesWidget(QWidget *parent = nullptr);
    ~JudgesWidget();
signals:
    void exit();
private:
    FormHeader *formHeader;
    QComboBox *id;
    QLineEdit *name, *mail;
    QTableView *tournaments;

    QFormLayout *layout;
};
#endif //JUDGESWIDGET_H
