//////////////////////////////////////////////////////////////////////
//	created:	2014/11/19
//	filename: 	GSLib\taskSystem\GM\taskDataMgr.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef	__GSLIB_TASKSYSTEM_GM_TASKDATAMGR_H__
#define __GSLIB_TASKSYSTEM_GM_TASKDATAMGR_H__

#include <BSLib/utility/hashMap.h>
#include <BSLib/utility/singleton.h>
#include <GSLib/taskSystem/GM/taskData.h>

namespace GSLib
{

namespace TaskSystem
{

namespace GM
{

class CTaskDataMgr
{
public:
	CTaskDataMgr();
	~CTaskDataMgr();
public:
	BSLIB_SINGLETON_DECLARE(CTaskDataMgr);	
	bool loadConfig(const std::string & a_path);

	const CDailyTaskAttr * getDailyTask(BSLib::uint32 a_TPID) const;
	const BSLib::Utility::CHashMap<BSLib::uint32, CDailyTaskAttr*> & getDailyTask() const;

	const CMainTaskAttr* getMainTask(BSLib::uint32 a_TPID) const;
	const CMainTaskAttr* getFirstMainTask() const;
	const CMainTaskAttr* getNextMainTask(BSLib::uint32 a_mainTaskTPID) const;

	const CPetTaskAttr* getPetTaskByTaskID(BSLib::uint32 a_TPID) const;

	BSLib::uint32 getTaskSystemResetHour() const;
	BSLib::uint32 getTaskSystemResetMinte() const;

	BSLib::uint32 getFirstMainTaskTPID() const;

	CPetTaskAttr* getRandomPetTask(BSLib::uint32 a_petID, BSLib::uint32 a_roleLevel);
	EPetTaskColor genRandomPetTaskColor();
	const CPetTaskColorAttr *getPetTaskColorAttr(EPetTaskColor a_color) const; 
private:
	void _addDailyTaskData(CDailyTaskAttr * a_task);
	void _addMainTaskData(CMainTaskAttr * a_task);
	void _addPetTaskData(CPetTaskAttr *a_task);

	bool _loadDailyTaskData(const std::string & a_path);
	bool _loadDailyTaskConfig(const std::string & a_path);
	bool _loadMainTaskConfig(const std::string & a_path);
	bool _loadPetTaskConfig(const std::string & a_path);

	void _initPetTaskColorAttr();
private:
	std::map<BSLib::uint32, CMainTaskAttr*> m_mapMainTaskData;
	BSLib::Utility::CHashMap<BSLib::uint32, CDailyTaskAttr*> m_hashDailyTaskData;
	BSLib::uint32 m_taskSystemResetHour;
	BSLib::uint32 m_taskSystemResetMinute;

	BSLib::uint32 m_firstMainTaskTPID;
	BSLib::Utility::CHashMap<BSLib::uint32, CPetTaskAttr*> m_hashPetAttrByTaskID;
	BSLib::Utility::CHashMap< BSLib::uint32, std::vector<CPetTaskAttr *> > m_hashPetAttrByPetID;

	std::vector<CPetTaskColorAttr> m_petTaskColorList;
};

}//GM

}//TaskSystem

}//GSLib

#endif//__GSLIB_TASKSYSTEM_GM_TASKDATAMGR_H__

