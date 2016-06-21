#ifndef __BSLIB_UTILITY_TIMERSERVER_H__
#define __BSLIB_UTILITY_TIMERSERVER_H__

#include <BSLib/utility/function.h>
#include <BSLib/utility/dateTime.h>
#include <BSLib/utility/hashMap.h>

#define TIMER_NUMBER_BITS_MAX 4

namespace BSLib
{

namespace Utility
{

typedef BSLib::int32 TimerHandle;
const TimerHandle INVALID_TIMER = -1;

struct STimerItem;

//////////////////////////////////////////////////////////////////////////
/// @brief ��ʱ��
//////////////////////////////////////////////////////////////////////////
class BSLIB_UTILITY_API CTimerServer
{
public:
	/// @brief �����������Ͷ���
	/// @return	bool �Ƿ��������, true ����������false �����ж�
	/// @param	a_para �������ݲ���
	typedef bool (*FTimerCallback)(BSLib::uint64, void* a_para);

	union TimerNumber
	{
		BSLib::uint8 m_bits[TIMER_NUMBER_BITS_MAX];
		BSLib::uint32 m_number;
	};

public:
	CTimerServer();
	virtual ~CTimerServer();

	/// @brief ���һ����ʱ��
	/// @return	BSLib::Utility::TimerHandle ����ɹ�����һ����ʱ���������ʧ�ܣ��򷵻� INVALID_TIMER
	/// @param	a_fun ��ʱ��������
	/// @param	a_object �ຯ���Ķ���
	/// @param	a_para �������ݲ���
	/// @param	a_msInterval �������ʱ��(����)
	/// @param	a_msDelay ��һ�δ���ʱ��(����)
	/// @param	a_counts ������������
	TimerHandle addTimer(FTimerCallback a_fun, BSLib::uint64 a_para1, void* a_para2, BSLib::uint32 a_msInterval,  BSLib::uint32 a_msDelay=0, BSLib::int32 a_counts = -1);
	TimerHandle addTimer(const CFunction<bool, BSLib::uint64, void*>& a_fun, BSLib::uint64 a_para1, void* a_para2, BSLib::uint32 a_msInterval,  BSLib::uint32 a_msDelay=0, BSLib::int32 a_counts = -1);
	template<class NAME>
	TimerHandle addTimer(bool (NAME::*a_fun)(BSLib::uint64, void*), NAME* a_object, BSLib::uint64 a_para1, void* a_para2, BSLib::uint32 a_msInterval,  BSLib::uint32 a_msDelay=0, BSLib::int32 a_counts = -1)
	{
		CFunctionObject<bool, NAME, BSLib::uint64, void*> fun(a_fun, a_object);
		return addTimer(fun, a_para1, a_para2, a_msInterval, a_msDelay, a_counts);
	}

	/// @brief ɾ����ʱ��
	/// @return	void
	/// @param	a_timerHandle ��ʱ�����
	void delTimer(TimerHandle a_timerHandle);

	/// @brief �ж϶�ʱ���Ƿ���Ч
	/// @return	bool ��Ч����true
	/// @param	a_timerHandle ��ʱ�����
	bool isValid(TimerHandle a_timerHandle);

	/// @brief �������ж�ʱ��
	/// @return	void
	void update();

	/// @brief �������ж�ʱ��
	/// @return	void
	void update(BSLib::int64 a_currentTime);

	BSLib::Utility::CRealTime* getRealTime() { return &m_realTime; }

private:
	TimerHandle _allocateHandle();
	bool _addTimer(STimerItem* a_timerItem, BSLib::uint32 a_msDelay=0);
	void  _clear();
	void _adjustTimer1(BSLib::uint8 point);
	void _adjustTimer2(BSLib::uint8 point);
	void _adjustTimer3(BSLib::uint8 point);

private:
	BSLib::Utility::CRealTime m_realTime;
	BSLib::Utility::CDelayTimer m_delayTimer;
	std::vector< std::list<STimerItem*>* > m_stages[TIMER_NUMBER_BITS_MAX];
	TimerNumber m_stagesPoint;
	CHashMap<TimerHandle, STimerItem*> m_timers;
	BSLib::int32 m_handles;
	BSLib::int64 m_lastTime;
	BSLib::int64 m_spareTimeInterval;
};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_TIMERSERVER_H__


