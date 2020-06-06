#include <iostream>


using namespace std;

//==================================================================================================================================
//														1 ������� �������� ��������� ������� ����������������� ������ ��������� �������� � �������
//==================================================================================================================================
template< typename T>
size_t FindInArr(T* arr, size_t size, T& f  ) {

	for (size_t i = 0; i < size; ++i) {
		if (arr[i] == f) return i;
	}
	return -1;
}

//==================================================================================================================================
//														2 ������� �������� ��������� ������� ��������� ������ ��������� �������� � �������
//==================================================================================================================================
template< typename T>
size_t SearchBinary(T* arr, size_t left,size_t right, T& f) {
	size_t middle = 0;
	while (1) {
		middle = (left + right) / 2;
		if (f < arr[middle])right = middle - 1;
		else {
			if (f > arr[middle]) left = middle + 1;
			else return middle;
		}
		if (left > right) return -1;
	}
}

//==================================================================================================================================
//														3 ������� �������� ��������� ������� ����������������� ������ ��������� �������� � �������
//==================================================================================================================================
template< typename T>
size_t InterpolarFind(T* arr, size_t size, T& f) {
	size_t i_min = 0, i_max = size - 1;
	while (i_min <= i_max) {
		T min = arr[i_min], max = arr[i_max];
		size_t k = ((f - min) * (i_max - i_min)) / (max - min) + i_min;
		if (arr[k] > f) i_max = k - 1;
		else {
			if (arr[k] < f) i_min = k + 1;
			else return k;
		}
	}
	return -1;
}

//==================================================================================================================================
//								4 ������� ��������  �������  ������  ����� �������  �����������  ������������������ ����� � �������
//==================================================================================================================================
template< typename T>
void searchForTheLongestNonDecreasingSequence(T* arr, size_t size, size_t& begin, size_t& end) {
	begin = 0;
	end = 0;
	size_t tmpbeg = 0, tmpend = 0;
	for (size_t i = 1; i < size; ++i) {
		if (arr[i-1] <= arr[i ]) {
			++tmpend;
		}
		else {
			if ((end - begin) < (tmpend - tmpbeg)) {
				begin = tmpbeg;
				end = tmpend;
			}
		}
		tmpbeg = tmpend = i;
	}
}

//==================================================================================================================================
//								5 ������� �������� �������, ������������ ������ ��������� ������.
//==================================================================================================================================
//������ ������
struct Node {
	Node* l, * r;
	char  x;
};
int Node_Height(const Node* p) {
	int l, r, h = 0;
	if (p != NULL) {
		l = Node_Height(p->l);
		r = Node_Height(p->r);
		h = ((l > r) ? l : r) + 1;
	}
	return h;
}

//==================================================================================================================================
//								6 ������� ��������  �������,  ������������  �������  ��������������  ����  ����� ��������� ������.( � ������ �����)
//==================================================================================================================================
void AvgTreeRecorse(Node* root, double& sum, int& count) {
	if (root == nullptr) return;
	sum = sum + root->x;
	count++;
	AvgTreeRecorse(root->l, sum,  count);
	AvgTreeRecorse(root->r,  sum,  count);
}
double AvgTree(Node* root) {
	double sum = 0;
	int count = 0;
	AvgTreeRecorse(root, sum, count);
	if (count > 0) sum = sum / count;
	return sum;
}

//==================================================================================================================================
//								7 ������� �������  ���������  �����  ���  ������  �  ��������������  �������  (������� ������). ������ ���� ������ ������ ��������� ���� �������������� ���� ��������� ������������� ����. ���������� ����������� �� ���������, ����������, ������� ���������� ����� ����, ������ �������� �� ����� � �������� ���� � �������� ������.(���� ��� ������ � ���������� �����������)
//==================================================================================================================================
template< typename T>
struct TempData {
	int _key;
	T  _val;
};
template< typename T>
struct TempNode {
	TempData<T>* _data;
	TempNode<T> _l, _r;
	TempNode(TempData<T>& data) :_data(data), _l(nullptr), _r(nullptr) {}
};
template< typename T>
class Tree {
	TempNode<T>* _root;
	TempNode<T>* Findmin(TempNode<T>* p) // ����� ���� � ����������� ������ � ������ p 
	{
		return p->_l ? Findmin(p->_lt) : p;
	}
	TempNode<T>* Removemin(TempNode<T>* p) // �������� ���� � ����������� ������ �� ������ p
	{
		if (p->_l == 0)
			return p->_right;
		p->_l = Removemin(p->_l);
		return Balance(p);
	}
	TempNode<T>* Balance(TempNode<T>* p) // ������������ ���� p
	{
		UpdateHeight(p);
		if (GetBalance(p) == 2)
		{
			if (GetBalance(p->_right) < 0)
				p->_right = RotateRight(p->_right);
			return RotateLeft(p);
		}
		if (GetBalance(p) == -2)
		{
			if (GetBalance(p->_left) > 0)
				p->_left = RotateLeft(p->_left);
			return RotateRight(p);
		}
		return p; // ������������ �� �����
	}
public:
	Tree() :_root(nullptr){}
	void DisposeTree(TempNode<T>* root) {
		if (root == nullptr) return;
		DisposeTree(root->_l);
		DisposeTree(root->_r);
		delete root;
		root = nullptr;
	}
	~Tree() {
		DisposeTree(_root);
	}
	TempNode<T>* Insert(TempData<T>& data, TempNode<T>* root=_root) {
		if (!root) return new TempNode<T>(data);
		if (data._key < root->_data._key)
			root->_l = Insert(data, root->_l);
		else {
			if (data._key > root->_data._key) {
				root->_r = Insert(data, root->_r);
			}
		}
		return root;
	}
	TempNode<T>* Remove(int key, TempNode<T>* root = _root) // �������� ����� k �� ������ p
	{
		if (!root) return 0;
		if (key < root->_data->_key)
			root->_l = Remove(key, root->_l);
		else if (key > root->_data->_key)
			root->_r = Remove(key, root->_r);
		else //  k == p->key 
		{
			TempNode<T>* q = root->_l;
			TempNode<T>* r = root->_r;
			delete root;
			if (!r) return q;
			TempNode<T>* min = findmin(r);
			min->_r = removemin(r);
			min->_l = q;
			return Balance(min);
		}
		return Balance(root);
	}
	
};

//==================================================================================================================================
//								8 ������� ����������� ��������� ����� ��� �������� ��� �������������� ���� ��������� �������������  ���� (�� ���)
//==================================================================================================================================

//==================================================================================================================================
//								9 ������� ����������� ��������� ����� ��� �������� ��� �������������� ���� ��������� �������������  ����.  �����  ������������  �  ��������������    ���-������  � �������������������  �������  ��������  ���������. (�� HashTable)
//==================================================================================================================================

//==================================================================================================================================
//								10 ����������� ������� ������� �������� ���-������� ���  ���������� �������� �����. (�� HashTable)
//==================================================================================================================================


//==================================================================================================================================
//								17 ����������� ��������� ����� ��� �������� �����, ��� ������ ������� �������� �������������  ����  �  ��������  �������������  ����. (�� ���)
//==================================================================================================================================


int main() {



}