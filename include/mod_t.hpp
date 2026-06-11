#ifndef MOD_T_HPP
#define MOD_T_HPP

#include <stdexcept>

// use template instead of storing modulo as a variable -> compile time error from runtime error, better handling

template <int Modulo>
class mod_t {
public:
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

    //euclid algo thing
    bool reciprocal(mod_t &rinv) const {

        if (remainder_ == 0){
            return false;
        }

        int a = remainder_;
        int m = Modulo;

        int t0 = 0, t1 = 1;
        int r0 = 0, r1 = a;

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

        inv_normalize(t0);
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

    mod_t exp(int e) const {

        if (e == 0) {
            
            return mod_t(1);
        }

        if (e < 0) {
            
            mod_t<Modulo> inv;
            if (!reciprocal(inv)){
                throw std::runtime_error("mod_t::exp: negative exponent of non-unit");
            }

            return inv.exp(-e);
        }

        mod_t<Modulo> base(*this);
        mod_t<Modulo> result(1);

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

    static void inv_normalize(int &x) {
        x %= Modulo;
        if (x < 0){
            x += Modulo;
        }
    }
};

#endif // MOD_T_HPP