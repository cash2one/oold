//////////////////////////////////////////////////////////////////////
//	created:	2014/07/29
//	filename: 	src\GSLib\petSystem\GM\petTPIDTask.cpp
//	author:	    zhangping	
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/tracer.h>
#include "petTPIDTask.h"

namespace GSLib
{

namespace PetSystem
{	

namespace GM
{

CPetTPIDTask::CPetTPIDTask()
{
};

CPetTPIDTask::~CPetTPIDTask()
{
};

bool CPetTPIDTask::addTask(BSLib::uint32 a_taskID){

    m_taskIDArray.push_back(a_taskID);
    return true;
}

}//GM

}//PlayerSystem

}//GSLib
