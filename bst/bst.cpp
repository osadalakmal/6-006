#include <iostream>
#include <sstream>
#include <cassert>
#include <cstring>

class TreeNode {

    int d_time;
    TreeNode *d_left;
    TreeNode *d_right;
    TreeNode *d_parent;
    public:
    TreeNode(int time) : d_time(time),d_left(NULL),d_right(NULL),d_parent(NULL) {}
    const int data() const { return d_time; }
    TreeNode*& left() { return d_left; }
    TreeNode*& right() { return d_right; }
    TreeNode*& parent() { return d_parent; }
    bool operator<(const TreeNode& other) {
        return d_time < other.data();
    }
    bool operator>(const TreeNode& other) {
        return d_time > other.data();
    }
};

class BSTree {

    TreeNode* head;
    public:
    BSTree() : head(NULL) {
    }

    void insert(int time) {
        TreeNode *newNode = new TreeNode(time);
        if (head == NULL) {
            head = newNode;
        } else {
            TreeNode **current = &head;
            TreeNode *parent = head;
            while ( (*current) != NULL) {
                parent = *current;
                if ( **current < *newNode) {
                    current = &((*current)->right());
                } else {
                    current = &((*current)->left());
                }
            }
            *current = newNode;
            newNode->parent() = parent;
        }
    }

    TreeNode* find(int time) {
        TreeNode *current = head;
        while(current != NULL) {
            if ( *current < time) {
                current = current->left();
            } else if ( *current > time) {
                current = current->right();
            } else {
                break;
            }
        }
        return current;
    }

    void print(std::ostringstream& os, TreeNode* node = NULL) {
        if (!node) {
            node = head;
        }
        os << " '" << node->data() << "' ";
        if (node->left()) {
            print(os, node->left());
        }
        if (node->right()) {
            print(os, node->right());
        }
    }

};

int test_main(int argc, char* argv[]) {
    BSTree tree;
    tree.insert(49);
    tree.insert(79);
    tree.insert(46);
    tree.insert(41);
    tree.insert(64);
    std::ostringstream os;
    tree.print(os);
    std::string expResult(" '49'  '46'  '41'  '79'  '64' ");
    assert(expResult == os.str());
    assert(tree.find(49) != NULL);
    assert(tree.find(59) == NULL);
    assert(tree.find(49)->parent() == tree.find(46));
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc > 1 && (strncmp(argv[1], "test", sizeof("test")) == 0) ) {
        test_main(argc, argv);
    }
    return 0;
}
