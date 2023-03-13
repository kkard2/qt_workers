#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QHeaderView>

#include <sstream>
#include <iomanip>
#include <numeric>

MainWindow::MainWindow() {
    setup();
}

auto MainWindow::setup() -> void {
    setWindowTitle("Workers");
    setMinimumSize(600, 400);

    auto main_widget = new QWidget();
    setCentralWidget(main_widget);
    auto main_layout = new QVBoxLayout();
    main_widget->setLayout(main_layout);

    auto header_label = new QLabel("Workers:");
    main_layout->addWidget(header_label);
    m_table_container = new QScrollArea;
    m_table_container->setWidgetResizable(true);
    main_layout->addWidget(m_table_container);

    m_workers = {
        Worker("Foo", "Bar", 20.5, 42),
        Worker("Baz", "Abc", 30.5, 84),
    };

    m_total_paycheck_label = new QLabel;
    m_total_paycheck_label->setTextInteractionFlags(Qt::TextSelectableByMouse);
    main_layout->addWidget(m_total_paycheck_label);

    update();
}

auto MainWindow::update() -> void {
    populate_table();

    auto total_paycheck = std::accumulate(
        m_workers.begin(),
        m_workers.end(),
        0.0,
        [](auto acc, const auto &worker) -> auto {
            return acc + worker.paycheck();
        }
    );

    auto total_paycheck_ss = std::stringstream();
    total_paycheck_ss << std::fixed << std::setprecision(2) << total_paycheck;

    m_total_paycheck_label->setText(QString(("Total paycheck: " + total_paycheck_ss.str()).c_str()));
}

auto MainWindow::create_table() -> void {
    m_table = new QTableWidget;
    m_table_container->setWidget(m_table);

    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->verticalHeader()->setVisible(false);

    m_table->setColumnCount(5);
    m_table->setHorizontalHeaderLabels({
        QString("First name"),
        QString("Last name"),
        QString("Hourly rate"),
        QString("Hours total"),
        QString("Paycheck"),
    });
}

auto MainWindow::populate_table() -> void {
    if (m_table == nullptr) {
        create_table();
    } else {
        m_table->clearContents();
    }

    m_table->setRowCount(static_cast<int>(m_workers.size()));

    for (size_t i = 0; i < m_workers.size(); ++i) {
        auto i_signed = static_cast<int>(i);
        const auto &worker = m_workers[i];
        m_table->setItem(i_signed, 0, new QTableWidgetItem(QString(worker.first_name().c_str())));
        m_table->setItem(i_signed, 1, new QTableWidgetItem(QString(worker.last_name().c_str())));

        auto hourly_rate_ss = std::stringstream();
        hourly_rate_ss << std::fixed << std::setprecision(2) << worker.hourly_rate();
        m_table->setItem(i_signed, 2, new QTableWidgetItem(QString(hourly_rate_ss.str().c_str())));

        m_table->setItem(i_signed, 3, new QTableWidgetItem(QString(std::to_string(worker.hours_total()).c_str())));

        auto paycheck_ss = std::stringstream();
        paycheck_ss << std::fixed << std::setprecision(2) << worker.paycheck();
        m_table->setItem(i_signed, 4, new QTableWidgetItem(QString(paycheck_ss.str().c_str())));
    }
}

