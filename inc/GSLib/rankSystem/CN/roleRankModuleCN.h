#ifndef __GSLIB_RANKSYSTEM_CN_ROLERANKMODULECN_H__
#define __GSLIB_RANKSYSTEM_CN_ROLERANKMODULECN_H__

#include <GSLib/playerSystem/CN/roleModuleCN.h>
#include <GSLib/dbSystem/keyTable.h>
#include <GSLib/rankSystem/cmmhdr.h>

namespace GSLib
{

namespace RankSystem
{

namespace CN
{
class CRoleRankModuleCN : public GSLib::PlayerSystem::CN::CRoleModuleCN
	, BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::CCallback
{
public:
	CRoleRankModuleCN(GSLib::PlayerSystem::CN::CRoleCN* a_roleCN, EModuleType a_moduleType);
	virtual ~CRoleRankModuleCN();

	virtual void preInit(bool isFirst);
	virtual void postInit(bool isFirst);
	virtual void init(bool isFirst);
	virtual void initToClient();
	virtual void final();

	virtual void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	virtual void updateDataToDB();
	virtual void cbSelectTableData(BSLib::uint32 a_sessionID, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream);
	void	synPlaceToGM(BSLib::uint32 a_id);

private:
	void	_onMsgRankSystemGC2CNReqRankList(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg); // todo
	void	_onMsgRankSystemGM2CNNtfUpdate(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void	_onMsgRankSystemGM2CNNtfInitFinish(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	virtual bool exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value);
	virtual bool cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
	bool _dbUpdate();

private:
	GSLib::DBSystem::CKeyTablePtr	m_keyTableCNPtr;
	SRoleRankCN m_roleRankCN;

};
}


}

}



#endif
