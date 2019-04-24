#include <iostream>
#include <vector>
#include <deque>
using namespace std;

//Definition for binary tree
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin) {
		if (pre.size() == 0 || vin.size() == 0)
			return NULL;
		vector<int>::iterator preStartIter = pre.begin();
		vector<int>::iterator preEndIter = pre.end() - 1;
		vector<int>::iterator vinStartIter = vin.begin();
		vector<int>::iterator vinEndIter = vin.end() - 1;
		return constructCore(preStartIter, preEndIter, vinStartIter, vinEndIter);
	}

private:
	TreeNode* constructCore(vector<int>::iterator preStartIter,
		vector<int>::iterator preEndIter, vector<int>::iterator vinStartIter, vector<int>::iterator vinEndIter) {
		int rootValue = *preStartIter;
		TreeNode* root = new TreeNode(rootValue);
		//���ֻ��һ�����ڵ㣬��ô���ظ��ڵ�
		if (preStartIter == preEndIter)
		{
			if (vinStartIter == vinEndIter && *preStartIter == *vinStartIter)
			{
				return root;
			}
			else
			{
				throw std::exception("invalid input!");
			}
		}

		//��������������ȥ���Ҹ��ڵ�ֵ���ҵ����������ָ��λ��
		vector<int>::iterator rootInVin = vinStartIter;
		while (rootInVin != vinEndIter && *rootInVin != rootValue)
		{
			++rootInVin;
		}
		//���������ĳ���
		int leftLength = rootInVin - vinStartIter;
		vector<int>::iterator preLeftEnd = preStartIter + leftLength;
		if (leftLength > 0)
		{
			//����������
			root->left = constructCore(preStartIter + 1, preLeftEnd, vinStartIter, rootInVin - 1);
		}
		if (leftLength < preEndIter - preStartIter) //�����������������ݹ鴴��������
		{
			//����������
			root->right = constructCore(preLeftEnd + 1, preEndIter, rootInVin + 1, vinEndIter);
		}
		return root;
	}
};

//ǰ�����������:��--��--��
void preScanf(TreeNode * t)
{
	if (t == NULL)
	{
		return;
	}
	cout << t->val << " ";
	preScanf(t->left);
	preScanf(t->right);
}
//�����������������---��---��
void middleScanf(TreeNode * t)
{
	if (t == NULL)
	{
		return;
	}
	middleScanf(t->left);
	cout << t->val << " ";
	middleScanf(t->right);
}
//�����������������---��---��
void backScanf(TreeNode * t)
{
	if (t == NULL)
	{
		return;
	}
	backScanf(t->left);
	backScanf(t->right);
	cout << t->val << " ";
}
//������������������ϵ��£�������
void fromTopToBottomScanf(TreeNode * t)
{
	if (t == NULL)
	{
		return;
	}
	deque<TreeNode*> dequeTreeNode;
	dequeTreeNode.push_back(t);

	while (dequeTreeNode.size())
	{
		TreeNode* pNode = dequeTreeNode.front(); //����ȡ�������е�ͷ��Ԫ�ؽ��д�ӡ
		dequeTreeNode.pop_front(); //

		cout << pNode->val << " ";
		if (pNode->left)
		{
			dequeTreeNode.push_back(pNode->left);
		}
		if (pNode->right)
		{
			dequeTreeNode.push_back(pNode->right);
		}
	}
}

int main()
{
	Solution s;
	vector<int> pre = { 1, 2, 4, 7, 3, 5, 6, 8 };
	vector<int> vin = { 4, 7, 2, 1, 5, 3, 8, 6 };
	TreeNode* t;
	t = s.reConstructBinaryTree(pre, vin);
	cout << "ǰ���������������Ϊ��" << endl;
	preScanf(t);
	cout << endl << "�����������������Ϊ��" << endl;
	middleScanf(t);
	cout << endl << "�����������������Ϊ��" << endl;
	backScanf(t);
	cout << endl << "�����������������Ϊ��" << endl;
	fromTopToBottomScanf(t);
	cout << endl;
	return 0;
}