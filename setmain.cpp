#include "subset.cpp"
using namespace std;

int main()
{
    sett tree;

    //checking insert

    tree.insert(60);
    tree.insert(90);
    tree.insert(50);
    tree.insert(91);
    tree.insert(6);
    tree.insert(9);
    tree.insert(3);
    tree.insert(2);

    tree.DFS(true);
    cout << endl;
    tree.NFS(true);
    cout << endl;
    //checking remove

    tree.remove(60);
    tree.remove(90);
    tree.remove(1);
    tree.remove(60);
    tree.remove(3);
    tree.remove(60);

    tree.DFS(true);

    //checking find

    cout << tree.find(2) << " ";
    cout << tree.find(7) << " ";
    cout << tree.find(6) << " ";
    cout << tree.find(91) << " ";
    cout << tree.find(49) << endl;
    tree.NFS(true);
    //checking size && height

    cout << tree.size_of_tree() << " " << tree.height_of_tree() << endl;
    tree.insert(5);
    tree.insert(100);
    cout << tree.size_of_tree() << " " << tree.height_of_tree() << endl;
    tree.remove(91);
    tree.remove(6);
    cout << tree.size_of_tree() << " " << tree.height_of_tree() << endl;

    return 0;
}
