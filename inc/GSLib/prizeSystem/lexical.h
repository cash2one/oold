#ifndef lexical_h__
#define lexical_h__
#include <vector>
#include <BSLib/utility/string.h>

namespace GSLib
{

	namespace PrizeSystem
	{
		

		template<typename T>
		bool lexicalCast(const std::string& str, std::vector<T>& v, const char* split_token = "|")
		{	
			using std::string;
			string buff(str);
			if(buff.empty())
				return false;

			do 
			{	
				string::size_type pos = buff.find_first_of(split_token);

				string tmp;
				bool need_exit = false;
				if( string::size_type(-1) == pos)
				{
					tmp = buff;
					buff.clear();
					need_exit = true;
				}
				else
				{
					tmp = buff.substr(0, pos);
					buff.erase(0, pos + 1);
				}

				bool success = true;
				try
				{	
					BSLib::Utility::CStringA bsTmp(tmp);
					T cur;
					bsTmp >> cur;
					v.push_back(cur);
				}
				catch (...)
				{	
					success = false;
				}

				if( !success)
					return false;

				if( need_exit)
					break;

			} while (true);

			return 0 != v.size();
		}


	}//PrizeSystem

}//GSLib




#endif // lexical_h__
