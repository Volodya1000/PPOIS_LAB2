#pragma once

#include "Detail.h"

class Detail;

using namespace std;
//—танок - абстрактный класс, его экземпл€ры создаватьс€ не будут, только наследники
class Machine
{
protected:
    bool Available;//true если ни один рабочий не использует

    //каждые 5 созданных деталей станок нужно чинить. 
    //ѕосле создани€ 30 деталей станок окончательно выходит из стро€ 
    int CountOfCreatedDetails=0;

    bool Broken = false; // —тановитс€ true когда   станок нужно чинить 

public:
    virtual shared_ptr<Detail> Processing(shared_ptr<Detail> Detail_) = 0; //обработка детали
    virtual ~Machine() {}

    Machine(bool Available_=true):Available(Available_) {}

    void SetAvailable(bool Available_)
    {
        Available = Available_;
    }

    bool GetAvailable()
    {
        return Available;
    }

    int GetCountOfCreatedDetails()
    {
        return CountOfCreatedDetails;
    }

    bool GetBroken()
    {
        return Broken;
    }

    void SetBroken(bool Value)
    {
        Broken = Value;
    }
};

