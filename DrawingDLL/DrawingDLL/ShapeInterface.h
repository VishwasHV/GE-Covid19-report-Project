#ifndef _H_SHAPE_
#define _H_SHAPE_



#include <string>
#include <vector>
using namespace std;
class CShapeInterface
{
public:
	CShapeInterface();
	virtual ~CShapeInterface();


	virtual vector< pair<int, string> > CalculateShape(vector< pair<string, string> >) = 0;

};
#endif
