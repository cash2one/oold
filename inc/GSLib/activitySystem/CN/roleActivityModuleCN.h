#ifndef __GSLIB_ACTIVITYSYSTEM_CN_ROLEACTIVITYMODULECN_H__
#define __GSLIB_ACTIVITYSYSTEM_CN_ROLEACTIVITYMODULECN_H__

#include <GSLib/playerSystem/CN/roleModuleCN.h>

namespace GSLib
{

namespace ActivitySystem
{

namespace CN
{
	class CRoleActivityModuleCN : public GSLib::PlayerSystem::CN::CRoleModuleCN
	{
	public:
		CRoleActivityModuleCN(GSLib::PlayerSystem::CN::CRoleCN* a_roleCN, EModuleType a_moduleType);
		virtual ~CRoleActivityModuleCN();

		virtual void preInit(bool isFirst);
		virtual void postInit(bool isFirst);
		virtual void init(bool isFirst);
		virtual void initToClient();
		virtual void final();

		virtual void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
		virtual void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

		virtual void updateDataToDB();
		virtual void cbSelectTableData(BSLib::uint32 a_sessionID, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream);
	
	};
}


}

}



#endif
