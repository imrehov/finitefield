#ifndef MOD_T_H
#define MOD_T_H

class mod_t {
public:
    mod_t(int remainder, int modulo);

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

private:
    int remainder_;
    int modulo_;

    void normalize(int x);
    void check_same_modulo(const mod_t& other) const;
};


#endif //MOD_T_H