#ifndef __GSLIB_RANKSYSTEM_RANKSYSTEMDEFINE_H__
#define __GSLIB_RANKSYSTEM_RANKSYSTEMDEFINE_H__

#include <GFLib/commonServer/message/message.h>
#include <GSLib/funType.h>
#include <GSLib/serverType.h>
#include <GSLib/baseDef.h>

namespace GSLib
{

namespace RankSystem
{

enum ERankType
{
	ERANK_TYPE_ARENA,							//竞技场排名
	ERANK_TYPE_COMBAT_POWER,			//战斗力排名
	ERANK_TYPE_LEVEL,							//等级排名

	ERANK_TYPE_MAX,
};

}//RankSystem

}//GSLib

#endif//__GSLIB_RANKSYSTEM_RANKSYSTEMDEFINE_H__

