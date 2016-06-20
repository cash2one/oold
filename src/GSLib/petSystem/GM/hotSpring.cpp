//////////////////////////////////////////////////////////////////////
//	created:	2014/07/29
//	filename: 	src\GSLib\petSystem\GM\hotSpring.cpp
//	author:	    zhangping	
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/tracer.h>
#include "GSLib/petSystem/GM/hotSpring.h"
#include <GSLib/petSystem/GM/petSystemGM.h>
#include <GSLib/petSystem/GM/petGM.h>
#include <GSLib/petSystem/GM/petModule.h>
#include "petConfigGMMgr.h"

namespace GSLib
{

namespace PetSystem
{	

namespace GM
{

CHotSpring::CHotSpring()
{
    m_level = 0;
    m_maxPetCount = 0;
    m_inPoolPetCount = 0;
    m_inPoolPetIDArray.clear();
}

CHotSpring::~CHotSpring()
{
    m_level = 0;
    m_maxPetCount = 0;
    m_inPoolPetCount = 0;
    m_inPoolPetIDArray.clear();
}

BSLib::uint32 CHotSpring::getLevel() const
{
    return m_level;
}

BSLib::uint32 CHotSpring::getMaxPetCount() const
{
    return m_maxPetCount;
}


BSLib::uint32 CHotSpring::getInPoolPetCount() const
{
    return m_inPoolPetCount;
}

BSLib::uint32 CHotSpring::getHelpPetCount() const
{
	return m_helperList.size();	
}

BSLib::uint32 CHotSpring::getMaxSitDownPlace() const
{
	switch (m_level) 
	{
	case 0:return 0; break;
	case 1:return 2; break;
	case 2:return 2; break;
	case 3:return 3; break;
	case 4:return 3; break;
	case 5:return 4; break;
	default: return 4;break;
	}
}

void CHotSpring::setLevel(BSLib::uint32 a_level)
{
    m_level = a_level;
    const BSLib::uint32 curHotSpringSize = CPetConfigGMMgr::singleton().getHotSpringSize(m_level);
    setMaxPetCount(curHotSpringSize);
}

void CHotSpring::setMaxPetCount(BSLib::uint32 a_maxPetCount)
{
    m_maxPetCount = a_maxPetCount;
}

bool CHotSpring::updatePetStatus(BSLib::uint32 a_petID,EPetStatus a_petStatus)
{
    switch (a_petStatus)
    {
    case EPetStatusFree:
        {
            if(isPetSitDown(a_petID)){
                standUp(a_petID);
                return true;
            } else if(getPetStatus(a_petID) == EPetStatusInSpring){
                return quitPool(a_petID);
            } else if(getPetStatus(a_petID) == EPetStatusFree){
                return true;
            }
        }
        break;
    case EPetStatusSit:
        {
            if(getPetStatus(a_petID) == EPetStatusSit){
                return true;
            } else if(getPetStatus(a_petID) == EPetStatusInSpring){
                quitPool(a_petID);
                sitDown(a_petID);
            } else if(getPetStatus(a_petID) == EPetStatusFree){
                sitDown(a_petID);
                return true;
            }
        }
        break;
    case EPetStatusInSpring:
        {
            if(getPetStatus(a_petID) == EPetStatusInSpring){
                return true;
            } else if(getPetStatus(a_petID) == EPetStatusSit){
                standUp(a_petID); 
                enterPool(a_petID);
                return true;
            } else if(getPetStatus(a_petID) == EPetStatusFree){
                enterPool(a_petID);
                return true;
            }
        }
        break;
    default: { return false ;} break;
    }
    return false; 
}

//bool CHotSpring::setPetStatus(BSLib::uint32 a_petID,EPetStatus a_oldStatus,EPetStatus a_petStatus)
//{
//    switch (a_oldStatus)
//    {
//    case EPetStatusFree:
//        {
//            if(a_petStatus == EPetStatusInSpring){
//                if(m_inPoolPetCount >= m_maxPetCount){
//                    return false;
//                }
//                m_inPoolPetIDArray.push_back(a_petID);
//                m_inPoolPetCount = m_inPoolPetIDArray.size();
//                return true;
//            } else if(a_petStatus == EPetStatusSit){
//                m_helperPetID = a_petID;
//                return true;
//            } else if(a_petStatus == EPetStatusFree){
//                return true;
//            }
//        }
//        break;
//    case EPetStatusSit:
//        {
//            if(a_petStatus == EPetStatusInSpring){
//                if(m_inPoolPetCount >= m_maxPetCount){
//                    return false;
//                }
//                m_inPoolPetIDArray.push_back(a_petID);
//                m_inPoolPetCount = m_inPoolPetIDArray.size();
//                m_helperPetID = 0;
//                return true;
//            } else if(a_petStatus == EPetStatusSit){
//                m_helperPetID = a_petID;
//                return true;
//            } else if(a_petStatus == EPetStatusFree){
//                m_helperPetID = 0;
//                return true;
//            }
//        }
//        break;
//    case EPetStatusInSpring:
//        {
//            if(a_petStatus == EPetStatusInSpring){
//                return true;
//            } else if(a_petStatus == EPetStatusSit){
//                for(std::vector<BSLib::uint32>::iterator it = m_inPoolPetIDArray.begin(); it != m_inPoolPetIDArray.end(); ++it){
//                    BSLib::uint32 petID = *it;
//                    if(petID == a_petID){
//                        m_inPoolPetIDArray.erase(it);
//                        m_inPoolPetCount = m_inPoolPetIDArray.size();
//                        m_helperPetID = a_petID;
//                        return true;
//                    } 
//                }
//                return false;
//            } else if(a_petStatus == EPetStatusFree){
//                for(std::vector<BSLib::uint32>::iterator it = m_inPoolPetIDArray.begin(); it != m_inPoolPetIDArray.end(); ++it){
//                    BSLib::uint32 petID = *it;
//                    if(petID == a_petID){
//                        m_inPoolPetIDArray.erase(it);
//                        m_inPoolPetCount = m_inPoolPetIDArray.size();
//                        return true;
//                    } 
//                }
//                return false;
//            }
//        }
//        break;
//    default: { return false ;} break;
//    }
//    return false;  
//}
//

bool CHotSpring::isPetSitDown(BSLib::uint32 a_petID) const
{
	for (std::vector<BSLib::uint32>::const_iterator itr = m_helperList.begin(); itr != m_helperList.end(); ++itr) {
		if (*itr == a_petID) {
			return true;
		}
	}
    return false;
}

bool CHotSpring::sitDown(BSLib::uint32 a_petID)
{
	if (!isPetSitDown(a_petID)) {
		m_helperList.push_back(a_petID);
	}
    return true;
}

void CHotSpring::standUp(BSLib::uint32 a_petID)
{
	for (std::vector<BSLib::uint32>::iterator itr = m_helperList.begin(); itr != m_helperList.end(); ++itr) {
		if (*itr == a_petID) {
			m_helperList.erase(itr);
			return;
		}
	}
}

EPetStatus CHotSpring::getPetStatus(BSLib::uint32 a_petID) const
{
    if(isPetSitDown(a_petID)){
        return EPetStatusSit;
    }
    else if(isPetInPool( a_petID)){
        return EPetStatusInSpring;
    }
    else{
        return EPetStatusFree;
    }
}
bool CHotSpring::isPetInPool(BSLib::uint32 a_petID) const
{
    for(std::vector<BSLib::uint32>::const_iterator it = m_inPoolPetIDArray.begin(); it != m_inPoolPetIDArray.end(); ++it){
        BSLib::uint32 petID = *it;
        if(petID == a_petID){
            return true;
        } 
    }
    return false;
}

bool CHotSpring::isPoolFull() const
{
    if(m_maxPetCount <= m_inPoolPetCount){
        return true;
    }
    return false;
}

bool CHotSpring::quitPool(BSLib::uint32 a_petID)
{
    for(std::vector<BSLib::uint32>::iterator it = m_inPoolPetIDArray.begin(); it != m_inPoolPetIDArray.end(); ++it){
        BSLib::uint32 petID = *it;
        if(petID == a_petID){
            m_inPoolPetIDArray.erase(it);
            m_inPoolPetCount = m_inPoolPetIDArray.size();
            return true;
        } 
    }
    return false;
}

bool CHotSpring::enterPool(BSLib::uint32 a_petID)
{
    m_inPoolPetIDArray.push_back(a_petID);
    m_inPoolPetCount = m_inPoolPetIDArray.size();
    return true;
}

bool CHotSpring::serializeTo(BSLib::Utility::CStream& stream) const
{
    stream << m_level;
    stream << m_maxPetCount;
	BSLib::uint16 count = (BSLib::uint16)m_helperList.size();
	stream << count;
	for (BSLib::uint16 i = 0; i < m_helperList.size(); ++i) {
		stream << m_helperList[i];
	}
    stream << m_inPoolPetCount;
    for(std::vector<BSLib::uint32>::const_iterator it = m_inPoolPetIDArray.begin(); it != m_inPoolPetIDArray.end(); ++it){
        BSLib::uint32 petID = *it;
        stream << petID;
    }
    
    return true;
}

bool CHotSpring::serializeFrom(BSLib::Utility::CStream& stream)
{
    stream >> m_level;
    stream >> m_maxPetCount;
	BSLib::uint16 count = 0;
	stream >> count;
	for (BSLib::uint16 i = 0; i < count; ++i) {
		BSLib::uint32 helperID = 0;
		stream >> helperID;
		m_helperList.push_back(helperID);
	}
    stream >> m_inPoolPetCount;
    m_inPoolPetIDArray.clear();
    for(BSLib::uint32 i = 0; i < m_inPoolPetCount; ++i){
        BSLib::uint32 petID = 0;
        stream >> petID;
        m_inPoolPetIDArray.push_back(petID);
    }

    return true;
}

bool CHotSpring::final()
{
    m_inPoolPetIDArray.clear();
    return true;
}

}//GM

}//PlayerSystem

}//GSLib
