#include <iostream>
#include <sstream>
#include <list>
#include <queue>
#include <cassert>
#include <cstring>
#include <cmath>

class TreeNode {

    int d_time;
    int d_height;
    TreeNode *d_left;
    TreeNode *d_right;
    TreeNode *d_parent;
    public:
    TreeNode(int time) : d_time(time),d_left(NULL),d_right(NULL),d_parent(NULL)
        ,d_height(0) {}
    const int data() const { return d_time; }
    const int height() const { return d_height; }
    void setHeight(int height) { d_height = height; }
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
    enum InsType {
        LEFT = 1,
        RIGHT = 2
    };
    struct QueueRec {
        TreeNode* rec;
        InsType insType;
    };
    std::list<QueueRec> insList;
    std::queue<QueueRec, std::list<QueueRec> > insQueue;

    int getHeight(TreeNode* parent) {
        int height = 0 - ( parent->left() == NULL ? 0 : 1 + parent->left()->height());
        height += ( parent->right() == NULL ? 0 : 1 + parent->right()->height());
        return height;
    }

    public:
    BSTree() : head(NULL), insQueue(insList) {
    }

    void insert(int time) {
        TreeNode *newNode = new TreeNode(time);
        insList.clear();
        if (head == NULL) {
            head = newNode;
            newNode->parent() == NULL;
        } else {
            TreeNode **current = &head;
            TreeNode *parent = head;
            while ( (*current) != NULL) {
                parent = *current;
                QueueRec rec;
                rec.rec = *current;
                if ( **current < *newNode) {
                    std::cout << "taking right\n";
                    rec.insType = LEFT;
                    current = &((*current)->right());
                } else {
                    std::cout << "taking left\n";
                    rec.insType = RIGHT;
                    current = &((*current)->left());
                }
                insQueue.push(rec);
            }
            *current = newNode;
            newNode->parent() = parent;
            parent->setHeight(getHeight(parent));
            newNode->setHeight(0);
            while (!insQueue.empty()) {
                insQueue.back();
            }
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
        os << " '" << node->data() << "(" << node->height() << ")' ";
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
    int inp = 0;
    int data = 0;
    std::cout << "Enter 1 to insert 2 to print and 0 to exit\n";
    std::cin >> inp;
    BSTree tree;
    while(inp != 0) {
        if (inp == 1) {
            std::cin >> data;
            tree.insert(data);
        } else if (inp == 2) {
            std::ostringstream os;
            tree.print(os);
            std::cout << "Tree is :" << os.str() << std::endl;
        } else {
            break;
        }
        std::cout << "Enter 1 to insert 2 to print and 0 to exit\n";
        std::cin >> inp;
    }
    return 0;
}
