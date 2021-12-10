#include<iostream>
#define SPACE 10

using namespace std;

class AVL {
  public:
    int value;
  AVL * left;
  AVL * right;

  AVL() {
    value = 0;
    left = NULL;
    right = NULL;
  }
  AVL(int v) {
    value = v;
    left = NULL;
    right = NULL;
  }
};

class AVLTree {
  public:
    AVL * root;
  AVLTree() {
    root = NULL;
  }
  bool isTreeEmpty() {
    if (root == NULL) {
      return true;
    } else {
      return false;
    }
  }
  // Get Height  
  int height(AVL * r) {
    if (r == NULL)
      return -1;
    else {
      /* compute the height of each subtree */
      int lheight = height(r -> left);
      int rheight = height(r -> right);

      /* use the larger one */
      if (lheight > rheight)
        return (lheight + 1);
      else return (rheight + 1);
    }
  }

  // Get Balance factor of node N  
  int getBalanceFactor(AVL * n) {
    if (n == NULL)
      return -1;
    return height(n -> left) - height(n -> right);
  }

  AVL * rightRotate(AVL * y) {
    AVL * x = y -> left;
    AVL * T2 = x -> right;

    // Perform rotation  
    x -> right = y;
    y -> left = T2;

    return x;
  }

  AVL * leftRotate(AVL * x) {
    AVL * y = x -> right;
    AVL * T2 = y -> left;

    // Perform rotation  
    y -> left = x;
    x -> right = T2;

    return y;
  }

  AVL * insert(AVL * r, AVL * new_node) {
    if (r == NULL) {
      r = new_node;
      cout << "Value inserted successfully" << endl;
      return r;
    }

    if (new_node -> value < r -> value) {
      r -> left = insert(r -> left, new_node);
    } else if (new_node -> value > r -> value) {
      r -> right = insert(r -> right, new_node);
    } else {
      cout << "No duplicate values allowed!" << endl;
      return r;
    }

    int bf = getBalanceFactor(r);
    // Left Left Case  
    if (bf > 1 && new_node -> value < r -> left -> value)
      return rightRotate(r);

    // Right Right Case  
    if (bf < -1 && new_node -> value > r -> right -> value)
      return leftRotate(r);

    // Left Right Case  
    if (bf > 1 && new_node -> value > r -> left -> value) {
      r -> left = leftRotate(r -> left);
      return rightRotate(r);
    }

    // Right Left Case  
    if (bf < -1 && new_node -> value < r -> right -> value) {
      r -> right = rightRotate(r -> right);
      return leftRotate(r);
    }

    /* return the (unchanged) node pointer */
    return r;

  }

  AVL * minValueNode(AVL * node) {
    AVL * current = node;
    /* loop down to find the leftmost leaf */
    while (current -> left != NULL) {
      current = current -> left;
    }
    return current;
  }

  AVL * deleteNode(AVL * r, int v) {
    // base case 
    if (r == NULL) {
      return NULL;
    }
    // If the key to be deleted is smaller than the root's key, 
    // then it lies in left subtree 
    else if (v < r -> value) {
      r -> left = deleteNode(r -> left, v);
    }
    // If the key to be deleted is greater than the root's key, 
    // then it lies in right subtree 
    else if (v > r -> value) {
      r -> right = deleteNode(r -> right, v);
    }
    // if key is same as root's key, then This is the node to be deleted 
    else {
      // node with only one child or no child 
      if (r -> left == NULL) {
        AVL * temp = r -> right;
        delete r;
        return temp;
      } else if (r -> right == NULL) {
        AVL * temp = r -> left;
        delete r;
        return temp;
      } else {
        // node with two children: Get the inorder successor (smallest 
        // in the right subtree) 
        AVL * temp = minValueNode(r -> right);
        // Copy the inorder successor's content to this node 
        r -> value = temp -> value;
        // Delete the inorder successor 
        r -> right = deleteNode(r -> right, temp -> value);
        //deleteNode(r->right, temp->value); 
      }
    }

    int bf = getBalanceFactor(r);
    // Left Left Imbalance/Case or Right rotation 
    if (bf == 2 && getBalanceFactor(r -> left) >= 0)
      return rightRotate(r);
    // Left Right Imbalance/Case or LR rotation 
    else if (bf == 2 && getBalanceFactor(r -> left) == -1) {
      r -> left = leftRotate(r -> left);
      return rightRotate(r);
    }
    // Right Right Imbalance/Case or Left rotation	
    else if (bf == -2 && getBalanceFactor(r -> right) <= -0)
      return leftRotate(r);
    // Right Left Imbalance/Case or RL rotation 
    else if (bf == -2 && getBalanceFactor(r -> right) == 1) {
      r -> right = rightRotate(r -> right);
      return leftRotate(r);
    }

    return r;
  }

  void print2D(AVL * r, int space) {
    if (r == NULL) 
      return;
    space += SPACE; 
    print2D(r -> right, space); 
    cout << endl;
    for (int i = SPACE; i < space; i++)  
      cout << " "; // 5.1  
    cout << r -> value << "\n";
    print2D(r -> left, space); 
  }
  void printPreorder(AVL * r)  
  {
    if (r == NULL)
      return;
    cout << r -> value << " ";
    printPreorder(r -> left);
    printPreorder(r -> right);
  }

  void printInorder(AVL * r) 
  {
    if (r == NULL)
      return;
    printInorder(r -> left);
        cout << r -> value << " ";
    printInorder(r -> right);
  }
  void printPostorder(AVL * r) 
  {
    if (r == NULL)
      return; 
    printPostorder(r -> left); 
    printPostorder(r -> right);
    cout << r -> value << " ";
  }

  /* Print nodes at a given level */
  void printGivenLevel(AVL * r, int level) {
    if (r == NULL)
      return;
    else if (level == 0)
      cout << r -> value << " ";
    else // level > 0  
    {
      printGivenLevel(r -> left, level - 1);
      printGivenLevel(r -> right, level - 1);
    }
  }
  void printLevelOrderBFS(AVL * r) {
    int h = height(r);
    for (int i = 0; i <= h; i++)
      printGivenLevel(r, i);
  }

  AVL * iterativeSearch(int v) {
    if (root == NULL) {
      return root;
    } else {
      AVL * temp = root;
      while (temp != NULL) {
        if (v == temp -> value) {
          return temp;
        } else if (v < temp -> value) {
          temp = temp -> left;
        } else {
          temp = temp -> right;
        }
      }
      return NULL;
    }
  }

  AVL * recursiveSearch(AVL * r, int val) {
    if (r == NULL || r -> value == val)
      return r;

    else if (val < r -> value)
      return recursiveSearch(r -> left, val);

    else
      return recursiveSearch(r -> right, val);
  }

};

int main() {
  AVLTree obj;
  int opt, val;

  do {
    cout << "What operation do you want to perform? " <<
      " Select Option number. Enter 0 to exit." << endl;
    cout << "1. Insert Node" << endl;
    cout << "2. Search Node" << endl;
    cout << "3. Delete Node" << endl;
    cout << "4. Print" << endl;
    cout << "5. Height of Tree" << endl;
    cout << "6. Clear Screen" << endl;
    cout << "0. Exit Program" << endl;

    cin >> opt;
    //Node n1;
    AVL * new_node = new AVL();

    switch (opt) {
    case 0:
      break;
    case 1:
      cout << "AVL INSERT" << endl;
      cout << "Enter VALUE of TREE NODE to INSERT in AVL Tree: ";
      cin >> val;
      new_node -> value = val;
      obj.root = obj.insert(obj.root, new_node);
      cout << endl;
      break;
    case 2:
      cout << "SEARCH" << endl;
      cout << "Enter VALUE of TREE NODE to SEARCH in AVL Tree: ";
      cin >> val;
      new_node = obj.recursiveSearch(obj.root, val);
      if (new_node != NULL) {
        cout << "Value found" << endl;
      } else {
        cout << "Value NOT found" << endl;
      }
      break;
    case 3:
      cout << "DELETE" << endl;
      cout << "Enter VALUE of TREE NODE to DELETE in AVL: ";
      cin >> val;
      new_node = obj.recursiveSearch(obj.root, val);
      if (new_node != NULL) {
        obj.root = obj.deleteNode(obj.root, val);
        cout << "Value Deleted" << endl;
      } else {
        cout << "Value NOT found" << endl;
      }
      break;
    case 4:
      cout << "PRINT 2D: " << endl;
      obj.print2D(obj.root, 5);
      cout << endl;
     	      cout <<"PRE-ORDER: ";
      //	      obj.printPreorder(obj.root);
      //	      cout<<endl;
      //	      cout <<"IN-ORDER: ";
      //	      obj.printInorder(obj.root);
      //	      cout<<endl;
      //	      cout <<"POST-ORDER: ";
      //	      obj.printPostorder(obj.root);
      break;
    case 5:
      cout << "TREE HEIGHT" << endl;
      cout << "Height : " << obj.height(obj.root) << endl;
      break;
    case 6:
      system("cls");
      break;
    default:
      cout << "Enter Proper Option number " << endl;
    }

  } while (opt != 0);

  return 0;
}
