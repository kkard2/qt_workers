#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QHeaderView>

#include <sstream>
#include <iomanip>
#include <numeric>
#include <set>

#include "addworkerdialog.h"

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

    auto bottom_row_layout = new QHBoxLayout;
    main_layout->addLayout(bottom_row_layout);

    m_delete_workers_button = new QPushButton("Remove worker(s)");
    bottom_row_layout->addWidget(m_delete_workers_button);

    auto add_worker_button = new QPushButton("Add worker");
    bottom_row_layout->addWidget(add_worker_button);

    m_total_paycheck_label = new QLabel;
    m_total_paycheck_label->setTextInteractionFlags(Qt::TextSelectableByMouse);
    bottom_row_layout->addWidget(m_total_paycheck_label);

    create_table();

    connect(m_table, &QTableWidget::itemSelectionChanged, this, &MainWindow::table_selection_changed);
    connect(m_delete_workers_button, &QPushButton::pressed, this, &MainWindow::delete_workers_button_pressed);
    connect(add_worker_button, &QPushButton::pressed, this, &MainWindow::add_worker_button_pressed);

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

    m_total_paycheck_label->setText(QString::fromStdString("Total paycheck: " + total_paycheck_ss.str()));

    m_delete_workers_button->setEnabled(!m_table->selectedItems().empty());
}

auto MainWindow::create_table() -> void {
    m_table = new QTableWidget;
    m_table_container->setWidget(m_table);

    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->verticalHeader()->setVisible(false);

    m_table->setColumnCount(5);
    m_table->setHorizontalHeaderLabels({
        "First name",
        "Last name",
        "Hourly rate",
        "Hours total",
        "Paycheck",
    });
}

auto MainWindow::populate_table() -> void {
    m_table->blockSignals(true);

    auto selected_items = m_table->selectedItems();
    auto selected_item_rows = std::vector<int>();

    for (const auto &item : selected_items) {
        selected_item_rows.push_back(item->row());
    }

    m_table->clearContents();
    m_table->setRowCount(static_cast<int>(m_workers.size()));

    for (size_t i = 0; i < m_workers.size(); ++i) {
        auto i_signed = static_cast<int>(i);
        const auto &worker = m_workers[i];
        m_table->setItem(i_signed, 0, new QTableWidgetItem(QString::fromStdString(worker.first_name())));
        m_table->setItem(i_signed, 1, new QTableWidgetItem(QString::fromStdString(worker.last_name())));

        auto hourly_rate_ss = std::stringstream();
        hourly_rate_ss << std::fixed << std::setprecision(2) << worker.hourly_rate();
        m_table->setItem(i_signed, 2, new QTableWidgetItem(QString::fromStdString(hourly_rate_ss.str())));

        m_table->setItem(i_signed, 3, new QTableWidgetItem(QString::fromStdString(std::to_string(worker.hours_total()))));

        auto paycheck_ss = std::stringstream();
        paycheck_ss << std::fixed << std::setprecision(2) << worker.paycheck();
        m_table->setItem(i_signed, 4, new QTableWidgetItem(QString::fromStdString(paycheck_ss.str())));
    }

    for (const auto &row : selected_item_rows) {
        if (row < m_table->rowCount()) {
            m_table->selectRow(row);
        }
    }

    m_table->blockSignals(false);
}

auto MainWindow::table_selection_changed() -> void {
    update();
}

auto MainWindow::delete_workers_button_pressed() -> void {
    auto selected_items = m_table->selectedItems();
    auto rows = std::set<int>();

    for (const auto &item : selected_items) {
        rows.insert(item->row());
    }

    auto rows_vector = std::vector(rows.begin(), rows.end());

    std::sort(rows_vector.begin(), rows_vector.end());

    for (int i = static_cast<int>(rows_vector.size()) - 1; i >= 0; i--) {
        m_workers.erase(m_workers.begin() + rows_vector[i]);
    }

    update();
}

auto MainWindow::add_worker_button_pressed() -> void {
    auto dialog = AddWorkerDialog(this);
    auto result = dialog.exec();

    if (result != QDialog::Accepted) {
        return;
    }

    auto &worker = dialog.worker();
    m_workers.push_back(*worker);
    update();
}
