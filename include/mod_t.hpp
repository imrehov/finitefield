#ifndef MOD_T_HPP
#define MOD_T_HPP


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

    mod_t operator+(const mod_t& other) const {
        return mod_t(remainder_ + other.remainder_);
    }

    mod_t operator-(const mod_t& other) const {
        return mod_t(remainder_ - other.remainder_);
    }

    mod_t operator-() const {
        return mod_t(-remainder_);
    }

    mod_t operator*(const mod_t& other) const {
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

    mod_t& operator+=(const mod_t& other) {
        normalize(remainder_ + other.remainder_);
        return *this;
    }

    mod_t& operator-=(const mod_t& other) {
        normalize(remainder_ - other.remainder_);
        return *this;
    }

    mod_t& operator*=(const mod_t& other) {
        normalize(remainder_ * other.remainder_);
        return *this;
    }

    bool operator==(const mod_t& other) const {
        return remainder_ == other.remainder_;
    }

    bool operator!=(const mod_t& other) const {
        return !(*this == other);
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