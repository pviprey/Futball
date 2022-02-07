
#ifndef SKB_DATA_H
#define SKB_DATA_H

#include <string>

#include <gf/Vector.h>


class Data {
public:
  Data(const std::string& raw, gf::Vector2i size);

  char operator()(gf::Vector2i coords) const;

  gf::Vector2i getSize() const {
    return m_size;
  }

private:
  std::string m_raw;
  gf::Vector2i m_size;
};

#endif // SKB_DATA_H