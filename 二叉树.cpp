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
		//如果只有一个根节点，那么返回根节点
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

		//在中序遍历结果中去查找根节点值，找到左右子树分割点位置
		vector<int>::iterator rootInVin = vinStartIter;
		while (rootInVin != vinEndIter && *rootInVin != rootValue)
		{
			++rootInVin;
		}
		//求左子树的长度
		int leftLength = rootInVin - vinStartIter;
		vector<int>::iterator preLeftEnd = preStartIter + leftLength;
		if (leftLength > 0)
		{
			//构建左子树
			root->left = constructCore(preStartIter + 1, preLeftEnd, vinStartIter, rootInVin - 1);
		}
		if (leftLength < preEndIter - preStartIter) //如果存在右子树，则递归创建右子树
		{
			//构建右子树
			root->right = constructCore(preLeftEnd + 1, preEndIter, rootInVin + 1, vinEndIter);
		}
		return root;
	}
};

//前序遍历二叉树:根--左--右
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
//中序遍历二叉树：左---根---右
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
//后序遍历二叉树：左---右---根
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
//层序遍历二叉树：从上到下，从左到右
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
		TreeNode* pNode = dequeTreeNode.front(); //依次取出队列中的头部元素进行打印
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
	cout << "前序遍历二叉树序列为：" << endl;
	preScanf(t);
	cout << endl << "中序遍历二叉树序列为：" << endl;
	middleScanf(t);
	cout << endl << "后序遍历二叉树序列为：" << endl;
	backScanf(t);
	cout << endl << "后序遍历二叉树序列为：" << endl;
	fromTopToBottomScanf(t);
	cout << endl;
	return 0;
}