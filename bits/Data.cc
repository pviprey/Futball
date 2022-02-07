#include "Data.h"

#include <cassert>

Data::Data(const std::string& raw, gf::Vector2i size)
: m_raw(raw)
, m_size(size)
{
  assert(raw.size() == static_cast<std::size_t>(size.x * size.y));
}

char Data::operator()(gf::Vector2i coords) const {
  assert(0 <= coords.x && coords.x < m_size.width);
  assert(0 <= coords.y && coords.y < m_size.height);

  return m_raw[coords.y * m_size.width + coords.x];
}