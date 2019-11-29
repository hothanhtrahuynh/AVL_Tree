#ifndef _NODE_H_
#define _NODE_H_
#include<iostream>
#include<vector>

using namespace std;

template<class T>
class Node
{
public:

	T value;
	Node* left, * right;
	int height;
	Node() {
		left = right = NULL;
	}
	~Node();
};

#endif



template<class Node, class T>
Node* createNode( T key)
{
	Node* p = new Node;
	p->value = key;
	p->left = p->right = NULL;
	p->height = 1;
	return p;
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

template<class Node>
int height(Node* p)
{
	if (p != NULL)
		return p->height;
	else return 0;
}
 
template<class Node>
int getBalance(Node* node)
{
	if (node == NULL) return 0;
	return (height(node->left) - height(node->right));
}

template<class Node>
Node* rightRotate(Node*& y)
{

	Node* x = y->left;
	Node* T2 = x->right;
	
	//Hoán đổi vị trí của x và y
	x->right = y;
	y->left = T2;

	//thay đổi chiều cao tại các nút được đổi
	x->height = 1 + max(height(x->left), height(x->right));
	y->height = 1 + max(height(y->left), height(y->right));
	return x;
}

template<class Node>
Node* leftRotae(Node*& y)
{

	Node* x = y->right;
	Node* T3 = x->left;

	x->left = y;
	y->right = T3;

	x->height = 1 + max(height(x->left), height(x->right));
	y->height = 1 + max(height(y->left), height(y->right));
	return x;
}

template<class Node, class T>
void insertNode(Node*& root, T key)
{
	Node* p = createNode<Node, T>(key);
	if (root == NULL)
	{
		root = p; return;
	}
	if (key < root->value)
	{
		insertNode(root->left, key);
	}
	else/* if (key > root->value)*/
	{
		insertNode(root->right, key);
	}
	
	root->height = 1 + max(height(root->right), height(root->left));

	int balance = getBalance(root);

	//Nếu cây không cân bằng thì tiến hành xét 4 trường hợp không cân bằng sau

	//TH1 : Left Left Case
	if (balance > 1 && key < root->left->value)
	{
		 root=rightRotate(root);
	}

	//TH2: Left Right Case
	if (balance > 1 && key > root->left->value)
	{
		root->left=leftRotae(root->left);
		root= rightRotate(root);
	}

	//TH3: Right Right Case

	if (balance<-1 && key>root->right->value)
	{
		 root=leftRotae(root);
	}

	//TH4: Right Left Case
	if (balance < -1 && key < root->right->value)
	{
		root->right=rightRotate(root->right);
		root=leftRotae(root);
	}
}

template<class Node>
Node* minValueNode(Node* root)
{
	Node cur = root;
	while (cur->left!=NULL)
	{
		cur = cur->left;
	}
	return cur;
}

template<class Node, class T>
void deleteNode(Node*& root, T value)
{
	//Thực hiện xóa như ở BST
	if (root == NULL) return;
	if (value < root->value)
	{
		deleteNode(root->left, value);
	}
	else if (value>root->value)
		{
			deleteNode(root->right, value);
		}
	else
	{
		if (root->left == NULL)
		{
			root = root->right;
		}
		else if (root->right == NULL)
		{
			root = root->left;
		}
		else
		{
			Node* temp = minValueNode(root->right);
			*root = *temp;
			deleteNode(root->right, value);
		}
	}

	if (root == NULL) return;
	//cập nhật lại chiều cao
	root->height = 1 + max(height(root->left), height(root->right));

	int balance = getBalance(root);

	//Left left case
	if (balance > 1 && getBalance(root->left) >= 0)
	{
		root=rightRotate(root);
	}

	//Left Right Case

	if (balance < -1 && getBalance(root->left) < 0)
	{
		root->left=leftRotae(root->left);
		root=rightRotate(root);
	}

	//Right Right Case
	if (balance < -1 && getBalance(root->right) <= 0)
	{
		root=leftRotae(root);
	}

	//Right Left Case
	if (balance < 1 && getBalance(root->right) > 0)
	{
		root->right=rightRotate(root->right);
		root=leftRotae(root);
	}
}

template<class Node>
void LNR(Node* root)
{
	if (root != NULL)
	{
		LNR(root->left);
		cout << root->value << " - "<<root<<" ";
		LNR(root->right);
	}
}
template<class T>
bool checkNT(T value)
{
	if (value < 2) return false;
	if (value == 2) return true;

	for (int i = 2; i < sqrt(value); i++)
	{
		if (value % i == 0) return false;
	}
	return true;
}

template <class Node, class T>
Node* searchNode(Node* root, T value)
{
	if (root == NULL || root->value == value)
	{
		return root;
	}
	if (value < root->value)
	{
		return searchNode(root->left,value);
	}
	else return searchNode(root->right,value);
}

template<class Node, class T>
void printNodeValue(Node* root, T value)
{
	if (root != NULL)
	{
		if (root->value = value)
		{
			cout << root->value << " - " << root;
		}
		else if (value < root->value) {
			printNodeValue(root->left, value);
		}
		else printNodeValue(root->right, value);
	}
}


//hàm tìm tất cả các các nút với giá trị được truyền vào
template<class Node, class T>
void searchNode_Value(Node* root, T value, vector <Node*>& dsNodekq)
{
	if (root != NULL)
	{
		if (root->value == value)
		{
			dsNodekq.push_back(root);
			
		}
	
		searchNode_Value(root->left, value,dsNodekq);

		searchNode_Value(root->right, value,dsNodekq);
	}
}

//tìm ra cực trị của cây.
template<class Node>
void searchMaxMin(Node* root)
{
	if (root == nullptr) return;
	vector<Node*> q;
	q.push_back(root);
	Node* temp = q.front();
	while (!q.empty())
	{
		if (temp->right != NULL&&temp->value < temp->right->value )
		{
			q.clear();
			q.push_back(temp->right);
		}
		else if (temp->right != NULL&&temp->value == temp->right->value )
		{
			q.push_back(temp->right);
		}
		if (temp->right == NULL)
		{
			temp = temp->left;
		}
		else temp = temp->right;
		if (temp == NULL) break;
	}
	for (int i = 0; i < q.size(); i++)
	{
		
		cout << q[i]->value << " - " <<q[i] << " ";
	}
	cout << " la nhung phan tu lon nhat." << endl;
	vector<Node*> min;
	min.push_back(root);
	Node* temp1 = min.front();
	while (!min.empty())
	{
		if (temp1->left != NULL && temp1->value > temp1->left->value)
		{
			min.clear();
			min.push_back(temp1->left);
		}
		else if (temp1->right != NULL && temp1->value == temp1->right->value)
		{
			min.push_back(temp1->right);
		}
		if (temp1->left == NULL)
		{
			temp1 = temp1->right;
		}
		else temp1 = temp1->left;
		if (temp1 == NULL) break;
	}
	for (int i = 0; i < min.size(); i++)
	{

		cout << min[i]->value << " - " << min[i] << " ";
	}
	cout << " la nhung phan tu nho nhat." << endl;
}


//tìm các nút có giá trị là số nguyên tố
template<class Node>
void searchNode_NguyenTo(Node* root, vector <Node*>& dsNodekq)
{
	if (root != NULL)
	{
		if (checkNT(root->value ))
		{
			dsNodekq.push_back(root);

		}

		searchNode_NguyenTo(root->left, dsNodekq);

		searchNode_NguyenTo(root->right, dsNodekq);
	}
}

//tìm nút có đủ lá
template<class Node>
void searchNode_DuLa(Node* root, vector <Node*>& dsNodekq)
{
	if (root != NULL)
	{
		if (root->left!=NULL&&root->right!=NULL)
		{
			dsNodekq.push_back(root);

		}
		searchNode_DuLa(root->left, dsNodekq);

		searchNode_DuLa(root->right, dsNodekq);
	}
	
}

//tìm nút không có đủ lá
template<class Node>
void searchNode_KhongDuLa(Node* root, vector <Node*>& dsNodekq)
{
	if (root != NULL)
	{
		if ((root->left == NULL && root->right != NULL)|| (root->left != NULL && root->right == NULL))
		{
			dsNodekq.push_back(root);

		}
		searchNode_KhongDuLa(root->left, dsNodekq);

		searchNode_KhongDuLa(root->right, dsNodekq);
	}

}
//tìm nút không có lá
template<class Node>
void searchNode_KhongCoLa(Node* root, vector <Node*>& dsNodekq)
{
	if (root != NULL)
	{
		if(root->left==NULL&&root->right==NULL)
		{
			dsNodekq.push_back(root);

		}
		searchNode_KhongCoLa(root->left, dsNodekq);

		searchNode_KhongCoLa(root->right, dsNodekq);
	}

}


//hàm in danh sách các nút tìm được
template<class Node>
void printVector(vector<Node*> dsNodekq)
{
	int i = 0;
	while (i<dsNodekq.size())
	{
		cout << dsNodekq[i]->value << " - " << dsNodekq[i] << endl;
		i++;
	}
}
int printMenu()
{
	int lenh;
	cout << "1. In cay" << endl;
	cout << "2. Tim cac nut trong cay voi gia tri duoc nhap vao: " << endl;
	cout << "3. Tim cuc tri." << endl;
	cout << "4. Tim so nguyen to." << endl;
	cout << "5. Tim nut co du la" << endl;
	cout << "6. Tim nut khong co du la" << endl;
	cout << "7. Tim nut khong co du la." << endl;
	cout << "0. Thoat." << endl;
	cout << "Ban chon lenh: ";
	cin >> lenh;
	return lenh;
}