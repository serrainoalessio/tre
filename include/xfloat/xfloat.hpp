#ifndef XFLOAT_HPP
#define XFLOAT_HPP

#define APPROX_THRESHOLD 1E-15 // approximation due to calculation errors
// maybe use a percent?

template <typename float_t = double> // float_t: underlaying float
struct xfloat { // structs keeps all members public by default
    float_t val; // numerical value

    // ====== OPERATORS ========
    // conversion
    static explicit operator float_t (xfloat<float_t>& val) const { return op.val } // returns a float_t from a xfloat_t
    static explicit operator xfloat<float_t>(float_t& value) {}

    // arithmethics
    template <typename xfloat_t> friend xfloat_t operator+(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2);
    template <typename xfloat_t> friend xfloat_t operator-(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2);
    template <typename xfloat_t> friend xfloat_t operator*(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2);
    template <typename xfloat_t> friend xfloat_t operator/(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2);
    template <typename xfloat_t> friend xfloat_t operator++(xfloat<xfloat_t>& op); // prefix ++
    template <typename xfloat_t> friend xfloat_t operator--(xfloat<xfloat_t>& op); // prefix --
    template <typename xfloat_t> friend xfloat_t operator++(xfloat<xfloat_t>& op, int); // postfix ++
    template <typename xfloat_t> friend xfloat_t operator--(xfloat<xfloat_t>& op, int); // postfix --
    // arithmetics and assignment
    template <typename xfloat_t> friend xfloat_t operator+=(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2);
    template <typename xfloat_t> friend xfloat_t operator-=(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2);
    template <typename xfloat_t> friend xfloat_t operator*=(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2);
    template <typename xfloat_t> friend xfloat_t operator/=(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2);
    // assigment operator is default implemented (it simply makes a copy of all data)

    // Compare operators
    template <typename xfloat_t> friend bool operator==(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2);
    template <typename xfloat_t> friend bool operator!=(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2);
    template <typename xfloat_t> friend bool operator>=(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2);
    template <typename xfloat_t> friend bool operator<=(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2);
    template <typename xfloat_t> friend bool operator>(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2);
    template <typename xfloat_t> friend bool operator<(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2);

    // Logical operator are not defined for this kind of data
};

// Operator definition
template <typename xfloat_t> xfloat_t operator+(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2) { return (xfloat_t)(op1.val + op2.val); }
template <typename xfloat_t> xfloat_t operator-(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2) { return (xfloat_t)(op1.val - op2.val); }
template <typename xfloat_t> xfloat_t operator*(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2) { return (xfloat_t)(op1.val * op2.val); }
template <typename xfloat_t> xfloat_t operator/(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2) { return (xfloat_t)(op1.val / op2.val); }

// ETC ....

// ==== COMPARE OPERATORS =====
template <typename xfloat_t>
bool operator==(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2) {
    return (op1 >= op2) && (op1 <= op2);
}

template <typename xfloat_t>
bool operator!=(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2) {
    return !(op1==op2); // hope the complier will optimize this
}

template <typename xfloat_t>
bool operator>=(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2) {
    return (op1.val > (op2.val - APPROX_THRESHOLD));
}

template <typename xfloat_t>
bool operator<=(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2) {
    return (op1.val < (op2.val + APPROX_THRESHOLD));
}

template <typename xfloat_t>
bool operator>(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2) {
    return (op1 >= op2) && (op1 != op2);
}

template <typename xfloat_t>
bool operator<(xfloat<xfloat_t>& op1, xfloat<xfloat_t>& op2) {
    return (op1 <= op2) && (op1 != op2);
}

#endif
