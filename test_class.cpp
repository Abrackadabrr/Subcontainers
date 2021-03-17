class a{
private:
    int q;
    int e;
public:
    a(int q = 0, int e = 0){this->e = e; this->q = q;}
    ~a() {}
    a(const a & drob) : q(drob.q), e(drob.e)
    {}

    bool operator < (const a& aa)
    {
        if (this->e < aa.e)
            return true;
        else return false;
    }

    bool operator > (const a& aa)
    {
        if (this->e > aa.e)
            return true;
        else return false;
    }

    bool operator == (const a& aa)
    {
        if (this->e == aa.e)
            return true;
        else return false;
    }

    friend ostream& operator << (ostream& os, a& aa);
};

ostream& operator << (ostream& os, a& aa)
{
    os << "{" << aa.q << " ," << aa.e << "}";
    return os;
}


