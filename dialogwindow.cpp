#include "dialogwindow.h"

DialogWindow::DialogWindow(QWidget *parent) : QDialog(parent),
    m_label_nSteps("Amount steps ="), m_label_dt("Time interval ="), m_label_speed("Max speed = "),
    m_lineEdit_nSteps("50"), m_lineEdit_dT("5"), m_lineEdit_speed("30"),
    m_pushButton_Ok("OK"), m_pushButton_Cancel("Cancel")
{
    setModal(true);
    setWindowTitle("Parameters");
    setLayout(&m_layout);

    m_layout.addWidget(&m_label_nSteps, 0, 0);
    m_layout.addWidget(&m_lineEdit_nSteps, 0, 1);
    m_layout.addWidget(&m_label_dt, 1, 0);
    m_layout.addWidget(&m_lineEdit_dT, 1, 1);
    m_layout.addWidget(&m_label_speed, 2, 0);
    m_layout.addWidget(&m_lineEdit_speed, 2, 1);

    m_layout.addWidget(&m_pushButton_Ok, 3, 0);
    m_layout.addWidget(&m_pushButton_Cancel, 3, 1);

    connect(&m_pushButton_Ok, &QPushButton::clicked, this, &DialogWindow::slot_setParameters);
    connect(&m_pushButton_Cancel, &QPushButton::clicked, this, &DialogWindow::hide);
}

void DialogWindow::slot_setParameters()
{
    emit signal_setParameters(m_lineEdit_nSteps.text().toInt(), m_lineEdit_dT.text().toInt(), m_lineEdit_speed.text().toInt());
    this->hide();
}
