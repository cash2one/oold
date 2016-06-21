#ifndef __BSLIB_UTILITY_FILE_XMLFILE_H__
#define __BSLIB_UTILITY_FILE_XMLFILE_H__

#include <BSLib/utility/baseDef.h>

namespace BSLib
{

namespace Utility
{

typedef void* HXmlNode;
typedef void* HXmlAttr;

class BSLIB_UTILITY_API CXmlFile
{
public:
	CXmlFile();
	virtual ~CXmlFile();

	/// @brief �����ļ�
	/// @return bool
	/// @param fileName
	bool loadFile(const std::string& fileName);

	/// @brief �����ַ���
	/// @return bool
	/// @param xml
	bool loadString(const std::string& xml);

	/// @brief �ر�
	/// @return void
	void clear();

	/// @brief ��ȡxml���ڵ�
	/// @return BSLib::Utility::HXmlNode
	/// @param rootName
	HXmlNode getRootNode(const std::string& rootName = "");

	/// @brief ����Xml
	/// @return bool
	bool createXml();
	HXmlNode createXml(const std::string& rootName, const std::string& rootValue="", const std::string& nodePi = "xml version='1.0' encoding='utf-8'");
	HXmlNode createRootNode(const std::string& rootName, const std::string& rootValue="");
	
	/// @brief ����
	/// @return bool
	/// @param fileName
	/// @param replace
	bool save(const std::string& fileName = "", bool replace = true);

	/// @brief  ��ȡxml
	/// @return bool
	/// @param xml
	bool getXml(std::string& xml);

	/// @brief ����ӽڵ�
	/// @return bool
	/// @param nodeName
	bool appendPiNode(const std::string& nodeName);
	HXmlNode appendNode(HXmlNode node, const std::string& nodeName);
	HXmlNode appendNode(HXmlNode node, const std::string& nodeName, const std::string& nodeValue);
	HXmlNode appendNode(HXmlNode node, const std::string& nodeName, double nodeValue);
	HXmlNode appendNode(HXmlNode node, const std::string& nodeName, float nodeValue);
	HXmlNode appendNode(HXmlNode node, const std::string& nodeName, int8 nodeValue);
	HXmlNode appendNode(HXmlNode node, const std::string& nodeName, int16 nodeValue);
	HXmlNode appendNode(HXmlNode node, const std::string& nodeName, int32 nodeValue);
	HXmlNode appendNode(HXmlNode node, const std::string& nodeName, int64 nodeValue);
	
	/// @brief �������
	/// @return BSLib::Utility::HXmlAttr
	/// @param node
	/// @param attrName
	/// @param attrValue
	HXmlAttr appendAttr(HXmlNode node, const std::string& attrName, const std::string& attrValue);
	HXmlAttr appendAttr(HXmlNode node, const std::string& attrName, double attrValue);
	HXmlAttr appendAttr(HXmlNode node, const std::string& attrName, float attrValue);
	HXmlAttr appendAttr(HXmlNode node, const std::string& attrName, int8 attrValue);
	HXmlAttr appendAttr(HXmlNode node, const std::string& attrName, int16 attrValue);
	HXmlAttr appendAttr(HXmlNode node, const std::string& attrName, int32 attrValue);
	HXmlAttr appendAttr(HXmlNode node, const std::string& attrName, int64 attrValue);

	/// @brief ɾ��node�����ӽڵ�
	/// @return bool
	/// @param node
	bool removeNode(HXmlNode node);

	/// @brief ɾ��nodeָ���ӽڵ�childNode
	/// @return bool
	/// @param node
	/// @param childNode
	bool removeNode(HXmlNode node, HXmlNode childNode);

	/// @brief ɾ��node��������
	/// @return bool
	/// @param node
	bool removeAttr(HXmlNode node);

	/// @brief ɾ��nodeָ������attr
	/// @return bool
	/// @param node
	/// @param attr
	bool removeAttr(HXmlNode node, HXmlAttr attr);

public:

	/// @brief ��ȡnode�����ӽڵ�
	/// @return BSLib::Utility::HXmlNode
	/// @param node
	static HXmlNode getChildNode(HXmlNode node);

	/// @brief ��ȡnode���׸�childName�ӽڵ�
	/// @return BSLib::Utility::HXmlNode
	/// @param node
	/// @param childName
	static HXmlNode getChildNode(HXmlNode node, const std::string& childName);

	/// @brief ��ȡnode���¸��ڵ�
	/// @return BSLib::Utility::HXmlNode
	/// @param node
	static HXmlNode getNextNode(HXmlNode node);

	/// @brief ��ȡnode���¸�nextNodeName�ڵ�
	/// @return BSLib::Utility::HXmlNode
	/// @param node
	/// @param nextNodeName
	static HXmlNode getNextNode(HXmlNode node, const std::string& nextNodeName);

	/// @brief ��ȡnode��������
	/// @return BSLib::Utility::HXmlAttr
	/// @param node
	static HXmlAttr getFirstAttr(HXmlNode node);

	/// @brief ��ȡattr���¸�����
	/// @return BSLib::Utility::HXmlAttr
	/// @param attr
	static HXmlAttr getNextAttr(HXmlAttr attr);

	/// @brief ��ȡnode��attrName����
	/// @return BSLib::Utility::HXmlAttr
	/// @param node
	/// @param attrName
	static HXmlAttr getNodeAttr(HXmlNode node, const std::string& attrName);
	
	/// @brief ��ȡ�ڵ�����
	/// @return bool
	/// @param node
	/// @param valueBuff
	/// @param buffSize
	static bool getNodeName(HXmlNode node, char* valueBuff, int buffSize);
	static bool getNodeName(HXmlNode node, std::string& value);

	/// @brief ��ȡ�ڵ�����
	/// @return bool
	/// @param node
	/// @param valueBuff
	/// @param buffSize
	static bool getNodeValue(HXmlNode node, char* valueBuff, int buffSize);
	static bool getNodeValue(HXmlNode node, std::string& value);
	static bool getNodeValue(HXmlNode node, double& nodeValue);
	static bool getNodeValue(HXmlNode node, float& nodeValue);
	static bool getNodeValue(HXmlNode node, int8& nodeValue);
	static bool getNodeValue(HXmlNode node, int16& nodeValue);
	static bool getNodeValue(HXmlNode node, int32& nodeValue);
	static bool getNodeValue(HXmlNode node, int64& nodeValue);

	/// @brief ��ȡ��������
	/// @return bool
	/// @param attr
	/// @param valueBuff
	/// @param buffSize
	static bool getAttrName(HXmlAttr attr, char* valueBuff, int buffSize);
	static bool getAttrName(HXmlAttr attr, std::string& value);

	/// @brief ��ȡ����ֵ
	/// @return bool
	/// @param attr
	/// @param valueBuff
	/// @param buffSize
	static bool getAttrValue(HXmlAttr attr, char* valueBuff, int buffSize);
	static bool getAttrValue(HXmlAttr attr, std::string& value);
	static bool getAttrValue(HXmlAttr attr, double& nodeValue);
	static bool getAttrValue(HXmlAttr attr, float& nodeValue);
	static bool getAttrValue(HXmlAttr attr, int8& nodeValue);
	static bool getAttrValue(HXmlAttr attr, int16& nodeValue);
	static bool getAttrValue(HXmlAttr attr, int32& nodeValue);
	static bool getAttrValue(HXmlAttr attr, int64& nodeValue);
	
	/// @brief ��ȡnode��attrName����ֵ
	/// @return bool
	/// @param node
	/// @param attrName
	/// @param valueBuff
	/// @param buffSize
	static bool getNodeAttrValue(HXmlNode node, const std::string& attrName, char* valueBuff, int buffSize);
	static bool getNodeAttrValue(HXmlNode node, const std::string& attrName, std::string& attrValue);
	static bool getNodeAttrValue(HXmlNode node, const std::string& attrName, double& nodeValue);
	static bool getNodeAttrValue(HXmlNode node, const std::string& attrName, float& nodeValue);
	static bool getNodeAttrValue(HXmlNode node, const std::string& attrName, int8& nodeValue);
	static bool getNodeAttrValue(HXmlNode node, const std::string& attrName, int16& nodeValue);
	static bool getNodeAttrValue(HXmlNode node, const std::string& attrName, int32& nodeValue);
	static bool getNodeAttrValue(HXmlNode node, const std::string& attrName, int64& nodeValue);
	

private:
	std::string m_fileName;
	void* m_xmlDoucument;
	std::vector<char> m_xmlBuff;
};


}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_FILE_XMLFILE_H__

