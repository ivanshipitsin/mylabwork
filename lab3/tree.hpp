#ifndef tree_HPP
#define tree_HPP 1

template<class Tv, class Tk>
struct Node{
public:
    Tv value;
    Tk key;
    unsigned char height;
    Node<Tv, Tk> * right;
    Node<Tv, Tk> * left;
    Node<Tv,Tk> * parent;
};

template<class Tv, class Tk>
class Tree{
public:
    Tree(){
        root = nullptr;
    }

    int HE(){
        return root->height;
    }

    Node<Tv,Tk> * foundNode(Tk key){
        return foundNoderev(key, root);
    }

    void addNode(Tk key, Tv value){
        Node<Tv,Tk> * ptr = foundNode(key);
        if(ptr){
            ptr->value = value;
        } else {
            addNoderev(key, value, root);
            //balancing(root);
        }
    }

    void deleteNode(Tk key){
        Node<Tv,Tk> * ptr = foundNode(key);
        if(!ptr) {
            throw "Not found Node";
        } else if((ptr->left) && (ptr->right) && (ptr->right->height < ptr->left->height) || (!ptr->right)&&(ptr->left)){
            Node<Tv,Tk> * curr = ptr->left;
            while(curr->right != nullptr){
                curr = curr->right;
            }
            ptr->key = curr->key;
            ptr->value = curr->value;
            Node<Tv,Tk> * paren = curr->parent;
            if(paren->left == curr){
                paren->left = nullptr;
            } else {
                paren->right = nullptr;
            }
            delete curr;

            while(paren != nullptr){
                balancing(paren);
                paren = paren->parent;
            }

        } else if((ptr->left) && (ptr->right) && (ptr->right->height > ptr->left->height) || (!ptr->left)&&(ptr->right)){
            Node<Tv,Tk> * curr = ptr->right;
            while(curr->left != nullptr){
                curr = curr->left;
            }
            ptr->key = curr->key;
            ptr->value = curr->value;
            Node<Tv,Tk> * paren = curr->parent;
            if(paren->left == curr){
                paren->left = nullptr;
            } else {
                paren->right = nullptr;
            }

            delete curr;

            while(paren != nullptr){
                balancing(paren);
                paren = paren->parent;
            }
        } else if((ptr->left) && (ptr->right) && (ptr->right->height == ptr->left->height)){
            Node<Tv,Tk> * currR = ptr->right;
            while(currR->left != nullptr){
                currR = currR->left;
            }
            Node<Tv,Tk> * currL = ptr->left;
            while(currL->right != nullptr){
                currL = currL->right;
            }
            Node<Tv,Tk> * paren;
            if(( ptr->key - currL->key) < (currR->key - ptr->key)){
                ptr->key = currL->key;
                ptr->value = currL->value;
                paren = currL->parent;
                if(paren->left == currL){
                    paren->left = nullptr;
                } else {
                    paren->right = nullptr;
                }
                delete currL;
            } else {
                ptr->key = currR->key;
                ptr->value = currR->value;
                paren = currR->parent;
                if(paren->left == currR){
                    paren->left = nullptr;
                } else {
                    paren->right = nullptr;
                }
                delete currR;
            }

            while(paren != nullptr){
                balancing(paren);
                paren = paren->parent;
            }
        } else if((!ptr->left) && (!ptr->right)){
            Node<Tv,Tk> * paren = ptr->parent;
            if(paren->left == ptr){
                paren->left = nullptr;
            } else {
                paren->right = nullptr;
            }
            delete ptr;

            while(paren != nullptr){
                balancing(paren);
                paren = paren->parent;
            }
        }
    }

    ~Tree(){
        deleteTree(root);
    }
protected:
    Node<Tv,Tk> * foundNoderev(Tk key, Node<Tv,Tk> * ptr){
        if(!ptr){
            return nullptr;
        }
        if(ptr->key == key){
            return ptr;
        }
        if(ptr->key > key){
            return foundNoderev(key, ptr->left);
        }
        if(ptr->key < key){
            return foundNoderev(key, ptr->right);
        }
    }

    void addNoderev(Tk key, Tv value, Node<Tv, Tk> * ptr){
        if(!ptr){
            Node<Tv, Tk> * newptr = new Node<Tv,Tk>;
            newptr->key = key;
            newptr->value = value;
            newptr->right = nullptr;
            newptr->left = nullptr;
            newptr->parent = nullptr;
            newptr->height = 1;
            root = newptr;
            return; 
        }else if(ptr->key < key && (!ptr->right)){
            Node<Tv, Tk> * newptr = new Node<Tv,Tk>;
            newptr->key = key;
            newptr->value = value;
            newptr->right = nullptr;
            newptr->left = nullptr;
            newptr->parent = ptr;
            newptr->height = 1;
            ptr->right = newptr;
        }else if(ptr->key < key && ptr->right){
            addNoderev(key, value, ptr->right);
            return;
        }else if(ptr->key > key && (!ptr->left)){
            Node<Tv, Tk> * newptr = new Node<Tv,Tk>;
            newptr->key = key;
            newptr->value = value;
            newptr->right = nullptr;
            newptr->left = nullptr;
            newptr->parent = ptr;
            newptr->height = 1;
            ptr->left = newptr;
        } else if(ptr->key > key){
            addNoderev(key, value, ptr->left);
            return;
        }
        Node<Tv,Tk> * curr = ptr;
        while(curr && bfactor(curr) != 2 && bfactor(curr) != -2) {
            fixheight(curr);
            curr = curr->parent;
        }
        if(curr){
            if(curr->parent){
                if(curr->parent->left == curr){
                    curr->parent->left = balancing(curr);
                } else if(curr->parent->right == curr){
                    curr->parent->right = balancing(curr);
                }
            } else {
                root = balancing(root);
            }
        }

    }

    Node<Tv,Tk>* rightbig(Node<Tv,Tk> * a){
        Node<Tv,Tk> * b = a->left;
        Node<Tv,Tk> * c = b->right;
        c->parent = a->parent;

        b->right = c->left;
        if(b->right){
            c->left->parent = b;
        }
        a->left = c->right;
        if(a->left){
            c->right->parent = a;
        }

        c->right = a;
        a->parent = c;

        c->left = b;
        b->parent = c;

        fixheight(a);
        fixheight(b);
        fixheight(c);

        return c;

    }
    Node<Tv,Tk>* rightlittle(Node<Tv,Tk> * a){
        Node<Tv,Tk> * b = a->left;

        b->parent = a->parent;

        a->left = b->right;
        if(b->right){
            b->right->parent = a;
        }

        b->right = a;
        a->parent = b;

        fixheight(a);
        fixheight(b);

        return b;
    }     
    Node<Tk,Tv>* leftbig(Node<Tv,Tk> * a){
        Node<Tv,Tk> * b = a->right;
        Node<Tv,Tk> * c = b->left;
        c->parent = a->parent;

        a->right = c->left;
        if(a->right){
            a->right->parent = a;
        }

        b->left = c->right;
        if(b->left){
            b->left->parent = b;
        }

        c->left = a;
        a->parent = c;

        c->right = b;
        b->parent  = c;

        fixheight(a);
        fixheight(b);
        fixheight(c);
        return c;
    }
    Node<Tv,Tk> * leftlittle(Node<Tv,Tk> * a){
        Node<Tv,Tk> * b = a->right;
        b->parent = a->parent;

        a->right = b->left;
        if(b->left){
            b->left->parent = a;
        }

        b->left = a;
        a->parent = b;
        fixheight(a);
        fixheight(b);
        return b;

    }


    unsigned char height(Node<Tv,Tk>* p)
    {
        return p?p->height:0;
    }

    signed char bfactor(Node<Tv,Tk>* p)
    {
        return height(p->right)-height(p->left);
    }

    void fixheight(Node<Tv,Tk> *p){
        unsigned char hl = height(p->left);
	    unsigned char hr = height(p->right);
	    p->height = (hl>hr?hl:hr)+1;
    }

    Node<Tv,Tk>* balancing(Node<Tv,Tk> * curr){
        if(curr == nullptr){
            return nullptr;
        }else if(bfactor(curr) == 2){
            if(bfactor(curr->right) >= 0){
                return leftlittle(curr);
            } else {
                return leftbig(curr);
            }
        } else if(bfactor(curr) == -2){
            if(bfactor(curr->left) <= 0){
                return rightlittle(curr);
            } else {
                return rightbig(curr);
            }
        }
        return curr;
    }

    void deleteTree(Node<Tv,Tk> * a){
        if(a == nullptr){
            return;
        }
        if(!(a->left) && !(a->right)){
            if(a->parent){
                if(a->parent->right == a){
                    a->parent->right = nullptr;
                } else if(a->parent->left == a){
                    a->parent->left = nullptr;
                }
            }
            delete a;
        } else if(!(a->left)){
            deleteTree(a->right);
            deleteTree(a);
        } else if(!(a->right)) {
            deleteTree(a->left);
            deleteTree(a);
        } else {
            deleteTree(a->left);
            deleteTree(a->right);
            deleteTree(a);
        }
    }
private:
    Node<Tv, Tk> * root;
};
#endif