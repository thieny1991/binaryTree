
#include<iostream>
#include<string>
#include<stack>
using namespace std;

class node {
public:
	int data;
	node *left;
	node *right;
	node() {
		left = nullptr;
		right = nullptr;
		data = 0;
	}
	node(int key) {
		left = nullptr;
		right = nullptr;
		data = key;
	}
};

class binaryTree {

private:
	node *root;
	
public:
	binaryTree() {
		root = nullptr;
	}
	bool isEmpty() {
		return (root == 0);
	}

	bool search(int key) {
		node *current;
		bool found = false;
		if (root == 0)
			cout << "Tree is empty" << endl;
		else {
			current = root;
			while (current != nullptr && !found) {
				if (current->data == key) found = true;
				else if (current->data > key)
					current = current->right;
				else
					current = current->left;
			}
		}

		return found;
	}
	bool searchRecursive(int key) {
		node *current = root;
		searchRecursive(current, key);
	}
	
	bool searchRecursive(node *cu, int key) {
		if (cu == 0) return 0;
		else if (cu->data == key) return true;
		else if (key > cu->data) {
			searchRecursive(cu->right, key);
		}
		else
			searchRecursive(cu->left, key);
	}

	 node* add(int key, node *&cu) {
		if (cu == 0) {
			cu = new node(key);// return new node(key)
			return cu;
		}
		else if (key > cu->data)
			cu->right=add(key, cu->right);
		else if(key<cu->data)
			cu->left= add(key, cu->left);
		return cu;
	}
	void add(int key) {
		add(key, root);
	}

	void printInOrder() {
		inOrder(root);
	}
	void printPreOrder() { 
		preOrder(root);
	}

	void preOrder(node *cu) {
		if (cu == 0) return;
		else {
			cout << cu->data << " ";
			preOrder(cu->left);
			preOrder(cu->right);
		}
	}

	void inOrder(node *cu) {
		if (cu == 0) return;
		else {
			inOrder(cu->left);
			cout << cu->data << " ";
			inOrder(cu->right);
		}
	}
	int getHeight() {
		return height(root);
	}
	int height(node *cu) {
		if (cu == 0) return 0;
		else if (cu->left == 0 && cu->right == 0) return 1;
		else {
			return 1 + max(height(cu->left),height(cu->right));
		}
	}
	int max(int x,int  y) {
		if (x > y) return x;
		else return y;
	}
	node* getMinNode() {
		return minNode(root);
	}
	node* minNode(node *cu) {
		if (cu->left == 0) return cu;
		else {
			return minNode(cu->left);
		}
	}
	int getMax() {
		return max(root);
	}
	int max(node *cu) {
		if (cu->right == 0)return cu->data;
		else
			return max(cu->right);
	}
	int countNode() {
		return countNode(root);
	}
	int countNode(node * cu) {
		if (cu == 0)return 0;
		else if (cu->left == 0 && cu->right == 0) return 1;
		else return 1 + countNode(cu->left) + countNode(cu->right);
	}
	int countLeaf() {
		return countLeaf(root);
	}
	int countLeaf(node *cu) {
		if (cu == 0)return 0;
		else if (cu->left == 0 && cu->right == 0) return 1;
		else return countNode(cu->left) + countNode(cu->right);
	}
	void deleteNode(int key) {
		deleteNode(root, key);
	}
	node* deleteNode(node* root, int key) {
		if (root == nullptr) return root;
		if (key < root->data)
			root->left = deleteNode(root->left, key);
		else if (key > root->data)
			root->right = deleteNode(root->right, key);
		else {//key is found
			//node with only one child
			if (root->left == 0) {
				node * temp = root->right;
				free(root);
				return temp;
			}
			else if (root->right == 0) {
				node *temp = root->left;
				free(root);
				return temp;
			}
			//node with two child, get inorder succcesor smallest in the right subtree
			node *temp = minNode(root->right);
			root->data = temp->data;
			root->right = deleteNode(root->right, temp->data);
		}//end else
		return root;
	}

	void inOrderStack() {
		node *cu = root;
		stack<node*> s;
		while (cu != 0 || !s.empty()) {
			if (cu != 0) {
				s.push(cu);
				cu = cu->left;
			}
			else {
				cu = s.top();
				cout << cu->data;
				s.pop();
				cu = cu->right;
			}
		}
		cout << endl;
	}

	void preOrderStack() {
		node *cu = root;
		stack<node*> s;

		while (cu != 0 || !s.empty()) {
			if (cu != 0) {
				cout << cu->data;
				s.push(cu);
				cu = cu->left;
			}
			else {
				cu = s.top();
				s.pop();
				cu = cu->right;
			}
		}
	}

	/*void printLevel(int L) {
		if (root == 0 || L<0) return;
		else if (root != 0 && L == 0) {
			cout << root->data;
			return;
		}
		printLevel(root, L, 0);
	}
	void printLevel(node *cu, int L, int l) {
		if (cu == 0) return;
		if (l == L)
		{
			cout << cu->data << " ";
		}
		else
		{
			printLevel(cu->left, L, l+1);
			printLevel(cu->right, L, l+1);
		}
	}*/
	void printAllLevel() {
		printAllLevel(root);
	}
	void printAllLevel(node *cu) {
		int h = height(root);
		for (int i = 0;i <h;i++) {
			printGivenLevel(i);
			cout << endl;
		}

	}
	void printGivenLevel(int L) {
		printGivenLevel(root, L);
	}
	void printGivenLevel(node * root, int L) {
		if (root == 0) return ;
		if (L == 0) cout << root->data << " ";
		else if (L > 0) {
			printGivenLevel(root->left, L - 1);
			printGivenLevel(root->right, L - 1);
		}
	}


};

int main() {

	int a[8] = { 13,10,15,5,11,16,4,6 };

	binaryTree tree;
	for (int i = 0; i <8;i++)
		tree.add(a[i]);
	
	tree.printInOrder();
	cout << endl;
	tree.printPreOrder();
	cout << tree.getHeight();
	cout << endl;
	node * min = tree.getMinNode();
	cout << "min= " << min->data << endl;
	cout << "max =" << tree.getMax() << endl;
	cout << " count node =" << tree.countNode() << endl;
	cout << " count leave =" << tree.countLeaf() << endl;
	//tree.deleteNode(12);
	tree.printInOrder();
	cout << endl;
	//tree.printGivenLevel(2);
	tree.printAllLevel();
	system("PAUSE");
	return  0;
}