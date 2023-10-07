#pragma once
#include "Workpiece.h"
class Workpiece;

//����������� �����
class Detail :
    public Workpiece
{
protected:
    int MarketPrice; //���� ��� ������� ������
public:

    Detail(Workpiece& workpiece, int MarketPrice_=30 )
        : MarketPrice(MarketPrice_),Workpiece(workpiece.GetCost()) {}
   
    virtual ~Detail() {}

    int GetMarketPrice()
    {
        return MarketPrice;
    }
};

