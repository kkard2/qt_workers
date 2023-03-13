#ifndef ADDWORKERDIALOG_H
#define ADDWORKERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>

#include <memory>

#include "worker.h"

class AddWorkerDialog : public QDialog {
    Q_OBJECT

private:
    QLineEdit *m_first_name_edit;
    QLineEdit *m_last_name_edit;
    QDoubleSpinBox *m_hourly_rate_spin;
    QSpinBox *m_hours_total_spin;
    QPushButton *m_ok_button;
    QPushButton *m_cancel_button;

    std::unique_ptr<Worker> m_worker = nullptr;

public:
    explicit AddWorkerDialog(QWidget *parent = nullptr);

public:
    auto worker() -> std::unique_ptr<Worker> &;
};

#endif // ADDWORKERDIALOG_H
