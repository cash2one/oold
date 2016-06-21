#include <BSLib/utility/random.h>
#include "btWeight.h"

namespace BSLib
{

namespace BehaviorTree
{

CBTWeight::CBTWeight()
{
	;
}

CBTWeight::~CBTWeight()
{
	;
}

void CBTWeight::setWeights(NodeWeights& weights)
{
	m_weights = weights;
}

void CBTWeight::setChildrenNodes(ChildNodes& childrenNodes)
{
	SWeightInfor weightInfor;
	int weight = 10000;
	for (BSLib::uint32 i = 0; i < childrenNodes.size(); ++i){
		if (i < m_weights.size()) {
			weight = m_weights[i];
		}
		weightInfor.m_used = false;
		weightInfor.m_node = childrenNodes[i];
		weightInfor.m_weight = weight;

		bool isSave = false;
		MultisetWeight::iterator it = m_weightMultiset.begin();
		for (; it != m_weightMultiset.end(); ++it) {
			if (it->m_weight < weightInfor.m_weight) {
				m_weightMultiset.insert(it, weightInfor);
				isSave = true;
				break;
			}
		}
		if (!isSave) {
			m_weightMultiset.push_back(weightInfor);
		}
	}
	m_weightChildrenNodes.resize(childrenNodes.size(), NULL);
}

void CBTWeight::recalculate()
{
	MultisetWeight::iterator it = m_weightMultiset.begin();
	for (; it != m_weightMultiset.end(); ++it){
		it->m_used = false;
	}

	MultisetWeight::iterator itSelect;
	for (BSLib::uint32 i = 0; i < m_weightChildrenNodes.size(); ++i){
		m_weightChildrenNodes[i] = NULL;

		itSelect = m_weightMultiset.end();
		it = m_weightMultiset.begin();
		for (; it != m_weightMultiset.end(); ++it){
			if (it->m_used) {
				continue;
			}
			if (!BSLib::Utility::CRandom::selectBy10K(it->m_weight)) {
				if (itSelect == m_weightMultiset.end()) {
					itSelect = it;
				}
				continue;
			}
			itSelect = it;
			break;
		}
		if (itSelect == m_weightMultiset.end()) {
			continue;
		}
		m_weightChildrenNodes[i] = itSelect->m_node;
		itSelect->m_used = true;
	}
}

}// BehaviorTree

}//BSLib
