// SerializeInSameWay.cpp : Defines the entry point for the console application.
//

#include <string>
#include <iostream>
using namespace std;

#include "MemoryInputStream.hpp"
#include "MemoryOutputStream.hpp"
#include "DataStreamHelper.hpp"
using namespace desmondwang::util;

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

struct Point
{
	int x;
	int y;

	void Serialize( DataStreamHelper& dataStream )
	{
		dataStream & x & y;
	}
};

struct Pie
{
	std::string name;
	Point	ptStart;
	Point	ptEnd;

	double	dbStartAngle;
	double	dbEndAngle;

	void Serialize( DataStreamHelper& dataStream )
	{		
		dataStream & name & ptStart & ptEnd & dbStartAngle & dbEndAngle;
	}
};

struct Line
{
	std::string name;
	Point	ptStart;
	Point	ptEnd;

	void Serialize( DataStreamHelper& dataStream )
	{		
		dataStream & name & ptStart & ptEnd;
	}
};

struct ShapeList
{
	Pie pie;
	Line line;

	void Serialize( DataStreamHelper& dataStream )
	{
		dataStream & pie & line;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	ShapeList shape;
	shape.line.name = "desmond wang line";
	shape.line.ptStart.x = 30;
	shape.line.ptStart.y = 50;
	shape.line.ptEnd.x = 300;
	shape.line.ptEnd.y = 500;

	shape.pie.name = "desmond wang pie";
	shape.pie.ptStart.x = 60;
	shape.pie.ptStart.y = 80;
	shape.pie.ptEnd.x = 600;
	shape.pie.ptEnd.y = 800;
	shape.pie.dbStartAngle = 30;
	shape.pie.dbEndAngle = 160;

	//serialize to memory
	MemoryOutputStream outStream;
	DataStreamHelper dataStreamS( &outStream );
	shape.Serialize( dataStreamS );

	//unserialize from memory
	MemoryInputStream inStream(outStream.Detach(), true);
	DataStreamHelper dataStreamL( &inStream );
	ShapeList shape2;
	shape2.Serialize( dataStreamL );

	cout << shape2.line.name << endl;
	cout << shape2.line.ptStart.x << endl;
	cout << shape2.line.ptStart.y << endl;
	cout << shape2.line.ptEnd.x << endl;
	cout << shape2.line.ptEnd.y << endl;

	cout << shape2.pie.name << endl;
	cout << shape2.pie.ptStart.x << endl;
	cout << shape2.pie.ptStart.y << endl;
	cout << shape2.pie.ptEnd.x << endl;
	cout << shape2.pie.ptEnd.y << endl;
	cout << shape2.pie.dbStartAngle << endl;
	cout << shape2.pie.dbEndAngle << endl;

	return 0;
}

