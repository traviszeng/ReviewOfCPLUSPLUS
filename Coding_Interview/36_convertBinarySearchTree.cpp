#include"BinaryTree.h"
#include<iostream>
using namespace std;



void ConvertNode(BinaryTreeNode* root, BinaryTreeNode** plast) {
	if (root == nullptr) {
		return;
	}
	BinaryTreeNode * pCurrent = root;
	if (pCurrent->m_pLeft != nullptr) {
		ConvertNode(pCurrent->m_pLeft, plast);
	}

	if (pCurrent->m_pRight != nullptr)
		ConvertNode(pCurrent->m_pRight, plast);

	
	pCurrent->m_pLeft = *plast;
	if (*plast != nullptr)
		(*plast)->m_pRight = pCurrent;
	*plast = pCurrent;

}



//将二叉树按照后序遍历转成双向链表
BinaryTreeNode* Convert(BinaryTreeNode* root) {
	if (root == nullptr) {
		return nullptr;
	}
	BinaryTreeNode* lastNode = nullptr;
	ConvertNode(root, &lastNode);

	BinaryTreeNode *pCurrent = lastNode;
	pCurrent->m_pRight = nullptr;
	while (pCurrent!=nullptr&&pCurrent->m_pLeft != nullptr)
		pCurrent = pCurrent->m_pLeft;

	return pCurrent;

}


BinaryTreeNode* Convert1(BinaryTreeNode* pRootOfTree)
{
	BinaryTreeNode *pLastNodeInList = nullptr;
	ConvertNode1(pRootOfTree, &pLastNodeInList);

	BinaryTreeNode *pHead = pLastNodeInList;
	while (pHead != nullptr && pHead->m_pLeft != nullptr)
		pHead = pHead->m_pLeft;
	return pHead;
}

//按照中序遍历的方式
void ConvertNode1(BinaryTreeNode* pNode, BinaryTreeNode** pLastNodeInList)
{
	if (pNode == nullptr)
		return;

	BinaryTreeNode *pCurrent = pNode;

	if (pCurrent->m_pLeft != nullptr)
		ConvertNode1(pCurrent->m_pLeft, pLastNodeInList);

	pCurrent->m_pLeft = *pLastNodeInList;
	if (*pLastNodeInList != nullptr)
		(*pLastNodeInList)->m_pRight = pCurrent;

	*pLastNodeInList = pCurrent;

	if (pCurrent->m_pRight != nullptr)
		ConvertNode1(pCurrent->m_pRight, pLastNodeInList);
}


// ====================测试代码====================
void PrintDoubleLinkedList(BinaryTreeNode* pHeadOfList)
{
	BinaryTreeNode* pNode = pHeadOfList;

	printf("The nodes from left to right are:\n");
	while (pNode != nullptr)
	{
		printf("%d\t", pNode->m_nValue);

		if (pNode->m_pRight == nullptr)
			break;
		pNode = pNode->m_pRight;
	}

	printf("\nThe nodes from right to left are:\n");
	while (pNode != nullptr)
	{
		printf("%d\t", pNode->m_nValue);

		if (pNode->m_pLeft == nullptr)
			break;
		pNode = pNode->m_pLeft;
	}

	printf("\n");
}

void DestroyList(BinaryTreeNode* pHeadOfList)
{
	BinaryTreeNode* pNode = pHeadOfList;
	while (pNode != nullptr)
	{
		BinaryTreeNode* pNext = pNode->m_pRight;

		delete pNode;
		pNode = pNext;
	}
}

void Test(const char* testName, BinaryTreeNode* pRootOfTree)
{
	if (testName != nullptr)
		printf("%s begins:\n", testName);

	PrintTree(pRootOfTree);

	BinaryTreeNode* pHeadOfList = Convert(pRootOfTree);

	PrintDoubleLinkedList(pHeadOfList);
}

//            10
//         /      \
//        6        14
//       /\        /\
//      4  8     12  16
void Test1()
{
	BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode14 = CreateBinaryTreeNode(14);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNode12 = CreateBinaryTreeNode(12);
	BinaryTreeNode* pNode16 = CreateBinaryTreeNode(16);

	ConnectTreeNodes(pNode10, pNode6, pNode14);
	ConnectTreeNodes(pNode6, pNode4, pNode8);
	ConnectTreeNodes(pNode14, pNode12, pNode16);

	Test("Test1", pNode10);

	DestroyList(pNode4);
}

//               5
//              /
//             4
//            /
//           3
//          /
//         2
//        /
//       1
void Test2()
{
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);

	ConnectTreeNodes(pNode5, pNode4, nullptr);
	ConnectTreeNodes(pNode4, pNode3, nullptr);
	ConnectTreeNodes(pNode3, pNode2, nullptr);
	ConnectTreeNodes(pNode2, pNode1, nullptr);

	Test("Test2", pNode5);

	DestroyList(pNode1);
}

// 1
//  \
//   2
//    \
//     3
//      \
//       4
//        \
//         5
void Test3()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNode1, nullptr, pNode2);
	ConnectTreeNodes(pNode2, nullptr, pNode3);
	ConnectTreeNodes(pNode3, nullptr, pNode4);
	ConnectTreeNodes(pNode4, nullptr, pNode5);

	Test("Test3", pNode1);

	DestroyList(pNode1);
}

// 树中只有1个结点
void Test4()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	Test("Test4", pNode1);

	DestroyList(pNode1);
}

// 树中没有结点
void Test5()
{
	Test("Test5", nullptr);
}

int main(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	system("pause");
	return 0;
}