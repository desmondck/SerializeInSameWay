#ifndef _UNSERIALIZER_H_DESMOND_WANG_2015_07_14_
#define _UNSERIALIZER_H_DESMOND_WANG_2015_07_14_

namespace desmondwang
{
	namespace util
	{
		template<typename T, bool bArithmetic>
		struct Unserializer
		{
			static void Do( T& t, IInputStream*	pInputStream ) { throw "Unserializer Unimplement"; }
		};

		template<typename T>
		struct Unserializer<T, true>
		{
			static void Do( T& t, IInputStream*	pInputStream ) 
			{
				pInputStream->Read( &t, sizeof(T) );
			}
		};

		template<typename T>
		struct Unserializer<T, false>
		{
			static void Do( T& t, IInputStream*	pInputStream ) 
			{
				DataStreamHelper helper(pInputStream);
				t.Serialize( helper );
			}
		};

		template<typename T>
		struct Unserializer<T*, false>
		{
			static void Do( T*& t, IInputStream*	pInputStream ) 
			{
				DataStreamHelper helper(pInputStream);
				t->Serialize( helper );
			}
		};

		//string
		template<>
		struct Unserializer<std::string, false>
		{
			static void Do( std::string& str, IInputStream*	pInputStream ) 
			{
				int nSize;
				pInputStream->Read( &nSize, sizeof(nSize) );

				char* pData = new char[nSize];
				pInputStream->Read( pData, nSize );
				str = pData;
				delete[] pData;
			}
		};

	}
}

#endif	//_UNSERIALIZER_H_DESMOND_WANG_2015_07_14_