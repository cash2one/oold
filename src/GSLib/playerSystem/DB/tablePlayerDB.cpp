#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/tracer.h>

namespace GSLib
{

namespace PlayerSystem
{

namespace DB
{

bool CRoleKey::serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << m_accountID;
	stream << m_zoneID;
	stream << m_roleIndex;
	return _serializeTo(stream);
}

bool CRoleKey::serializeFrom(BSLib::Utility::CStream& stream)
{
	BSLib::uint32 size = stream.readSize();
	if (size < (int)(sizeof(m_accountID) + sizeof(m_zoneID) + sizeof(m_roleIndex))){
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "序列化消息失败");
		return false;
	}
	stream >> m_accountID;
	stream >> m_zoneID;
	stream >> m_roleIndex;
	try {
		return _serializeFrom(stream);
	} catch (...) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "序列化消息失败[AccountID=%lld][ZoneID=%d][RoleIndex=%d]", m_accountID, m_zoneID, m_roleIndex);
		return false;
	} 
}


bool CRoleBagData::serializeTo(BSLib::Utility::CStream& stream) const 
{
	for (BSLib::uint32 i=0; i<m_bagItemArray.size(); ++i) {
		m_bagItemArray[i].serializeTo(stream);
	}
	return true;
}


}//DB

}//DBSystem

}//GSLib
