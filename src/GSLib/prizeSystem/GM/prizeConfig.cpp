//////////////////////////////////////////////////////////////////////
//	created:	2014/10/13
//	filename: 	src\GSLib\prizeSystem\GM\prizeConfig.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/file/xmlFile.h>
#include <GSLib/tracer.h>
#include <GSLib/prizeSystem/GM/prizeConfig.h>
#include <BSLib/utility/string.h>
#include <GSLib/prizeSystem/lexical.h>
#include <BSLib/utility/dateTime.h>

namespace GSLib
{

namespace PrizeSystem
{

namespace GM
{

BSLIB_SINGLETON_DEFINE(CPrizeConfig);

// bool readItemNode(BSLib::Utility::CXmlFile& a_xmlFile, BSLib::Utility::HXmlNode& a_itemNode, SPrizeItemInfo* a_prizeItemInfor)
// {
// 	if (!a_xmlFile.getNodeAttrValue(a_itemNode, "f_type", a_prizeItemInfor->m_type)) {
// 		BSLIB_LOG_ERROR(ETT_GSLIB_PRIZESYSTEM, "获取f_type属性失败");
// 		return false;
// 	}
// 	a_xmlFile.getNodeAttrValue(a_itemNode, "f_para1", a_prizeItemInfor->m_para1);
// 	a_xmlFile.getNodeAttrValue(a_itemNode, "f_para2", a_prizeItemInfor->m_para2);
// 	a_xmlFile.getNodeAttrValue(a_itemNode, "f_para3", a_prizeItemInfor->m_para3);
// 	return true;
// }

bool readPrizeNode(BSLib::Utility::CXmlFile& a_xmlFile, BSLib::Utility::HXmlNode& a_prizeNode, BSLib::int32& a_prizeID,
				   SPrizeItemInfo*& a_prizeItemList)
{	
	std::string strStartTime;
	std::string strEndTime;
	BSLib::int32 periodType = 0;
	BSLib::int32 periodNum = 0;
	BSLib::int32 sendType = 0;
	std::string strItem;
	bool success = true;
	BSLib::int32 limitNum = 0;
	std::string sender;
	std::string title;
	std::string content;
	BSLib::int32 stateSwitch = 0;
	std::string stateList;
	success = a_xmlFile.getNodeAttrValue(a_prizeNode, "f_id", a_prizeID) && success;
	success = a_xmlFile.getNodeAttrValue(a_prizeNode, "f_start_time", strStartTime) && success;
	success = a_xmlFile.getNodeAttrValue(a_prizeNode, "f_end_time", strEndTime) && success;
	success = a_xmlFile.getNodeAttrValue(a_prizeNode, "f_period_type", periodType) && success;
	success = a_xmlFile.getNodeAttrValue(a_prizeNode, "f_period_num", periodNum) && success;
	success = a_xmlFile.getNodeAttrValue(a_prizeNode, "f_send_type", sendType) && success;
	success = a_xmlFile.getNodeAttrValue(a_prizeNode, "f_item", strItem) && success;
	success = a_xmlFile.getNodeAttrValue(a_prizeNode, "f_limit_num", limitNum) && success;

	success = a_xmlFile.getNodeAttrValue(a_prizeNode, "f_mail_sender", sender) && success;
	success = a_xmlFile.getNodeAttrValue(a_prizeNode, "f_mail_title", title) && success;
	success = a_xmlFile.getNodeAttrValue(a_prizeNode, "f_mail_content", content) && success;
	success = a_xmlFile.getNodeAttrValue(a_prizeNode, "f_state_switch", stateSwitch) && success;
	success = a_xmlFile.getNodeAttrValue(a_prizeNode, "f_state_list", stateList) && success;
	
	if( !success){
		BSLIB_LOG_ERROR(ETT_GSLIB_PRIZESYSTEM, "获取prize属性失败, id:%d", a_prizeID);
		return false;
	}

	SPrizeItemInfo* prizeItem = new SPrizeItemInfo;
	success = false;
	// 解析时间
	do 
	{
		// 开始时间
		std::vector<BSLib::uint32> startTimeVec;
		if(!lexicalCast<BSLib::uint32>(strStartTime, startTimeVec, ".")){
			break;
		}

		if( 1 == startTimeVec.size() && 1 >= startTimeVec[0]){
			prizeItem->m_startTime = startTimeVec[0];
		}
		else if( 3 == startTimeVec.size()){
			BSLib::Utility::CDateTime startTime(startTimeVec[0], startTimeVec[1], startTimeVec[2]);
			prizeItem->m_startTime = startTime.getSeconds();
		}
		else{
			break;
		}
		
		// 结束时间
		std::vector<BSLib::uint32> endTimeVec;
		if(!lexicalCast<BSLib::uint32>(strEndTime, endTimeVec, ".")){
			break;
		}

		if( 1 == endTimeVec.size() && 1 >= endTimeVec[0]){
			prizeItem->m_endTime = endTimeVec[0];
		}
		else if( 3 == endTimeVec.size()){
			BSLib::Utility::CDateTime endTime(endTimeVec[0], endTimeVec[1], endTimeVec[2]);
			prizeItem->m_endTime = endTime.getSeconds();
		}
		else{
			break;
		}
	
		// 奖励
		// 格式 x_x_x|x_x_x
		std::vector<std::string> itemsVec;
		if( !lexicalCast<std::string>(strItem, itemsVec, "|")){
			break;
		}
		
		// 考虑为 0 的情况
		if( 1 == itemsVec.size()){
			std::vector<BSLib::uint32> item;
			if(!lexicalCast<BSLib::uint32>(itemsVec[0], item, "_")){
				break;
			}

			if( 1 != item.size() && 3 != item.size()){
				break;
			}
			
			if( 3 == item.size()){
				if( 0 != item[1] && 0 != item[2]){
					prizeItem->m_itemTypes.push_back(item[0]);
					prizeItem->m_itemIds.push_back(item[1]);
					prizeItem->m_itemNums.push_back(item[2]);
				}
			}
		}
		else{
			
			bool needExit = false;
			for(BSLib::uint32 i = 0; i < itemsVec.size(); i++){
				std::vector<BSLib::uint32> item;
				if(!lexicalCast<BSLib::uint32>(itemsVec[i], item, "_")){
					break;
				}

				if( 3 != item.size()){
					needExit = true;
					break;
				}

				if( 0 != item[1] && 0 != item[2]){
					prizeItem->m_itemTypes.push_back(item[0]);
					prizeItem->m_itemIds.push_back(item[1]);
					prizeItem->m_itemNums.push_back(item[2]);
				}
			} // for

			if(needExit){
				break;
			}

		} // else


		// 状态列表
		{
			bool needExit = false;
			do 
			{
				// 格式 x_x_x|x_x_x
				std::vector<std::string> stateVec;
				if( !lexicalCast<std::string>(stateList, stateVec, "|")){
					break;
				}

				// 考虑为 0 的情况
				if( 1 == stateVec.size()){
					std::vector<BSLib::int32> states;
					if(!lexicalCast<BSLib::int32>(stateVec[0], states, "_")){
						break;
					}

					if( 1 != states.size() && 3 != states.size()){
						break;
					}

					if( 3 == states.size()){
						StateMachineSt st;
						st.type = states[0];
						st.key = states[1];
						st.value = states[2];
						prizeItem->m_stateM.push_back(st);
					}
				}
				else
				{
					for(BSLib::uint32 i = 0; i < stateVec.size(); i++){
						std::vector<BSLib::int32> states;
						if(!lexicalCast<BSLib::int32>(stateVec[i], states, "_")){
							break;
						}

						if( 3 != states.size()){
							needExit = true;
							break;
						}

						StateMachineSt st;
						st.type = states[0];
						st.key = states[1];
						st.value = states[2];
						prizeItem->m_stateM.push_back(st);

					} // for

					if(needExit){
						break;
					}

				} // else

			} while (false);
			
			if(needExit){
				break;
			}
		}
		

		success = true;
	} while (false);
	
	if( !success){
		delete prizeItem;
		BSLIB_LOG_ERROR(ETT_GSLIB_PRIZESYSTEM, "prize加载失败, id:%d", a_prizeID);
		return false;
	}
	
	prizeItem->m_id = a_prizeID;
	prizeItem->m_periodType = periodType;
	prizeItem->m_periodNum = periodNum;
	prizeItem->m_sendType = sendType;
	a_prizeItemList = prizeItem;
	prizeItem->m_limitNum = limitNum;
	prizeItem->m_sender = sender;
	prizeItem->m_title = title;
	prizeItem->m_content = content;
	prizeItem->m_stateSwitch = stateSwitch;
	return true;
}

CPrizeConfig::CPrizeConfig()
{
	;
}

CPrizeConfig::~CPrizeConfig()
{
}

bool CPrizeConfig::loadConfigFile(const std::string& a_configFile)
{
	BSLib::Utility::CXmlFile xmlFile;

	if (!xmlFile.loadFile(a_configFile)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PRIZESYSTEM, "读取%s文件失败", a_configFile.c_str());
		return false;
	}
	BSLib::Utility::HXmlNode root = xmlFile.getRootNode();
	if (root == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PRIZESYSTEM, "获取%s文件根节点失败", a_configFile.c_str());
		return false;
	}
	BSLib::Utility::HXmlNode childerNode = xmlFile.getChildNode(root);
	while (childerNode != NULL) {
		BSLib::Utility::CStringA nodeName;
		if (!xmlFile.getNodeName(childerNode, nodeName)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_PRIZESYSTEM, "获取%s文件节点失败", a_configFile.c_str());
			xmlFile.clear();
			return false;
		}
		nodeName.toLower();

		if (nodeName == "item") {
			BSLib::int32 prizeID = 0;
			SPrizeItemInfo* prizeItemList = NULL;
			if (!readPrizeNode(xmlFile, childerNode, prizeID, prizeItemList)) {
				BSLIB_LOG_ERROR(ETT_GSLIB_PRIZESYSTEM, " 读取%s文件节点值失败", a_configFile.c_str());
				xmlFile.clear();
				return false;
			}
			if (m_prizesHashMap.find(prizeID) != m_prizesHashMap.end()) {
				BSLIB_LOG_ERROR(ETT_GSLIB_PRIZESYSTEM, " 读取%s文件失败，[f_id=%d]重复", a_configFile.c_str(), prizeID);
				xmlFile.clear();
				return false;
			}
			m_prizesHashMap.setValue(prizeID, prizeItemList);
		}
		childerNode = xmlFile.getNextNode(childerNode);
	}
	xmlFile.clear();
	return true;
}


bool CPrizeConfig::getPrize(BSLib::int32 a_prizeID, SPrizeItemInfo*& a_prizeItemList)
{
	BSLib::Utility::CHashMap<BSLib::int32, SPrizeItemInfo*>::iterator it = m_prizesHashMap.find(a_prizeID);
	if (it == m_prizesHashMap.end()) {
		return false;
	}

	a_prizeItemList = it->second;
	return true;
}

}//GM

}//PrizeSystem

}//GSLib
