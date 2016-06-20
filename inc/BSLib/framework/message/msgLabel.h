//////////////////////////////////////////////////////////////////////
//	created:	2012/07/20
//	filename: 	BSLib\framework\message\msgLabel.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_FRAMEWORK_MESSAGE_MSGLABEL_H__
#define __BSLIB_FRAMEWORK_MESSAGE_MSGLABEL_H__

#include <BSLib/framework/message/message.h>

namespace BSLib
{

namespace Framework
{

enum EMsgLabelType
{
	ELABELTYPE_BASE = 0,
	ELABELTYPE_SYS,
	ELABELTYPE_NET,
	ELABELTYPE_EXTEND,
};

#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

struct BSLIB_FRAMEWORK_API SMsgLabel
{
public:
	SMsgLabel(uint32 lableSize = sizeof(SMsgLabel)) : m_msgSize(0), m_labelSize(lableSize)
	{
		if (m_labelSize < sizeof(SMsgLabel))	{
			m_labelSize = sizeof(SMsgLabel);
		}
		m_labelType = ELABELTYPE_BASE;
	}

	int getLabelType() { return m_labelType; }

public:
	uint32 m_msgSize;   //消息大小

	uint32 getLabelSize() { return m_labelSize; }

protected:
	uint32 m_labelSize;
	int m_labelType;
};


struct BSLIB_FRAMEWORK_API SSysMsgLabel : public SMsgLabel
{
public:
	CChannelID m_sysMsgIDFrome;
	CChannelID m_sysMsgIDTo;

	SSysMsgLabel() : SMsgLabel(sizeof(SSysMsgLabel))
	{
		m_sysMsgIDFrome = INVALID_CHANNELID;
		m_sysMsgIDTo = INVALID_CHANNELID;
		m_labelType = ELABELTYPE_SYS;
	}
};

#ifdef WIN32
#pragma pack (pop)
#else
#pragma pack ()
#endif

}//Framework

}//BSLib

#endif//__BSLIB_FRAMEWORK_MESSAGE_MSGLABEL_H__
