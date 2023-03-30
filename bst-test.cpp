#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"


using namespace std;


int main(int argc, char *argv[])
{
    BinarySearchTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(5, 8));
	// testTree.insert(std::make_pair(3, 159));
	// testTree.insert(std::make_pair(1, 9));
	// testTree.insert(std::make_pair(3, 0x5a));
	// testTree.insert(std::make_pair(15, 0xb));
	// testTree.insert(std::make_pair(1, 4));
	testTree.insert(std::make_pair(5, 159));
	testTree.print();
    return 0;
}
