#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); 
    virtual void remove(const Key& key);  // TODO:
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    AVLNode<Key, Value>* findCorrectParent(const Key& currKey, AVLNode<Key, Value>* tempNode);
    void rightRotate(AVLNode<Key, Value>* node);
    void leftRotate(AVLNode<Key, Value>* node);
    bool isLine(AVLNode<Key, Value>* child);
    bool isZigZag(AVLNode<Key, Value>* child);
    void insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node);
    void removeFix(AVLNode<Key, Value>* node, int diff);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // 1. Find the right spot to insert
    // 2. if greater go right, if less go left
    // 3. do this until it's null or equal to the value
    // 4. set it's parent and set parent's child
    Key key = new_item.first;
    std::cout <<"INSERTING NODE: " << key << std::endl;
    Value val = new_item.second; 
    if(this->empty()){
        AVLNode<Key, Value> *node = new AVLNode<Key, Value>(key, val, NULL);
        this->root_ = node;
    }
  
    else{
        AVLNode<Key, Value> *parent = findCorrectParent(key, (AVLNode<Key,Value>*)this->root_);
        
        if(key > parent->getKey()){
            AVLNode<Key, Value> *node = new AVLNode<Key, Value>(key, val, parent);
            parent->setRight(node);
            parent->updateBalance(+1);
            if(parent->getBalance() != 0 && parent->getParent() != NULL){
            
            //call insert fix
            insertFix(parent, node);
        }
        }
        else if(key < parent->getKey()){
            AVLNode<Key, Value> *node = new AVLNode<Key, Value>(key, val, parent);
            parent->setLeft(node);
            parent->updateBalance(-1);
            if(parent->getBalance() != 0 && parent->getParent() != NULL){
            
            //call insert fix
            insertFix(parent, node);
        }
        }
        else if(key == parent->getKey()){
            parent->setValue(val);
        }

        //after update the balance factor of parent,
        //if our parent is out of balance not 0, we know that our grandparent may be out of balance.

        


    }
    // std::cout << "IS BALANCERD: " << std::boolalpha << this->isBalanced() << std::endl;
}
template<class Key, class Value>
void AVLTree<Key, Value>:: insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node){
    //if num = -1, assume p is left child of g
    //if num = 1, assume p is right child of g


    if(parent == NULL || parent->getParent() == NULL){
        return;
    }
    AVLNode<Key, Value> *grandParent = parent->getParent();
    int num;
    if(grandParent->getLeft() == parent){
        num = -1;
    }
    else if(grandParent->getRight() == parent){
        num = 1;
        
    }
    else{
        std::cout << "NUM IS NOT INIT" << std::endl;
    }


    if(num == -1){
    
        grandParent->updateBalance(num);
        if(grandParent->getBalance() == 0){
            return;
        }
        else if(grandParent->getBalance() == -1){
        
            insertFix(grandParent, parent);
        }
        else if(grandParent->getBalance() == -2){
            if(isLine(node)){
                rightRotate(parent);
                parent->setBalance(0);
                grandParent->setBalance(0);
            }
            else if(isZigZag(node)){
                leftRotate(node);
                rightRotate(node);
                if(node->getBalance() == num){
                    parent->setBalance(0);
                    grandParent->setBalance(-num);
                    node->setBalance(0);
                }
                else if(node->getBalance() == 0){
                    parent->setBalance(0);
                    grandParent->setBalance(0);
                    node->setBalance(0);
                }
                else if(node->getBalance() == -num){
                    parent->setBalance(num);
                    grandParent->setBalance(0);
                    node->setBalance(0);
                }
            }
            else{
                std::cout << "NEITHER ZIG ZAG OR LINE" << std::endl;
            }
        }
    }
    else if(num == 1){
        grandParent->updateBalance(num);
        if(grandParent->getBalance() == 0){
            return;
        }
        else if(grandParent->getBalance() == 1){
            
            insertFix(grandParent, parent);
        }
        else if(grandParent->getBalance() == 2){
            
            if(isLine(node)){
                
                leftRotate(parent);
                parent->setBalance(0);
                grandParent->setBalance(0);
            }
            else if(isZigZag(node)){
                rightRotate(node);
                leftRotate(node);
                if(node->getBalance() == num){
                    parent->setBalance(0);
                    grandParent->setBalance(-num);
                    node->setBalance(0);
                }
                else if(node->getBalance() == 0){
                    parent->setBalance(0);
                    grandParent->setBalance(0);
                    node->setBalance(0);
                }
                else if(node->getBalance() == -num){
                    parent->setBalance(num);
                    grandParent->setBalance(0);
                    node->setBalance(0);
                }
            }
            else{
                std::cout << "NEITHER ZIG ZAG OR LINE" << std::endl;
            }
        }
    }

}

template<class Key, class Value>
bool AVLTree<Key, Value>::isLine(AVLNode<Key, Value>* child){
    //Assume there exists grandParent
    AVLNode<Key, Value> *g = child->getParent()->getParent();

    if(g->getLeft() != NULL && g->getLeft()->getLeft()!= NULL && g->getLeft()->getLeft() == child){
        //      g
        //    p 
        //  c 
        
        return true;
    }
    else if(g->getRight() != NULL && g->getRight()->getRight()!= NULL && g->getRight()->getRight() == child){
        
        //      g
        //        p
        //          c
        return true;
    }
 
    
    return false;
}
template<class Key, class Value>
bool AVLTree<Key, Value>::isZigZag(AVLNode<Key, Value>* child){
    //Assume there exists grandParent
    AVLNode<Key, Value> *g = child->getParent()->getParent();

    if(g->getRight() != NULL && g->getRight()->getLeft() != NULL &&
    g->getRight()->getLeft() == child){
        //    g
        //       p
        //     c
        return true;
    }
    else if(g->getLeft() != NULL && g->getLeft()->getRight() != NULL &&
    g->getLeft()->getRight() == child){
        //     g
        //  p   
        //    c
        return true;
    }
    return false;

}
template<class Key, class Value>
void AVLTree<Key, Value>:: rightRotate(AVLNode<Key, Value>* node){
    //assume there exists parent's node
    //case 1 when parent's node is root: have to update the root at the end
    //case 2 when parent's node is not root: general case
    //case 3 when there is no right child.
    //1. get parent's node 
    //2. get right child of node
    //3. get grand parent node
    //3. move right child of the node to the left child of the parent's node 
    //3-1. update right child's parent to the parent's node
    //4. move parent's node to the right child of the node
    //4-1. update parent's parent to the node
    //5-1. update node's parent to grand parent.

    AVLNode<Key, Value> *parent = node->getParent();
    AVLNode<Key, Value> *grandParent = parent->getParent();
    AVLNode<Key, Value> *rightChild = node->getRight();

    
    parent->setLeft(rightChild);
    if(rightChild != NULL){
        rightChild->setParent(parent);
        
    }

    node->setRight(parent);
    parent->setParent(node);
 
    node->setParent(grandParent);
    
    //if grandParent exists
    if(grandParent != NULL){
        if(grandParent->getRight() == parent){
            grandParent->setRight(node);
        }
        else if(grandParent->getLeft() == parent){
            grandParent->setLeft(node);
        }        
    }

    //if grandParent is a root
    else{
        this->root_ = node;
    }
    
}

template<class Key, class Value>
void AVLTree<Key, Value>:: leftRotate(AVLNode<Key, Value>* node){
    //assume there exists parent's node

    AVLNode<Key, Value> *parent = node->getParent();
    AVLNode<Key, Value> *grandParent = parent->getParent();
    AVLNode<Key, Value> *leftChild = node->getLeft();

    
    parent->setRight(leftChild);
    if(leftChild != NULL){
        leftChild->setParent(parent);
        
    }

    node->setLeft(parent);
    parent->setParent(node);
 
    node->setParent(grandParent);
    
    //if grandParent exists
    if(grandParent != NULL){
        if(grandParent->getRight() == parent){
            grandParent->setRight(node);
        }
        else if(grandParent->getLeft() == parent){
            grandParent->setLeft(node);
        }        
    }

    //if grandParent is a root
    else{
        this->root_ = node;
    }
}



/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO:
    // check if it's not empty and if there is a key needs to remove
    // if true, check if there are two childs, one child, or no child
    // case1: 0 child just delete the node and set its parents to NULL for the 
    std::cout << "REMOVING NODE: " << key << std::endl;
    AVLNode<Key, Value> *node = (AVLNode<Key,Value>*)this->internalFind(key);
    if(!this->empty() && node != NULL){
        int diff =1;
        
        //case 1: 0 child
        if(node->getLeft() == NULL && node->getRight() == NULL){

            if(node == this->root_){
                this->root_ = NULL;
            }
            else if(this->isLeft(node)){
                diff = 1;
                node->getParent()->setLeft(NULL);
            }
            else if(this->isRight(node)){
                diff = -1;
                node->getParent()->setRight(NULL);
            }
        }
        //case 2: 2 childs
        else if(node->getLeft() != NULL && node->getRight() != NULL){
            //swap with its predecessor, remove it
            AVLNode<Key, Value> *pre = (AVLNode<Key,Value>*)this->predecessor(node);
            nodeSwap(node, pre);

            //case 1 after swap, if the node has 1 child: HAVE TO PROMOTE THE ONE

            if(node->getLeft() != NULL){
                AVLNode<Key, Value> *parent = node->getParent();
                node->getLeft()->setParent(parent);
                if(this->isLeft(node)){
                    parent->setLeft(node->getLeft());
                    diff = 1;
                }
                else if(this->isRight(node)){
                    parent->setRight(node->getLeft());
                    diff = -1;
                }
                
            }
            else{
                //case 2 after swap, if the node has 0 child
                if(this->isLeft(node)){
                    node->getParent()->setLeft(NULL);
                    diff = 1;
                }
                else if(this->isRight(node)){
                    node->getParent()->setRight(NULL);
                    diff = -1;
                }
            }
        }
        //case 3: 1 child
        else if(node->getLeft() == NULL){
            //right child
            AVLNode<Key, Value> *parent = node->getParent();
            if(node == this->root_){
                this->root_ = node->getRight();
            }
            else if(this->isLeft(node)){
                parent->setLeft(node->getRight());
                diff = 1;
            }
            else if(this->isRight(node)){
                parent->setRight(node->getRight());
                diff = -1;
            }
            node->getRight()->setParent(parent);
        }
        else if(node->getRight() == NULL){
            //left child
            AVLNode<Key, Value> *parent = node->getParent();
            if(node == this->root_){
                this->root_ = node->getLeft();
            }
            else if(this->isLeft(node)){
                diff = 1;
                parent->setLeft(node->getLeft());
            }
            else if(this->isRight(node)){
                diff = -1;
                parent->setRight(node->getLeft());
            }
            node->getLeft()->setParent(parent);
        }
        AVLNode<Key, Value> *parent = node->getParent();
        // this->print();
        // std::cout <<"node: "<< node->getKey() << std::endl;
        // std::cout <<"parent: "<< parent->getRight()->getKey() << std::endl;
        if(parent != NULL){

            if(this->isLeft(node)){
                std::cout << "Node is Left" << std::endl;
                diff = 1;
            }
            else if(this->isRight(node)){
                std::cout << "Node is Right" << std::endl;

                diff = -1;
            }
            else{
                std::cout << "NEITHER" << std::endl;
            }
        }
        else{
            std::cout << "NO PARENT" << std::endl;
        }
        // AVLNode<Key, Value> *parent = node->getParent();
        delete node;
        this->print();
        // std::cout <<"node: "<< parent->getKey() << " balance: " << (int)parent->getBalance() << std::endl;
        removeFix(parent, diff);
        // std::cout <<"node: "<< parent->getKey() << " balance: " << (int)parent->getBalance() << std::endl;
        std::cout << "is Balance: " << std::boolalpha << this->isBalanced() << std::endl;
    }
}
template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* node, int diff){
    std::cout << "calling removeFix at node: " << node << " diff: " << diff << std::endl;
    if(node == NULL){
        return;
    }
    AVLNode<Key, Value>* parent = node->getParent();
    int nextDiff = diff;
    int num = diff;
    
    
    if(parent){
        if(this->isLeft(node)){
            nextDiff = 1;
        }
        // else if(this->isRight(node)){
        //     nextDiff = -1;
        // }
        else{
            nextDiff = -1;
        }
    }
    else{
        std::cout << "PARENT IS NULL NODE MAYBE ROOT" << std::endl;
    }

    //Assume diff = -1
    //case 1: b(n) + diff = -2
    if(node->getBalance() + diff == 2*num){
        std::cout << "CALLING REMOVING CASE 1 " << std::endl;
        //Let child = taller of the children
        AVLNode<Key, Value>* child;
        if(num == -1){
            child = node->getLeft();
        }
        else if(num == 1){
            child = node->getRight();
        }
        if(child->getBalance() == num){
            std::cout << "CALLING REMOVING CASE 1-a " << std::endl;
            //zig-zig case
            if(num == -1){
                rightRotate(child);
            }
            else if(num == 1){
                leftRotate(child);
            }

            node->setBalance(0);

            child->setBalance(0);

            removeFix(parent, nextDiff);

        }
        else if(child->getBalance() == 0){
            std::cout << "CALLING REMOVING CASE 1-b " << std::endl;
            //zig-zig case
            if(num == -1){
                rightRotate(child);
            }
            else if(num == 1){
                leftRotate(child);
            }
            node->setBalance(num);
            child->setBalance(-num);
            //DONE!
        }
        else if(child->getBalance() == -num){
            std::cout << "CALLING REMOVING CASE 1-c " << std::endl;
            //zig-zig case
            AVLNode<Key, Value>* grandChild;
            if(num == -1){
                grandChild = child->getRight();
                leftRotate(grandChild);
                rightRotate(grandChild);
            }
            else if(num == 1){
                grandChild = child->getLeft();
                rightRotate(grandChild);
                leftRotate(grandChild);
            }

            if(grandChild->getBalance() == -num){
                node->setBalance(0);
                child->setBalance(num);
                grandChild->setBalance(0);
            }
            else if(grandChild->getBalance() == 0){
                node->setBalance(0);
                child->setBalance(0);
                grandChild->setBalance(0);
            }
            else if(grandChild->getBalance() == num){
                node->setBalance(-num);
                child->setBalance(0);
                grandChild->setBalance(0);
            }
            else{
                std::cout << "GRAND CHILD BALANCE IS OUT OF RANGE" << std::endl;
            }
            removeFix(parent, nextDiff);
        }
    }
    //case 2: b(n) + diff == -1
    else if(node->getBalance() + diff == num){
        std::cout << "CALLING REMOVING CASE 2 " << std::endl;
        node->setBalance(num); //DONE
    }
    //case 3: b(n) + diff == 0
    else if(node->getBalance() + diff == 0){
        std::cout << "CALLING REMOVING CASE 3 " << std::endl;
        node->setBalance(0);
        removeFix(parent, nextDiff);
    }
    else{

        std::cout << "NO CASE FOUND" << std::endl;
    }
 
    

}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::findCorrectParent(const Key& currKey, AVLNode<Key, Value>* tempNode){

    AVLNode<Key, Value>* result;
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


#endif
