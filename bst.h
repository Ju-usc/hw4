#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.
    static Node<Key, Value>* successor(Node<Key, Value>* current); // TODO

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    Node<Key, Value>* findCorrectParent(const Key& currKey, Node<Key, Value>* tempNode);
    bool isLeft(Node<Key,Value>* node);
    bool isRight(Node<Key,Value>* node);
    void removeAllNodes(Node<Key, Value>* node);
    Node<Key, Value>* findNodeGivenKey(Node<Key, Value>* node, const Key& key) const;
    int height(Node<Key, Value>* root) const;
protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = NULL;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return (this->current_ == rhs.current_);
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return !(this->current_ == rhs.current_);
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    current_ = successor(current_); 
	return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear();
    
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // 1. Find the right spot to insert
    // 2. if greater go right, if less go left
    // 3. do this until it's null or equal to the value
    // 4. set it's parent and set parent's child
    Key key = keyValuePair.first;
    Value val = keyValuePair.second; 

    if(empty()){
        Node<Key, Value> *node = new Node<Key, Value>(key, val, NULL);
        root_ = node;
    }
  
    else{
        Node<Key, Value> *parent = findCorrectParent(key, root_);
        if(key > parent->getKey()){
            Node<Key, Value> *node = new Node<Key, Value>(key, val, parent);
            parent->setRight(node);
        }
        else if(key < parent->getKey()){
            Node<Key, Value> *node = new Node<Key, Value>(key, val, parent);
            parent->setLeft(node);
        }
        else if(key == parent->getKey()){
            parent->setValue(val);
        }

    }
}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::findCorrectParent(const Key& currKey, Node<Key, Value>* tempNode){

    Node<Key, Value>* result;
    if(currKey > tempNode->getKey()){
        if(tempNode->getRight() == NULL){
            return tempNode;
        }
        result = findCorrectParent(currKey, tempNode->getRight());
    }
    else if(currKey < tempNode->getKey()){
        if(tempNode->getLeft() == NULL){
            return tempNode;
        }
        result = findCorrectParent(currKey, tempNode->getLeft());
    }
    else if(currKey == tempNode->getKey()){
        return tempNode;
    }
    return result;

}

/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    // check if it's not empty and if there is a key needs to remove
    // if true, check if there are two childs, one child, or no child
    // case1: 0 child just delete the node and set its parents to NULL for the 
    Node<Key, Value> *node = internalFind(key);
    if(!empty() && node != NULL){
        //case 1: 0 child
        if(node->getLeft() == NULL && node->getRight() == NULL){

            if(node == root_){
                root_ = NULL;
            }
            else if(isLeft(node)){
                node->getParent()->setLeft(NULL);
            }
            else if(isRight(node)){
                node->getParent()->setRight(NULL);
            }
        }
        //case 2: 2 childs
        else if(node->getLeft() != NULL && node->getRight() != NULL){
            //swap with its predecessor, remove it
            Node<Key, Value> *pre = predecessor(node);
            nodeSwap(node, pre);

            //case 1 after swap, if the node has 1 child: HAVE TO PROMOTE THE ONE

            if(node->getLeft() != NULL){
                Node<Key, Value> *parent = node->getParent();
                node->getLeft()->setParent(parent);


                if(isLeft(node)){
                    parent->setLeft(node->getLeft());
                }
                else if(isRight(node)){
                    parent->setRight(node->getLeft());
                }
                
            }
            else{
                //case 2 after swap, if the node has 0 child
                if(isLeft(node)){
                    node->getParent()->setLeft(NULL);
                }
                else if(isRight(node)){
                    node->getParent()->setRight(NULL);
                }
            }
        }
        //case 3: 1 child
        else if(node->getLeft() == NULL){
            //right child
            Node<Key, Value> *parent = node->getParent();
            if(node == root_){
                root_ = node->getRight();
            }
            else if(isLeft(node)){
                parent->setLeft(node->getRight());
            }
            else if(isRight(node)){
                parent->setRight(node->getRight());
            }
            node->getRight()->setParent(parent);
        }
        else if(node->getRight() == NULL){
            //left child
            Node<Key, Value> *parent = node->getParent();
            if(node == root_){
                root_ = node->getLeft();
            }
            else if(isLeft(node)){
                parent->setLeft(node->getLeft());
            }
            else if(isRight(node)){
                parent->setRight(node->getLeft());
            }
            node->getLeft()->setParent(parent);
        }
        delete node;
     
    }
    ;
}

template<class Key, class Value>
bool BinarySearchTree<Key, Value>::isLeft(Node<Key,Value>* node){

    if(node == root_){
        return false;
    }
    else if(node->getParent()->getLeft() == node){
        return true;
    }
    return false;
}   
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::isRight(Node<Key,Value>* node){
    if(node == root_){
        return false;
    }
    else if(node->getParent()->getRight() == node){
        return true;
    }
    return false;
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    // the next smallest value
    // ex) 1 2 5 10 13 14 predecessor of 5 is 2. predecessor of 14 is 13.
    // predecessor is the right most node of the left subtree.
    // else walk up the ancestor chain until I travese the first right child pointer
    // find the first node who is a right child of parent... that parent is the predecessor
    // if I get to the root without finding a node who is a right child, there is no predecessor
    
    if(current->getLeft()!= NULL){
        current = current->getLeft();
        while(current->getRight() != NULL){
            current = current->getRight();
        }
    }
    else{

        while(true){
            if(current->getParent() == NULL){
                return NULL;
            }
            else if(current->getParent()->getRight()== current){
                return current->getParent();
            }
            current = current->getParent();
        }        
    }
    return current;
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    // TODO
    // the next greatest value
    // ex) 1 2 5 10 13 14 successor of 5 is 2. successor of 14 is 13.
    // successor is the right most node of the left subtree.
    // else walk up the ancestor chain until I travese the first right child pointer
    // find the first node who is a right child of parent... that parent is the successor
    // if I get to the root without finding a node who is a right child, there is no successor

    if(current->getRight()!= NULL){
        current = current->getRight();
        while(current->getLeft() != NULL){
            current = current->getLeft();
        }
    }
    else{
        while(true){
            if(current->getParent() == NULL){
                return NULL;
            }
            else if(current->getParent()->getLeft()== current){
                return current->getParent();
            }
            current = current->getParent();
        }        
    }
    return current;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    if(!empty()){
        removeAllNodes(root_);
        root_ = NULL;

    }


}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::removeAllNodes(Node<Key, Value>* node){
    if(node != NULL){

        removeAllNodes(node->getLeft());
        removeAllNodes(node->getRight());
        delete node;
    }
    
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    if(root_ == NULL){
        return NULL;
    }
    Node<Key, Value> *node = root_;
    while(node->getLeft() != NULL){
        node = node->getLeft();

    }

    return node;
    

}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    return findNodeGivenKey(root_, key);
    
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::findNodeGivenKey(Node<Key, Value>* node, const Key& key) const{
    if(node == NULL){
        return NULL;
    }
    if(node -> getKey() == key){
        return node;
    }
    Node<Key, Value>* l = findNodeGivenKey(node->getLeft(), key);
    Node<Key, Value>* r = findNodeGivenKey(node->getRight(), key);
    if(l){
        return l;
    }
    if(r){
        return r;
    }
    return NULL;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    if(root_ == NULL){
        return true;
    }

    return height(root_) != -1;
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height(Node<Key, Value>* root) const{
    if(root == NULL){
        return 0;
    }
    int rh = height(root->getLeft());
    int lh = height(root->getRight());
    if(abs(rh-lh) > 1 || rh == -1 || lh == -1){
        return -1;
    }
    return std::max(rh, lh) + 1;
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
