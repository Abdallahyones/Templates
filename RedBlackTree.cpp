#include <bits/stdc++.h>


#define Body  ios_base::sync_with_stdio(false);cin.tie(NULL);
#define files    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
#define clo cout << "Time execute: " << clock()/ (double)CLOCKS_PER_SEC << " sec" << endl;
#define all(ele)  ele.begin(), ele.end()
#define fo(i , n) for (long long int i =0 ; i < n ; i++)
#define ll long long int
#define X first
#define Y second

using namespace std;

const int N = 1e5+7, mod = 1e9+7 ;

template<class T>
struct Node{
    T vl ;
    Node* lf , *rt , *pr ;
    char color ;
    Node(){
        lf = rt = nullptr;
        color = 'B';
    }
    Node(T vl, char color):vl(vl),color(color),lf(nullptr),rt(nullptr),pr(nullptr){};
};
template<class T>
class RedBlackTree{
    Node<T>* root;
public:

    RedBlackTree():root(nullptr){};

    void insert(T vl){
        Node<T>* v = new Node<T>(vl , 'R') , *u = root ;
        if (u == nullptr){
            root = v ;
            root ->color = 'B';
            return;
        }
        while (u != nullptr){
            if (vl >= u->vl){
                if (u->rt == nullptr){
                    u->rt = v ;
                    v->pr = u ;
                    break;
                }else {
                    u = u-> rt ;
                }
            }else{
                if (u->lf == nullptr){
                    u->lf = v ;
                    v->pr = u ;
                    break;
                }else {
                    u = u -> lf ;
                }
            }
        }
        BalansInsert(v);
    }
    void erase(T vl) {
        Node<T>* u = root;
        while (u != nullptr) {
            if (vl > u->vl) {
                u = u->rt;
            } else if (vl < u->vl) {
                u = u->lf;
            } else {
                erase(u);
                return;
            }
        }
    }

    void print(){
        if (root == nullptr) return;
        InOrder(root);
        cout << endl ;
    }

private:
    void erase(Node<T>* u) {
        if (u == nullptr) return;

        // Case 1: Node with two children
        if (u->lf != nullptr && u->rt != nullptr) {
            Node<T>* successor = minSuccessor(u->rt);
            u->vl = successor->vl;  // Replace value
            erase(successor);       // Recursively delete successor
        } else {
            Node<T>* child = (u->lf != nullptr) ? u->lf : u->rt;

            // Case 2: Node with one child
            if (child != nullptr) {
                // Replace u with its child
                if (u == root) {
                    root = child;
                    root->pr = nullptr;
                } else if (u == u->pr->lf) {
                    u->pr->lf = child;
                } else {
                    u->pr->rt = child;
                }
                child->pr = u->pr;
                child->color = 'B';  // Ensure child is black
                delete u;
            }
                // Case 3: Node with no children
            else {
                if (u == root) {
                    root = nullptr;  // Tree becomes empty
                } else {
                    if (u->color == 'B') {
                        // Handle double black
                        BalansDelete(u);
                    }
                    if (u == u->pr->lf) {
                        u->pr->lf = nullptr;
                    } else {
                        u->pr->rt = nullptr;
                    }
                }
                delete u;
            }
        }
    }

    void BalansInsert(Node<T>*& u){
        Node<T>* parent , *grandparent , *uncle ;

        while (u != root && u ->color == 'R' && u ->pr->color == 'R'){
            parent = u ->pr;
            grandparent = parent->pr;
            if (parent == grandparent->lf){
                uncle = grandparent->rt ;
                if (uncle != nullptr && uncle->color == 'R'){
                    grandparent->color = 'R';
                    parent->color = 'B';
                    uncle->color = 'B';
                    u = grandparent;
                }else{
                    if (u == parent->rt){
                        LeftRotate(parent);
                        u = parent ;
                        parent = u->pr ;
                    }
                    RightRotate(grandparent);
                    swap(parent->color , grandparent->color);
                    u = parent ;
                }
            }else{
                uncle = grandparent->lf;
                if (uncle != nullptr && uncle->color == 'R') {
                    grandparent->color = 'R';
                    parent->color = 'B';
                    uncle->color = 'B';
                    u = grandparent;
                } else {
                    if (u == parent->lf) {
                        RightRotate(parent);
                        u = parent;
                        parent = u->pr;
                    }
                    LeftRotate(grandparent);
                    swap(parent->color, grandparent->color);
                    u = parent;
                }
            }
        }
        root->color = 'B';
    }

    void BalansDelete(Node<T>* u) {
        while (u != root && (u == nullptr || u->color == 'B')) {
            if (u == u->pr->lf) {
                Node<T>* sibling = u->pr->rt;

                // Case 1: Sibling is red
                if (sibling->color == 'R') {
                    sibling->color = 'B';
                    u->pr->color = 'R';
                    LeftRotate(u->pr);
                    sibling = u->pr->rt;
                }

                // Case 2: Sibling's children are black
                if ((sibling->lf == nullptr || sibling->lf->color == 'B') &&
                    (sibling->rt == nullptr || sibling->rt->color == 'B')) {
                    sibling->color = 'R';
                    u = u->pr;
                } else {
                    // Case 3: Sibling's left child is red, right child is black
                    if (sibling->lf != nullptr && sibling->lf->color == 'R') {
                        sibling->lf->color = 'B';
                        sibling->color = 'R';
                        RightRotate(sibling);
                        sibling = u->pr->rt;
                    }

                    // Case 4: Sibling's right child is red
                    sibling->color = u->pr->color;
                    u->pr->color = 'B';
                    if (sibling->rt != nullptr) sibling->rt->color = 'B';
                    LeftRotate(u->pr);
                    u = root;
                }
            } else {
                // Symmetric cases for u being the right child
                Node<T>* sibling = u->pr->lf;

                if (sibling->color == 'R') {
                    sibling->color = 'B';
                    u->pr->color = 'R';
                    RightRotate(u->pr);
                    sibling = u->pr->lf;
                }

                if ((sibling->lf == nullptr || sibling->lf->color == 'B') &&
                    (sibling->rt == nullptr || sibling->rt->color == 'B')) {
                    sibling->color = 'R';
                    u = u->pr;
                } else {
                    if (sibling->rt != nullptr && sibling->rt->color == 'R') {
                        sibling->rt->color = 'B';
                        sibling->color = 'R';
                        LeftRotate(sibling);
                        sibling = u->pr->lf;
                    }

                    sibling->color = u->pr->color;
                    u->pr->color = 'B';
                    if (sibling->lf != nullptr) sibling->lf->color = 'B';
                    RightRotate(u->pr);
                    u = root;
                }
            }
        }

        if (u != nullptr) u->color = 'B';
    }



    Node<T>* minSuccessor(Node<T>* u){
        while (u -> lf != nullptr){
            u  = u-> lf ;
        }
        return u ;
    }
    Node<T>* maxSuccessor(Node<T>* u){
        while (u -> rt != nullptr){
            u = u->rt ;
        }
        return u ;
    }

    void LeftRotate(Node<T>*& u){
        Node<T>* rightchild = u->rt ;

        u->rt = rightchild ->lf ;
        if (rightchild->lf != nullptr){
            rightchild->lf->pr = u ;
        }

        rightchild->pr = u->pr ;
        if (u->pr == nullptr) root = rightchild;
        else if (u == u->pr->lf)
            u->pr->lf = rightchild;
        else
            u->pr->rt = rightchild;

        rightchild->lf  = u ;
        u ->pr = rightchild ;
    }
    void RightRotate(Node<T>*& u){
        Node<T>* leftchild = u->lf;
        u->lf = leftchild->rt;

        if (u->lf != nullptr)
            u->lf->pr = u;

        leftchild->pr = u->pr;

        if (u->pr == nullptr)
            root = leftchild;
        else if (u == u->pr->lf)
            u->pr->lf = leftchild;
        else
            u->pr->rt = leftchild;

        leftchild->rt = u;
        u->pr = leftchild;
    }
    void InOrder(Node<T>* u){
        if (u->lf != nullptr) InOrder(u->lf);
        cout << '(' << u->vl << " , " << u->color << ") "; ;
//        if (u == root) cout << " isroot " << u->vl << ' ';
        if (u -> rt != nullptr) InOrder(u -> rt);
    }

};



int main() {
    RedBlackTree<char>redBlackTree;
    redBlackTree.insert('M');
    redBlackTree.insert('T');
    redBlackTree.insert('F');
    redBlackTree.insert('Q');
    redBlackTree.insert('P');
    redBlackTree.print();
    redBlackTree.erase('F');
    redBlackTree.print();
    redBlackTree.erase('Q');
    redBlackTree.print();
    redBlackTree.erase('T');
    redBlackTree.print();
    return 0;
}