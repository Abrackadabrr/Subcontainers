#include "subset.cpp"
using namespace std;

int main()
{
    sett s;
    s.set_tree();
    cout << s.size_of_tree()<<endl;
    cout << s.height_of_tree()<<endl;
    int elem = 34;
    if (s.find(elem)) cout << "true " << elem << endl; else cout << "false " <<elem<< endl;
    s.DFS(true);
    s.NFS(true);
    s.remove(1);
    s.DFS(true);
    s.NFS(true);
    s.remove(10);
    s.DFS(true);
    s.NFS(true);
    s.insert(123);
    cout << s.size_of_tree()<<endl;
    cout << s.height_of_tree()<<endl;

}

