#include <iostream>
#include <sstream>
#include <deque>
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
    enum InsType {
        LEFT = 1,
        RIGHT = 2
    };
    TreeNode(int time) : d_time(time),d_left(NULL),d_right(NULL),d_parent(NULL)
        ,d_height(0) {}
    const int data() const { return d_time; }
    const int height() const { return d_height; }
    void setHeight(int height) { d_height = height; }
    TreeNode*& left() { return d_left; }
    TreeNode*& right() { return d_right; }
    TreeNode*& parent() { return d_parent; }
    TreeNode*& link(InsType type) { return type == LEFT ? left() : right(); }
    bool operator<(const TreeNode& other) {
        return d_time < other.data();
    }
    bool operator>(const TreeNode& other) {
        return d_time > other.data();
    }
};

class BSTree {

    TreeNode* head;
    struct QueueRec {
        TreeNode* rec;
        TreeNode::InsType insType;
    };
    std::deque<QueueRec> insList;

    int getHeight(TreeNode* parent) {
        int height = 0 - ( parent->left() == NULL ? 0 : 1 + parent->left()->height());
        height += ( parent->right() == NULL ? 0 : 1 + parent->right()->height());
        return height;
    }

    public:
    BSTree() : head(NULL) {
    }

    TreeNode* LeftRotate(TreeNode* centre) {
        TreeNode* root = centre;
        root = centre->right();
        if (centre->right()->left()) {
            centre->right() = centre->right()->left();
        }
        root->left() = centre;
        root->setHeight(root->height() + 1);
        centre->setHeight(centre->height() - 1);
        return root;
    }

    TreeNode* RightRotate(TreeNode* centre) {
        TreeNode* root = centre;
        root = centre->left();
        if (centre->left()->right()) {
            centre->left() = centre->left()->right();
        }
        root->right() = centre;
        //root->setHeight(root->height() + 1);
        centre->setHeight(centre->height() - 1);
        return root;
    }

    bool isLeftHeavy(TreeNode* node) {
        if (!node) {
            return false;
        }
        std::cout << "Checking if node " << node->data() << " is left heavy\n";
        if (!node->left()) {
            return false;
        } else if (!node->right()) {
            std::cout << "L node height " << node->left()->height() << "\n";
            return ( (node->left()->height()) > 1);
        } else {
            std::cout << "L node height both " << (node->left()->height() - node->right()->height()) << "\n";
            return ( (node->left()->height() - node->right()->height()) > 1);
        }
    }

    bool isRightHeavy(TreeNode* node) {
        if (!node) {
            return false;
        }
        std::cout << "Checking if node " << node->data() << " is right heavy\n";
        if (!node->right()) {
            return false;
        } else if (!node->left()) {
            std::cout << "R node height " << node->right()->height() << "\n";
            return ( (node->right()->height()) > 1);
        } else {
            std::cout << "R node height both " << (node->right()->height() - node->left()->height()) << "\n";
            return ( (node->right()->height() - node->left()->height()) > 1);
        }
    }

    void insert(int time) {
        TreeNode *newNode = new TreeNode(time);
        insList.clear();
        if (head == NULL) {
            head = newNode;
            newNode->parent() == head;
        } else {
            TreeNode **current = &head;
            TreeNode *parent = head;
            while ( *current ) {
                parent = *current;
                QueueRec rec;
                rec.rec = *current;
                if ( **current < *newNode) {
                    rec.insType = TreeNode::RIGHT;
                    current = &((*current)->right());
                } else {
                    rec.insType = TreeNode::LEFT;
                    current = &((*current)->left());
                }
                insList.push_back(rec);
            }
            *current = newNode;
            newNode->parent() = parent;
            newNode->setHeight(0);
            QueueRec rec;
            while ( !insList.empty() ) {
                TreeNode *current = insList.back().rec;
                if (current->left() && current->right()) {
                    insList.back().rec->setHeight( 
                        std::max(current->left()->height(),current->right()->height()) + 1);
                } else if (current->left()) {
                    insList.back().rec->setHeight( current->left()->height() + 1);
                } else if (current->right()) {
                    insList.back().rec->setHeight( current->right()->height() + 1);
                }
                if (isRightHeavy(current)) {
                    if (isLeftHeavy(current->right())) {
                        std::cout << "DLR\n";
                        current->right() = RightRotate(current->right());
                        TreeNode* parent = current->parent();
                        if (!parent) {
                            head = LeftRotate(current);
                        } else if (parent->right() == current) {
                            parent->right() = LeftRotate(current);
                        } else {
                            parent->right() = LeftRotate(current);
                        }
                    } else {
                        std::cout << "SLR\n";
                        TreeNode* parent = current->parent();
                        if (!parent) {
                            head = LeftRotate(current);
                        } else if (parent->right() == current) {
                            parent->right() = LeftRotate(current);
                        } else {
                            parent->right() = LeftRotate(current);
                        }
                    }
                } else if (isLeftHeavy(current)) {
                    if (isRightHeavy(current->left())) {
                        std::cout << "DRR\n";
                        std::cout << "DLR\n";
                        current->left() = LeftRotate(current->left());
                        TreeNode* parent = current->parent();
                        if (!parent) {
                            head = RightRotate(current);
                        } else if (parent->right() == current) {
                            parent->right() = RightRotate(current);
                        } else {
                            parent->right() = RightRotate(current);
                        }
                    } else {
                        std::cout << "SRR\n";
                        TreeNode* parent = current->parent();
                        if (!parent) {
                            head = RightRotate(current);
                        } else if (parent->right() == current) {
                            parent->right() = RightRotate(current);
                        } else {
                            parent->right() = RightRotate(current);
                        }
                    }
                }
                rec = QueueRec(insList.back());
                insList.pop_back();
            }
            insList.clear();
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
