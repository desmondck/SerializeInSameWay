#ifndef _MEMORY_OUTPUT_STREAM_H_DESMOND_WANG_2015_07_14_
#define _MEMORY_OUTPUT_STREAM_H_DESMOND_WANG_2015_07_14_

#include <assert.h>
#include <memory.h>

#include "DataStream.hpp"

namespace desmondwang
{
	namespace util
	{
		class MemoryOutputStream : public IOutputStream
		{
		public:
			MemoryOutputStream( unsigned long nInitSize = 0 )
				: m_pData(NULL), m_nDataSize(0), m_nMemorySize(0)
			{
				_Grow( nInitSize );
			}

			virtual void			Release() {	delete this; }

			//virtual const void*		GetData() const		{ return m_pData; }
			//virtual unsigned long	GetDataSize() const	{ return m_nDataSize; }

			virtual unsigned long Write(const void* pData, unsigned long cbSize);

			virtual IDataStream* Detach();

		private:
			bool _Grow( unsigned long newSize );
		private:
			void* m_pData;
			unsigned long m_nDataSize;
			unsigned long m_nMemorySize;
		};

		unsigned long MemoryOutputStream::Write( const void* pData, unsigned long cbSize )
		{
			if( !_Grow( m_nDataSize + cbSize ) )
			{
				assert(false);
				return 0;
			}

			memcpy( (char*)m_pData + m_nDataSize, pData, cbSize );
			m_nDataSize += cbSize;

			return cbSize;
		}

		IDataStream* MemoryOutputStream::Detach()
		{
			if( m_pData && m_nDataSize )
			{
				DataStream* pDataStream = new DataStream( m_pData, m_nDataSize, release_type_free );
				
				m_pData = NULL;
				m_nDataSize		= 0;
				m_nMemorySize	= 0;

				return pDataStream;
			}

			return NULL;
		}

		bool MemoryOutputStream::_Grow( unsigned long newSize )
		{
			if( newSize <= m_nMemorySize )
				return true;

			if( newSize < (unsigned long)(m_nMemorySize * 1.2) ) 
				newSize = (unsigned long)(m_nMemorySize * 1.2);	

			const int ALLOC_SIZE = 4096;
			newSize = ((newSize + ALLOC_SIZE - 1)/ALLOC_SIZE) * ALLOC_SIZE;	// round to ALLOC_SIZE

			void* p = malloc(newSize);
			if( !p )	
				return false;
			memset( p, 0, newSize );

			if( m_pData && m_nDataSize > 0 )
			{
				memcpy( p, m_pData, m_nDataSize );
				free(m_pData);
			}

			m_pData = (void*)p;
			m_nMemorySize = newSize;
			return true;
		}
	}
}

#endif	//_MEMORY_OUTPUT_STREAM_H_DESMOND_WANG_2015_07_14_