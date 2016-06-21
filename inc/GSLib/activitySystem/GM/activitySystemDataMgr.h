#ifndef		__GSLIB_ACTIVITYSYSTEM_GM_ACTIVITYSYSTEMDATAMGR_H__	
#define		__GSLIB_ACTIVITYSYSTEM_GM_ACTIVITYSYSTEMDATAMGR_H__		

#include <BSLib/utility/baseDef.h>
#include <BSLib/utility/hashMap.h>
#include <BSLib/utility/singleton.h>
#include <GSLib/activitySystem/GM/activitySystemDefine.h>

namespace GSLib
{

namespace ActivitySystem
{

namespace GM
{
	class CAttendenceAttr;

class CActivitySystemDataMgr
{
public:
	CActivitySystemDataMgr();
	~CActivitySystemDataMgr();
public:
	BSLIB_SINGLETON_DECLARE(CActivitySystemDataMgr);
public:
	bool loadActivityConfig(const std::string & a_path);
	void addAttendenceAttr(BSLib::uint32 a_tableID, CAttendenceAttr *a_attendenceAttr);
	BSLib::uint32 getCurAttendencePrizeTable() const;
	const CAttendenceAttr * getAttendenceAttr(BSLib::uint32 a_tableID, BSLib::uint32 a_day) const;
	const CAttendenceAttr * getCurAttendenceAttr(BSLib::uint32 a_day) const;

	const BSLib::Utility::CHashMap<BSLib::uint32, CAttendenceAttr *>* getAttendenceAttrMap(BSLib::uint32 a_tableID) const;
	const BSLib::Utility::CHashMap<BSLib::uint32, CAttendenceAttr *>* getCurAttendenceAttrMap() const;
	const BSLib::Utility::CHashMap<BSLib::uint32, CPetCardInfo> & getPetCardInfoMap(BSLib::uint32 a_level) const;
private:
	bool _loadAttendenceAttrs(const std::string & a_path);	
	bool _loadAttendenceConfig(const std::string & a_path);
	bool _loadPetCardConfig(const std::string & a_path);
	bool _loadDrawCardWeightBonusConfig(const std::string & a_path);
private:
	BSLib::uint32 m_curAttendenceTable;
	BSLib::Utility::CHashMap< BSLib::uint32, BSLib::Utility::CHashMap<BSLib::uint32, CAttendenceAttr *> > m_hashAttendenceAttrs;	
	BSLib::Utility::CHashMap<BSLib::uint32, CPetCardInfo> m_hashPetCardInfo[MAX_DRAW_CARD_LEVEL];
	BSLib::Utility::CHashMap<BSLib::uint32, CCardLevelWeightBonus> m_drawCardWeightBonusInfo[EDRAW_CARD_WEIGHT_BONUS_TYPE_MAX];
};

} //GM

} //ActivitySystem

} //GSLib


#endif



