#include "addworkerdialog.h"

#include <QLabel>
#include <QGridLayout>
#include <QPushButton>

AddWorkerDialog::AddWorkerDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Add worker");
    setFixedSize(400, 300);

    QLabel *first_name_label = new QLabel("First name:");
    m_first_name_edit = new QLineEdit;

    QLabel *last_name_label = new QLabel("Last name:");
    m_last_name_edit = new QLineEdit;

    QLabel *hourly_rate_label = new QLabel("Hourly rate:");
    m_hourly_rate_spin = new QDoubleSpinBox;
    m_hourly_rate_spin->setMaximum(1000.0);

    QLabel *hours_total_label = new QLabel("Hours total:");
    m_hours_total_spin = new QSpinBox;
    m_hours_total_spin->setMaximum(1000);

    m_ok_button= new QPushButton("OK");
    m_cancel_button= new QPushButton("Cancel");

    QGridLayout *layout= new QGridLayout();
    layout->addWidget(first_name_label, 0, 0);
    layout->addWidget(m_first_name_edit, 0, 1);
    layout->addWidget(last_name_label, 1, 0);
    layout->addWidget(m_last_name_edit, 1, 1);
    layout->addWidget(hourly_rate_label, 2, 0);
    layout->addWidget(m_hourly_rate_spin, 2, 1);
    layout->addWidget(hours_total_label, 3, 0);
    layout->addWidget(m_hours_total_spin, 3, 1);


    QHBoxLayout *button_layout = new QHBoxLayout;
    button_layout->addStretch();
    button_layout->addWidget(m_ok_button);
    button_layout->addWidget(m_cancel_button);

    layout->addLayout(button_layout, 4, 0, 1, 2);

    setLayout(layout);

    connect(m_ok_button, &QPushButton::clicked, this, [this]() {
        m_worker = std::make_unique<Worker>(
            m_first_name_edit->text().toStdString(),
            m_last_name_edit->text().toStdString(),
            m_hourly_rate_spin->value(),
            m_hours_total_spin->value()
        );
        accept();
    });
    connect(m_cancel_button, &QPushButton::clicked, this, &QDialog::reject);
}

auto AddWorkerDialog::worker() -> std::unique_ptr<Worker> & {
    return m_worker;
}
