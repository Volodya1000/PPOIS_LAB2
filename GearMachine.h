#pragma once
#include "Machine.h"
#include "Detail.h"
#include "GearDetail.h"
#include <iostream>
#include <memory>

class Detail;
class Machine;
class GearDetail;


class GearMachine :
    public Machine
{

public:
    shared_ptr<Detail> Processing(shared_ptr<Detail> Detail_) {
        shared_ptr<GearDetail> GearDetailPtr = dynamic_pointer_cast<GearDetail>(Detail_);
        GearDetailPtr->SetCountOfTeeth(10);
        GearDetailPtr->SetLength(5);
        GearDetailPtr->SetWidth(3);
        GearDetailPtr->SetHeight(2);
            CountOfCreatedDetails++;
        if (CountOfCreatedDetails % 30 == 0)
        {
            Broken = true;
        }
        return GearDetailPtr;
    }

    GearMachine(bool Available_ = true)
        : Machine(Available_) {}

};

