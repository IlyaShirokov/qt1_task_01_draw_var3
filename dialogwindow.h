#ifndef DAILOGWINDOW_H
#define DAILOGWINDOW_H

#include <QLabel>
#include <QLayout>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class DialogWindow : public QDialog
{
    Q_OBJECT

public:
    DialogWindow(QWidget *parent = nullptr);

signals:
    void signal_setParameters(int, int, int);

private:
    QGridLayout m_layout;

    QLabel m_label_nSteps;
    QLabel m_label_dt;
    QLabel m_label_speed;

    QLineEdit m_lineEdit_nSteps;
    QLineEdit m_lineEdit_dT;
    QLineEdit m_lineEdit_speed;

    QPushButton m_pushButton_Ok;
    QPushButton m_pushButton_Cancel;

private slots:
    void slot_setParameters();
};

#endif // DAILOGWINDOW_H
