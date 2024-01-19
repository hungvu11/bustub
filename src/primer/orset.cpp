#include "primer/orset.h"
#include <algorithm>
#include <string>
#include <vector>
#include "common/exception.h"
#include "fmt/format.h"

namespace bustub {

template <typename T>
auto ORSet<T>::Contains(const T &elem) const -> bool {
  // TODO(student): Implement this
  // throw NotImplementedException("ORSet<T>::Contains is not implemented");
  auto it = m_elements.lower_bound({elem, 0});
  if (it != m_elements.end() && it->first == elem) return true;
  return false;
}

template <typename T>
void ORSet<T>::Add(const T &elem, uid_t uid) {
  // TODO(student): Implement this
  // throw NotImplementedException("ORSet<T>::Add is not implemented");
  m_elements.insert({elem, uid});
}

template <typename T>
void ORSet<T>::Remove(const T &elem) {
  // TODO(student): Implement this
  // throw NotImplementedException("ORSet<T>::Remove is not implemented");

  while ( true )
  {
    auto it = m_elements.lower_bound({elem, 0});
    if (it == m_elements.end() || it->first > elem) break;

    m_elements.erase(it);
    m_deletes.insert(*it);
  }
}

template <typename T>
void ORSet<T>::Merge(const ORSet<T> &other) {
  // TODO(student): Implement this
  // throw NotImplementedException("ORSet<T>::Merge is not implemented");

  auto A = other.all_element();
  auto B = other.all_delete();

  for (auto p : m_deletes) {
    auto it = A.find(p);
    if (it != A.end()) A.erase(it);
  }

  for (auto p : B) {
    auto it = m_elements.find(p);
    if (it != m_elements.end()) m_elements.erase(it);
  }

  m_elements.merge(A);
  m_deletes.merge(B);
}

template <typename T>
auto ORSet<T>::Elements() const -> std::vector<T> {
  // TODO(student): Implement this
  // throw NotImplementedException("ORSet<T>::Elements is not implemented");
  std::vector<T> A;
  for (auto p : m_elements) {
    if (A.empty()) A.push_back(p.first);
    else if (p.first != A.back()) A.push_back(p.first);
  }
  return A;
}

template <typename T>
auto ORSet<T>::ToString() const -> std::string {
  auto elements = Elements();
  std::sort(elements.begin(), elements.end());
  return fmt::format("{{{}}}", fmt::join(elements, ", "));
}

template <typename T>
auto ORSet<T>::all_element() const -> std::set<std::pair<T, uid_t>> {
  return m_elements;
}

template <typename T>
auto ORSet<T>::all_delete() const -> std::set<std::pair<T, uid_t>> {
  return m_deletes;
}

template class ORSet<int>;
template class ORSet<std::string>;

}  // namespace bustub
