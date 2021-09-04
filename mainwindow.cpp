#include "mainwindow.h"
#include <QtMath>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    m_menu_File("File"), m_menu_Edit("Edit"), m_menu_Help("Help"),
    m_pen(Qt::black, 3),
    m_amountSteps(0), m_timeIntervals(0), m_maxSpeed(0)
{
    setMinimumSize(400, 300);

    menuBar()->addMenu(&m_menu_File);
    menuBar()->addMenu(&m_menu_Edit);
    menuBar()->addMenu(&m_menu_Help);

    m_menu_File.addAction("Exit",  this, SLOT(close()));
    m_menu_Edit.addAction("Set parameters", this, SLOT(slot_dialogWindow()));
    m_menu_Help.addAction("About", this, SLOT(slot_messageBox()));

    m_messageBox.setIcon(QMessageBox::Information);
    m_messageBox.setModal(true);
    m_messageBox.setWindowTitle("About");
    m_messageBox.setStyleSheet("QLabel {font: 12pt TimesNewRoman;}");
    m_messageBox.setText("<p align=\"center\"> Internship Harman <br>Qt task #1 Draw <br>Made by Shirokov Ilya </p>");
    m_messageBox.addButton(m_messageBox.button(QMessageBox::StandardButton::Ok), QMessageBox::AcceptRole);

    connect(&m_dialogWindow, &DialogWindow::signal_setParameters, this, &MainWindow::slot_setParameters);
}

MainWindow::~MainWindow()
{
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    m_window_Width  = event->size().width();
    m_window_Height = event->size().height();

    motionSimulation();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    m_painter.begin(this);
    m_painter.drawPixmap(0, 0, m_pixmap);
    m_painter.end();
}

void MainWindow::motionSimulation()
{
    m_pixmap = QPixmap(m_window_Width, m_window_Height);
    m_pixmap.fill(Qt::white);

    m_painter.begin(&m_pixmap);
    m_painter.setPen(m_pen);
    QPoint currPoint(m_window_Width / 2, m_window_Height / 2);

    int lastSpeed;
    float lastAngle;
    makeVectorCoords(lastSpeed, lastAngle);

    m_painter.drawPoint(currPoint);
    m_painter.setFont(QFont("Times", 10, QFont::Bold));
    m_painter.drawText(currPoint, "Start Point");

    for (int i = 0; i < m_amountSteps - 1; ++i)
    {
        m_painter.drawLine(m_vecCoords.at(i), m_vecCoords.at(i + 1));

        if (i == m_amountSteps - 2)
        {
            const QRect rectangle = QRect(m_vecCoords.at(m_amountSteps - 1).x(), m_vecCoords.at(m_amountSteps - 1).y(), m_vecCoords.at(m_amountSteps - 1).x() + 50, m_vecCoords.at(m_amountSteps - 1).y() + 50);
            m_painter.drawText(rectangle, Qt::TextWordWrap, "End Point \nLast speed = " + QString::number(lastSpeed) + "\nLast angle = " + QString::number(lastAngle));
        }
    }

    m_painter.end();
}

void MainWindow::slot_dialogWindow()
{
    m_dialogWindow.show();
}
void MainWindow::slot_messageBox()
{
    m_messageBox.show();
}

void MainWindow::slot_setParameters(int nSteps, int dT, int speed)
{
    m_amountSteps  = nSteps;
    m_timeIntervals = dT;
    m_maxSpeed = speed;

    m_window_Width  = this->size().width();
    m_window_Height = this->size().height();

    motionSimulation();
}

void MainWindow::makeVectorCoords(int& speed, float& angle)
{
    m_vecCoords.clear();

    std::mt19937 gen(time(0));
    std::uniform_int_distribution<int> randomSpeed(1, m_maxSpeed);
    std::uniform_real_distribution<float> randomAngle(0, 2 * M_PI);

    int currSpeed, currDist, pointCounter = 0;
    float currAngle;
    QPoint currPoint(m_window_Width / 2, m_window_Height / 2);

    m_vecCoords.reserve(m_amountSteps);
    m_vecCoords.push_back(QPoint(m_window_Width / 2, m_window_Height / 2));

    while (pointCounter != m_amountSteps)
    {
        currSpeed = randomSpeed(gen);
        currAngle = randomAngle(gen);
        currDist = currSpeed * m_timeIntervals;
        currPoint.setX(currPoint.x() + (currDist * cos(currAngle)));
        currPoint.setY(currPoint.y() + (currDist * sin(currAngle)));

        if ((currPoint.x() < m_window_Width - 20) && (currPoint.y() < m_window_Height - 20) && (currPoint.x() > 20) && (currPoint.y() > 20))
        {
            m_vecCoords.push_back(currPoint);

            if (pointCounter == m_amountSteps - 1)
            {
                speed = currSpeed;
                angle = currAngle;
            }

            pointCounter ++;
        }
    }
}
