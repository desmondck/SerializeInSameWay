#ifndef _SERIALIZER_H_DESMOND_WANG_2015_07_14_
#define _SERIALIZER_H_DESMOND_WANG_2015_07_14_

#include "IDataStream.h"

namespace desmondwang
{
	namespace util
	{
		class DataStreamHelper;

		template<typename T, bool bArithmetic>
		struct Serializer
		{
			static void Do( T& t, IOutputStream* pOutStream ) { throw "Serializer Unimplement"; }
		};

		template<typename T>
		struct Serializer<T, true>
		{
			static void Do( T& t, IOutputStream* pOutStream ) 
			{
				pOutStream->Write( &t, sizeof(T) );
			}
		};

		template<typename T>
		struct Serializer<T, false>
		{
			static void Do( T& t, IOutputStream* pOutStream  ) 
			{
				DataStreamHelper helper(pOutStream);
				t.Serialize( helper );
			}
		};

		template<typename T>
		struct Serializer<T*, false>
		{
			static void Do( const T*& t, IOutputStream*	pOutStream ) 
			{
				DataStreamHelper helper(pOutStream);
				t->Serialize( helper );
			}
		};

		//string
		template<>
		struct Serializer<std::string, false>
		{
			static void Do( std::string& str, IOutputStream*	pOutStream ) 
			{
				int nSize = str.size();
				pOutStream->Write( &nSize, sizeof(nSize) );
				pOutStream->Write( str.c_str(), str.size() );
			}
		};
	}
}

#endif	//_SERIALIZER_H_DESMOND_WANG_2015_07_14_