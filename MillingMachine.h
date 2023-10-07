#pragma once
#include "Machine.h"
#include "Detail.h"
#include "MillingDetail.h"
#include <iostream>
#include <memory>

class Detail;
class Machine;

using namespace std;
//Фрезерный станок
class MillingMachine : public Machine {
public:
    shared_ptr<Detail> Processing(shared_ptr<Detail> Detail_) {
        shared_ptr<MillingDetail> MillingDetailPtr = dynamic_pointer_cast<MillingDetail>(Detail_);
        MillingDetailPtr->SetShape("Параллелепипед с фасками и скошенными углами");
        MillingDetailPtr->SetHeight(7);
        CountOfCreatedDetails++;
        if (CountOfCreatedDetails % 40 == 0)
        {
            Broken = true;
        }
        return MillingDetailPtr;
    }

    MillingMachine(bool Available_=true)
        : Machine(Available_){}

};
