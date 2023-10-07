#pragma once
#include"Workpiece.h";
#include "Detail.h"

class Workpiece;

class MillingDetail :
    public Detail
{
private:
	string Shape="Параллелепипед";

	


public:
	
	MillingDetail( Workpiece& Workpiece_) : Detail(Workpiece_), Shape("Параллелепипед") {}
	void SetShape(string Shape_)
	{
		Shape = Shape_;
	}

	string GetShape()
	{
		return Shape;
	}
};

