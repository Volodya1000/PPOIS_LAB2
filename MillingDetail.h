#pragma once
#include"Workpiece.h";
#include "Detail.h"

class Workpiece;

class MillingDetail :
    public Detail
{
private:
	string Shape="��������������";

	


public:
	
	MillingDetail( Workpiece& Workpiece_) : Detail(Workpiece_), Shape("��������������") {}
	void SetShape(string Shape_)
	{
		Shape = Shape_;
	}

	string GetShape()
	{
		return Shape;
	}
};

