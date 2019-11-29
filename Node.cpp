#include "Node.h"
int main()
{
	int a[] = { 10, 6, 15, 13, 14, 9, 7, 3, 17, 10, 9, 3, 1, 10, 7, 8 };
	int n = sizeof(a) / sizeof(a[0]);

	Node<int>* root = NULL;
	for (int i = 0; i < n; i++)
	{
		insertNode(root, a[i]);
	}
	int lenh;
	do
	{
		lenh = printMenu();
		switch (lenh)
		{
		case 1://in ra giá trị và địa chỉ của các nút trong cây.
		{
			LNR(root);
			cout << endl;
		}break;
		case 2://tìm tất cả các nút có giá trị bằng với giá trị nhập vào
		{
			int key;
			cout << "Nhap vao gia tri can tim: ";
			cin >> key;
			vector<Node<int>*> dsKq;
			searchNode_Value(root, key, dsKq);
			printVector(dsKq);
		}break;
		case 3://tìm cực trị
		{
			searchMaxMin(root);
		}break;
		case 4://Tim so nguyen to
		{
			vector<Node<int>*> ds;
			searchNode_NguyenTo(root, ds);
			printVector(ds);
		}break;
		case 5://Tim nut co du la
		{
			vector<Node<int>*> ds;
			searchNode_DuLa(root, ds);
			printVector(ds);
		}break;
		case 6://Tim nut khong co du la
		{
			vector<Node<int>*> ds;
			searchNode_KhongDuLa(root, ds);
			printVector(ds);
		}break;
		case 7://Tim nut khong co la
		{
			vector<Node<int>*> ds;
			searchNode_KhongCoLa(root, ds);
			printVector(ds);
		}break;
		default:
			lenh = 3;
			break;
		}
	} while (lenh!=3);

}