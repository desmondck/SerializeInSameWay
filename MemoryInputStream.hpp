#ifndef _MEMORY_INPUT_STREAM_H_DESMOND_WANG_2015_07_14_
#define _MEMORY_INPUT_STREAM_H_DESMOND_WANG_2015_07_14_

#include <assert.h>
#include <stdlib.h>

#include "DataStream.hpp"

namespace desmondwang
{
	namespace util
	{
		class MemoryInputStream : public IInputStream
		{
		public:
			MemoryInputStream( IDataStream* pDataStream, bool bAutoRelease )
				: m_pDataStream(pDataStream), m_nCurPos(0), m_bAutoRelease(bAutoRelease)
			{
				assert( m_pDataStream );
			}
			~MemoryInputStream() 
			{
				if(m_bAutoRelease)
					m_pDataStream->Release();
			}
			
			virtual void			Release(){ delete this; }

			virtual unsigned long Read(void* pData, unsigned long cbSize)
			{
				const char* pStoreData	= (const char*)m_pDataStream->GetData();
				unsigned long nStoreSize = m_pDataStream->GetDataSize();

				if(!pStoreData || nStoreSize == 0)
					throw std::bad_exception("no data");

				//whether has enough 
				long readed = min( cbSize, nStoreSize - m_nCurPos );

				memcpy( pData, pStoreData + m_nCurPos, readed );
				m_nCurPos += readed;

				return readed;
			}

			//ignore some data
			virtual unsigned long Ignore( unsigned long nSize )
			{
				unsigned long nIgnoreSize = min( nSize, m_pDataStream->GetDataSize() - m_nCurPos );
				m_nCurPos += nIgnoreSize;

				return nIgnoreSize;
			}

			virtual unsigned long TotalReadSize()
			{
				return m_nCurPos;
			}
		private:
			bool	m_bAutoRelease;
			IDataStream*	m_pDataStream;	
			unsigned long	m_nCurPos;
		};
	}
}

#endif	//_MEMORY_INPUT_STREAM_H_DESMOND_WANG_2015_07_14_