#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QScrollArea>

#include "worker.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    QTableWidget *m_table = nullptr;
    QScrollArea *m_table_container = nullptr;
    std::vector<Worker> m_workers;

public:
    MainWindow();

private:
    auto setup() -> void;
    auto create_table() -> void;
    auto populate_table() -> void;
};

#endif // MAINWINDOW_H
