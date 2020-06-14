//
//  tree.h
//  Laba3
//
//  Created by Анна Потёмкина on 13.06.2020.
//  Copyright © 2020 Анна Потёмкина. All rights reserved.
//

#ifndef tree_h
#define tree_h
#include <iostream>
#include <list>
#include <queue>
#include <string>

using namespace std;

template <typename T>
struct TreeNode {
    T key;
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode(T keyy){
        key = keyy;
        left = right = 0;
        height = 1;
    }
};

template<typename T>
class Tree{
private:
    TreeNode<T>* root;
    
    void deleteTree(TreeNode<T>* node);
    TreeNode<T>* rotateRight(TreeNode<T>* node);
    TreeNode<T>* rotateLeft(TreeNode<T>* node);
    int height(TreeNode<T> *node);
    int bfactor(TreeNode<T> *node);
    void fixHeight(TreeNode<T> *node);
    TreeNode<T>* FindMinimum(TreeNode<T> *node);
    TreeNode<T>* FindNode(TreeNode<T> *node, T val);
    TreeNode<T>* balance(TreeNode<T>* node);
    TreeNode<T>* RemoveMin(TreeNode<T>* node);
    TreeNode<T>* insert(T key, TreeNode<T>* node);
    void map(T(*func)(T),TreeNode<T> *node);
    void reduce(T (*func)(T), TreeNode<T> *leaf, T* res);
    void where(bool (*func)(T), Tree<T> *res);
    void visit (TreeNode<T>* node, string form, string* res);
    TreeNode<T>* remove(TreeNode<T>* p, int k);
public:
    Tree();
    ~Tree();
    Tree(TreeNode<T> *root) {
           this->root = root;
       }
    TreeNode<T>* balance();
    void deleteTree();
    int height();
    TreeNode<T> *findNode(T val);
    void insert(T valToInsert);
    void map(T (*func)(T));
    Tree<T>* SubTree(T val);
    TreeNode<T> *get_root();
    Tree<T>* where(bool (*func)(T));
    T reduce(T (*func)(T));
    bool check(T val);
    void remove( int k);
    bool ContainSub(Tree<T> *subtree);
    bool Equal(Tree<T> *tree);
    string getStr(string format);
    
};

template<typename T>
TreeNode<T>* Tree<T>::rotateRight(TreeNode<T>* node){
    TreeNode<T>* temp = node->left;
    node->left = temp->right;
    temp->right = node;
    fixHeight(node);
    fixHeight(temp);
    return temp;
}

template <typename T>
TreeNode<T>* Tree<T>::rotateLeft(TreeNode<T>* node) {
    TreeNode<T>* temp = node->right;
    node->right = temp->left;
    temp->left = node;
    fixHeight(node);
    fixHeight(temp);
    return temp;
}

template <typename T>
int Tree<T>:: bfactor(TreeNode<T> *node)
{
    return (height(node->right)-height(node->left));
}

template <typename T>
int Tree<T>:: height(TreeNode<T> *node)
{
    return node?node->height:0;
}

template<typename T>
void Tree<T>:: fixHeight(TreeNode<T> *node) {
    int heightl = height(node->left);
    int heightr = height(node->right);
    node->height = ((heightl>heightr)? heightl : heightr) + 1;
}

template <typename T>
TreeNode<T>* Tree<T>::FindMinimum(TreeNode<T>* node){
     return node->left? FindMinimum(node->left) : node;;
    
}

template <typename T>
TreeNode<T>* Tree<T>::FindNode(TreeNode<T> *node, T val) {
    if (node->key == val) {
        return node;
    } else if (val < node->key) {
        if (node->left != nullptr) {
            return FindNode(node->left, val);
        } else {
            return nullptr;
        }
    } else {
        if (node->right != nullptr) {
            return FindNode(node->right, val);
        } else {
            return nullptr;
        }
    }
}

template<typename T>
TreeNode<T> *Tree<T>::balance(TreeNode<T> *node) {
    fixHeight(node);
    if( bfactor(node) == 2 )
    {
        if( bfactor(node->right) < 0 )
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    if( bfactor(node) == -2 )
    {
        if( bfactor(node->left) > 0  )
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    return node;
}

template <typename T>
TreeNode<T> *Tree<T>::RemoveMin(TreeNode<T>* node){
    if(node->left == 0)
        return node->right;
    node->left = RemoveMin(node->left);
    return balance(node);

}

template <typename T>
TreeNode<T>* Tree<T>::insert(T key, TreeNode<T>* node) {
    if (!node) return new TreeNode<T>(key);
    if (key < node->key)
        node->left = insert(key, node->left);
    else
        node->right = insert(key, node->right);
    return balance(node);
}

template <typename T>
void Tree<T>::map(T (*func)(T), TreeNode<T> *node) {
       node->key = func(node->key);
       if (node->left == nullptr && node->right == nullptr) {
           return;
       }
       if (node->left != nullptr) {
           map(func, node->left);
       }
       if (node->right != nullptr) {
           map(func, node->right);
       }
   }

template<typename T>
void Tree<T>::deleteTree(TreeNode<T> *node) {
    if(node!=NULL)
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

template<class T>
void Tree<T>::visit(TreeNode<T>* node, string form, string* res) {
    if (node != NULL) {
        for (int i = 0; i < 3; ++i) {
            if (form[i] == 'L') {
                visit(node->left, form, res);
            } else if (form[i] == 'R') {
                visit(node->right, form, res);
            } else {
                *res += to_string(node->key);
                *res += " ";
            }
        }
    }
}


template<typename T>
Tree<T>::Tree() {
    root = NULL;
}

template<typename T>
Tree<T>::~Tree() {
    deleteTree();
}

template<typename T>
TreeNode<T> *Tree<T>::balance() {
    return balance(root);
}

template<typename T>
void Tree<T>::deleteTree() {
    deleteTree(root);
}

template<typename T>
int Tree<T>::height() {
    return height(this->root);
}

template <typename T>
TreeNode<T>* Tree<T>::findNode(T val) {
       return FindNode(this->root, val);
   }

template<typename T>
void Tree<T>:: insert(T valToInsert){
     if (root != nullptr) {
            root = insert( valToInsert, root);
        } else {
            root = new TreeNode<T>(valToInsert);
        }
    }

template <typename T>
void Tree<T>::map(T (*func)(T)) {
    this->map(func, this->root);
}

template<typename T>
bool Tree<T>:: check(T val) {
       TreeNode<T> *ptr = this->root;
       while (ptr != nullptr) {
           if (val < ptr->key) {
               ptr = ptr->left;
           } else if (val > ptr->key) {
               ptr = ptr->right;
           } else {
               return true;
           }
       }
       if (ptr == nullptr) {
           return false;
       }
    return false;
   }

template<typename T>
Tree<T>* Tree<T>::SubTree(T val) {
    if (this->check(val)) {
        TreeNode<T> *ptr = this->findNode(val);
        Tree<T> *newTree = new Tree<T>(ptr);
        return newTree;
    } else {
        return nullptr;
    }
}

template<typename T>
T Tree<T>::reduce(T (*func)( T)) {
    T* res = new T();
    reduce(func, root, res);
    return *res;
}

template<typename T>
void Tree<T>::reduce(T (*func)(T), TreeNode<T> *leaf, T* res) {
    auto *temp = new list<TreeNode<T>*>;
    temp->push_back(root);
    while (temp->size() != 0) {
        TreeNode<T> *tmp = temp->front();
        temp->pop_front();
        *res = *res + func(tmp->key);
        if (tmp->left) {
            temp->push_back(tmp->left);
        }
        if (tmp->right) {
            temp->push_back(tmp->right);
        }
    }
    delete(temp);
}

template<typename T>
Tree<T> *Tree<T>::where(bool (*func)(T)) {
    auto* res = new Tree<T>();
    where(func, res);
    return res;
}

template<typename T>
void Tree<T>::where(bool (*func)(T), Tree<T> *res) {
    auto *temp = new list<TreeNode<T>*>;
    temp->push_back(root);
    while (temp->size() != 0) {
        TreeNode<T> *tmp = temp->front();
        temp->pop_front();
        if (func(tmp->key)) {
            res->insert(tmp->key);
        }
        if (tmp->left) {
            temp->push_back(tmp->left);
        }
        if (tmp->right) {
            temp->push_back(tmp->right);
        }
    }
    delete(temp);
}


template <typename T>
TreeNode<T>* Tree<T>::get_root() {
          return this->root;
      }

template <typename T>
bool Tree<T>::ContainSub(Tree<T> *subtree) {
       if (subtree->get_root() == nullptr) {
           return true;
       }
       if (this->check(subtree->get_root()->key)) {
           Tree<T> *checking = this->SubTree(subtree->get_root()->key);
           return checking->Equal(subtree);
       } else {
           return false;
       }
   }

template<typename T>
string Tree<T>::getStr(string form) {
    if (form.size() == 3) {
        bool N = false;
        bool L = false;
        bool R = false;
        for (int i = 0; i < 3; ++i) {
            if (form[i] == 'N') {
                N = true;
            } else if (form[i] == 'L') {
                L = true;
            } else if (form[i] == 'R') {
                R = true;
            } else {
                throw "Wrong simbol";
            }
        }
        if (N && L && R) {
            auto *res = new string;
            visit(root, form, res);
            return *res;
        } else {
            throw "BadFormat";
        }
    } else {
        throw "Wrong size";
    }
}

template <typename T>
bool Tree<T>::Equal(Tree<T> *tree) {
       if (this->root == nullptr && tree->get_root() == nullptr) {
           return true;
       }
       if (tree->get_root()->left == nullptr && tree->get_root()->right == nullptr && this->root->left == nullptr &&
           this->root->right == nullptr) {
           return this->root->key == tree->get_root()->key;
       }
       bool res = true;
       TreeNode<T> *this_right = this->root->right;
       TreeNode<T> *this_left = this->root->left;
       TreeNode<T> *tree_right = tree->get_root()->right;
       TreeNode<T> *tree_left = tree->get_root()->left;

       if (this_left != nullptr && tree_left != nullptr) {
           res = res && this->SubTree(this_left->key)->Equal(tree->SubTree(tree_left->key));
       } else if (this_left == nullptr && tree_left == nullptr) {}
       else {
           return false;
       }

       if (this_right != nullptr && tree_right != nullptr) {
           res = res && this->SubTree(this_right->key)->Equal(tree->SubTree(tree_right->key));
       } else if (this_right == nullptr && tree_right == nullptr) {}
       else {
           return false;
       }

       return res;
   }

template<typename T>
TreeNode<T>* Tree<T>::remove(TreeNode<T>* p, int k)
{
    if( !p ) return 0;
    if( k < p->key )
        p->left = remove(p->left,k);
    else if( k > p->key )
        p->right = remove(p->right,k);
    else //  k == p->key
    {
        TreeNode<T>* q = p->left;
        TreeNode<T>* r = p->right;
        delete p;
        if( !r ) return q;
        TreeNode<T>* min = FindMinimum(r);
        min->right = RemoveMin(r);
        min->left = q;
        return balance(min);
        }
            return balance(p);
        }

template<typename T>
void Tree<T>::remove( int k)
{
    root =remove(root, k);
    }
#endif /* tree_h */
