#pragma once

#include <vector>
#include <memory>

#include "Machine.h"
#include "Workpiece.h"
#include "Detail.h"
#include "MillingDetail.h"
#include "GearMachine.h"

class Machine;
class Workpiece;
class Detail;
class MillingDetail;
class GearMachine;

using namespace std;

//Работник
class Worker
{
private:
	shared_ptr<Machine> MyMachine; //указывает на экземпляр Machine. Каждому работнику соответствует своя machine

	int Pay; // заработная плата 
	int CountOfMonthWork; //количесвто месяцев работы. Каждые два месяца разряд увеличивается

	int Level; // разряд мастера

public:
	Worker(int Pay_=200,int Level_=1) :Pay(Pay_), Level(Level_) {};

	virtual ~Worker() {};

	shared_ptr <Detail> CreateMillingDetail(shared_ptr < Workpiece> Workpiece_)
	{
		if (MyMachine)
		{
			shared_ptr<Detail> MillingDetail_ = make_shared<MillingDetail>(*Workpiece_);
			return MyMachine->Processing(MillingDetail_);
		}
		return nullptr;
	}

	shared_ptr <Detail> CreateGearDetail(shared_ptr < Workpiece> Workpiece_)
	{
		if (MyMachine)
		{
			shared_ptr<Detail> GearDetail_ = make_shared<GearDetail>(*Workpiece_);
			return MyMachine->Processing(GearDetail_);
		}
		return nullptr;
	}

	void SetMillingMachine(shared_ptr<MillingMachine> MyMachine_)
	{
		MyMachine = MyMachine_;
	}

	void SetGearMachine(shared_ptr<GearMachine> MyMachine_)
	{
		MyMachine = MyMachine_;
	}

	shared_ptr<Machine> GetMachine()
	{
		return MyMachine;
	}

	int GetPay()
	{
		return Pay;
	}

	

	bool ContainsGearMachine() {
		return dynamic_cast<GearMachine*>(MyMachine.get()) != nullptr;
	}

	int GetCountOfMonthWork()
	{
		return CountOfMonthWork;
	}

	void IncreaseCountOfMonthWork()
	{
		CountOfMonthWork++;
	}

	void IncreaseLevel()
	{
		Level++;
	}

	int GetLevel()
	{
		return Level;
	}
};

