//////////////////////////////////////////////////////////////////////
//	created:	2012/10/21
//	filename:	src\BSLib\behaviorTree\btWeight.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_BEHAVIORTREE_BTWEIGHT_H__
#define __BSLIB_BEHAVIORTREE_BTWEIGHT_H__

#include <set>
#include <vector>
#include <BSLib/behaviorTree/btNode.h>

namespace BSLib
{

namespace BehaviorTree
{

struct SWeightInfor
{
	bool m_used;
	int m_weight;
	CBTNode* m_node;

	SWeightInfor() : m_used(false), m_weight(0), m_node(NULL) {}
};

// struct SWeightInforLess : public std::binary_function<SWeightInfor, SWeightInfor, bool>
// {	
// 	bool operator()(const SWeightInfor& _Left, const SWeightInfor& _Right) const
// 	{
// 		return (_Left.m_weight < _Right.m_weight);
// 	}
// };

typedef std::vector<int> NodeWeights;
typedef std::vector<SWeightInfor> MultisetWeight;

class CBTWeight
{
public:
	CBTWeight();
	~CBTWeight();

	void setWeights(NodeWeights& weights);

	void setChildrenNodes(ChildNodes& childrenNodes);

	ChildNodes::const_iterator begin() { return m_weightChildrenNodes.begin(); }

	ChildNodes::const_iterator end() { return m_weightChildrenNodes.end(); }

	void recalculate();

private:
	ChildNodes m_weightChildrenNodes;
	MultisetWeight m_weightMultiset;
	NodeWeights m_weights;
};

}// BehaviorTree

}//BSLib

#endif//__BSLIB_BEHAVIORTREE_BTWEIGHT_H__
