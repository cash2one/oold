//////////////////////////////////////////////////////////////////////
//	created:	2012/07/20
//	filename:	src\BSLib\framework\message\msgExecMgr.cpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/framework/message/msgExecMgr.h>

namespace BSLib
{

namespace Framework
{

CMsgExecMgr::CMsgExecMgr()
{
	;
}

CMsgExecMgr::~CMsgExecMgr()
{
	;
}

bool CMsgExecMgr::executeMessage(SMsgLabel* msgLabel, SMessage* msg)
{
	if (msgLabel == NULL || msg == NULL) {
		return false;
	}

	int16 type = msg->getType();
	int16 id = msg->getID();
	uint32 key = BSLIB_HI_SHIFT(type, 16) + id;

	BSLib::Utility::CHashMap<uint32, SMsgExecItem*>::iterator msgExecIt = m_msgExecHashMap.find(key);
	if (msgExecIt != m_msgExecHashMap.end()) {
		SMsgExecItem* msgExecItem = msgExecIt->second;
		if (msgExecItem != NULL){
			if (msgExecItem->m_msgExecPtr != NULL) {
				msgExecItem->m_msgExecPtr->executeMessage(msgLabel, msg);
				if (msgExecItem->m_afterMsgExecFun == NULL) {
					return true;
				}
				(*msgExecItem->m_afterMsgExecFun)(this, msgLabel, msg);
				return true;
			}
			if (msgExecItem->m_afterMsgExecFun != NULL) {
				BSLIB_SAFE_DELETE(msgExecItem->m_afterMsgExecFun);
			}
		}
		BSLIB_SAFE_DELETE(msgExecItem);
		m_msgExecHashMap.remove(key);
	}

	BSLib::Utility::CHashMap<uint16, SMsgExecItem*>::iterator typeMsgExecIt = m_typeMsgExecHashMap.find(type);
	if (typeMsgExecIt != m_typeMsgExecHashMap.end()) {
		SMsgExecItem* msgExecItem = typeMsgExecIt->second;
		if (msgExecItem != NULL){
			if (msgExecItem->m_msgExecPtr != NULL) {
				msgExecItem->m_msgExecPtr->executeMessage(msgLabel, msg);
				if (msgExecItem->m_afterMsgExecFun == NULL) {
					return true;
				}
				(*msgExecItem->m_afterMsgExecFun)(this, msgLabel, msg);
				return true;
			}
			if (msgExecItem->m_afterMsgExecFun != NULL) {
				BSLIB_SAFE_DELETE(msgExecItem->m_afterMsgExecFun);
			}
		}
		BSLIB_SAFE_DELETE(msgExecItem);
		m_typeMsgExecHashMap.remove(type);
	}
	return false;
}

bool CMsgExecMgr::addMsgExecPtr(uint32 msgID, CMsgExecPtr& msgExecPtr)
{
	uint16 type = msgID & 0X0000FFFF;
	uint16 id = BSLIB_LO_SHIFT(msgID, 16);

	return addMsgExecPtr(type , id, msgExecPtr);
}

bool CMsgExecMgr::addMsgExecPtr(uint32 msgID, CMsgExecPtr& msgExecPtr, void(*afterMsgExecFun)(CMsgExecMgr*, SMsgLabel*, SMessage*))
{
	uint16 type = msgID & 0X0000FFFF;
	uint16 id = BSLIB_LO_SHIFT(msgID, 16);

	return addMsgExecPtr(type , id, msgExecPtr, afterMsgExecFun);
}

bool CMsgExecMgr::addMsgExecPtr(uint32 msgID, CMsgExecPtr& msgExecPtr, const BSLib::Utility::CFunction<void, CMsgExecMgr*, SMsgLabel*, SMessage*>& afterMsgExecFun)
{
	uint16 type = msgID & 0X0000FFFF;
	uint16 id = BSLIB_LO_SHIFT(msgID, 16);

	return addMsgExecPtr(type , id, msgExecPtr, afterMsgExecFun);
}

bool CMsgExecMgr::addMsgExecPtr(uint16 type, uint16 id, CMsgExecPtr& msgExecPtr)
{
	if (msgExecPtr == NULL) {
		return false;
	}

	uint32 key = BSLIB_HI_SHIFT(type, 16) + id;
	BSLib::Utility::CHashMap<uint32, SMsgExecItem*>::iterator msgExecIt = m_msgExecHashMap.find(key);
	if (msgExecIt != m_msgExecHashMap.end()) {
		return false;
	}
	
	SMsgExecItem* msgExecItem = new SMsgExecItem();
	if (msgExecItem == NULL){
		return false;
	}
	msgExecItem->m_msgExecPtr = msgExecPtr;
	msgExecItem->m_afterMsgExecFun = NULL;
	
	m_msgExecHashMap.setValue(key, msgExecItem);
	return true;
}

bool CMsgExecMgr::addMsgExecPtr(uint16 type, uint16 id, CMsgExecPtr& msgExecPtr, void(*afterMsgExecFun)(CMsgExecMgr*, SMsgLabel*, SMessage*))
{
	if (afterMsgExecFun == NULL){
		return addMsgExecPtr(type, id, msgExecPtr);
	}
	BSLib::Utility::CFunction<void, CMsgExecMgr*, SMsgLabel*, SMessage*> fun(afterMsgExecFun);
	return addMsgExecPtr(type, id, msgExecPtr, fun);
}

bool CMsgExecMgr::addMsgExecPtr(uint16 type, uint16 id, CMsgExecPtr& msgExecPtr, const BSLib::Utility::CFunction<void, CMsgExecMgr*, SMsgLabel*, SMessage*>& afterMsgExecFun)
{
	if (msgExecPtr == NULL) {
		return false;
	}

	uint32 key = BSLIB_HI_SHIFT(type, 16) + id;
	BSLib::Utility::CHashMap<uint32, SMsgExecItem*>::iterator msgExecIt = m_msgExecHashMap.find(key);
	if (msgExecIt != m_msgExecHashMap.end()) {
		return false;
	}
	SMsgExecItem* msgExecItem = new SMsgExecItem();
	if (msgExecItem == NULL){
		return false;
	}
	msgExecItem->m_msgExecPtr = msgExecPtr;
	msgExecItem->m_afterMsgExecFun = afterMsgExecFun.clone();

	m_msgExecHashMap.setValue(key, msgExecItem);
	return true;
}

bool CMsgExecMgr::addMsgTypeExecPtr(uint16 type, CMsgExecPtr& msgExecPtr)
{
	if (msgExecPtr == NULL) {
		return false;
	}

	BSLib::Utility::CHashMap<uint16, SMsgExecItem*>::iterator typeMsgExecIt = m_typeMsgExecHashMap.find(type);
	if (typeMsgExecIt != m_typeMsgExecHashMap.end()) {
		return false;
	}
	SMsgExecItem* msgExecItem = new SMsgExecItem();
	if (msgExecItem == NULL){
		return false;
	}
	msgExecItem->m_msgExecPtr = msgExecPtr;
	msgExecItem->m_afterMsgExecFun = NULL;

	m_typeMsgExecHashMap.setValue(type, msgExecItem);
	return true;
}

bool CMsgExecMgr::addMsgTypeExecPtr(uint16 type, CMsgExecPtr& msgExecPtr, void(*afterMsgExecFun)(CMsgExecMgr*, SMsgLabel*, SMessage*))
{
	if (afterMsgExecFun == NULL){
		return addMsgExecPtr(type, msgExecPtr);
	}
	BSLib::Utility::CFunction<void, CMsgExecMgr*, SMsgLabel*, SMessage*> fun(afterMsgExecFun);
	return addMsgExecPtr(type, msgExecPtr, fun);
}

bool CMsgExecMgr::addMsgTypeExecPtr(uint16 type, CMsgExecPtr& msgExecPtr, const BSLib::Utility::CFunction<void, CMsgExecMgr*, SMsgLabel*, SMessage*>& afterMsgExecFun)
{
	if (msgExecPtr == NULL) {
		return false;
	}

	BSLib::Utility::CHashMap<uint16, SMsgExecItem*>::iterator typeMsgExecIt = m_typeMsgExecHashMap.find(type);
	if (typeMsgExecIt != m_typeMsgExecHashMap.end()) {
		return false;
	}
	SMsgExecItem* msgExecItem = new SMsgExecItem();
	if (msgExecItem == NULL){
		return false;
	}
	msgExecItem->m_msgExecPtr = msgExecPtr;
	msgExecItem->m_afterMsgExecFun = afterMsgExecFun.clone();

	m_typeMsgExecHashMap.setValue(type, msgExecItem);
	return true;
}

void CMsgExecMgr::delMsgExecPtr(uint32 msgID)
{
	uint16 type = msgID & 0X0000FFFF;
	uint16 id = BSLIB_LO_SHIFT(msgID, 16);

	delMsgExecPtr(type, id);
}

void CMsgExecMgr::delMsgExecPtr(uint16 type, uint16 id)
{
	uint32 key = BSLIB_HI_SHIFT(type, 16) + id;

	BSLib::Utility::CHashMap<uint32, SMsgExecItem*>::iterator msgExecIt = m_msgExecHashMap.find(key);
	if (msgExecIt == m_msgExecHashMap.end()) {
		return ;
	}
	SMsgExecItem* msgExecItem = msgExecIt->second;
	if (msgExecItem != NULL){
		if (msgExecItem->m_msgExecPtr != NULL) {
			msgExecItem->m_msgExecPtr = NULL;
			if (msgExecItem->m_afterMsgExecFun != NULL) {
				BSLIB_SAFE_DELETE(msgExecItem->m_afterMsgExecFun);
			}
		}
		BSLIB_SAFE_DELETE(msgExecItem);
	}
	m_msgExecHashMap.remove(key);
}

void CMsgExecMgr::delMsgExecPtr(uint16 type)
{
	BSLib::Utility::CHashMap<uint16, SMsgExecItem*>::iterator typeMsgExecIt = m_typeMsgExecHashMap.find(type);
	if (typeMsgExecIt != m_typeMsgExecHashMap.end()) {
		return ;
	}
	SMsgExecItem* msgExecItem = typeMsgExecIt->second;
	if (msgExecItem != NULL){
		if (msgExecItem->m_msgExecPtr != NULL) {
			msgExecItem->m_msgExecPtr = NULL;
			if (msgExecItem->m_afterMsgExecFun != NULL) {
				BSLIB_SAFE_DELETE(msgExecItem->m_afterMsgExecFun);
			}
		}
		BSLIB_SAFE_DELETE(msgExecItem);
	}
	m_msgExecHashMap.remove(type);
}

void CMsgExecMgr::clear()
{
	BSLib::Utility::CHashMap<uint32, SMsgExecItem*>::iterator msgExecIt = m_msgExecHashMap.begin();
	for (; msgExecIt != m_msgExecHashMap.end(); ++msgExecIt){
		SMsgExecItem* msgExecItem = msgExecIt->second;
		if (msgExecItem == NULL){
			continue;
		}
		if (msgExecItem->m_msgExecPtr != NULL) {
			msgExecItem->m_msgExecPtr = NULL;
		}
		if (msgExecItem->m_afterMsgExecFun != NULL) {
			BSLIB_SAFE_DELETE(msgExecItem->m_afterMsgExecFun);
		}
		BSLIB_SAFE_DELETE(msgExecItem);
	}
	m_msgExecHashMap.clear();

	BSLib::Utility::CHashMap<uint16, SMsgExecItem*>::iterator typeMsgExecIt = m_typeMsgExecHashMap.begin();
	for (; typeMsgExecIt != m_typeMsgExecHashMap.end(); ++typeMsgExecIt){
		SMsgExecItem* msgExecItem = typeMsgExecIt->second;
		if (msgExecItem == NULL){
			continue;
		}
		if (msgExecItem->m_msgExecPtr != NULL) {
			msgExecItem->m_msgExecPtr = NULL;
		}
		if (msgExecItem->m_afterMsgExecFun != NULL) {
			BSLIB_SAFE_DELETE(msgExecItem->m_afterMsgExecFun);
		}
		BSLIB_SAFE_DELETE(msgExecItem);
	}
	m_typeMsgExecHashMap.clear();
}

}//Framework

}//BSLib

