#include <GSLib/petSystem/GM/hotSpringTask.h>
#include <GSLib/tracer.h>

namespace GSLib
{

namespace PetSystem
{	

namespace GM
{

CHotSpringTask::CHotSpringTask()
{
    m_petTPID = 0;
    m_taskType = EHotSpringTaskTypeInvalid;
    m_minFriendlyLevel = 0;
    m_maxFriendlyLevel = 0;
    m_minFriendlyValue = 0;
    m_maxFriendlyValue = 0;
    m_friendlyA = 0;
    m_friendlyB = 0;
    m_itemID = 0;
    m_weight = 0;
    m_answerArray.clear();
    m_endArray.clear();
}

CHotSpringTask::~CHotSpringTask()
{
}

bool CHotSpringTask::isInRange(BSLib::uint32 a_curLevel,BSLib::uint32 a_curFriendlyValue) const
{
    if(a_curLevel < m_minFriendlyLevel){
        return false;
    }
    if(a_curLevel > m_maxFriendlyLevel){
        return false;
    }
    if ((a_curLevel == m_minFriendlyLevel)&&(a_curFriendlyValue < m_minFriendlyValue)){
        return false;
    }
    if((a_curLevel == m_maxFriendlyLevel)&&(a_curFriendlyValue > m_maxFriendlyValue)){
        return false;
    }
    return true;
}

BSLib::uint32 CHotSpringTask::getTaskID() const
{
    return m_taskID;
}

PetID CHotSpringTask::getPetTPID() const
{
    return m_petTPID;
}

EHotSpringTaskStatus CHotSpringTask::getType() const
{
    return m_type;
}

EHotSpringTaskType CHotSpringTask::getHotSpringTaskSubType() const
{
    return m_taskType;
}


BSLib::uint32 CHotSpringTask::getMinFriendlyLevel() const
{
    return m_minFriendlyLevel;
}

BSLib::uint32 CHotSpringTask::getMinFriendlyValue() const
{
    return m_minFriendlyValue;
}

BSLib::uint32 CHotSpringTask::getAnswerFriendlyValue(BSLib::uint32 a_answerID) const
{
    BSLib::uint32 totalFriendlyValue = m_talkQuestion.getFriendlyValue();
    const BSLib::uint32 size = m_answerArray.size();
	if(a_answerID >= size){
		return totalFriendlyValue;
	}
	const BSLib::uint32 answerFriendlyValue = m_answerArray[a_answerID].getFriendlyValue();
	totalFriendlyValue += answerFriendlyValue;
	return totalFriendlyValue;
}

BSLib::uint32 CHotSpringTask::getEndFriendlyValue(BSLib::uint32 a_endID) const
{
    const BSLib::uint32 size = m_endArray.size();
    if(a_endID+1 > size){
        return 0;
    }

    return m_endArray[a_endID].getFriendlyValue();
}

BSLib::uint32 CHotSpringTask::getItemTPID() const
{
    return m_itemID;
}

BSLib::uint32 CHotSpringTask::getWeight() const
{
    return m_weight;
}

bool CHotSpringTask::SerializeFrom(BSLib::Utility::CStream& stream)
{
    stream >> m_petTPID;
     BSLib::uint32 taskType = 0;
    stream >> taskType;
    m_taskType = (EHotSpringTaskType)taskType;
    stream >> m_itemID;
    m_talkQuestion.SerializeFrom(stream);
    BSLib::uint32 answerCount = 0; 
    stream >> answerCount;
    for (BSLib::uint32 i = 0; i < answerCount; ++i)
    {
        CTalkAnswer item;
        item.SerializeFrom(stream);
    }
    return true;
}

bool CHotSpringTask::SerializeTo(BSLib::Utility::CStream& stream) const
{
    stream << m_petTPID;
    BSLib::uint32 taskType = (BSLib::uint32)m_taskType;
    stream << taskType;
    stream << m_itemID;
    m_talkQuestion.SerializeTo(stream);
    BSLib::uint32 answerCount = m_answerArray.size(); 
    stream << answerCount;
    for (BSLib::uint32 i = 0; i < answerCount; ++i)
    {
        const CTalkAnswer& item = m_answerArray[i];
        item.SerializeTo(stream);
    }
    return true;
}


bool CHotSpringTask::getTaskEndData(BSLib::uint32 a_answerID,BSLib::Utility::CStream& stream) const
{
    BSLib::uint32 endCount = m_endArray.size(); 
    if(a_answerID + 1 > endCount){
        return false;
    }
    const CTalkAnswer& item = m_endArray[a_answerID];
    return item.SerializeTo(stream);
}

bool CHotSpringTask::loadData(BSLib::Utility::CTableRow& a_tableRow)
{
    a_tableRow["f_pet_id"] >> m_petTPID;
    a_tableRow["f_id"] >> m_taskID;
    a_tableRow["f_level_begin"] >> m_minFriendlyLevel;
    a_tableRow["f_level_end"] >> m_maxFriendlyLevel;

    a_tableRow["f_friendly_begin"] >> m_minFriendlyValue;
    a_tableRow["f_friendly_end"] >> m_maxFriendlyValue;
    a_tableRow["f_percent"] >> m_weight;
    a_tableRow["f_item_id"] >> m_itemID;

    
    BSLib::uint32 type = 0;
    a_tableRow["f_task_type"] >> type;
    m_type = (EHotSpringTaskStatus)type;

    BSLib::uint32 taskType = 0;
    a_tableRow["f_type"] >> taskType;
    m_taskType = (EHotSpringTaskType)taskType;
    

    std::string question = "";
    a_tableRow["f_question"] >> question;

    std::string answer = "";
    a_tableRow["f_answer"] >> answer;

    std::string end = "";
    a_tableRow["f_end"] >> end;

    return _init(question,answer,end);
}

bool CHotSpringTask::init(PetTPID a_petTPID,BSLib::uint32 a_itemID,EHotSpringTaskType a_taskType,const std::string&a_question, const std::string& a_answer,ETaskUser a_taskUser)
{
    m_petTPID = a_petTPID;
    m_taskType = a_taskType;
    m_itemID = a_itemID;
    m_talkQuestion.init(a_question);
   
    BSLib::Utility::CStringA strAnswer(a_answer);
    std::vector<std::string> vecStr;
    std::string separator("--");
    strAnswer.split(vecStr, separator);

    for(BSLib::uint32 i=0;i<vecStr.size();++i){
        std::string str = vecStr[i];
        CTalkAnswer answer;
        answer.init(i,str);
        m_answerArray.push_back(answer);
    }

    for(BSLib::uint32 i=0;i<vecStr.size();++i){
        std::string str = vecStr[i];
        CTalkAnswer answer;
        answer.init(i,str);
        m_answerArray.push_back(answer);
    }
    return true;
}


bool CHotSpringTask::_init(const std::string&a_question, const std::string& a_answer, const std::string& a_end)
{
    m_talkQuestion.init(a_question);

    BSLib::Utility::CStringA strAnswer(a_answer);
    std::vector<std::string> vecStr;
    std::string separator("--");
    strAnswer.split(vecStr, separator);
    for(BSLib::uint32 i=0;i<vecStr.size();++i){
        std::string str = vecStr[i];
        CTalkAnswer answer;
        if(!answer.init(i,str)){
            BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "[CHotSpringTask][LOADCONFIG_ERROR][m_taskID=%d][strAnswer=%s]",m_taskID, a_answer.c_str());
        }
        m_answerArray.push_back(answer);
    }

    BSLib::Utility::CStringA strEnd(a_end);
    std::vector<std::string> vecEndStr;
    std::string separatorEnd("--");
    strEnd.split(vecEndStr, separatorEnd);
    for(BSLib::uint32 i=0;i<vecEndStr.size();++i){
        std::string strEndItem = vecEndStr[i];
        CTalkAnswer endItem;
        if(!endItem.init(i,strEndItem)){
            BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "[CHotSpringTask][LOADCONFIG_ERROR][m_taskID=%d][strEnd=%s]",m_taskID, strEnd.c_str());
        }
        m_endArray.push_back(endItem);
    }

    return true;
}

}//GM

}//PlayerSystem

}//GSLib

