#ifndef _DATA_STREAM_HPP_DESMOND_WANG_2015_07_14_
#define _DATA_STREAM_HPP_DESMOND_WANG_2015_07_14_

#include <malloc.h>
#include "IDataStream.h"

namespace desmondwang
{
	namespace util
	{
		enum release_type
		{
			release_type_null = 0,
			release_type_free,
			release_type_delete,
			release_type_delete_array,
		};
		class DataStream : public IDataStream
		{
		public:
			DataStream( const void* pData, unsigned long nDataSize, release_type type ) 
				: m_nDataSize(nDataSize), m_pData(pData), m_bReleaseType(type)
			{
			}
			~DataStream() 
			{
				switch (m_bReleaseType)
				{
				case release_type_null:	break;
				case release_type_free:			free( (void*)m_pData );	break;
				case release_type_delete:		delete m_pData;		break;
				case release_type_delete_array: delete[] m_pData;	break;
				}
			}

			virtual void			Release() override				{ delete this; }

			virtual const void*		GetData() const override		{ return m_pData; }
			virtual unsigned long	GetDataSize() const override	{ return m_nDataSize; }
		private:
			unsigned long	m_nDataSize;
			const void*		m_pData;
			release_type	m_bReleaseType;
		};
	}
}

#endif