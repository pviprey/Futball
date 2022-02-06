#ifndef BALLON_H
#define BALLON_H

#include <cstddef>
#include <iosfwd>
#include <set>
#include <gf/Entity.h>
#include <gf/Vector.h>

class Ballon : public gf::Entity{
    public:
        Ballon();
    private:
        int size;

        gf::Vector2f position;
};

inline Ballon::Ballon():size(62){}

#endif  //BALLON_H