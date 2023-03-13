#include "worker.h"

Worker::Worker(std::string first_name, std::string last_name, double hourly_rate, uint32_t hours_total)
    : m_first_name(std::move(first_name))
    , m_last_name(std::move(last_name))
    , m_hourly_rate(hourly_rate)
    , m_hours_total(hours_total)
{
}

auto Worker::first_name() const -> const std::string & {
    return m_first_name;
}

auto Worker::last_name() const -> const std::string & {
    return m_last_name;
}

auto Worker::hourly_rate() const -> double {
    return m_hourly_rate;
}

auto Worker::hours_total() const -> uint32_t {
    return m_hours_total;
}

auto Worker::paycheck() const -> double {
    return m_hourly_rate * static_cast<double>(m_hours_total);
}
