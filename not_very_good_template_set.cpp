#include <iostream>

using namespace std;

template<typename type>
class sett
{
private:
    struct subset_node // structure == element of tree
    {
        type key;
        subset_node* left;
        subset_node* right;
        subset_node* parent;
        int level;

        subset_node(type k)
        {
            this->key = k;
            this->left = NULL;
            this->right = NULL;
            this->level = 0;
        }
    };

    subset_node* root;  // root of the tree (pointer to the top element)

    struct subforwardlist // structure which can create a queue for BFS
    {
        subset_node* data;
        subforwardlist* next;
    };
    subforwardlist* start = NULL; //
    subforwardlist* End = NULL;   // pointer to start and end of the queue

    //-----------------------Private methods-------------------------//

    unsigned int size(subset_node* sn)
    {
        int zero = 0;
        unsigned int sb = 0, sm = 0;
        if (sn == NULL) return zero;
        if (sn != NULL)
        {
            sb = size(sn->left);
            sm = 1 + size(sn->right);
        }
        return (sm+sb);
    }

    unsigned int height(subset_node* sn)
    {
        if (sn == NULL)
            return 0;
        return (max(height(sn->right), height(sn->left)) + 1);
    }

    void destructor(subset_node **sn)
    {
        if (!*sn) return;
        destructor(&((*sn)->left));
        destructor(&((*sn)->right));
        delete *sn;
        *sn = NULL;
        return;
    }

    unsigned int dfs (subset_node *sn, type* keys, unsigned int nomer)
    {
        unsigned int num = nomer;
        if (sn != NULL)
        {
            nomer = dfs((sn->left),keys,nomer);
            keys[nomer] = sn->key;
            nomer = nomer + 1;
            nomer = dfs((sn->right),keys,nomer);
        }
        else
        {
            return nomer;
        }
        return nomer;
    }

    void pottyagivay_k_bate(bool right, subset_node *batya, subset_node *pott)
    {
        if (right)
        {
            batya->right = pott;
            batya->right->parent = batya;
        }
        else
        {
            batya->left = pott;
            batya->left->parent = batya;
        }
    }

    bool delete_root(subset_node **root)
    {
        subset_node* predok;
        subset_node** tmp;
        if ((*root)->right)
        {
            tmp = &((*root)->right);
            while (*tmp!= NULL)
            {
                if  ((*tmp)->left == NULL)  predok = *tmp;
                tmp = &((*tmp)->left);
            }
            *tmp = (*root)->left;
            if (*tmp) {(*tmp) ->parent = predok;};
            subset_node* newroot = (*root)->right;
            newroot->parent = NULL;
            delete *(root);
            *root = newroot;

            return true;
        }
        else if ((*root)->left)
        {
            subset_node* newroot = (*root)->left;
            delete (*root);
            newroot->parent = NULL;
            *root = newroot;

            return true;
        }
        else
        {
            delete (*root);
            *root = NULL;

            return true;
        }
    }

    subset_node* find__(type k)
    {
        subset_node* sn = this -> root;
        if (this -> size_of_tree()==0) return NULL;
        while (sn != NULL)
        {
            if (k > sn->key) sn = sn->right;
            else if (k < sn->key) sn = sn->left;
            else if (k == sn->key) {return sn;};
        }

        return NULL;
    }

    void nfs(subset_node* root, subforwardlist** start, subforwardlist** End, subset_node** a)
    {
        bool is_root = true;
        int i = 0;
        if (is_root)
        {
            this -> push_back(root);
        }
        while (this -> size_of_list())
        {
            is_root = false;
            subset_node* tmp = root->left;
            subset_node* tmp1 = root->right;
            if (tmp != NULL)  this -> push_back(tmp);
            if (tmp1 != NULL) this -> push_back(tmp1);

            type c;
            if (tmp) c = tmp->key;
            type b;
            if (tmp1) b = tmp1->key;
            (a)[i] = root;
            i++;
            this -> pop_forward();
            if (*start) root = (*start)->data;
        }
        return;
    }


    //-----------Private methods (special to working with queue)-------//

    unsigned int size_of_list()
    {
        subforwardlist** sfl = &(this ->start);
        unsigned int size = 0;
        while (*sfl != NULL)
        {
            sfl = &((*sfl)->next);
            size++;
        }
        return size;
    }

    bool push_back(subset_node* e_tree)
    {
        subforwardlist** start = &(this -> start);
        subforwardlist** End = &(this -> End);
        if (this -> size_of_list() > 0)
        {
            subforwardlist* tmp = new subforwardlist;
            tmp ->data = e_tree;
            tmp ->next = NULL;
            (*End)->next = tmp;
            *End = tmp;
        }
        else
        {
            subforwardlist* tmp = new subforwardlist;
            tmp ->data = e_tree;
            tmp ->next = NULL;
            *start = tmp;
            *End = tmp;
        }
    }

    int pop_forward()
    {
        subforwardlist** start = &(this -> start);
        subforwardlist** End = &(this -> End);
        if (this -> size_of_list() > 1)
        {
            subforwardlist* tmp = (*start)->next;
            delete *start;
            *start = tmp;
        }
        else
        {
            delete *start;
            this -> start = NULL;
            this -> End = NULL;
        }
        return 1;
    }

    //-----------------------------------------------------------------//
public:
    sett()
    {
        this -> root = NULL;
    }

    bool insert(type k) // adds an element (k) to the tree
    {
        subset_node** sn = &(this -> root);
        subset_node* tmp = new subset_node(k);
        subset_node* predok = NULL;
        while (*sn != NULL)
        {
            if ( (k > (*sn)->key) && ((*sn)->right == NULL) ) predok = *sn;
            if ( (k < (*sn)->key) && ((*sn)->left == NULL) ) predok = *sn;
            if (k > (*sn)->key) {subset_node** t = sn; sn = &((*t)->right);}
            else if (k < (*sn)->key) {subset_node** t1 = sn; sn = &((*t1)->left);}
            else if (k == (*sn)->key) {delete tmp; return false;};
        }
        *sn = tmp;
        (*sn)->parent = predok;
        if((*sn)->parent) (*sn)->level = (*sn)->parent->level + 1;
        else (*sn)->level = 1;
        return true;
    }

    bool remove(type k) // remove an element (k) from the tree
    {
        subset_node** sn = &(this -> root);
        if (this -> size_of_tree()==0) return false;
        subset_node* rem_e = (this -> find__(k));
        if (!rem_e) return false;
        if (k == (*sn)->key) {delete_root(sn); return true;};
        bool right = (rem_e->parent->right == rem_e);
        subset_node** tmp;
        subset_node* predok;
        if (rem_e ->right)
        {
            tmp = &(rem_e ->right);
            pottyagivay_k_bate(right,rem_e->parent,*tmp);
            while (*tmp!= NULL)
            {
                if  ((*tmp)->left == NULL)  predok = *tmp;
                tmp = &((*tmp)->left);
            }
            *tmp = rem_e->left;
            if (*tmp) {(*tmp)->parent = predok;};
            delete rem_e;


            return true;
        }
        else if (rem_e->left)
        {
            pottyagivay_k_bate(right,rem_e->parent,rem_e->left);
            delete rem_e;


            return true;
        }
        else
        {
            if (right) rem_e->parent->right = NULL;
            else rem_e->parent->left = NULL;
            delete rem_e;


            return true;
        }

    }

    unsigned int size_of_tree() // checks size of tree (amount of elements)
    {
        subset_node* sn = this -> root;
        return(size(sn));
    }

    unsigned int height_of_tree() // checks height of tree
    {
        subset_node* sn = (this -> root);
        return(height(sn));
    }

    bool find(type k) // checks if there is an element in the tree (if it is function returns true, in other way function returns false
    {
        subset_node* sn = (this -> root);
        if (this -> size_of_tree()==0) return false;
        while (sn != NULL)
        {
            if (k > sn->key) sn = sn->right;
            else if (k < sn->key) sn = sn->left;
            else if (k == sn->key) {return true;};
        }
        return false;
    }

    void DFS(bool vim_type_of_search) // depth-first search (displays order of elements keys after depth-first search)
    {
        if (vim_type_of_search) cout <<"//---------------------DFS--------------------//"<<endl;
        subset_node* sn = this -> root;
        unsigned int n = this -> size_of_tree();
        if (n>0)
        {
            type* keys = new type [n];
            dfs (sn,keys,0);
            for (int i = 0; i < this -> size_of_tree(); i ++)
            {
                cout << keys[i] << " ";
            }
            cout << endl;
            delete[] keys;
        }
        else cout << "Empty tree" <<endl;
        cout << endl;
    }

    void set_int_tree() // set int tree
    {
        insert(10);
        insert(7);
        insert(5);
        insert(15);
        insert(20);
        insert(14);
        insert(24);
        insert(19);
        insert(8);
        insert(9);
        insert(6);
        insert(3);
        insert(4);
        insert(2);
        insert(1);
        insert(13);
        insert(17);
        insert(18);
        insert(16);
        insert(27);
    }


    void NFS(bool vim_type_of_search) // breadth-first search (displays order of elements keys after breadth-first search)
    {
        if (this->root == NULL) return;
        if (vim_type_of_search) cout <<"//---------------------BFS--------------------//"<<endl;
        subset_node* root = this -> root;
        subset_node** a = new subset_node* [this -> size_of_tree()];
        nfs(root,&(this -> start),&(this ->End), a);
        for (int i = 0; i < this -> size_of_tree(); i++)
        {
            cout << a[i]->key <<" ";
        }
        cout << endl<<endl;
        delete[] a;
    }

    ~sett()
    {
        subset_node** sn = &(this -> root);
        this -> destructor(sn);
    }

};// конец дерева

int main()
{}
