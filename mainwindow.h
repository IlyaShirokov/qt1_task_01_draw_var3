#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QtWidgets>
#include <QMessageBox>
#include <QDebug>

#include "dialogwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void resizeEvent(QResizeEvent*);
    void paintEvent(QPaintEvent*);

    void motionSimulation();
    void makeVectorCoords(int& speed, float& angle);

    DialogWindow m_dialogWindow;
    QMessageBox m_messageBox;

    QMenu m_menu_File;
    QMenu m_menu_Edit;
    QMenu m_menu_Help;

    QPainter m_painter;
    QPixmap  m_pixmap;
    QPen     m_pen;

    int m_window_Height;
    int m_window_Width;

    int m_amountSteps;
    int m_timeIntervals;
    int m_maxSpeed;
    QVector<QPoint> m_vecCoords;

private slots:
    void slot_dialogWindow();
    void slot_messageBox();
    void slot_setParameters(int nSteps, int dT, int speed);
};
#endif // MAINWINDOW_H
