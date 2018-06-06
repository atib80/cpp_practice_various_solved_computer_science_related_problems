#include <iostream>
#include <queue>
#include <utility>

template <typename T>
struct node {
  T data;
  node* left{};
  node* right{};
  node* parent{};

  node(const T& d, node* l = nullptr, node* r = nullptr, node* p = nullptr)
      : data{d}, left{l}, right{r}, parent{p} {}
};

using namespace std;

template <typename T>
pair<T, size_t> find_deepest_node_and_level_of_binary_tree(node<T>* root) {
  if (!root)
    return make_pair(T{}, 0);

  size_t max_level{1};
  node<T>* deepest_node{root};
  queue<pair<node<T>*, size_t>> q{{make_pair(root, 1)}};

  while (!q.empty()) {
    node<T>* n{q.front().first};
    const size_t current_level{q.front().second};
    q.pop();

    if (!n)
      continue;

    if (current_level > max_level) {
      max_level = current_level;
      deepest_node = n;
    }

    if (n->left)
      q.emplace(make_pair(n->left, current_level + 1));
    if (n->right)
      q.emplace(make_pair(n->right, current_level + 1));
  }

  return make_pair(deepest_node->data, max_level);
}

int main() {
  node<int> root{17};
  node<int> left{35};
  node<int> left_left_child{12};
  node<int> right{38};
  node<int> right_left_child{53};
  root.left = &left;
  root.right = &right;
  left.left = &left_left_child;
  right.left = &right_left_child;

  const pair<int, size_t> result{
      find_deepest_node_and_level_of_binary_tree(&root)};

  cout << "deepest node's value is " << result.first << "\nmax level is "
       << result.second << '\n';

  return 0;
}
