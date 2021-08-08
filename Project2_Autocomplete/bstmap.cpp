// Yusuf Pisan pisan@uw.edu
// 17 Jan 2021

// BST class
// Creates a BST to store values
// Uses Node which holds the data

#include "bstmap.h"
#include <cassert>

using namespace std;

static vector<BSTMap::value_type> vect;

// copy constructor
BSTMap::BSTMap(const BSTMap &bst) {
  clear();
  if (bst.root == nullptr) {
    return;
  }
  auto *node1 = bst.root;
  auto *node0 = new Node();
  node0->data = node1->data;
  root = node0;
  assign(node0, node1);
}

// helper function for copy constructor, works recursively
void BSTMap::assign(Node *node0, Node *node1) {
  if (node1->left != nullptr) {
    auto *node = new Node();
    node->data = node1->left->data;
    node0->left = node;
    assign(node0->left, node1->left);
  }
  if (node1->right != nullptr) {
    auto *node = new Node();
    node->data = node1->right->data;
    node0->right = node;
    assign(node0->right, node1->right);
  }
}

// destructor
BSTMap::~BSTMap() { clear(); }

// delete all nodes in tree
void BSTMap::clear() {
  clearHelper(root);
  root = nullptr;
}

// helper function for clear, works recursively
void BSTMap::clearHelper(Node *&node) {
  if (node == nullptr) {
    return;
  }
  clearHelper(node->left);
  clearHelper(node->right);
  delete node;
  node = nullptr;
}

// true if no nodes in BST
bool BSTMap::empty() const { return (root == nullptr); }

// Number of nodes in BST
int BSTMap::size() const { return sizeHelper(root); }

// helper function for size, works recursively
int BSTMap::sizeHelper(Node *root) const {
  if (root == nullptr) {
    return 0;
  }
  int s = 1;
  s += sizeHelper(root->left);
  s += sizeHelper(root->right);
  return s;
}

// If k matches the key returns a reference to its value
// If k does not match any key, inserts a new element
// with that key and returns a reference to its mapped value.
BSTMap::mapped_type &BSTMap::operator[](const key_type &k) {
  if (contains(k)) {
    return find(root, k);
  }
  return add(k, 0);
}

// true if item is in BST
bool BSTMap::contains(const key_type &key) const {
  return containsHelper(root, key);
}

// helper function for contains, works recursively
bool BSTMap::containsHelper(Node *root, const key_type &key) const {
  if (root == nullptr) {
    return false;
  }
  if (key == root->data.first) {
    return true;
  }
  if (key < root->data.first) {
    return containsHelper(root->left, key);
  }
  return containsHelper(root->right, key);
}

// helper function for operator []
// find key in BST and return mapped_value, works recursively
BSTMap::mapped_type &BSTMap::find(Node *curr, const key_type &k) {
  if (curr->data.first == k) {
    return curr->data.second;
  }
  if (curr->data.first > k) {
    return find(curr->left, k);
  }
  return find(curr->right, k);
}

// helper function for operator []
// add Node to BST if no such value
BSTMap::mapped_type &BSTMap::add(const key_type &k, const mapped_type &value) {
  if (root == nullptr) {
    root = new Node();
    root->data = make_pair(k, value);
    return root->data.second;
  }
  return insert(root, k, value);
}

// helper function for operator []
// insert new element to the BST sorted by weight, works recursively
BSTMap::mapped_type &BSTMap::insert(Node *curr, const key_type &k,
                                    const mapped_type &value) {
  key_type currNodeKey = curr->data.first;
  if (k < currNodeKey) {
    if (curr->left == nullptr) {
      insertLeft(curr, k, value);
      return curr->data.second;
    }
    return insert(curr->left, k, value);
  }
  if (curr->right == nullptr) {
    insertRight(curr, k, value);
    return curr->data.second;
  }
  return insert(curr->right, k, value);
}

// helper functions for insert
// precondition: arrived at the node to be inserted
// insert new element to the left of the predecesssor node
void BSTMap::insertLeft(Node *&node, const key_type &k,
                        const mapped_type &value) {
  node->left = new Node();
  node = node->left;
  node->data = make_pair(k, value);
}

// insert new element to the right of the predecesssor node
void BSTMap::insertRight(Node *&node, const key_type &k,
                         const mapped_type &value) {
  node->right = new Node();
  node = node->right;
  node->data = make_pair(k, value);
}

vector<BSTMap::value_type> BSTMap::getAll(const key_type &k) const {
  vector<value_type> v;
  vect.clear();
  inorder_vv(root, k, v);
  return v;
}

// helper function for getAll(), works recursively
void BSTMap::inorder_vv(Node *curr, const key_type &k,
                        vector<value_type> &v) const {
  if (curr == nullptr) {
    return;
  }
  string st;
  st = curr->data.first.substr(0, k.length());
  if (st >= k) {
    inorder_vv(curr->left, k, v);
  }

  if (k == st) {
    v.push_back(curr->data);
  }
  if (st <= k) {
    inorder_vv(curr->right, k, v);
  }
}

// 0 if empty, 1 if only root, otherwise
// height of root is max height of subtrees + 1
int BSTMap::height() const { return getHeight(root); }

// height of a Node, nullptr is 0, root is 1, static, no access to 'this'
// helper function to height(), used by printVertical
int BSTMap::getHeight(const Node *n) {
  if (n == nullptr) {
    return 0;
  }
  int l = getHeight(n->left);
  int r = getHeight(n->right);
  if (l > r) {
    return ++l;
  }
  return ++r;
}

// same as contains, but returns 1 or 0
// compatibility with std::map
size_t BSTMap::count(const string &k) const { return contains(k) ? 1 : 0; }

// inorder traversal: left-root-right
// takes a function that takes a single parameter of type T
void BSTMap::inorder(void visit(const BSTMap::value_type &item)) const {
  inorderHelper(root, visit);
}

// helper function for inorder, works recursively
void BSTMap::inorderHelper(Node *curr,
                           void visit(const BSTMap::value_type &item)) const {
  if (curr == nullptr) {
    return;
  }
  inorderHelper(curr->left, visit);
  visit(curr->data);
  inorderHelper(curr->right, visit);
}

// preorder traversal: root-left-right
void BSTMap::preorder(void visit(const BSTMap::value_type &item)) const {
  preorderHelper(root, visit);
}

// helper function for preorder, works recursively
void BSTMap::preorderHelper(Node *curr,
                            void visit(const value_type &item)) const {
  if (curr == nullptr) {
    return;
  }
  visit(curr->data);
  preorderHelper(curr->left, visit);
  preorderHelper(curr->right, visit);
}

// postorder traversal: left-right-root
void BSTMap::postorder(void visit(const value_type &item)) const {
  postorderHelper(root, visit);
}

// helper function for postorder, works recusively
void BSTMap::postorderHelper(Node *curr,
                             void visit(const BSTMap::value_type &item)) const {
  if (curr == nullptr) {
    return;
  }
  postorderHelper(curr->left, visit);
  postorderHelper(curr->right, visit);
  visit(curr->data);
}

// balance the BST by saving all nodes to a vector inorder
// and then recreating the BST from the vector
void BSTMap::rebalance() {
  Node *curr = root;
  vector<Node *> nodes;
  allNodesInOrder(curr, nodes);
  clear();
  rebuild(nodes, 0, nodes.size() - 1);
  for (auto n : nodes) {
    delete n;
  }
}

// helper function for rebalancing BSTree
// get all nodes in BSTree and store in vector in-order, works recursively
void BSTMap::allNodesInOrder(Node *curr, vector<Node *> &nodes) {
  if (curr != nullptr) {
    allNodesInOrder(curr->left, nodes);
    auto *temp = new Node;
    temp->data = curr->data;
    nodes.push_back(temp);
    allNodesInOrder(curr->right, nodes);
  }
}

// helper function for rebalancing BSTree
// rebuild BSTree using the vector of in-order nodes, works recursively
void BSTMap::rebuild(const vector<Node *> &nodes, int start, int end) {
  if (start <= end) {
    int mid = (start + end) / 2;
    Node *node = nodes[mid];
    this->add(node->data.first, node->data.second);
    rebuild(nodes, start, mid - 1);
    rebuild(nodes, mid + 1, end);
  }
}

// trees are equal if they have the same structure
// AND the same item values at all the nodes
bool BSTMap::operator==(const BSTMap &other) const {
  Node *node1 = root;
  Node *node2 = other.root;
  return isEqual(node1, node2);
}

// not == to each other
bool BSTMap::operator!=(const BSTMap &other) const {
  Node *node1 = root;
  Node *node2 = other.root;
  return !isEqual(node1, node2);
}

// helper function for  operator == and !=, works recursively
bool BSTMap::isEqual(const Node *node1, const Node *node2) const {
  if (node1 == nullptr && node2 == nullptr) {
    return true;
  }
  if (node1 == nullptr || node2 == nullptr) {
    return false;
  }
  return isSameNode(node1, node2) && isEqual(node1->left, node2->left) &&
         isEqual(node1->right, node2->right);
}

// helper function for operator == and !=
bool BSTMap::isSameNode(const Node *node1, const Node *node2) const {
  return node1->data.first == node2->data.first &&
         node1->data.second == node2->data.second;
}
