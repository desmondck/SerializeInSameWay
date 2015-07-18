# SerializeInSameWay

In usual, serialize/unserialize like this
```c++
void XXX::Serialize(archive& ar)
{  
  if(ar.isloading())  
  {
    //serialize
    ar << a;
    ar << b;
    ar << c;
  }
  else
  {
    //unserialize
    ar >> a;
    ar >> b;
    ar >> c;
  }
}
```

SerializeInSameWay implement like this:
```c++
void XXX::Serialize(DataStreamHelper& helper)
{
  helper & a & b & c;
}
```

```
/*
Two way imp serialize:
1. add void Serialize( DataStreamHelper& dataStream ) in you class as public member(Recommended!)
2. spec follow template class(struct)
	template<typename T, bool bArithmetic>
	struct Serializer
	{
	static void Do( T& t, IOutputStream* pOutStream ) { throw "Serializer Unimplement"; }
	};
	template<typename T, bool bArithmetic>
	struct Unserializer
	{
	static void Do( T& t, IInputStream*	pInputStream ) { throw "Unserializer Unimplement"; }
	};

*/
```
