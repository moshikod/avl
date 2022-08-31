/**
 * @file avl.h
 * @author Moshe Pontch (pontch at gmail.com)
 * @brief AVL tree (Adelson-Velsky and Landis)
 * @version 1.0
 * @date 2022-08-31
 *
 */
#ifndef _AVL__H
#define _AVL__H

#define _MAX(X, Y) ((X) > (Y) ? (X) : (Y))

template <class T>
class AvlTree;

template <class T>
class AvlNode
{
  friend class AvlTree<T>;

public:
  T data;

  AvlNode(int key, const T &data, AvlNode<T> *parent)
      : data(data),
        key_(key),
        parent_(parent),
        left_(NULL),
        right_(NULL),
        height_(1)
  {
  }

  AvlNode(const AvlNode<T> &other, AvlNode<T> *parent = NULL) : data(other.data), key_(other.key_), parent_(parent), height_(other.height_)
  {
    left_ = AvlNode::clone(other.left_, this);
    right_ = AvlNode::clone(other.right_, this);
  }

  AvlNode<T> &operator=(const AvlNode<T> &other)
  {
    // Avoid self assignment
    if (this != &other)
    {
      // Avoid assigning parent
      key_ = other.key_;
      data = other.data;
      left_ = other.left_;
      right_ = other.right_;
      height_ = other.height_;
    }

    return *this;
  }

  /**
   * @brief node is equal to another iif keys are equal
   * @note node comparison is agnostic to data
   *
   * @param other
   * @return true
   * @return false
   */
  bool operator==(const AvlNode<T> &other) const
  {
    return key_ == other.key_;
  }

  bool operator!=(const AvlNode<T> &other)
  {
    return !(*this == other);
  }

  int key() const
  {
    return key_;
  }

  const AvlNode<T> *parent() const
  {
    return parent_;
  }

  AvlNode<T> *left() const
  {
    return left_;
  }

  AvlNode<T> *right() const
  {
    return right_;
  }

  int height() const
  {
    return height_;
  }

  int balance() const
  {
    return (left_ ? left_->height_ : 0) - (right_ ? right_->height_ : 0);
  }

  int count() const
  {
    return (left_ ? left_->count : 0) + 1 + (right_ ? right_->count() : 0);
  }

  AvlNode<T> *next() const
  {
    return next(const_cast<AvlNode<T> *>(this));
  }

  AvlNode<T> *previous() const
  {
    return previous(const_cast<AvlNode<T> *>(this));
  }

  AvlNode<T> *min_left()
  {
    return min_left(this);
  }

  AvlNode<T> *max_right()
  {
    return max_right(this);
  }

  int min_key()
  {
    return min_left()->key();
  }

  int max_key()
  {
    return max_right()->key();
  }

protected:
  void update_height()
  {
    height_ = 1 + _MAX(left_ ? left_->height_ : 0, right_ ? right_->height_ : 0);
  }

  AvlNode<T> *min_left(AvlNode<T> *node) const
  {
    if (!node)
    {
      return NULL;
    }
    while (node->left_)
    {
      node = node->left_;
    }
    return node;
  }

  AvlNode<T> *max_right(AvlNode<T> *node) const
  {
    if (!node)
    {
      return NULL;
    }
    while (node->right_)
    {
      node = node->right_;
    }
    return node;
  }

  /**
   * @brief Inorder successor
   * @note The time complexity is O(log n) since the next node is no more than "height" steps away
   *
   * @param node
   * @return AvlNode<T>*
   */
  AvlNode<T> *next(AvlNode<T> *node) const
  {
    if (!node)
    {
      return NULL;
    }

    if (node->right_)
    {
      return node->right_->min_left();
    }

    if (!node->parent_)
    {
      return NULL;
    }

    if (node == node->parent_->left_)
    {
      return node->parent_;
    }

    AvlNode<T> *alt = node;
    while (alt->parent_ && alt->parent_->left_ != alt)
    {
      alt = alt->parent_;
    }

    return alt->parent_;
  }

  /**
   * @brief Inorder predecessor
   * @note The time complexity is O(log n) since the previous node is no more than "height" steps away
   *
   * @param node
   * @return AvlNode<T>*
   */
  AvlNode<T> *previous(const AvlNode<T> *node) const
  {
    if (!node)
    {
      return NULL;
    }

    if (node->left_)
    {
      return node->left_->max_right();
    }

    if (!node->parent_)
    {
      return NULL;
    }

    if (node->parent_->right_ == node)
    {
      return node->parent_;
    }

    AvlNode<T> *alt = node->parent_;
    while (alt->parent_ && alt->parent_->left_ == alt)
    {
      alt = alt->parent_;
    }

    return alt->parent_;
  }

private:
  int key_;
  AvlNode<T> *parent_;
  AvlNode<T> *left_;
  AvlNode<T> *right_;
  int height_;

  static AvlNode<T> *clone(const AvlNode<T> *other, AvlNode<T> *parent = NULL)
  {
    if (!other)
    {
      return NULL;
    }
    return new AvlNode<T>(*other, parent);
  }
};

template <class T>
class AvlTree
{
public:
  AvlTree() : root_(NULL), count_(0){};
  virtual ~AvlTree()
  {
    clear();
  }

  AvlTree(const AvlTree<T> &other) : root_(other.root_), count_(other.count_), max_key_(other.max_key_), min_key_(other.min_key_)
  {
    root_ = AvlNode<T>::clone(other.root_);
  }

  AvlTree<T> *clone() const
  {
    return new AvlTree<T>(this);
  }

  AvlTree<T> &operator=(const AvlTree<T> &other)
  {
    // Avoid self assignment
    if (this != &other)
    {
      clear();
      root_ = AvlNode<T>::clone(other.root_);
      count_ = other.count_;
      max_key_ = other.max_key_;
      min_key_ = other.min_key_;
    }
    return *this;
  }

  /**
   * @brief check whether this tree is equal to the specified one using inorder traversal
   *
   * for example, the following balanced trees have the same inorder traversal:
   *
   *    2      1
   *   /        \
   *  1          2
   *
   * @param other tree to compare with
   * @return true if this tree is equivalent to the specified one
   * @return false if this tree is different from the specified one
   */
  bool operator==(const AvlTree<T> &other) const
  {
    if (!root_ || !other.root_)
    {
      return root_ == other.root_;
    }
    AvlNode<T> *this_node = root_->min_left();
    AvlNode<T> *other_node = other.root_->min_left();
    while (this_node && other_node && *this_node == *other_node)
    {
      this_node = this_node->next();
      other_node = other_node->next();
    }
    return !this_node && !other_node;
  }

  bool operator!=(const AvlTree<T> &other) const
  {
    return !(*this == other);
  }

  void clear()
  {
    AvlTree::clear(root_);
    root_ = NULL;
  }

  bool empty() const
  {
    return count() == 0;
  }

  int count() const
  {
    return count_;
  }

  int height() const
  {
    return root_ ? root_->height() : 0;
  }

  AvlNode<T> *insert(int key, const T &data = {})
  {
    bool inserted = false;
    AvlNode<T> *inserted_node;
    root_ = insert(NULL, root_, key, data, inserted, &inserted_node);
    if (inserted)
    {
      count_++;
      if (!max_key_ || max_key_ < inserted_node->key())
      {
        max_key_ = inserted_node->key();
      }
      if (!min_key_ || min_key_ > inserted_node->key())
      {
        min_key_ = inserted_node->key();
      }
    }
    return inserted_node;
  }

  AvlNode<T> *root() const
  {
    return root_;
  }

  AvlNode<T> *min_left() const
  {
    return root_ ? root_->min_left() : NULL;
  }

  AvlNode<T> *max_right() const
  {
    return root_ ? root_->max_right() : NULL;
  }

  int min_key() const
  {
    return min_key_;
  }

  int max_key() const
  {
    return max_key_;
  }

  bool remove(int key, T *removed_data = NULL)
  {
    bool removed = false;
    root_ = remove(root_, key, removed, removed_data);
    if (removed)
    {
      count_--;
      min_key_ = root_ ? root_->min_key() : 0;
      max_key_ = root_ ? root_->max_key() : 0;
    }
    return removed;
  }

  AvlNode<T> *lookup(int key) const
  {
    return AvlTree::lookup(root_, key);
  }

private:
  AvlNode<T> *root_ = NULL;
  int count_ = 0;
  int max_key_ = 0;
  int min_key_ = 0;

  static void clear(AvlNode<T> *node)
  {
    if (!node)
    {
      return;
    }
    AvlTree::clear(node->left_);
    AvlTree::clear(node->right_);
    delete node;
  }

  /**
   * @brief change sub-tree layout while keeping the order
   *
   *   parent          parent
   *     |               |
   *    node            left
   *    /  \            /  \
   *  left  N1   =>   N2  node
   *  /  \                /  \
   * N2 right          right  N1
   *
   * @param node branch root
   * @return AvlNode<T>* new branch root, node's left
   */
  static AvlNode<T> *rotate_right(AvlNode<T> *node)
  {
    AvlNode<T> *left = node->left_;
    AvlNode<T> *right = left->right_;

    node->left_ = right;

    if (right)
    {
      right->parent_ = node;
    }
    left->parent_ = node->parent_;

    left->right_ = node;
    node->parent_ = left;

    node->update_height();
    left->update_height();

    return left;
  }

  /**
   * @brief change sub-tree layout while keeping the order
   *
   *  parent            parent
   *    |                 |
   *   node             right
   *   /  \             /   \
   * N1   right  =>   node   N2
   *      /  \        /  \
   *   left   N2    N1   left

   * @param node branch root
   * @return AvlNode<T>* new branch root, node's right
   */
  static AvlNode<T> *rotate_left(AvlNode<T> *node)
  {
    AvlNode<T> *right = node->right_;
    AvlNode<T> *left = right->left_;

    node->right_ = left;

    if (left)
    {
      left->parent_ = node;
    }
    right->parent_ = node->parent_;

    right->left_ = node;
    node->parent_ = right;

    node->update_height();
    right->update_height();

    return right;
  }

  /**
   * @brief
   * @note The time required is O(log n) for lookup, plus a maximum of O(log n) retracing levels (O(1) on average) on the way back to the root,
   *  so the operation can be completed in O(log n) time.
   *
   * @param parent
   * @param node
   * @param key
   * @param data
   * @param inserted
   * @param inserted_node
   * @return AvlNode<T>*
   */
  AvlNode<T> *insert(AvlNode<T> *parent, AvlNode<T> *node, int key, const T &data, bool &inserted, AvlNode<T> **inserted_node = NULL)
  {
    if (!node)
    {
      node = new AvlNode<T>(key, data, parent);
      inserted = true;
      if (inserted_node)
      {
        *inserted_node = node;
      }
      return node;
    }
    else if (key < node->key_)
    {
      node->left_ = insert(node, node->left_, key, data, inserted, inserted_node);
    }
    else if (key > node->key_)
    {
      node->right_ = insert(node, node->right_, key, data, inserted, inserted_node);
    }
    else
    {
      if (inserted_node)
      {
        *inserted_node = node;
      }
      return node;
    }

    node->update_height();

    int balance = node->balance();

    if (balance > 1)
    {
      if (key > node->left_->key_)
      {
        node->left_ = rotate_left(node->left_);
      }
      node = rotate_right(node);
    }

    if (balance < -1)
    {
      if (key < node->right_->key_)
      {
        node->right_ = rotate_right(node->right_);
      }
      node = rotate_left(node);
    }

    return node;
  }

  /**
   * @brief
   * @note The time required is O(log n) for lookup, plus a maximum of O(log n) retracing levels (O(1) on average) on the way back to the root,
   *  so the operation can be completed in O(log n) time.
   *
   * @param node
   * @param key
   * @param removed
   * @param removed_data
   * @return AvlNode<T>*
   */
  AvlNode<T> *remove(AvlNode<T> *node, int key, bool &removed, T *removed_data = NULL)
  {
    if (!node)
    {
      return NULL;
    }

    if (key < node->key_)
    {
      node->left_ = remove(node->left_, key, removed, removed_data);
    }
    else if (key > node->key_)
    {
      node->right_ = remove(node->right_, key, removed, removed_data);
    }
    else
    {
      if (node->left_ && node->right_)
      {
        AvlNode<T> *alt = node->right_->min_left();
        if (removed_data)
        {
          *removed_data = node->data;
        }
        node->key_ = alt->key_;
        node->data = alt->data;
        node->right_ = remove(node->right_, alt->key_, removed, NULL);
      }
      else
      {
        AvlNode<T> *alt = node;

        if (removed_data)
        {
          *removed_data = node->data;
        }

        if (alt->left_)
        {
          alt = alt->left_;
        }
        else
        {
          alt = alt->right_;
        }

        if (alt)
        {
          *node = *alt;
        }
        else
        {
          alt = node;
          node = NULL;
        }

        delete alt;
      }

      removed = true;
    }
    if (!node)
    {
      return NULL;
    }

    node->update_height();

    int balance = node->balance();

    if (balance > 1)
    {
      if (node->left_->balance() < 0)
      {
        node->left_ = rotate_left(node->left_);
      }
      node = rotate_right(node);
    }

    if (balance < -1)
    {
      if (node->right_->balance() > 0)
      {
        node->right_ = rotate_right(node->right_);
      }
      node = rotate_left(node);
    }

    return node;
  }

  /**
   * @brief searching for a specific key
   * @note search is limited by the height h, unsuccessful search is very close to h, so both cases requires O(log n)
   *
   * @param node
   * @param key
   * @return AvlNode<T>*
   */
  static AvlNode<T> *
  lookup(AvlNode<T> *node, int key)
  {
    if (!node)
    {
      return NULL;
    }
    if (key < node->key_)
    {
      return AvlTree::lookup(node->left_, key);
    }
    if (key > node->key_)
    {
      return AvlTree::lookup(node->right_, key);
    }
    return node;
  }
};

#endif // _AVL__H
