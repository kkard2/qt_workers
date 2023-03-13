#ifndef WORKER_H
#define WORKER_H

#include <string>
#include <cstdint>

class Worker {
private:
    std::string m_first_name;
    std::string m_last_name;
    double m_hourly_rate;
    uint32_t m_hours_total;

public:
    Worker(std::string first_name, std::string last_name, double hourly_rate, uint32_t hours_total);

public:
    auto first_name() const -> const std::string &;
    auto last_name() const -> const std::string &;
    auto hourly_rate() const -> double;
    auto hours_total() const -> uint32_t;

    auto paycheck() const -> double;
};

#endif // WORKER_H
