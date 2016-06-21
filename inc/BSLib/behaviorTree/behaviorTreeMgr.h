#ifndef __BSLIB_BEHAVIORTREE_BEHAVIORTREEMGR_H__
#define __BSLIB_BEHAVIORTREE_BEHAVIORTREEMGR_H__

#include <BSLib/utility/hashMap.h>
#include <BSLib/utility/function.h>
#include <BSLib/behaviorTree/behaviorTree.h>
#include <BSLib/behaviorTree/btLeafNode.h>

#define BSLIB_BTMGR_GROUPS_MAX 10

namespace BSLib
{

namespace BehaviorTree
{

typedef CBTNode*(*CreateLeafNodeFun)(const std::string& a_name, CBTNode* a_parent, void* a_temp);

template<typename T>
CBTNode* createLeafNode(const std::string& a_name, CBTNode* a_parent, void* a_temp)
{
	return new T(a_parent);
}

struct SBTInforInFile;
struct SBTNodeInforInFile;

struct SBTCreatorNodeInfor;

class BSLIB_BEHAVIORTREE_API CBehaviorTreeMgr
{
public:
	CBehaviorTreeMgr();
	~CBehaviorTreeMgr();

	void init();
	
	void final();

	bool loadBTFromFile(const std::string& a_behaviorTreeFile);

	CBehaviorTree* createBT(const std::string& a_behaviorTreeName, BSLib::Utility::CScriptEnvironment* a_btEnvironment, SBTStopProtocol a_btStopProtocol);
	CBehaviorTree* createBT(BTTPID a_btTPID, BSLib::Utility::CScriptEnvironment* a_btEnvironment, SBTStopProtocol a_btStopProtocol);

	void removeBT(BTID a_btID);

	void removeBT(CBehaviorTree** a_tree);

	CBehaviorTree* getBT(BTID a_btID);

	void registerLeafNodeFun(const std::string& a_name, CreateLeafNodeFun fun, void* a_temp = NULL);
	void registerLeafNodeFun(const std::string& a_name, BSLib::Utility::CFunction<CBTNode*, const std::string&, CBTNode*, void*>& a_fun, void* a_temp = NULL);

	template<class NAME>
	void registerLeafNodeFun(const std::string& a_name, CBTNode*(NAME::*a_fun)(const std::string&, CBTNode*, void*), NAME* a_object, void* a_temp = NULL)
	{
		BSLib::Utility::CFunctionObject<CBTNode*, NAME, const std::string&, CBTNode*, void*> objFun(a_fun, a_object);
		return registerLeafNodeFun(a_name, objFun, a_temp);
	}

private:
	CBehaviorTree* _createBT(SBTInforInFile* a_btInfor, BSLib::Utility::CScriptEnvironment* a_btEnvironment, SBTStopProtocol a_btStopProtocol);
	bool _createChildBT(const std::string& a_childBTName, CBehaviorTree* a_tree, CBTNode* a_parentNode);
	CBTNode* _createBTNode(const std::string& a_name, CBTNode* a_parent);
	bool _assembleBTNode(CBehaviorTree* tree, CBTNode* btNode, std::vector<SBTNodeInforInFile*>& subNodes);
	CBTNode* _assembleBTRootNode(CBehaviorTree* a_tree, SBTInforInFile* a_btInfor);
	CBTNode* _assembleBTLinkNode(CBehaviorTree* a_tree, CBTNode* a_btNode, std::vector<SBTNodeInforInFile*>& a_subNodes);
	CBTNode* _createLinkNode(const std::string& a_name, CBTNode* a_parent, void* a_temp);
	CBTNode* _createTimerNode(const std::string& a_name, CBTNode* a_parent, void* a_temp);
	BTID _allocateBTID();

private:
	BSLib::Utility::CHashMap<std::string, SBTInforInFile*> m_behaviorTreeInforsByName;
	BSLib::Utility::CHashMap<BTTPID, SBTInforInFile*> m_behaviorTreeInforsByTPID;

	BSLib::Utility::CHashMap<std::string, SBTCreatorNodeInfor*> m_creatorLeafNodes;
	BSLib::Utility::CHashMap<BTID, CBehaviorTree*> m_behaviorTrees;
	BSLib::Utility::CRealTime m_realTime;

private:
	static BTID m_currentBTID;

	friend class CBTLinkNode;
};

}// CBehaviorTree

}//BSLib

#endif//__BSLIB_BEHAVIORTREE_BEHAVIORTREEMGR_H__

