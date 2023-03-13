#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>

#include "worker.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    QTableWidget *m_table = nullptr;
    QScrollArea *m_table_container = nullptr;
    QLabel *m_total_paycheck_label = nullptr;
    QPushButton *m_delete_workers_button = nullptr;
    std::vector<Worker> m_workers;

public:
    MainWindow();

private:
    auto setup() -> void;
    auto update() -> void;
    auto create_table() -> void;
    auto populate_table() -> void;

public slots:
    auto table_selection_changed() -> void;
    auto delete_workers_button_pressed() -> void;
};

#endif // MAINWINDOW_H
