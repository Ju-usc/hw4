#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here


bool equalPaths(Node * root)
{
    // Add your code below
    if(root == nullptr){
        return true;
    }
    int lh = height(root->left);
    int rh = height(root->right);
    if(lh <= 1 && rh <= 1){
        return true;
    }
    return height(root->left) == height(root->right);
}
int height(Node* root){
    if(root == nullptr){
        return 0;
    }
    int rh = height(root->left);
    int lh = height(root->right);


    return max(rh, lh) + 1;
}

