/********************************************************************
	created:	2011/07/24
	filename:	src\BSSrc\src\utility\io\xmlFile.cpp
	author:		mazhejiang
	
	purpose:	
*********************************************************************/
#include <fstream>
#include <BSLib/utility/string.h>
#include <BSLib/utility/file/xmlFile.h>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_print.hpp>

namespace rapidxml
{

#ifndef RAPIDXML_NO_STREAMS

template<> 
inline std::basic_ostream<wchar_t> &print(std::basic_ostream<wchar_t> &out, const xml_node<wchar_t> &node, int flags)
{
	print(std::ostream_iterator<wchar_t, wchar_t>(out), node, flags);
	return out;
}

#endif

}//rapidxml

namespace BSLib
{

namespace Utility
{

CXmlFile::CXmlFile()
: m_xmlDoucument(NULL)
{
	;
}

CXmlFile::~CXmlFile()
{
	clear();
}

bool CXmlFile::loadFile(const std::string& fileName)
{
	if (m_xmlDoucument != NULL){
		return false;
	}
	rapidxml::xml_document<>* xmlDoc = NULL;
	try {
		std::basic_ifstream<char> stream(fileName.c_str(), std::ios::binary);
		if (!stream){
			return false;
		}
		stream.unsetf(std::ios::skipws);

		stream.seekg(0, std::ios::end);
		size_t size = stream.tellg();
		stream.seekg(0);   
		m_xmlBuff.resize(size + 1);
		stream.read(&m_xmlBuff.front(), static_cast<std::streamsize>(size));
		m_xmlBuff[size] = 0;

		xmlDoc = new rapidxml::xml_document<>();
		if (xmlDoc == NULL)	{
			stream.close();
			return false;
		}
		xmlDoc->parse<0>(&m_xmlBuff.front());
		stream.close();
	} catch (...) {
		if (xmlDoc != NULL){
			delete xmlDoc;
			xmlDoc = NULL;
		}
		m_xmlBuff.clear();
	}
	if (xmlDoc == NULL){
		return false;
	}
	m_xmlDoucument = xmlDoc;
	m_fileName = fileName;
	return true;
}

bool CXmlFile::loadString(const std::string& xml)
{
	if (m_xmlDoucument != NULL){
		return false;
	}
	rapidxml::xml_document<>* xmlDoc = NULL;
	try {
		m_xmlBuff.resize(xml.size() + 1);
		memcpy(&m_xmlBuff.front(), xml.c_str(), xml.size());
		m_xmlBuff.push_back(0);

		xmlDoc = new rapidxml::xml_document<>();
		if (xmlDoc == NULL)	{
			return false;
		}
		xmlDoc->parse<0>(&m_xmlBuff.front());
	} catch (...) {
		if (xmlDoc != NULL){
			delete xmlDoc;
			xmlDoc = NULL;
		}
	}
	if (xmlDoc == NULL){
		return false;
	}
	m_xmlDoucument = xmlDoc;
	m_fileName = "";
	return true;
}

void CXmlFile::clear()
{
	rapidxml::xml_document<>* xmlDoc = (rapidxml::xml_document<>*)m_xmlDoucument;
	if (xmlDoc == NULL){
		return ;
	}
	try {
		xmlDoc->clear();
		delete xmlDoc;
		m_xmlDoucument = NULL;
	} catch (...) {
	}
	m_xmlBuff.clear();
}

HXmlNode CXmlFile::getRootNode(const std::string& rootName)
{
	if (m_xmlDoucument == NULL){
		return NULL;
	}
	rapidxml::xml_node<>* root = NULL;
	rapidxml::xml_document<>* xmlDoc = (rapidxml::xml_document<>*)m_xmlDoucument;
	root = xmlDoc->first_node();
	while (root != NULL) {
		if (root->type() == rapidxml::node_element) {
			break;
		}
		root = root->next_sibling();
	}

	if (rootName.empty() || rootName == "") {
		return root;
	}
	if (rootName != root->name()) {
		return NULL;
	}
	return root;
}

bool CXmlFile::createXml()
{
	rapidxml::xml_document<>* xmlDoc = (rapidxml::xml_document<>*)m_xmlDoucument;
	if (xmlDoc != NULL){
		return false;
	}
	xmlDoc = new rapidxml::xml_document<>();
	if (xmlDoc == NULL)	{
		return false;
	}
	m_xmlDoucument = xmlDoc;
	return true;
}

HXmlNode CXmlFile::createXml(const std::string& rootName, const std::string& rootValue, const std::string& nodePi)
{
	rapidxml::xml_document<>* xmlDoc = (rapidxml::xml_document<>*)m_xmlDoucument;
	if (xmlDoc != NULL){
		return NULL;
	}
	xmlDoc = new rapidxml::xml_document<>();
	if (xmlDoc == NULL)	{
		return NULL;
	}
	m_xmlDoucument = xmlDoc;
	rapidxml::xml_node<>* rootNode = NULL;
	try {
		rapidxml::xml_node<>* rot = xmlDoc->allocate_node(rapidxml::node_pi, xmlDoc->allocate_string(nodePi.c_str()));
		if (rot == NULL){
			return NULL;
		}
		xmlDoc->append_node(rot);
		rootNode = xmlDoc->allocate_node(rapidxml::node_element, xmlDoc->allocate_string(rootName.c_str()), xmlDoc->allocate_string(rootValue.c_str())); 
		if (rootNode == NULL){
			return NULL;
		}
		xmlDoc->append_node(rootNode);
	} catch (...){
		rootNode = NULL;
	}
	return rootNode;
}

HXmlNode CXmlFile::createRootNode(const std::string& rootName, const std::string& rootValue)
{
	rapidxml::xml_document<>* xmlDoc = (rapidxml::xml_document<>*)m_xmlDoucument;
	if (xmlDoc == NULL){
		return NULL;
	}
	if (getRootNode() != NULL){
		return NULL;
	}
	rapidxml::xml_node<>* rootNode = NULL;
	try {
		rootNode = xmlDoc->allocate_node(rapidxml::node_element, xmlDoc->allocate_string(rootName.c_str()), xmlDoc->allocate_string(rootValue.c_str())); 
		if (rootNode == NULL){
			return NULL;
		}
		xmlDoc->append_node(rootNode);
	} catch (...){
		rootNode = NULL;
	}
	return rootNode;
}

bool CXmlFile::save(const std::string& fileName, bool replace)
{
	std::string file;
	if (m_xmlDoucument == NULL){
		return false;
	}
	if (fileName.empty()){
		if (m_fileName.empty()){
			return false;
		}
		file = m_fileName;
	} else {
		file = fileName;
	}

	rapidxml::xml_document<>* xmlDoc = (rapidxml::xml_document<>*)m_xmlDoucument;
	std::ios_base::openmode mode;
	
#ifdef __GNUC__

	mode = std::ios_base::in;
	try {
		std::ofstream outTo(file.c_str(), mode);
		if (outTo.is_open()) {
			if (!replace) {
				return false;
			}
			outTo.close();
		} 
		mode = std::ios_base::out;
		outTo.open(file.c_str(), mode);
		if (!outTo.is_open()) {
			return false;
		}
		outTo << (*xmlDoc);
		m_fileName = file;
		return true;
	} catch (...){
	}

#else

	mode = std::ios_base::out;
	if (!replace){
		mode |= std::ios_base::_Noreplace;
	}
	try {
		std::ofstream outTo(file.c_str(), mode);
		if (!outTo.is_open()) {
			return false;
		}
		outTo << (*xmlDoc);
		m_fileName = file;
		return true;
	} catch (...){
	}

#endif
		
	
	return false;
}

bool CXmlFile::getXml(std::string& xml)
{
	rapidxml::xml_document<>* xmlDoc = (rapidxml::xml_document<>*)m_xmlDoucument;
	if (xmlDoc == NULL){
		return false;
	}
	try {
		rapidxml::print(std::back_inserter(xml), *xmlDoc);
		return true;
	} catch (...){
	}
	return false;
}

bool CXmlFile::appendPiNode(const std::string& nodeName)
{
	rapidxml::xml_document<>* xmlDoc = (rapidxml::xml_document<>*)m_xmlDoucument;
	if (xmlDoc == NULL){
		return false;
	}
	rapidxml::xml_node<>* rotNode = NULL;
	try {
		rapidxml::xml_node<>* rot = xmlDoc->allocate_node(rapidxml::node_pi, xmlDoc->allocate_string(nodeName.c_str()));
		if (rot == NULL){
			return false;
		}
		xmlDoc->append_node(rot);
	} catch (...){
		if (rotNode != NULL){
			rotNode = NULL;
		}
	}
	return rotNode != NULL;
}

HXmlNode CXmlFile::appendNode(HXmlNode node, const std::string& nodeName)
{
	rapidxml::xml_document<>* xmlDoc = (rapidxml::xml_document<>*)m_xmlDoucument;
	if (xmlDoc == NULL){
		return NULL;
	}
	rapidxml::xml_node<>* xmlNode = (rapidxml::xml_node<>*)node;
	if (xmlNode == NULL){
		return NULL;
	}
	rapidxml::xml_node<>* newXmlNode = NULL;
	try {
		newXmlNode = xmlDoc->allocate_node(rapidxml::node_element, xmlDoc->allocate_string(nodeName.c_str()), NULL);
		if (newXmlNode == NULL){
			return NULL;
		}
		xmlNode->append_node(newXmlNode);
	} catch (...){
		if (newXmlNode != NULL){
			newXmlNode = NULL;
		}
	}
	return newXmlNode;
}

HXmlNode CXmlFile::appendNode(HXmlNode node, const std::string& nodeName, const std::string& nodeValue)
{
	rapidxml::xml_document<>* xmlDoc = (rapidxml::xml_document<>*)m_xmlDoucument;
	if (xmlDoc == NULL){
		return NULL;
	}
	rapidxml::xml_node<>* xmlNode = (rapidxml::xml_node<>*)node;
	if (xmlNode == NULL){
		return NULL;
	}
	rapidxml::xml_node<>* newXmlNode = NULL;
	try {
		newXmlNode = xmlDoc->allocate_node(rapidxml::node_element, xmlDoc->allocate_string(nodeName.c_str()), xmlDoc->allocate_string(nodeValue.c_str()));
		if (newXmlNode == NULL){
			return NULL;
		}
		xmlNode->append_node(newXmlNode);
	} catch (...){
		if (newXmlNode != NULL){
			newXmlNode = NULL;
		}
	}
	return newXmlNode;
}

HXmlNode CXmlFile::appendNode(HXmlNode node, const std::string& nodeName, double nodeValue)
{
	CStringA nodeValueStr(nodeValue);
	return appendNode(node, nodeName, nodeValueStr);
}

HXmlNode CXmlFile::appendNode(HXmlNode node, const std::string& nodeName, float nodeValue)
{
	CStringA nodeValueStr(nodeValue);
	return appendNode(node, nodeName, nodeValueStr);
}

HXmlNode CXmlFile::appendNode(HXmlNode node, const std::string& nodeName, int8 nodeValue)
{
	CStringA nodeValueStr(nodeValue);
	return appendNode(node, nodeName, nodeValueStr);
}

HXmlNode CXmlFile::appendNode(HXmlNode node, const std::string& nodeName, int16 nodeValue)
{
	CStringA nodeValueStr(nodeValue);
	return appendNode(node, nodeName, nodeValueStr);
}

HXmlNode CXmlFile::appendNode(HXmlNode node, const std::string& nodeName, int32 nodeValue)
{
	CStringA nodeValueStr(nodeValue);
	return appendNode(node, nodeName, nodeValueStr);
}

HXmlNode CXmlFile::appendNode(HXmlNode node, const std::string& nodeName, int64 nodeValue)
{
	CStringA nodeValueStr(nodeValue);
	return appendNode(node, nodeName, nodeValueStr);
}

HXmlAttr CXmlFile::appendAttr(HXmlNode node, const std::string& attrName, const std::string& attrValue)
{
	rapidxml::xml_document<>* xmlDoc = (rapidxml::xml_document<>*)m_xmlDoucument;
	if (xmlDoc == NULL){
		return NULL;
	}
	rapidxml::xml_node<>* xmlNode = (rapidxml::xml_node<>*)node;
	if (xmlNode == NULL){
		return NULL;
	}
	rapidxml::xml_attribute<>* newXmlAttr = NULL;
	try {
		newXmlAttr = xmlDoc->allocate_attribute(xmlDoc->allocate_string(attrName.c_str()), xmlDoc->allocate_string(attrValue.c_str()));
		if (newXmlAttr == NULL){
			return NULL;
		}
		xmlNode->append_attribute(newXmlAttr);
	} catch (...){
		if (newXmlAttr != NULL){
			newXmlAttr = NULL;
		}
	}
	return newXmlAttr;
}

HXmlAttr CXmlFile::appendAttr(HXmlNode node, const std::string& attrName, double attrValue)
{
	CStringA addrValueStr(attrValue);
	return appendAttr(node, attrName, addrValueStr);
}

HXmlAttr CXmlFile::appendAttr(HXmlNode node, const std::string& attrName, float attrValue)
{
	CStringA addrValueStr(attrValue);
	return appendAttr(node, attrName, addrValueStr);
}

HXmlAttr CXmlFile::appendAttr(HXmlNode node, const std::string& attrName, int8 attrValue)
{
	CStringA addrValueStr(attrValue);
	return appendAttr(node, attrName, addrValueStr);
}

HXmlAttr CXmlFile::appendAttr(HXmlNode node, const std::string& attrName, int16 attrValue)
{
	CStringA addrValueStr(attrValue);
	return appendAttr(node, attrName, addrValueStr);
}

HXmlAttr CXmlFile::appendAttr(HXmlNode node, const std::string& attrName, int32 attrValue)
{
	CStringA addrValueStr(attrValue);
	return appendAttr(node, attrName, addrValueStr);
}

HXmlAttr CXmlFile::appendAttr(HXmlNode node, const std::string& attrName, int64 attrValue)
{
	CStringA addrValueStr(attrValue);
	return appendAttr(node, attrName, addrValueStr);
}

bool CXmlFile::removeNode(HXmlNode node)
{
	rapidxml::xml_node<>* xmlNode = (rapidxml::xml_node<>*)node;
	if (xmlNode == NULL){
		return false;
	}
	xmlNode->remove_all_nodes();
	return true;
}

bool CXmlFile::removeNode(HXmlNode node, HXmlNode childNode)
{
	rapidxml::xml_node<>* xmlNode = (rapidxml::xml_node<>*)node;
	if (xmlNode == NULL){
		return false;
	}
	rapidxml::xml_node<>* xmlChildNode = (rapidxml::xml_node<>*)childNode;
	if (xmlChildNode == NULL){
		return false;
	}
	xmlNode->remove_node(xmlChildNode);
	return true;
}

bool CXmlFile::removeAttr(HXmlNode node)
{
	rapidxml::xml_node<>* xmlNode = (rapidxml::xml_node<>*)node;
	if (xmlNode == NULL){
		return false;
	}
	xmlNode->remove_all_attributes();
	return true;
}

bool CXmlFile::removeAttr(HXmlNode node, HXmlAttr attr)
{
	rapidxml::xml_node<>* xmlNode = (rapidxml::xml_node<>*)node;
	if (xmlNode == NULL){
		return false;
	}
	rapidxml::xml_attribute<>* xmlAttr = (rapidxml::xml_attribute<>*)attr;
	if (xmlAttr == NULL){
		return false;
	}
	xmlNode->remove_attribute(xmlAttr);
	return true;
}

HXmlNode CXmlFile::getChildNode(HXmlNode node)
{
	rapidxml::xml_node<>* xmlNode = (rapidxml::xml_node<>*)node;
	if (xmlNode == NULL){
		return NULL;
	}

	rapidxml::xml_node<>* xmlChileNode = NULL;
	xmlChileNode = xmlNode->first_node();
	return xmlChileNode;
}

HXmlNode CXmlFile::getChildNode(HXmlNode node, const std::string& nodeName)
{
	rapidxml::xml_node<>* xmlNode = (rapidxml::xml_node<>*)node;
	if (xmlNode == NULL){
		return NULL;
	}

	rapidxml::xml_node<>* xmlChileNode = NULL;
	try {
		xmlChileNode = xmlNode->first_node(nodeName.c_str(), nodeName.size());
	}
	catch (...){
		return NULL;
	}
	return xmlChileNode;
}

HXmlNode CXmlFile::getNextNode(HXmlNode node)
{
	rapidxml::xml_node<>* xmlNode = (rapidxml::xml_node<>*)node;
	if (xmlNode == NULL){
		return NULL;
	}

	rapidxml::xml_node<>* xmlNextNode = NULL;
	xmlNextNode = xmlNode->next_sibling();
	return xmlNextNode;
}

HXmlNode CXmlFile::getNextNode(HXmlNode node, const std::string& nodeName)
{
	rapidxml::xml_node<>* xmlNode = (rapidxml::xml_node<>*)node;
	if (xmlNode == NULL){
		return NULL;
	}

	rapidxml::xml_node<>* xmlNextNode = NULL;
	try {
		xmlNextNode = xmlNode->next_sibling(nodeName.c_str(), nodeName.size());
	}
	catch (...){
		return NULL;
	}
	return xmlNextNode;
}

HXmlAttr CXmlFile::getFirstAttr(HXmlNode node)
{
	rapidxml::xml_node<>* xmlNode = (rapidxml::xml_node<>*)node;
	if (xmlNode == NULL){
		return NULL;
	}

	rapidxml::xml_attribute<>* xmlFirstAttr = NULL;
	xmlFirstAttr = xmlNode->first_attribute();
	return xmlFirstAttr;
}

HXmlAttr CXmlFile::getNextAttr(HXmlAttr attr)
{
	rapidxml::xml_attribute<>* xmlAttr = (rapidxml::xml_attribute<>*)attr;
	if (xmlAttr == NULL){
		return NULL;
	}

	rapidxml::xml_attribute<>* xmlNextAttr = NULL;
	xmlNextAttr = xmlAttr->next_attribute();
	return xmlNextAttr;
}

HXmlAttr CXmlFile::getNodeAttr(HXmlNode node, const std::string& attrName)
{
	rapidxml::xml_node<>* xmlNode = (rapidxml::xml_node<>*)node;
	if (xmlNode == NULL){
		return NULL;
	}

	rapidxml::xml_attribute<>* xmlFirstAttr = NULL;
	try {
		xmlFirstAttr = xmlNode->first_attribute(attrName.c_str(), attrName.size());
	}
	catch (...){
		return NULL;
	}
	return xmlFirstAttr;
}

bool CXmlFile::getNodeName(HXmlNode node, char* valueBuff, int buffSize)
{
	rapidxml::xml_node<>* xmlNode = (rapidxml::xml_node<>*)node;
	if (xmlNode == NULL){
		return false;
	}
	xmlNode->name(valueBuff, buffSize);
	return true;
}

bool CXmlFile::getNodeName(HXmlNode node, std::string& value)
{
	rapidxml::xml_node<>* xmlNode = (rapidxml::xml_node<>*)node;
	if (xmlNode == NULL){
		return false;
	}
	try {
		value = xmlNode->name();
	}
	catch (...){
		return false;
	}
	return true;
}

bool CXmlFile::getNodeValue(HXmlNode node, char* valueBuff, int buffSize)
{
	rapidxml::xml_node<>* xmlNode = (rapidxml::xml_node<>*)node;
	if (xmlNode == NULL){
		return false;
	}
	xmlNode->value(valueBuff, buffSize);
	return true;
}

bool CXmlFile::getNodeValue(HXmlNode node, std::string& value)
{
	rapidxml::xml_node<>* xmlNode = (rapidxml::xml_node<>*)node;
	if (xmlNode == NULL){
		return false;
	}
	try {
		value = xmlNode->value();
	}
	catch (...){
		return false;
	}
	return true;
}

bool CXmlFile::getNodeValue(HXmlNode node, double& nodeValue)
{
	std::string nodeValueStr;
	if (!getNodeValue(node, nodeValueStr)){
		return false;
	}
	if (nodeValueStr.empty() || nodeValueStr == ""){
		return false;
	}
	
	nodeValue = (double)atof(nodeValueStr.c_str());
	return true;
}
bool CXmlFile::getNodeValue(HXmlNode node, float& nodeValue)
{
	std::string nodeValueStr;
	if (!getNodeValue(node, nodeValueStr)){
		return false;
	}
	if (nodeValueStr.empty() || nodeValueStr == ""){
		return false;
	}
	nodeValue = (float)atof(nodeValueStr.c_str());
	return true;
}

bool CXmlFile::getNodeValue(HXmlNode node, int8& nodeValue)
{
	std::string nodeValueStr;
	if (!getNodeValue(node, nodeValueStr)){
		return false;
	}
	if (nodeValueStr.empty() || nodeValueStr == ""){
		return false;
	}
	nodeValue = (int8)atoi(nodeValueStr.c_str());
	return true;
}

bool CXmlFile::getNodeValue(HXmlNode node, int16& nodeValue)
{
	std::string nodeValueStr;
	if (!getNodeValue(node, nodeValueStr)){
		return false;
	}
	if (nodeValueStr.empty() || nodeValueStr == ""){
		return false;
	}
	nodeValue = (int16)atoi(nodeValueStr.c_str());
	return true;
}

bool CXmlFile::getNodeValue(HXmlNode node, int32& nodeValue)
{
	std::string nodeValueStr;
	if (!getNodeValue(node, nodeValueStr)){
		return false;
	}
	if (nodeValueStr.empty() || nodeValueStr == ""){
		return false;
	}
	nodeValue = (int32)atoi(nodeValueStr.c_str());
	return true;
}

bool CXmlFile::getNodeValue(HXmlNode node, int64& nodeValue)
{
	std::string nodeValueStr;
	if (!getNodeValue(node, nodeValueStr)){
		return false;
	}
	if (nodeValueStr.empty() || nodeValueStr == ""){
		return false;
	}
	nodeValue = (int64)atol(nodeValueStr.c_str());
	return true;
}

bool CXmlFile::getAttrName(HXmlAttr attr, char* valueBuff, int buffSize)
{
	rapidxml::xml_attribute<>* xmlAttribute = (rapidxml::xml_attribute<>*)attr;
	if (xmlAttribute == NULL){
		return false;
	}
	xmlAttribute->name(valueBuff, buffSize);
	return true;
}

bool CXmlFile::getAttrName(HXmlAttr attr, std::string& value)
{
	rapidxml::xml_attribute<>* xmlAttribute = (rapidxml::xml_attribute<>*)attr;
	if (xmlAttribute == NULL){
		return false;
	}
	try {
		value = xmlAttribute->name();
	}
	catch (...){
		return false;
	}
	return true;
}

bool CXmlFile::getAttrValue(HXmlAttr attr, char* valueBuff, int buffSize)
{
	rapidxml::xml_attribute<>* xmlAttribute = (rapidxml::xml_attribute<>*)attr;
	if (xmlAttribute == NULL){
		return false;
	}
	xmlAttribute->value(valueBuff, buffSize);
	return true;
}

bool CXmlFile::getAttrValue(HXmlAttr attr, std::string& value)
{
	rapidxml::xml_attribute<>* xmlAttribute = (rapidxml::xml_attribute<>*)attr;
	if (xmlAttribute == NULL){
		return false;
	}
	try {
		value = xmlAttribute->value();
	}
	catch (...){
		return false;
	}
	return true;
}

bool CXmlFile::getAttrValue(HXmlAttr attr, double& nodeValue)
{
	std::string attrValueStr;
	if (!getAttrValue(attr, attrValueStr)){
		return false;
	}
	if (attrValueStr.empty() || attrValueStr == ""){
		return false;
	}
	nodeValue= (double)atof(attrValueStr.c_str());
	return true;
}

bool CXmlFile::getAttrValue(HXmlAttr attr, float& nodeValue)
{
	std::string attrValueStr;
	if (!getAttrValue(attr, attrValueStr)){
		return false;
	}
	if (attrValueStr.empty() || attrValueStr == ""){
		return false;
	}
	nodeValue= (float)atof(attrValueStr.c_str());
	return true;
}

bool CXmlFile::getAttrValue(HXmlAttr attr, int8& nodeValue)
{
	std::string attrValueStr;
	if (!getAttrValue(attr, attrValueStr)){
		return false;
	}
	if (attrValueStr.empty() || attrValueStr == ""){
		return false;
	}
	nodeValue= (int8)atoi(attrValueStr.c_str());
	return true;
}

bool CXmlFile::getAttrValue(HXmlAttr attr, int16& nodeValue)
{
	std::string nodeValueStr;
	if (!getAttrValue(attr, nodeValueStr)){
		return false;
	}
	if (nodeValueStr.empty() || nodeValueStr == ""){
		return false;
	}
	nodeValue= (int16)atoi(nodeValueStr.c_str());
	return true;
}

bool CXmlFile::getAttrValue(HXmlAttr attr, int32& nodeValue)
{
	std::string nodeValueStr;
	if (!getAttrValue(attr, nodeValueStr)){
		return false;
	}
	if (nodeValueStr.empty() || nodeValueStr == ""){
		return false;
	}
	nodeValue= (int32)atoi(nodeValueStr.c_str());
	return true;
}

bool CXmlFile::getAttrValue(HXmlAttr attr, int64& nodeValue)
{
	std::string nodeValueStr;
	if (!getAttrValue(attr, nodeValueStr)){
		return false;
	}
	if (nodeValueStr.empty() || nodeValueStr == ""){
		return false;
	}
	nodeValue= (int64)atol(nodeValueStr.c_str());
	return true;
}

bool CXmlFile::getNodeAttrValue(HXmlNode node, const std::string& attrName, char* valueBuff, int buffSize)
{
	rapidxml::xml_node<>* xmlNode = (rapidxml::xml_node<>*)node;
	if (xmlNode == NULL){
		return false;
	}

	rapidxml::xml_attribute<>* xmlFirstAttr = NULL;
	try {
		xmlFirstAttr = xmlNode->first_attribute(attrName.c_str(), attrName.size());
		if (xmlFirstAttr == NULL){
			return false;
		}
		xmlFirstAttr->value(valueBuff, buffSize);
	}
	catch (...){
		return false;
	}
	return true;
}

bool CXmlFile::getNodeAttrValue(HXmlNode node, const std::string& attrName, std::string& attrValue)
{
	rapidxml::xml_node<>* xmlNode = (rapidxml::xml_node<>*)node;
	if (xmlNode == NULL){
		return false;
	}

	rapidxml::xml_attribute<>* xmlFirstAttr = NULL;
	try {
		xmlFirstAttr = xmlNode->first_attribute(attrName.c_str(), attrName.size());
		if (xmlFirstAttr == NULL){
			return false;
		}
		attrValue = xmlFirstAttr->value();
	}
	catch (...){
		return false;
	}
	return true;
}

bool CXmlFile::getNodeAttrValue(HXmlNode node, const std::string& attrName, int8& nodeValue)
{
	std::string attrValueStr;
	if (!getNodeAttrValue(node, attrName, attrValueStr)){
		return false;
	}
	if (attrValueStr.empty() || attrValueStr == ""){
		return false;
	}
	nodeValue= (int8)atoi(attrValueStr.c_str());
	return true;
}

bool CXmlFile::getNodeAttrValue(HXmlNode node, const std::string& attrName, double& nodeValue)
{
	std::string attrValueStr;
	if (!getNodeAttrValue(node, attrName, attrValueStr)){
		return false;
	}
	if (attrValueStr.empty() || attrValueStr == ""){
		return false;
	}
	nodeValue= (double)atof(attrValueStr.c_str());
	return true;
}

bool CXmlFile::getNodeAttrValue(HXmlNode node, const std::string& attrName, float& nodeValue)
{
	std::string attrValueStr;
	if (!getNodeAttrValue(node, attrName, attrValueStr)){
		return false;
	}
	if (attrValueStr.empty() || attrValueStr == ""){
		return false;
	}
	nodeValue= (float)atof(attrValueStr.c_str());
	return true;
}

bool CXmlFile::getNodeAttrValue(HXmlNode node, const std::string& attrName, int16& nodeValue)
{
	std::string attrValueStr;
	if (!getNodeAttrValue(node, attrName, attrValueStr)){
		return false;
	}
	if (attrValueStr.empty() || attrValueStr == ""){
		return false;
	}
	nodeValue= (int16)atoi(attrValueStr.c_str());
	return true;
}

bool CXmlFile::getNodeAttrValue(HXmlNode node, const std::string& attrName, int32& nodeValue)
{
	std::string attrValueStr;
	if (!getNodeAttrValue(node, attrName, attrValueStr)){
		return false;
	}
	if (attrValueStr.empty() || attrValueStr == ""){
		return false;
	}
	nodeValue= (int32)atoi(attrValueStr.c_str());
	return true;
}

bool CXmlFile::getNodeAttrValue(HXmlNode node, const std::string& attrName, int64& nodeValue)
{
	std::string attrValueStr;
	if (!getNodeAttrValue(node, attrName, attrValueStr)){
		return false;
	}
	if (attrValueStr.empty() || attrValueStr == ""){
		return false;
	}
	nodeValue= (int64)atol(attrValueStr.c_str());
	return true;
}

}//Utility

}//BSLib
