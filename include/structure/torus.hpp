#ifndef TORUS_HPP
#define TORUS_HPP

#include "structure/galoisfield.hpp"

class GaloisFieldElement;

class DiscreteTorus {
friend class TorusPoly;

private:
    uint32_t x;
    uint32_t P = Params::P;

public:
    DiscreteTorus();
    DiscreteTorus(uint32_t x);

    // DiscreteTorus(const uint32_t &x); 
    DiscreteTorus(const DiscreteTorus &t);
    DiscreteTorus(const GaloisFieldElement &a);

    // DiscreteTorus(uint32_t &&x) noexcept;

    uint32_t val() const;

    void operator+=(const DiscreteTorus &t);
    void operator-=(const DiscreteTorus &t);
    void operator*=(const uint32_t c);

    // should replace it to faster algo
    uint32_t modP(uint32_t x);

    friend std::ostream& operator<<(std::ostream &os, const DiscreteTorus &t);

};

DiscreteTorus operator+(const DiscreteTorus &t1, const DiscreteTorus &t2);
DiscreteTorus operator*(const uint32_t c, const DiscreteTorus &t1);

#endif