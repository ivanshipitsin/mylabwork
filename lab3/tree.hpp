#ifndef tree_HPP
#define tree_HPP 1

template<class Tv, class Tk>
class Node{
public:
    Node(Tv val = Tv(), Tk key = Tk(), Node<T>* rig = nullptr,Node<T>* left = nullptr):value(val), key(key), right(rig), left(left) {}

private:
    Tv value;
    Tk key;
    Node<Tv, Tk> * right;
    Node<Tv, Tk> * left;
};

template<class Tv, class Tk>
class Tree{
public:
    Tree(){
        root = nullptr;
    }
    
private:
    Node<Tv, Tk> * root;
};
#endif