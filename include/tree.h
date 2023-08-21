#ifndef TREE_T
#define TREE_T

#include <iostream>
using namespace std;

class TreeNode {
  public:
    int num;
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode(void) : num(0), left(nullptr), right(nullptr) {}
    TreeNode(int num) : num(num), left(nullptr), right(nullptr) {}
    int get_height(void) { return height; }
    void set_height(int h) { height = h; }
    void update_height(TreeNode* node) {
        if (!node) {
            return;
        }
        update_height(node->left);
        update_height(node->right);
        int right_h = -1, left_h = -1;
        if (node->left) {
            left_h = (node->left)->get_height();
        }
        if (node->right) {
            right_h = (node->right)->get_height();
        }
        node->set_height(1 + (left_h > right_h ? left_h : right_h));
    }
    void update_height(void) { update_height(this); }
};

class TreeBase {
  protected:
    TreeNode* root;
    int node_num;

  public:
    TreeBase(void) : root(nullptr), node_num(0) {}
    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    TreeNode* findMax(TreeNode* node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }
    void printTree(TreeNode* node, string prefix = "", bool isLeft = true) {
        if (node == nullptr) {
            return;
        }

        printTree(node->right, prefix + (isLeft ? "│   " : "    "), false);

        cout << prefix;
        cout << (isLeft ? "└── " : "┌── ");
        cout << node->num << endl;

        printTree(node->left, prefix + (isLeft ? "    " : "│   "), true);
    }
    void printTree(void) { printTree(root); }
    void inorder_traversal(TreeNode* node) {
        if (!node)
            return;
        inorder_traversal(node->left);
        cout << node->num << " ";
        inorder_traversal(node->right);
    }
    void inorder_traversal(void) {
        inorder_traversal(root);
        cout << endl;
    }
    int size(void) { return node_num; }
};

class BinarySearchTree : public TreeBase {
  public:
    TreeNode* insert(TreeNode* node, int num) {
        TreeNode* new_node;
        if (!node) { // 建立新的node
            new_node = new TreeNode(num);
            return new_node;
        } else if (num == node->num) { // 重複
            return node;
        }

        if (num > node->num) {
            new_node = insert(node->right, num);
            if (!node->right) {
                node->right = new_node;
            }
        } else {
            new_node = insert(node->left, num);
            if (!node->left) {
                node->left = new_node;
            }
        }
        return new_node;
    }
    bool search(TreeNode* node, int num) {
        if (!node) {
            return false;
        } else if (num == node->num) {
            return true;
        }

        if (num > node->num) {
            return search(node->right, num);
        } else {
            return search(node->left, num);
        }
    }
    TreeNode* remove(TreeNode* node, int num, bool free = true) {
        if (!node) { // 不存在
            return nullptr;
        } else if (num == node->num) { // 刪除
            TreeNode* new_node = nullptr;
            if (node->right) { // 取代
                if (node->left) {
                    new_node = findMin(node->right);
                    new_node->right = remove(node->right, new_node->num, false);
                    new_node->left = node->left;
                } else {
                    new_node = node->right;
                }
            } else if (node->left) {
                new_node = node->left;
            }

            if (free) {
                delete node;
            }
            return new_node;
        }

        if (num > node->num) {
            node->right = remove(node->right, num, free);
        } else {
            node->left = remove(node->left, num, free);
        }

        return node;
    }
    TreeNode* insert(int num) {
        if (!root) {
            return root = insert(root, num);
        } else {
            return insert(root, num);
        }
    }
    bool search(int num) { return search(root, num); }
    void remove(int num) { root = remove(root, num); }
};

/** -----------------------------------------------------------------*/

class AVLTree : public BinarySearchTree {
  private:
    int balance_factor(TreeNode* node) {
        if (!node) {
            return -1;
        }

        return (node->left ? (node->left)->get_height() : -1) -
               (node->right ? (node->right)->get_height() : -1);
    }
    void right_rotation(TreeNode* node) {}
    void left_rotation(TreeNode* node) {}
    void update_treebalance(TreeNode* node) {
        node->update_height();
        node->get_height();
    }

  public:
    void insert(int num) { TreeNode* new_node = BinarySearchTree::insert(num); }
    bool search(int num) { return BinarySearchTree::search(num); }
    void remove(int num) { BinarySearchTree::remove(num); }
};

#endif