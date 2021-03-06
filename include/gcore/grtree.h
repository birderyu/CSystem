#ifndef _CORE_R_TREE_H_
#define _CORE_R_TREE_H_

#include "gmath.h"

#define RTREE_DONT_USE_MEMPOOLS // This version does not contain a fixed memory allocator, fill in lines with EXAMPLE to implement one.
#define RTREE_USE_SPHERICAL_VOLUME // Better split classification, may be slower on some systems

namespace gsystem { // gsystem

/// \class RTree
/// Implementation of RTree, a multidimensional bounding rectangle tree.
/// Example usage: For a 3-dimensional tree use RTree<Object*, float, 3> myTree;
///
/// This modified, templated C++ version by Greg Douglas at Auran (http://www.auran.com)
///
/// DataT Referenced data, should be int, void*, obj* etc. no larger than sizeof<void*> and simple type
/// ElemT Type of element such as int or float
/// NUMDIMS Number of dimensions such as 2 or 3
/// ELEMTYPEREAL Type of element that allows fractional and large values such as float or double, for use in volume calcs
///
/// NOTES: Inserting and removing data requires the knowledge of its constant Minimal Bounding Rectangle.
///        This version uses new/delete for nodes, I recommend using a fixed size allocator for efficiency.
///        Instead of using a callback function for returned results, I recommend and efficient pre-sized, grow-only memory
///        array similar to MFC CArray or STL Vector for returning search query result.
///
template<typename DataT, 
	typename ElemT, 
	gsize NUMDIMS, 
	typename ELEMTYPEREAL = ElemT, 
	gsize TMAXNODES = 8, 
	gsize TMINNODES = TMAXNODES / 2>
class GRTree
{
	static_assert(TMAXNODES > TMINNODES, "TMAXNODES should be greater than TMINNODES.");
	static_assert(TMINNODES > 0, "TMINNODES should be greater than zero.");
	static_assert(sizeof(DataT) == sizeof(gvoid*) || sizeof(DataT) == sizeof(gint32),
		"We only support machine word size simple data type eg. integer index or object pointer. Since we are storing as union with non data branch");

protected:
	struct Node;  // Fwd decl.  Used by other internal structs and iterator

public:
	GRTree();
	~GRTree();

	/// Insert entry
	/// \param a_min Min of bounding rect
	/// \param a_max Max of bounding rect
	/// \param a_dataId Positive Id of data.  Maybe zero, but negative numbers not allowed.
	gvoid Insert(const ElemT a_min[NUMDIMS], const ElemT a_max[NUMDIMS], const DataT& a_dataId);

	/// Remove entry
	/// \param a_min Min of bounding rect
	/// \param a_max Max of bounding rect
	/// \param a_dataId Positive Id of data.  Maybe zero, but negative numbers not allowed.
	gvoid Remove(const ElemT a_min[NUMDIMS], const ElemT a_max[NUMDIMS], const DataT& a_dataId);

	/// Find all within search rectangle
	/// \param a_min Min of search bounding rect
	/// \param a_max Max of search bounding rect
	/// \param a_searchResult Search result array.  Caller should set grow size. Function will reset, not append to array.
	/// \param a_resultCallback Callback function to return result.  Callback should return 'true' to continue searching
	/// \param a_context User context to pass as parameter to a_resultCallback
	/// \return Returns the number of entries found
	gsize Search(const ElemT a_min[NUMDIMS], const ElemT a_max[NUMDIMS], gbool __cdecl a_resultCallback(DataT a_data, gptr a_context), gptr a_context);

	/// Remove all entries from tree
	gvoid RemoveAll();

	/// Count the data elements in this container.  This is slow as no internal counter is maintained.
	gsize Count();

	/// Iterator is not remove safe.
	class Iterator
	{
	private:

		enum { MAX_STACK = 32 }; //  Max stack size. Allows almost n^32 where n is number of branches in node

		struct StackElement
		{
			Node* m_node;
			gint m_branchIndex;
		};

	public:

		Iterator()                                    { Init(); }

		~Iterator()                                   { }

		/// Is iterator invalid
		gbool IsNull()                                 { return (m_tos <= 0); }

		/// Is iterator pointing to valid data
		gbool IsNotNull()                              { return (m_tos > 0); }

		/// Access the current data element. Caller must be sure iterator is not NULL first.
		DataT& operator*()
		{
			GASSERT(IsNotNull());
			StackElement& curTos = m_stack[m_tos - 1];
			return curTos.m_node->m_branch[curTos.m_branchIndex].m_data;
		}

		/// Access the current data element. Caller must be sure iterator is not NULL first.
		const DataT& operator*() const
		{
			GASSERT(IsNotNull());
			StackElement& curTos = m_stack[m_tos - 1];
			return curTos.m_node->m_branch[curTos.m_branchIndex].m_data;
		}

		/// Find the next data element
		gbool operator++()                             { return FindNextData(); }

		/// Get the bounds for this node
		gvoid GetBounds(ElemT a_min[NUMDIMS], ElemT a_max[NUMDIMS])
		{
			GASSERT(IsNotNull());
			StackElement& curTos = m_stack[m_tos - 1];
			Branch& curBranch = curTos.m_node->m_branch[curTos.m_branchIndex];

			for (gsize index = 0; index < NUMDIMS; ++index)
			{
				a_min[index] = curBranch.m_rect.m_min[index];
				a_max[index] = curBranch.m_rect.m_max[index];
			}
		}

	private:

		/// Reset iterator
		gvoid Init()                                   { m_tos = 0; }

		/// Find the next data element in the tree (For internal use only)
		gbool FindNextData()
		{
			for (;;)
			{
				if (m_tos <= 0)
				{
					return false;
				}
				StackElement curTos = Pop(); // Copy stack top cause it may change as we use it

				if (curTos.m_node->IsLeaf())
				{
					// Keep walking through data while we can
					if (curTos.m_branchIndex + 1 < curTos.m_node->m_count)
					{
						// There is more data, just point to the next one
						Push(curTos.m_node, curTos.m_branchIndex + 1);
						return true;
					}
					// No more data, so it will fall back to previous level
				}
				else
				{
					if (curTos.m_branchIndex + 1 < curTos.m_node->m_count)
					{
						// Push sibling on for future tree walk
						// This is the 'fall back' node when we finish with the current level
						Push(curTos.m_node, curTos.m_branchIndex + 1);
					}
					// Since cur node is not a leaf, push first of next level to get deeper into the tree
					Node* nextLevelnode = curTos.m_node->m_branch[curTos.m_branchIndex].m_child;
					Push(nextLevelnode, 0);

					// If we pushed on a new leaf, exit as the data is ready at TOS
					if (nextLevelnode->IsLeaf())
					{
						return true;
					}
				}
			}
		}

		/// Push node and branch onto iteration stack (For internal use only)
		gvoid Push(Node* a_node, gint a_branchIndex)
		{
			m_stack[m_tos].m_node = a_node;
			m_stack[m_tos].m_branchIndex = a_branchIndex;
			++m_tos;
			GASSERT(m_tos <= MAX_STACK);
		}

		/// Pop element off iteration stack (For internal use only)
		StackElement& Pop()
		{
			GASSERT(m_tos > 0);
			--m_tos;
			return m_stack[m_tos];
		}

		StackElement m_stack[MAX_STACK];              ///< Stack as we are doing iteration instead of recursion
		gint m_tos;                                   ///< Top Of Stack index

		friend GRTree; // Allow hiding of non-public functions while allowing manipulation by logical owner
	};

	/// Get 'first' for iteration
	void GetFirst(Iterator& a_it)
	{
		a_it.Init();
		Node* first = m_root;
		while (first)
		{
			if (first->IsInternalNode() && first->m_count > 1)
			{
				a_it.Push(first, 1); // Descend sibling branch later
			}
			else if (first->IsLeaf())
			{
				if (first->m_count)
				{
					a_it.Push(first, 0);
				}
				break;
			}
			first = first->m_branch[0].m_child;
		}
	}

	/// Get Next for iteration
	void GetNext(Iterator& a_it)                    { ++a_it; }

	/// Is iterator NULL, or at end?
	bool IsNull(Iterator& a_it)                     { return a_it.IsNull(); }

	/// Get object at iterator position
	DataT& GetAt(Iterator& a_it)                 { return *a_it; }

protected:

	/// Minimal bounding rectangle (n-dimensional)
	struct Rect
	{
		ElemT m_min[NUMDIMS];                      ///< Min dimensions of bounding box 
		ElemT m_max[NUMDIMS];                      ///< Max dimensions of bounding box 
	};

	/// May be data or may be another subtree
	/// The parents level determines this.
	/// If the parents level is 0, then this is data
	struct Branch
	{
		Rect m_rect;                                  ///< Bounds
		union
		{
			Node* m_child;                              ///< Child node
			DataT m_data;                            ///< Data Id or Ptr
		};
	};

	/// Node for each branch level
	struct Node
		: public GNewT<Node>
	{
		gbool IsInternalNode()                         { return (m_level > 0); } // Not a leaf, but a internal node
		gbool IsLeaf()                                 { return (m_level == 0); } // A leaf, contains data

		gint m_count;                                  ///< Count
		gint m_level;                                  ///< Leaf is zero, others positive
		Branch m_branch[TMAXNODES];                    ///< Branch
	};

	/// A link list of nodes for reinsertion after a delete operation
	struct ListNode
	{
		ListNode* m_next;                             ///< Next in list
		Node* m_node;                                 ///< Node
	};

	/// Variables for finding a split partition
	struct PartitionVars
	{
		gint m_partition[TMAXNODES + 1];
		gint m_total;
		gint m_minFill;
		gint m_taken[TMAXNODES + 1];
		gint m_count[2];
		Rect m_cover[2];
		ELEMTYPEREAL m_area[2];

		Branch m_branchBuf[TMAXNODES + 1];
		gint m_branchCount;
		Rect m_coverSplit;
		ELEMTYPEREAL m_coverSplitArea;
	};

	Node* AllocNode();
	gvoid FreeNode(Node* a_node);
	gvoid InitNode(Node* a_node);
	gvoid InitRect(Rect* a_rect);
	gbool InsertRectRec(Rect* a_rect, const DataT& a_id, Node* a_node, Node** a_newNode, gint a_level);
	gbool InsertRect(Rect* a_rect, const DataT& a_id, Node** a_root, gint a_level);
	Rect NodeCover(Node* a_node);
	gbool AddBranch(Branch* a_branch, Node* a_node, Node** a_newNode);
	gvoid DisconnectBranch(Node* a_node, gint a_index);
	gint PickBranch(Rect* a_rect, Node* a_node);
	Rect CombineRect(Rect* a_rectA, Rect* a_rectB);
	gvoid SplitNode(Node* a_node, Branch* a_branch, Node** a_newNode);
	ELEMTYPEREAL RectSphericalVolume(Rect* a_rect);
	ELEMTYPEREAL RectVolume(Rect* a_rect);
	ELEMTYPEREAL CalcRectVolume(Rect* a_rect);
	gvoid GetBranches(Node* a_node, Branch* a_branch, PartitionVars* a_parVars);
	gvoid ChoosePartition(PartitionVars* a_parVars, gint a_minFill);
	gvoid LoadNodes(Node* a_nodeA, Node* a_nodeB, PartitionVars* a_parVars);
	gvoid InitParVars(PartitionVars* a_parVars, gint a_maxRects, gint a_minFill);
	gvoid PickSeeds(PartitionVars* a_parVars);
	gvoid Classify(gint a_index, gint a_group, PartitionVars* a_parVars);
	gbool RemoveRect(Rect* a_rect, const DataT& a_id, Node** a_root);
	gbool RemoveRectRec(Rect* a_rect, const DataT& a_id, Node* a_node, ListNode** a_listNode);
	ListNode* AllocListNode();
	gvoid FreeListNode(ListNode* a_listNode);
	gbool Overlap(Rect* a_rectA, Rect* a_rectB);
	gvoid ReInsert(Node* a_node, ListNode** a_listNode);
	gbool Search(Node* a_node, Rect* a_rect, gsize& a_foundCount, gbool __cdecl a_resultCallback(DataT a_data, gptr a_context), gptr a_context);
	gvoid RemoveAllRec(Node* a_node);
	gvoid Reset();
	gvoid CountRec(Node* a_node, gsize& a_count);

	Node* m_root;                                    ///< Root of tree
	ELEMTYPEREAL m_unitSphereVolume;                 ///< Unit sphere constant for required number of dimensions
};

} // namespace gsystem

#include "inline/grtree.inl"

#endif // _CORE_R_TREE_H_