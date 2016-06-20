//////////////////////////////////////////////////////////////////////
//	created:	2014/12/11
//	filename: 	GSLib\activitySystem\GM\activitySystemError.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////

#ifndef		__GSLIB_ACTIVITYSYSTEM_GM_ACTIVITYSYSTEMERROR_H__
#define		__GSLIB_ACTIVITYSYSTEM_GM_ACTIVITYSYSTEMERROR_H__

namespace GSLib
{
namespace ActivitySystem
{

namespace GM
{

enum EGetAttendenceDataResult
{
	EGET_ATTENDENCE_DATA_RESULT_SUCCESS  = 0,
	EGET_ATTENDENCE_DATA_RESULT_FAIL,
	EGET_ATTENDENCE_DATA_RESULT_PRIZE_TABLE_ERROR,

};

enum EAttendenceSignInResult
{
	EATTENDENCE_SIGN_IN_RESULT_SUCCESS = 0,
	EATTENDENCE_SIGN_IN_RESULT_FAIL,
	EATTENDENCE_SIGN_IN_RESULT_ALREADY_SIGN_IN,

};

enum EDrawCardResult
{
	EDRAW_CARD_RESULT_SUCCESS = 0,
	EDRAW_CARD_RESULT_FAIL,
	EDRAW_CARD_RESULT_ERROR_TYPE,
	EDRAW_CARD_RESULT_ERROR_COUNT,
	EDRAW_CARD_RESULT_NOT_ENOUGH_GOLD,
	EDRAW_CARD_RESULT_NOT_ENOUGH_DIAMOND,
};

} //GM

} //ActivitySystem

}	// GSLIB

#endif
