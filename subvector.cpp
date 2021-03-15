#include <iostream>
using namespace std;

class subvector
{
private:
	int* mas;
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

    bool push_back(int d)
    {
        if (this ->top + 1 > this ->capacity)
        {
            int* p = new int[this ->capacity + 1];
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
            int e = *(this ->mas + this ->top);
            return e;
        }
        else
        {
            return 0;
        }
    }

    bool resize(unsigned int new_capacity)
    {
        if (new_capacity > 0) {
            int* p = new int[new_capacity];
            for (int i = 0; i < this ->top; i++)
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
                int* p = new int[this ->top];
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
    subvector s1;
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

int main()
{
    mini_profiler();
}

