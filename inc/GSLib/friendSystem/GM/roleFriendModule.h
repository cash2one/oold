
#ifndef __GSLIB_FRIENDSYSTEM_GM_ROLEFRIENDMODULE_H__
#define __GSLIB_FRIENDSYSTEM_GM_ROLEFRIENDMODULE_H__

#include <GSLib/playerSystem/GM/roleModuleGM.h>
#include <BSLib/database/dbTableRow.h>
#include <GSLib/friendSystem/DB/tableFriendDB.h>
#include <GSLib/dbSystem/keyIndexTable.h>
#include <GSLib/friendSystem/DB/tableFriendDB.h>
#include <GSLib/friendSystem/commhdr.h>

namespace GSLib
{

namespace FriendSystem
{

namespace GM
{


class CRoleFriendModule : public GSLib::PlayerSystem::GM::CRoleModuleGM
	, BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::CCallback
{
public:
	CRoleFriendModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType);
	virtual ~CRoleFriendModule();

	virtual void preInit(bool isFirst);
	virtual void postInit(bool isFirst);
	virtual void initToClient();
	virtual void final();

	virtual void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	virtual void updateDataToDB();
	
	// 接口
	bool		isMyFriend(const SRoleKey& a_role);				// 是否是我好友
	void		getMyFriends(std::vector<SRoleKey>& a_roles);	// 获得我的好友列表
	bool		extendCapacity(BSLib::uint32 a_size);

private:
	void	_onMsgFriendSystemGC2GMReqLocal(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void	_onMsgFriendSystemCN2GMNtfFriendChange(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	virtual bool cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
	virtual bool	exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value);

private:
	DB::SRoleFriendData		m_myfriend; 

};

}//GM

}

}//GSLib

#endif