#pragma once
//«аготовка детали
class Workpiece
{
protected:
	int Cost; //стоимость заготовки

	int Width;
	int Height;
	int Length;
public:
	Workpiece(int Cost_=10,int Length_=15,int Width_=20, int Height_ =15) :
		Cost(Cost_),Length(Length_),Width(Width_),Height(Height_) {}

	int GetCost()
	{
		return Cost;
	}

	void SetWidth(int NewWidth) {
		if (NewWidth > 0&& Width -NewWidth>0)
			Width -= NewWidth;
	}
	void SetHeight(int NewHeight ) {
		if (NewHeight > 0 && Height - NewHeight > 0)
			Height -= NewHeight;
	}
	void SetLength(int NewLength ) {
		if (NewLength > 0 && Length - NewLength > 0)
			Length -= NewLength;
	}
};

