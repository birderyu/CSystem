#pragma once
#include <gtest/gtest.h>
#include "gbintree.h"
#include "gbstree.h"
#include "grbtree.h"
#include "gstring.h"

#define GRED		0
#define GBLACK		1

template <typename NodeT>
struct GCheckRBTreeNode
{
	gsystem::gvoid operator()(const NodeT &node)
	{
		gsystem::gsmall color = node.m_nColor;

		// 1��ÿ�����Ҫô�Ǻ�ģ�Ҫô�Ǻڵģ�
		if (color != GRED && color != GBLACK)
		{
			//ASSERT_EQ(false) << "ÿ�����Ҫô�Ǻ�ģ�Ҫô�Ǻڵģ����ýڵ����ɫ�ǣ�" << color;
			std::cout << "ÿ�����Ҫô�Ǻ�ģ�Ҫô�Ǻڵģ����ýڵ����ɫ�ǣ�" << (gint)color << std::endl;
			return;
		}

		// 2�����������Ǻڵ�
		if (!node.m_pParent)
		{
			//ASSERT_EQ(color, GBLACK) << "���������Ǻڵģ����ýڵ����ɫ�ǣ�" << (gint)color;
			if (color != GBLACK)
			{
				std::cout << "���������Ǻڵģ����ýڵ����ɫ�ǣ�" << (gint)color << std::endl;
				return;
			}
		}

		// 4�����һ������Ǻ�ģ���ô�����������Ӷ��Ǻڵģ�
		if (color == GRED)
		{
			if (node.m_pLeft)
			{
				/*
				ASSERT_EQ(node.m_pLeft->m_nColor, GBLACK)
					<< "���һ������Ǻ�ģ���ô���������Ǻڵģ����ýڵ��������ɫ�ǣ�"
					<< (gint)(node.m_pLeft->m_nColor);
					*/
				if (node.m_pLeft->m_nColor != GBLACK)
				{
					std::cout << "���һ������Ǻ�ģ���ô���������Ǻڵģ����ýڵ��������ɫ�ǣ�"
						<< (gint)(node.m_pLeft->m_nColor) << std::endl;
					return;
				}
			}
			if (node.m_pRight)
			{
				/*
				ASSERT_EQ(node.m_pRight->m_nColor, GBLACK)
					<< "���һ������Ǻ�ģ���ô�����Һ����Ǻڵģ����ýڵ���Һ�����ɫ�ǣ�"
					<< (gint)(node.m_pRight->m_nColor);
					*/
				if (node.m_pRight->m_nColor != GBLACK)
				{
					std::cout << "���һ������Ǻ�ģ���ô�����Һ����Ǻڵģ����ýڵ���Һ�����ɫ�ǣ�"
						<< (gint)(node.m_pRight->m_nColor) << std::endl;
					return;
				}
			}
		}

		// 5����ÿ����㣬�Ӹý�㵽�������������·���ϰ�����ͬ��Ŀ�ĺڽ�㡣
		gsystem::gint other = -1;
		if (!check5(&node, &node, other, 0))
		{
			return;
		}
	}

private:
	// root: ���ڵ�
	// node: ��ǰ�ڵ�
	// other: ������Ҷ�ӽڵ�·���ϵĺ�ɫ�ڵ����������ʼֵΪ-1����ʾ��ǰ·���ǵ�һ��
	// current����ǰ·���Ϻ�ɫ�ڵ������
	gsystem::gbool check5(const NodeT *root, const NodeT *node, gsystem::gint &other, gsystem::gint current)
	{
		if (!node)
		{
			// �Ѿ�����NIL�ڵ�
			current++;
			if (other == -1)
			{
				other = current;
				return true;
			}
			else
			{
				if (other != current)
				{
					std::cout << "��ǰ·���к�ɫ�ڵ����Ŀ����������5: " << root->m_tKey << std::endl;
					return false;
				}
				else
				{
					return true;
				}
			}
		}
		else
		{
			if (node->m_nColor == GBLACK)
			{
				current++;
			}
			return check5(root, node->m_pLeft, other, current)
				&& check5(root, node->m_pRight, other, current);
		}
	}
};


TEST(RedBlackTreeTest, HandleNoneZeroInput)
{
	using namespace gsystem;
	gsize size = 5;

	GRBTree<gint, gint> rbt;
	GCheckRBTreeNode<GRBTree<gint, gint>::Node> checker;
	std::cout << "�������ݣ�" << std::endl;
	for (gint i = 0; i < size; i++)
	{
		gint key = i * i * (i % 2 == 0 ? (-1) : 1);
		rbt.Insert(key, 0);
		rbt.PreOrderTraverse(checker); // ÿ����һ�����ݣ�����һ���ж�
	}
	std::cout << "ɾ�����ݣ�" << std::endl;
	for (gsize i = 0; i < size; i++)
	{
		GRBTree<gint, gint>::Node *root = rbt.Root();
		gint key = root->m_tKey;
		if (root->m_pLeft)
		{
			key = root->m_pLeft->m_tKey;
		}
		else if (root->m_pRight)
		{
			key = root->m_pRight->m_tKey;
		}
		rbt.Delete(key);
		rbt.PreOrderTraverse(checker); // ÿɾ��һ�����ݣ�����һ���ж�
	}
	
}

#undef GBLACK
#undef GRED
