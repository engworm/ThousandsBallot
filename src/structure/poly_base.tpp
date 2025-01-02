#include "structure/poly_base.hpp"

template<Arithmetic T>
PolyBase<T>::PolyBase() = default;

template<Arithmetic T>
PolyBase<T>::PolyBase(const std::vector<T> &coeffs) : coeffs(coeffs) {
    this->N = coeffs.size();
}

template<Arithmetic T>
uint32_t PolyBase<T>::size() const {
    return this->N;
}

template<Arithmetic T>
T PolyBase<T>::operator[](int i) const {
    return coeffs[i];
}

template<Arithmetic T>
T& PolyBase<T>::operator[](int i) {
    return coeffs[i];
}

template<Arithmetic T>
std::vector<T> PolyBase<T>::get_coeffs() const {
    return coeffs;
}

template<Arithmetic T>
std::ostream& operator<<(std::ostream &os, const PolyBase<T> &poly) {
    for (auto coeff: poly.get_coeffs()) {
        os << coeff << ' ';
    }
    return os;
}