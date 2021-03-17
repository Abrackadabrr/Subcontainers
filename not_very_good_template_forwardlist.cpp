#include <iostream>
using namespace std;

template<typename type>
class listt
{
private:
    struct uzzel
    {
        type data;
        uzzel* next;

        uzzel(type d)
        {
            data = d;
            next = NULL;
        }
    };

    uzzel* start;

    void clear_work(uzzel** sfl)
    {
        if (*sfl == NULL) return;
        clear_work(&((*sfl)->next));
        delete *sfl;
        *sfl = NULL;
    }

public:
    listt ()
    {
        start = NULL;
    }

    bool push_back(type d) //add element (d) to the end of the list
    {
        uzzel** sfl = &(this -> start);
        uzzel* tmp = new uzzel(d);
        while (*sfl != NULL)
        {
            sfl = &((*sfl)->next);
        }
        *sfl = tmp;
        return true;
    }

    bool pop_back() //erase element from the end of the list + return it's data
    {
        if (start == NULL) return false;
        uzzel** sfl = &(this -> start);
        while ((*sfl)->next != NULL) {
            sfl = &((*sfl)->next);
        }
        delete *sfl;
        *sfl = NULL;
        return true;
    }

    bool push_forward(type d) //add element (d) to the beginning of the list
    {
        uzzel** sfl = &(this -> start);
        uzzel* tmp = new uzzel(d);
        tmp->next = (*sfl);
        tmp->data = d;
        *sfl = tmp;
        return true;
    }

    bool pop_forward() //erase element from the beginning of the list + return it's data
    {
        if (start == NULL) return false;
        uzzel** sfl = &(this -> start);
        uzzel* tmp = (*sfl)->next;
        delete *sfl;
        *sfl = tmp;
        return true;
    }
    bool push_where(unsigned int where, type d) //add element (d) to (where)th position of the list
    {
        uzzel** sfl = &(this -> start);
        uzzel* tmp = new uzzel(d);
        for (int i = 1; i < where; i++)
        {
            if (*sfl == NULL) return false;
            sfl = &((*sfl)->next);
        }
        tmp->next = (*sfl);
        (*sfl) = tmp;
        return true;
    }

    bool erase_where(unsigned int where) //erase element from (where)th position of the list
    {
        uzzel** sfl = &(this -> start);
        for (int i = 1; i < where; i++)
        {
            if (*sfl == NULL) return false;
            sfl = &((*sfl)->next);
        }
        uzzel* tmp = (*sfl)->next;
        delete (*sfl);
        (*sfl) = tmp;
        return true;
    }

    unsigned int size() //check size of list
    {
        uzzel* sfl = this -> start;
        unsigned int size = 0;
        while (sfl != NULL)
        {
            sfl = (sfl)->next;
            size++;
        }
        return size;
    }

    void clear() //delete all elements (interface function, work function is private)
    {
        uzzel** sfl = &(this -> start);
        this ->clear_work(sfl);
    }

    void print()
    {
        uzzel* tmp = start;
        if (!tmp) cout << "empty list";
        while (tmp != NULL)
        {
            cout << tmp->data << " ";
            tmp = (tmp)->next;
        }
        cout << endl<<endl;
        return;
    }

    ~listt()
    {
        this -> clear();
    }

    void int_mini_profiler()// mini-test to check working for int
    {
        cout << "//----------------------Push_back(10 elements)----------------------//"<< endl;
        for (int i = 0; i < 10; this -> push_back(3*i+2),i++) {this -> print();}
        this -> print();

        cout << "//----------------------Pop_back(8 elements)----------------------//"<< endl;
        for (int i = 0; i < 8; this -> pop_back(),i++) {this -> print();}
        this -> print();

        cout << "//----------------------Push_forward(8 elements)----------------------//"<< endl;
        for (int i = 0; i < 8; this -> push_forward(5*i + 7),i++) {this -> print();}
        this -> print();

        cout << "//----------------------Pop_forward(1 elements)----------------------//"<< endl;
        this -> pop_forward();
        this -> print();

        cout << "//----------------------Push 112 to 3rd place----------------------//"<< endl;
        this -> push_where(3,112);
        this -> print();

        cout << "//----------------------Push 221 to 3rd place/Erase 112 from 4rd place----------------------//"<< endl;
        this -> push_where(3,221);
        this -> print();
        this -> erase_where(4);
        this -> print();

        cout << "//----------------------Check size----------------------//"<< endl;
        cout << this -> size()<<endl;

        cout << "//----------------------Clear list----------------------//"<< endl;
        this -> clear();
        this -> print();

    }
};

int main()
{
    listt<int> l;
    l.int_mini_profiler();
    return 0;
}

/*ostream& operator << (ostream& os, a& aa)
{
    os << "{" << aa.q << " ," << aa.e << "}";
    return os;
}*/

/* class a{
private:
    int q;
    int e;
public:
    a(int q = 0, int e = 0){this->e = e; this->q = q;}
    ~a() {cout << "I am a destructor" << endl;}
    a(const a & drob) : q(drob.q), e(drob.e)
    {
        std::cout << "Copy constructor worked here!\n"; // просто, чтобы показать, что это работает
    }

    friend ostream& operator << (ostream& os, a& aa);
}; */
