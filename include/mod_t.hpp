#ifndef MOD_T_HPP
#define MOD_T_HPP

#include <istream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>

// use template instead of storing modulo as a variable -> compile time error from runtime error, better handling

template <int Modulo>
class mod_t {
public:
    // need this so i can declare
    mod_t() : remainder_(0) {}

    mod_t(int remainder) {
        static_assert(Modulo > 0, "Modulo must be positive");
        normalize(remainder);
    }

    int get_remainder() const {
        return remainder_;
    }

    static constexpr int get_modulo() {
        return Modulo;
    }

    mod_t operator+(const mod_t &other) const {
        return mod_t(remainder_ + other.remainder_);
    }

    mod_t operator-(const mod_t &other) const {
        return mod_t(remainder_ - other.remainder_);
    }

    mod_t operator-() const {
        return mod_t(-remainder_);
    }

    mod_t operator*(const mod_t &other) const {
        return mod_t(remainder_ * other.remainder_);
    }

    mod_t operator+(int a) const {
        return mod_t(remainder_ + a);
    }

    mod_t operator-(int a) const {
        return mod_t(remainder_ - a);
    }

    mod_t operator*(int a) const {
        return mod_t(remainder_ * a);
    }

    mod_t &operator+=(const mod_t &other) {
        normalize(remainder_ + other.remainder_);
        return *this;
    }

    mod_t &operator-=(const mod_t &other) {
        normalize(remainder_ - other.remainder_);
        return *this;
    }

    mod_t &operator*=(const mod_t &other) {
        normalize(remainder_ * other.remainder_);
        return *this;
    }

    bool operator==(const mod_t &other) const {
        return remainder_ == other.remainder_;
    }

    bool operator!=(const mod_t &other) const {
        return !(*this == other);
    }

    bool operator==(int other) const {

        int r = other % Modulo;

        if (r < 0){
            r += Modulo;
        }
        return remainder_ == r;
    }

    bool operator!=(int other) const {
        return !(*this == other);
    }

    bool operator<(const mod_t &other) const {
        return remainder_ < other.remainder_;
    }

    bool operator>(const mod_t &other) const {
        return remainder_ > other.remainder_;
    }

    bool operator<=(const mod_t &other) const {
        return remainder_ <= other.remainder_;
    }

    bool operator>=(const mod_t &other) const {
        return remainder_ >= other.remainder_;
    }

    //parse from string, care it can parse like "123abc"
    bool from_string(const std::string &s, int m) {
        int r;

        //iss behaves like std::cin
        std::istringstream iss(s);
        iss >> r;
        if (iss.fail()) {
            return false;
        }

        *this = mod_t(r);

        return true;
    }

    friend std::ostream &operator<<(std::ostream &os, const mod_t &a) {
        
        os << a.remainder_;
        return os;
    }

    friend std::istream &operator>>(std::istream &is, mod_t &a) {
        int b = is.peek();
        if(!is) {
            is.setstate(std::ios::failbit);
            return is;
        }

        is >> std::ws;

        if (!is) {
            is.setstate(std::ios::failbit);
            return is;
        }
        is >> a.remainder_;
        a.remainder_ %= a.get_modulo();

        if(a.remainder_ < 0){
            a.remainder_ += a.get_modulo();
        }

        return is;
    }

    //euclid algo thing
    bool reciprocal(mod_t &rinv) const {

        if (remainder_ == 0){
            return false;
        }

        int a = remainder_;
        int m = Modulo;

        int t0 = 0, t1 = 1;
        int r0 = m, r1 = a;

        while (r1 != 0) {
            int q = r0 / r1;
            int r2 = r0 - q * r1;
            int t2 = t0 - q * t1;

            r0 = r1;
            r1 = r2;
            t0 = t1;
            t1 = t2;
        }
        if (r0 != 1){
            return false;
        }

        rinv = mod_t<Modulo>(t0);

        return true;
    }

    mod_t operator/(const mod_t &other) const {
        mod_t<Modulo> inv;

        if(!other.reciprocal(inv)) {
            throw std::runtime_error("mod_t: division by non-invertible element");
        }

        return *this * inv;
    }

    mod_t &operator/=(const mod_t &other) {
        *this = *this / other;
        
        return *this;
    }

    // Legacy: operator% (zero in a field). Kept for API compatibility.
    mod_t operator%(const mod_t &other) const {

        mod_t inv;

        if (!other.reciprocal(inv)) {
            throw std::runtime_error("mod_t: operator% with non-invertible divisor");
        }
        return mod_t(0);
    }

    mod_t &operator%=(const mod_t &other) {
        *this = *this % other;
        return *this;
    }

    //uses binary exponentiation
    mod_t exp(int e) const {

        if (e == 0) {
            
            return mod_t(1);
        }

        //if the exponent is negative, we need to to invert the base and multiply exponent by -1 care edgecase -int_min overflow
        if (e < 0) {
            
            mod_t<Modulo> inv;
            if (!reciprocal(inv)){
                throw std::runtime_error("mod_t::exp: negative exponent of non-unit");
            }

            return inv.exp(-e);
        }

        mod_t<Modulo> base(*this);
        mod_t<Modulo> result(1);

        /*
        binary exponentiation is faster than doing a * a * a * ...
        instead we check the exponent in binary representation
        e & 1 checks if the last binary digit is 1, so the number is odd
        basically every round we take the base to powers of 2 and the condition tells us whoch ones we need, only those get added to the result
        and we reduce the exponent by shifting the binary to the right
        */
        while (e != 0) {
            if (e & 1) {
                result = result * base;
            }
            e = static_cast<unsigned>(e) >> 1;
            base = base * base;
        }

        return result;
    }

    

private:
    int remainder_;

    void normalize(int x) {
        int r = x % Modulo;

        if (r < 0) {
            r += Modulo;
        }

        remainder_ = r;
    }

};

#endif // MOD_T_HPP