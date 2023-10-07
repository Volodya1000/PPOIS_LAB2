#pragma once
#include "Worker.h"
class Master :
    public Worker
{
private:
    int CountOfMachineFixing;
public:
    Master(int CountOfMachineFixing_ = 0) :CountOfMachineFixing(CountOfMachineFixing_) {};



    void FixMachine(shared_ptr<Machine> Machine_)
    {
        Machine_->SetBroken(false);
    }


    int GetCountOfMachineFixing()
    {
        return CountOfMachineFixing;
    }

    void IncreaseCountOfMachineFixing()
    {
        CountOfMachineFixing++;
    }

    void ReSetIncreaseCountOfMachineFixing()
    {
        CountOfMachineFixing = 0;
    }
};

