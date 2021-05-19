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

    Node<Tv,Tk> * foundNode(Tk key){
        return foundNoderev(key, root);
    }

    void addNode(Tk key, Tv value){
        Node<Tv,Tk> * ptr = foundNode(key);
        if(ptr){
            ptr->value = value;
        } else {
            addNoderev(key, value, root);
            balancing(root);
        }
    }

    void deleteNode(Tk key){
        Node<Tv,Tk> * ptr = foundNode(key);
        if(!ptr) {
            throw "Not found Node";
        } else if((ptr->left) && (ptr->right) && (ptr->right->height < ptr->left->height) || (!ptr->right)){
            Node<Tv,Tk> * curr = ptr->left;
            while(curr->right != nullptr){
                curr = curr->right;
            }
            ptr->key = curr->key;
            ptr->value = curr->value;
            Node<Tv,Tk> * paren = curr->parent;
            delete curr;

            while(paren != nullptr){
                balancing(paren);
                paren = paren->parent;
            }

        } else if((ptr->left) && (ptr->right) && (ptr->right->height > ptr->left->height) || (!ptr->left)){
            Node<Tv,Tk> * curr = ptr->right;
            while(curr->left != nullptr){
                curr = curr->left;
            }
            ptr->key = curr->key;
            ptr->value = curr->value;
            Node<Tv,Tk> * paren = curr->parent;
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
                delete currL;
            } else {
                ptr->key = currR->key;
                ptr->value = currR->value;
                paren = currR->parent;
                delete currR;
            }

            while(paren != nullptr){
                balancing(paren);
                paren = paren->parent;
            }
        } else if((!ptr->left) && (!ptr->right)){
            Node<Tv,Tk> * paren = ptr->parent;
            delete ptr;
            
            while(paren != nullptr){
                balancing(paren);
                paren = paren->parent;
            }
        }
    }
protected:
    Node<Tv,Tk> * foundNoderev(Tk key, Node<Tv,Tk> * ptr){
        if(!ptr){
            return nullptr;
        }
        if(ptr->key == key){
            return ptr;
        }
        if(ptr->key < key){
            return foundNoderev(key, ptr->left);
        }
        if(ptr->key > key){
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
            newptr->height = 0;
            root = newptr;
            return; 
        }else if(!ptr->key >= key && (!ptr->right)){
            Node<Tv, Tk> * newptr = new Node<Tv,Tk>;
            newptr->key = key;
            newptr->value = value;
            newptr->right = nullptr;
            newptr->left = nullptr;
            newptr->parent = ptr;
            newptr->height = 0;
            ptr->right = newptr;
        }else if(ptr->key >= key && ptr->rigth){
            addNode(key, value, ptr->right);
            return;
        }else if(!ptr->key < key && (!ptr->left)){
            Node<Tv, Tk> * newptr = new Node<Tv,Tk>;
            newptr->key = key;
            newptr->value = value;
            newptr->right = nullptr;
            newptr->left = nullptr;
            newptr->parent = ptr;
            newptr->height = 0;
            ptr->left = newptr;
        } else if(ptr->key < key){
            addNode(key, value, ptr->left);
            return;
        }
        Node<Tv,Tk> * curr = ptr;
        while(curr && bfactor(curr) != 2 && bfactor(curr) != -2) {
            fixheight(curr);
            curr = curr->parent;
        }

        if(curr) {
            balancing(curr);
        }

    }

    Node<Tv,Tk>* rightbig(Node<Tv,Tk> * a){
        Node<Tv,Tk> * b = a->left;
        Node<Tv,Tk> * c = b->right;
        c->parent = a->parent;

        b->right = c->left;
        c->left->parent = b;

        a->left = c->right;
        c->right->parent = a;

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
        b->right->parent = a;

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
        a->right->parent = a;

        b->left = c->right;
        b->left->parent = b;

        c->left = a;
        a->parent = c;

        c->right = b;
        b->parent  = c;

        fixheight(a);
        fixheight(b);
        fixheight(c);

    }
    Node<Tv,Tk> * leftlittle(Node<Tv,Tk> * a){
        Node<Tv,Tk> * b = a->right;
        b->parent = a->parent;

        a->right = b->left;
        b->left->parent = a;

        b->left = a;
        a->parent = b;
        fixheight(a);
        fixheight(b);


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

    void balancing(Node<Tv,Tk> * curr){
        if(curr == nullptr){
            return;
        }else if(bfactor(curr) == 2){
            if(bfactor(curr->right) >= 0){
                curr = leftlittle(curr);
            } else {
                curr = leftbig(curr);
            }
        } else if(bfactor(curr) == -2){
            if(bfactor(curr->left) <= 0){
                curr = rightlittle(curr);
            } else {
                curr = rightbig(curr);
            }
        }
    }
private:
    Node<Tv, Tk> * root;
};
#endif