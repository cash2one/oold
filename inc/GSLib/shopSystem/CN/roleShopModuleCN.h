#ifndef __GSLIB_SHOPSYSTEM_CN_ROLESHOPMODULECN_H__
#define __GSLIB_SHOPSYSTEM_CN_ROLESHOPMODULECN_H__

#include <GSLib/playerSystem/CN/roleModuleCN.h>

namespace GSLib
{

namespace ShopSystem
{

namespace CN
{
	class CRoleShopModuleCN : public GSLib::PlayerSystem::CN::CRoleModuleCN
	{
	public:
		CRoleShopModuleCN(GSLib::PlayerSystem::CN::CRoleCN* a_roleCN, EModuleType a_moduleType);
		virtual ~CRoleShopModuleCN();

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
