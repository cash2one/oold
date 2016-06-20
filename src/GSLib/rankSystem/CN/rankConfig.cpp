#include <BSLib/utility/file/dirInfo.h>
#include <GSLib/rankSystem/CN/rankConfig.h>
#include <BSLib/utility/file/xmlFile.h>
#include <GSLib/tracer.h>
#include <algorithm>
#include <BSLib/utility/random.h>
#include <GSLib/prizeSystem/lexical.h>

namespace GSLib
{
namespace RankSystem
{
namespace CN
{

BSLIB_SINGLETON_DEFINE(CRankConfig)

CRankConfig::CRankConfig()
{

}

CRankConfig::~CRankConfig()
{

}


typedef bool (*cbReadNode)(BSLib::Utility::CXmlFile& a_xmlFile, BSLib::Utility::HXmlNode& a_Node, BSLib::int32& a_Id, void*& a_config);


bool readRankMailNode(BSLib::Utility::CXmlFile& a_xmlFile, BSLib::Utility::HXmlNode& a_Node, BSLib::int32& a_Id,
	void*& a_shopConfig)
{	

	bool success = true;
	SRankMailInfo* item = new SRankMailInfo;
	BSLib::int32 id = 0;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_id", id) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_sender", item->m_sender) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_title", item->m_title) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_content", item->m_content) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_list_size", item->m_maxSize) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_prize_size", item->m_prizeSize) && success;

	if( !success){
		BSLIB_LOG_ERROR(ETT_GSLIB_SHOPSYSTEM, "获取item属性失败, id:%d", a_Id);
		delete item;
		return false;
	}
	
	a_shopConfig = item;
	a_Id =  id;
	return true;
}


bool readRankPrizeNode(BSLib::Utility::CXmlFile& a_xmlFile, BSLib::Utility::HXmlNode& a_Node, BSLib::int32& a_Id,
					  void*& a_shopConfig)
{	

	bool success = true;
	SRankPosInfo* item = new SRankPosInfo;
	BSLib::int32 id = 0;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_id", id) && success;
	std::string pos;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_pos", pos) && success;
	std::string prize;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_prize", prize) && success;
	do 
	{
		if(!success)
			break;
		
		success = false; // 默认为false;

		if(pos.empty() || "0" == pos)
			break;

		if(prize.empty() || "0" == prize)
			break;
		
		std::vector<BSLib::int32> sub_pos;
		if( !GSLib::PrizeSystem::lexicalCast(pos, sub_pos, "_"))
			break;

		if(sub_pos.empty())
			break;

		if( 1 == sub_pos.size())
		{
			item->m_posStart = sub_pos[0];
			item->m_posEnd = sub_pos[0];
		}
		else
		{
			item->m_posStart = sub_pos[0];
			item->m_posEnd = sub_pos[1];
		}

		std::vector<std::string> sub_prize;
		if( !GSLib::PrizeSystem::lexicalCast(prize, sub_prize, "|"))
			break;

		if(sub_prize.empty())
			break;

		for(std::vector<std::string>::size_type i = 0; i < sub_prize.size(); i++)
		{
			std::vector<BSLib::int32> prizePair;
			if(!GSLib::PrizeSystem::lexicalCast(sub_prize[i], prizePair, "_"))
				goto exit;

			if( 2 != prizePair.size())
				goto exit;

			item->m_ids.push_back(prizePair[0]);
			item->m_nums.push_back(prizePair[1]);
		}

		success = true;
	} while (false);

exit:

	if( !success){
		BSLIB_LOG_ERROR(ETT_GSLIB_SHOPSYSTEM, "获取item属性失败, id:%d", a_Id);
		delete item;
		return false;
	}

	a_shopConfig = item;
	a_Id =  id;
	return true;
}

template<class T>
bool loadXml(const std::string& a_path, std::map<BSLib::int32, T* >& container, cbReadNode a_cb)
{
	BSLib::Utility::CXmlFile xmlFile;

	if (!xmlFile.loadFile(a_path)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SHOPSYSTEM, "读取%s文件失败", a_path.c_str());
		return false;
	}
	BSLib::Utility::HXmlNode root = xmlFile.getRootNode();
	if (root == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SHOPSYSTEM, "获取%s文件根节点失败", a_path.c_str());
		return false;
	}
	BSLib::Utility::HXmlNode childerNode = xmlFile.getChildNode(root);
	bool success = true;
	for(; childerNode != NULL; childerNode = xmlFile.getNextNode(childerNode)) 
	{
		BSLib::Utility::CStringA nodeName;
		if (!xmlFile.getNodeName(childerNode, nodeName)) {
			success = false;
			break;
		}

		nodeName.toLower();
		if (nodeName != "item") {
			success = false;
			break;
		}

		BSLib::int32 id = 0;
		T* node = NULL;
		if (!(*a_cb)(xmlFile, childerNode, id, (void *&)node)) {
			success = false;
			break;
		}

		if (container.find(id) != container.end()) {
			success = false;
			break;
		}

		container.insert(std::make_pair(id, node));
	}

	if( !success){
		BSLIB_LOG_ERROR(ETT_GSLIB_SHOPSYSTEM, " 读取%s文件节点值失败", a_path.c_str());
	}

	xmlFile.clear();
	return success;
}


template<class T>
bool loadXml(const std::string& a_path, std::map<BSLib::int32, std::vector< T* > >& container, cbReadNode a_cb)
{
	BSLib::Utility::CXmlFile xmlFile;

	if (!xmlFile.loadFile(a_path)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SHOPSYSTEM, "读取%s文件失败", a_path.c_str());
		return false;
	}
	BSLib::Utility::HXmlNode root = xmlFile.getRootNode();
	if (root == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SHOPSYSTEM, "获取%s文件根节点失败", a_path.c_str());
		return false;
	}
	BSLib::Utility::HXmlNode childerNode = xmlFile.getChildNode(root);
	bool success = true;
	for(; childerNode != NULL; childerNode = xmlFile.getNextNode(childerNode)) 
	{
		BSLib::Utility::CStringA nodeName;
		if (!xmlFile.getNodeName(childerNode, nodeName)) {
			success = false;
			break;
		}

		nodeName.toLower();
		if (nodeName != "item") {
			success = false;
			break;
		}

		BSLib::int32 id = 0;
		T* node = NULL;
		if (!(*a_cb)(xmlFile, childerNode, id, (void *&)node)) {
			success = false;
			break;
		}
		
		typename std::map<BSLib::int32, std::vector< T* > >::iterator it = container.find(id);
		if (it != container.end()) {
			it->second.push_back(node);
		}
		else
		{
			container.insert(std::make_pair(id, std::vector< T* >()));	
			it = container.find(id);
			it->second.push_back(node);
		}
	}

	if( !success){
		BSLIB_LOG_ERROR(ETT_GSLIB_SHOPSYSTEM, " 读取%s文件节点值失败", a_path.c_str());
	}

	xmlFile.clear();
	return success;
}


bool CRankConfig::loadConfigFile(const std::string& a_configFile)
{	
	std::string mailPath(a_configFile);
	mailPath +="\\rank\\t_rank_cfg.xml";
	BSLib::Utility::CDirInfo::standardization(mailPath);
	if( !loadXml(mailPath, m_rankMailHashMap, readRankMailNode)){
		return false;
	}
	
	std::string prizePath(a_configFile);
	prizePath += "\\rank\\t_rank_prize.xml";
	BSLib::Utility::CDirInfo::standardization(prizePath);
	if( !loadXml(prizePath, m_rankItemsHashMap, readRankPrizeNode))
		return false;

	return true;
}


bool CRankConfig::getRankPrize(BSLib::int32 a_rankId, BSLib::int32 a_pos, SRankPosInfo*& a_Item)
{	
	typedef std::map<BSLib::int32, std::vector<SRankPosInfo*> > RankMap; 
	RankMap::iterator it = m_rankItemsHashMap.find(a_rankId);
	if( it == m_rankItemsHashMap.end())
		return false;

	std::vector<SRankPosInfo*>& v = it->second;
	for(std::vector<SRankPosInfo*>::iterator posIt = v.begin(); posIt != v.end(); ++posIt)
	{
		SRankPosInfo* info = *posIt;
		if( info->m_posStart >= a_pos &&  info->m_posEnd <= a_pos)
		{
			a_Item = info;
			return true;
		}
	}

	return false;
}

bool CRankConfig::getRankMail(BSLib::int32 a_rankId, SRankMailInfo*& a_rankConfig)
{	
	typedef std::map<BSLib::int32, SRankMailInfo* > ConfigMap;
	ConfigMap::iterator it = m_rankMailHashMap.find(a_rankId);
	if( it == m_rankMailHashMap.end())
		return false;

	a_rankConfig = it->second;
	return true;
}


} // CN
} // RankSystem
} // GSLib