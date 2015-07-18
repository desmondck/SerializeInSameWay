#ifndef _I_DATA_STREAM_H_DESMOND_WANG_2015_07_14_
#define _I_DATA_STREAM_H_DESMOND_WANG_2015_07_14_

#ifndef interface
	#define interface struct
#endif

namespace desmondwang
{
	namespace util
	{
		interface IDataStream
		{
			virtual void			Release() = 0;
			
			virtual const void*		GetData() const = 0;
			virtual unsigned long	GetDataSize() const = 0;
		};
		
		interface IInputStream
		{
			virtual void Release() = 0;

			virtual unsigned long Read(void* pData, unsigned long cbSize) = 0;
		};
		
		interface IOutputStream
		{
			virtual void Release() = 0;
			virtual unsigned long Write(const void* pData, unsigned long cbSize) = 0;
		};
	}
}

#endif	//_I_DATA_STREAM_H_DESMOND_WANG_2015_07_14_
