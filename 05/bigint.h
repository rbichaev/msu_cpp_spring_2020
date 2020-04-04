class BigInt
{
    size_t len;
    bool positive = true;
public:
    char *numbers;
    BigInt(const char *x);
    BigInt();
    BigInt(const BigInt &bint);
    BigInt &operator=(BigInt bint);
    void fill(char *mass, size_t l, bool pos);
    ~BigInt();
    size_t getLen() const;
    bool isPositive() const;
    bool isZero() const;
    friend size_t getFirstNeq(const BigInt &bint_1, const BigInt &bint_2);
    BigInt add(const BigInt &bint, bool pos) const;
    BigInt sub(const BigInt &bint, bool pos) const;
    friend BigInt operator+(const BigInt &bint_1, const BigInt &bint_2);
    friend BigInt operator-(const BigInt &bint_1, const BigInt &bint_2);
    BigInt operator-();
    bool operator<(const BigInt &bint) const;
    bool operator>(const BigInt &bint) const;
    bool operator<=(const BigInt &bint) const;
    bool operator>=(const BigInt &bint) const;
    friend std::ostream &operator<<(std::ostream &stream, const BigInt &bint);
};
