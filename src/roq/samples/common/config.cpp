/* Copyright (c) 2017-2019, Hans Erik Thrane */

#include "roq/samples/common/config.h"

namespace roq {
namespace samples {
namespace common {

void Config::dispatch(Handler& handler) const {
  for (auto& instrument : instruments) {
    for (auto& [name, account] : instrument.accounts) {
      handler.on(
          roq::client::Account {
            .name_or_regex = name.c_str(),
          });
    }
    handler.on(
        roq::client::Symbol {
          .exchange = instrument.exchange.c_str(),
          .name_or_regex = instrument.symbol.c_str(),
        });
  }
}

}  // namespace common
}  // namespace samples
}  // namespace roq

namespace {
std::ostream& operator<<(
    std::ostream& stream,
    const std::map<
        std::string,
        roq::samples::common::Config::Instrument::Account>& accounts) {
  stream << "{";
  bool first = true;
  for (const auto& iter : accounts) {
    if (first == false)
      stream << ", ";
    first = false;
    stream << "\"" << iter.first << "\"={"
      "long_limit=" << iter.second.long_limit << ", "
      "short_limit=" << iter.second.short_limit << ", "
      "long_start_of_day=" << iter.second.long_start_of_day << ", "
      "short_start_of_day=" << iter.second.short_start_of_day <<
      "}";
  }
  return stream << "}";
}
std::ostream& operator<<(
    std::ostream& stream,
    const roq::samples::common::Config::Instrument& instrument) {
  return stream << "{"
    "exchange=\"" << instrument.exchange << "\", "
    "symbol=\"" << instrument.symbol << "\", "
    "net_limit=" << instrument.net_limit << ", "
    "tick_size=" << instrument.tick_size << ", "
    "multiplier=" << instrument.multiplier << ", "
    "accounts=" << instrument.accounts <<
    "}";
}
}  // namespace

std::ostream& operator<<(
    std::ostream& stream,
    const roq::samples::common::Config& config) {
  stream << "[";
  bool first = true;
  for (const auto& iter : config.instruments) {
    if (first == false)
      stream << ", ";
    first = false;
    stream << iter;
  }
  return stream << "]";
}
