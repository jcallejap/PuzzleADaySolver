#ifndef ENUM_CLASS_ITERATOR_H_2023_09_24
#define ENUM_CLASS_ITERATOR_H_2023_09_24

/*
 * Class to iterate over a enum class.
 * Based on:
 * https://stackoverflow.com/a/31836401/218774
 */

#include <type_traits>
#include <limits>

template <typename TYPE, TYPE begin_val, TYPE end_val>
class EnumClassIterator {
  typedef typename std::underlying_type<TYPE>::type value_type;
  static_assert(std::is_integral<value_type>::value);
  static_assert(static_cast<value_type>(end_val) < std::numeric_limits<value_type>::max());

 public:
  EnumClassIterator(const TYPE& value)
      : m_value(static_cast<value_type>(value)) {}
  EnumClassIterator() : m_value(static_cast<value_type>(begin_val)) {}
  EnumClassIterator& operator++() {
    ++m_value;
    return *this;
  }
  TYPE operator*() { return static_cast<TYPE>(m_value); }
  EnumClassIterator begin() { return {begin_val}; }
  EnumClassIterator end() {
    return {static_cast<TYPE>(static_cast<value_type>(end_val) + 1)};
  }
  bool operator!=(const EnumClassIterator& other) {
    return m_value != other.m_value;
  }

 private:
  value_type m_value;
};

#endif  // ENUM_CLASS_ITERATOR_H_2023_09_24
