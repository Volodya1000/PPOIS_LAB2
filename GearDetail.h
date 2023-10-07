#pragma once
#include"Workpiece.h";
#include "Detail.h"

class Workpiece;

class GearDetail :
	public Detail
{
	int Radius;
	int CountOfTeeth;//количество зубьев



public:

	GearDetail(Workpiece& Workpiece_) : Detail(Workpiece_), Radius(5), CountOfTeeth(0) {}

	void SetRadius(int Radius_)
	{
		Radius = Radius_;
	}

	int GetShape()
	{
		return Radius;
	}

	void SetCountOfTeeth(int CountOfTeeth_)
	{
		if(CountOfTeeth_>0)
		CountOfTeeth = CountOfTeeth_;
	}

	int GetCountOfTeeth()
	{
		return CountOfTeeth;
	}
};

