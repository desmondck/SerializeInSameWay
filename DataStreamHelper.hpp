#ifndef _DATA_STREAM_HELPER_H_DESMOND_WANG_2015_07_14_
#define _DATA_STREAM_HELPER_H_DESMOND_WANG_2015_07_14_

#include "IDataStream.h"

#include "Serializer.hpp"
#include "Unserializer.hpp"

namespace desmondwang
{
	namespace util
	{
		class DataStreamHelper
		{
		public:
			enum data_stream_flag
			{
				loading,
				store
			};

			DataStreamHelper( IInputStream* pInputStream )
				: m_pInputStream(pInputStream), m_pOutputStream(NULL), m_eFlag(loading)
			{
			}
			DataStreamHelper( IOutputStream* pOutputStream )
				: m_pInputStream(NULL), m_pOutputStream(pOutputStream), m_eFlag(store)
			{
			}

			~DataStreamHelper(void)
			{
			}

			IInputStream*	GetInputStream()	{ return m_pInputStream; }
			IOutputStream*	GetOutputStream()	{ return m_pOutputStream; }

			template<typename T> DataStreamHelper& operator & ( T& t )
			{
				return m_eFlag == store ? *this << t : *this >> t;
			}
		private:
			template<typename T> DataStreamHelper& operator << ( T& t )
			{
				Serializer<T, std::is_arithmetic<T>::value>::Do( t, m_pOutputStream );

				return *this;
			}

			template<typename T> DataStreamHelper& operator>>( T& t )
			{
				Unserializer<T, std::is_arithmetic<T>::value>::Do( t, m_pInputStream );

				return *this;
			}

			data_stream_flag	m_eFlag;

			IInputStream*	m_pInputStream;
			IOutputStream*	m_pOutputStream;
		};
	}
}

#endif	//_DATA_STREAM_HELPER_H_DESMOND_WANG_2015_07_14_