#include <iostream>
#include <string>
using namespace std;

template<typename type>
class subvector
{
private:
    type* mas;
    unsigned int top;
    unsigned int capacity;
public:
    subvector()
    {
        this -> mas = NULL;
        this ->top = 0;
        this ->capacity = 0;
    }

    ~subvector()
    {
        if (this->capacity > 0) delete[] this->mas;
    }

    unsigned int get_cap()
    {
        return this ->capacity;
    }

    unsigned int get_top()
    {
        return this ->top;
    }

    bool push_back(type d)
    {
        if (this ->top + 1 > this ->capacity)
        {
            type* p = new type[this ->capacity + 1];
            for (int i = 0; i < this ->capacity; i++)
            {
                *(p + i) = *(this -> mas + i);
            }
            if (this ->capacity > 0) delete[] this ->mas;
            this ->capacity++;
            this ->mas = p;
            *(this ->mas + this ->top) = d;
            this ->top++;
        }
        else
        {
            *(this ->mas + this ->top) = d;
            this ->top++;
        }
        return true;
    }

    void print ()
    {
        if (this ->top > 0)
        {
            for (int i = 0; i< this -> top; i++)
                cout << this -> mas [i]<<" ";
            cout<<endl;
        }
        else cout << "empty subvector";
    }

    bool pop_back()
    {
        if (this ->top > 0)
        {
            this ->top--;
            return 1;
        }
        else
        {
            return 0;
        }
    }

    bool resize(unsigned int new_capacity)
    {
        if (new_capacity > 0 && new_capacity != 1) {
            type* p = new type[new_capacity];
            int size = 0;
            if (new_capacity > this->top) size = this->top; else size = new_capacity;
            for (int i = 0; i < size ; i++)
            {
                *(p + i) = *(this ->mas + i);
            }
            if (this ->capacity > 0) delete[] this ->mas;
            this ->capacity = new_capacity;
            this ->mas = p;
            if (new_capacity < this ->top) this ->top = new_capacity;
            return true;
        }
        else
        {
            if (this ->capacity > 0) delete[] this ->mas;
            this -> mas = NULL;
            this ->top = 0;
            this ->capacity = 0;
            return true;
        }
    }

    void shrink_to_fit()
    {
        if (this ->capacity > this ->top)
        {
            if (this ->top > 0)
            {
                type* p = new type[this ->top];
                for (int i = 0; i < this ->top; i++)
                {
                    *(p + i) = *(this ->mas + i);
                }
                delete[] this ->mas;
                this ->capacity = this ->top;
                this ->mas = p;
            }
            else
            {
                delete[] this ->mas;
                this -> mas = NULL;
                this ->top = 0;
                this ->capacity = 0;
            }
        }
    }
    void clear()
    {
        this ->top = 0;
    }

};

int mini_profiler()
{
    subvector<int> s1;
    //check push
    s1.push_back(2);
    s1.push_back(3);
    s1.push_back(1);
    s1.push_back(1);
    s1.push_back(2);
    s1.print();
    //check pop
    s1.pop_back();
    s1.print();
    //check resize
    s1.push_back(1);
    s1.push_back(1);
    s1.push_back(1);
    s1.push_back(1);
    s1.push_back(2);
    s1.print();
    s1.resize(2);
    s1.print();
    //check shrink_to_fit
    s1.resize(1000);
    cout<< "top =" << s1.get_top()<<"  capasity = "<< s1.get_cap()<<" " << endl;
    s1.shrink_to_fit();
    cout<< "top =" << s1.get_top()<<"  capasity = "<< s1.get_cap()<<" " << endl;
    //check clear
    s1.clear();
    s1.print();
    //I can't check destructor =(((((((((((
    cout << endl;
    return 0;
}

// закомменченный класс мячиков для проверки шаблона (работает)
// переопределяется только отператор <<
/*
class ball{

    friend ostream& operator << (ostream& is, ball b);

private:
    int radius;
    string color;
public:
    ball(int r,string c)
    {
        radius = r;
        color = c;
    }
    ball():ball(0, "nope"){}
};
*/
int main()
{
    subvector<char> big_alfabet;
    for (int i = 0; i < 26; i++){
        big_alfabet.push_back('A'+i);
    }
    big_alfabet.print();

    /*subvector<ball> balls;
    for (int i = 0; i < 26; i++){
        ball a = {i,"red"};
        balls.push_back(a);
    }
    balls.print(); */

    return 0;
}
/*
ostream& operator << (ostream& is, ball b)
{
    is << "Ball: 1)radius is " << b.radius <<  endl << "    2)color is " << b.color <<endl;
}
*/
