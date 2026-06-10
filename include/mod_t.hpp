#ifndef MOD_T_H
#define MOD_T_H

class mod_t {
public:
    mod_t(int remainder, int modulo);

    int get_remainder() const;

    int get_modulo() const;

    mod_t operator+(const mod_t& other) const;

    mod_t operator-(const mod_t& other) const;

    mod_t operator-() const;

    mod_t operator*(const mod_t& other) const;


    mod_t operator+(int a) const;

    mod_t operator-(int a) const;

    mod_t operator*(int a) const;


    mod_t operator+=(const mod_t& other);
    
    mod_t operator-=(const mod_t& other);
    
    mod_t operator*=(const mod_t& other);


    // need reciprocal for division

    bool recip(mod_t& rinv) const;

    mod_t operator/(const mod_t& other) const;

    mod_t operator/=(const mod_t& other);


    // % operation just for compatibility

    mod_t operator%(const mod_t& other) const;

    mod_t operator%=(const mod_t& other);


    // exponentation a^e (e>=0); returns inverse^|e| if invertible

    mod_t exp(int e) const;


    // comparisons

    bool operator==(const mod_t& other) const;

    bool operator!=(const mod_t& other) const;

    bool operator==(int other) const;

    bool operator!=(int other) const;

    bool operator<(const mod_t& other) const;

    bool operator>(const mod_t& other) const;

    bool operator<=(const mod_t& other) const;

    bool operator>=(const mod_t& other) const;


    
private:
    int remainder_;
    int modulo_;

    void normalize(int x);
    void check_if_modulo_set() const;
    void check_same_modulo(const mod_t& other) const;
};


#endif //MOD_T_H