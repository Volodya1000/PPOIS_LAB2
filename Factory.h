#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "Machine.h"
#include "MillingMachine.h"
#include "Worker.h"
#include "Workpiece.h"
#include "Detail.h"
#include "MillingDetail.h"
#include "GearDetail.h"
#include "Master.h"
#include "Report.h"

class Machine;
class MillingMachine;
class Worker;
class Workpiece;
class Detail;
class MillingDetail;
class GearDetail;
class Master;
class Report;

using namespace std;

// Фабрика - главный класс, управляет всеми остальными
class Factory
{
private:
     int Budjet;
     int SalaryPerWorker;
     int MillingMachineCost;
     int GearMachineCost;
     int WorkpieceCost;
     int EnergyForMillingMachine; //Затраты электроэнергии на одном станке для производства одной детали
     int EnergyForGearMachine;
     int HoursPerWorker;//количество часов работы работника в месяц
     

     vector<shared_ptr<Machine>> ArrayMachines;
     vector<shared_ptr<Worker>> ArrayWorkers;
     vector<shared_ptr<Workpiece>> ArrayWorkpieces;
     vector<shared_ptr<Detail>> ArrayDetails;
     

    
     vector<Report> ArrayReports;//отчёты за все месяцы работы фабрики
public:
    Factory(int Budjet_): Budjet(Budjet_) {}

    Factory(int Budjet_,
            int SalaryPerWorker_,
            int MillingMachineCost_,
            int WorkpieceCost_,
            int EnergyForMillingMachine_,
            int HoursPerWorker_, 
            int EnergyForGearMachine_,
            int GearMachineCost_):
        Budjet(Budjet_), 
        SalaryPerWorker(SalaryPerWorker_),
        MillingMachineCost(MillingMachineCost_),
        WorkpieceCost(WorkpieceCost_),
        EnergyForMillingMachine(EnergyForMillingMachine_),
        HoursPerWorker(HoursPerWorker_),
        EnergyForGearMachine(EnergyForGearMachine_),
        GearMachineCost(GearMachineCost_)
    { 
        //При создании завода изначально добавляется мастер, который чинит станки
        //Предпологается, что мастер обслуживает станки гораздо быстрее, чем они ломаются, так что при любм количестве станков мастер один
        shared_ptr<Worker> Master_ = make_shared<Master>();
        ArrayWorkers.push_back(Master_);
    }

    void AddNewMillingMachine() {
        if (!ChangeBudjet(-MillingMachineCost)) return;
       shared_ptr<Machine> NewMillingMachine = make_shared<MillingMachine>(MillingMachineCost);
        ArrayMachines.push_back(NewMillingMachine);
    }

    void AddNewGearMachine() {
        if (!ChangeBudjet(-GearMachineCost)) return;
        shared_ptr<Machine> NewGearMachine = make_shared<GearMachine>(GearMachineCost);
        ArrayMachines.push_back(NewGearMachine);
    }

    void AddWorkpiece()
    {
        if (!ChangeBudjet(-WorkpieceCost)) return;
        shared_ptr<Workpiece> NewWorkpiece = make_shared<Workpiece>();
        ArrayWorkpieces.push_back(NewWorkpiece);
    }

   

    //Возвращает те эллементы из ArrayMachines которые являются MillingMachine
    vector<shared_ptr<MillingMachine>> GetMillingMachines() {
        vector<shared_ptr<MillingMachine>> MillingMachines;
        for (const auto& MachinePtr : ArrayMachines) {
            // Проверяем, является ли элемент MillingMachine
            if (auto MillingMachinePtr = dynamic_pointer_cast<MillingMachine>(MachinePtr)) {
                MillingMachines.push_back(MillingMachinePtr);
            }
        }
        return MillingMachines;
    }

    //Возвращает те эллементы из ArrayMachines которые являются MillingMachine
    vector<shared_ptr<GearMachine>> GetGearMachines() {
        vector<shared_ptr<GearMachine>> GearMachines;
        for (const auto& MachinePtr : ArrayMachines) {
            // Проверяем, является ли элемент MillingMachine
            if (auto GearMachinePtr = dynamic_pointer_cast<GearMachine>(MachinePtr)) {
                GearMachines.push_back(GearMachinePtr);
            }
        }
        return GearMachines;
    }


    

    //Добавление нового рабочего, которому сразу присваевается MillingMachine
    void AddMillingtWorker()
    {
        bool FoundAvailable = false;
        shared_ptr<Worker> MillingWorker = make_shared<Worker>(SalaryPerWorker);
        for (const auto& MillingMachinePtr : GetMillingMachines())
        {
            if (MillingMachinePtr->GetAvailable())
            {
                MillingMachinePtr->SetAvailable(false);
                MillingWorker->SetMillingMachine(MillingMachinePtr);
                FoundAvailable = true;
                break;
            }
        }
        if (!FoundAvailable)
        {
            cout << "No Available milling machine";
        }

        ArrayWorkers.push_back(MillingWorker);
    }

    //Добавление нового рабочего, которому сразу присваевается GearMachine
    void AddGeartWorker()
    {
        bool FoundAvailable = false;
        shared_ptr<Worker> GearWorker = make_shared<Worker>(SalaryPerWorker);
        for (const auto& GearMachinePtr : GetGearMachines())
        {
            if (GearMachinePtr->GetAvailable())
            {
                GearMachinePtr->SetAvailable(false);
                GearWorker->SetGearMachine(GearMachinePtr);
                FoundAvailable = true;
                break;
            }
        }
        if (!FoundAvailable)
        {
            cout << "No Available gear machine";
        }

        ArrayWorkers.push_back(GearWorker);
    }

    void OrderMillingDetail(shared_ptr<Worker> Worker_)
    {
        if (!ArrayWorkpieces.empty()&& Worker_->GetMachine())
        {
            if (Worker_->GetMachine()->GetBroken())
            {
                OrderFixingMachine(Worker_->GetMachine());
            }
            ChangeBudjet(-EnergyForMillingMachine);
            ArrayDetails.push_back(Worker_->CreateMillingDetail(ArrayWorkpieces.front()));
            ArrayWorkpieces.erase(ArrayWorkpieces.begin());// заготовка удаляется она использована для создания детали
        }
    }

    void OrderGearDetail(shared_ptr<Worker> Worker_)
    {
        if (!ArrayWorkpieces.empty() && Worker_->GetMachine())
        {
            if (Worker_->GetMachine()->GetBroken())
            {
                OrderFixingMachine(Worker_->GetMachine());
            }
            ChangeBudjet(-EnergyForMillingMachine);
            ArrayDetails.push_back(Worker_->CreateGearDetail(ArrayWorkpieces.front()));
            ArrayWorkpieces.erase(ArrayWorkpieces.begin());// заготовка удаляется она использована для создания детали
        }
    }

    void OrderFixingMachine(shared_ptr <Machine> BrokenMachine)
    {
        shared_ptr<Master> Master_ = dynamic_pointer_cast<Master>(ArrayWorkers[0]);
        Master_->FixMachine(BrokenMachine);
        Master_->IncreaseCountOfMachineFixing();
    }

    int GetBudjet()
    {
        return Budjet;
    }

    //Позволяет изменить бюджет только, если он не уйдёт в минус
    bool ChangeBudjet(int Value)
    {
        if (Budjet + Value >= 0)
        {
            Budjet += Value;
            return true;
        }
        else
        {
            cout << "No money for operation";
            return false;
        }
    }

    shared_ptr<Worker> GetWorker()
    {
        return ArrayWorkers[0];
    }

    //Для тестов
    string GetMillingDetailShape()
    {
        shared_ptr<MillingDetail> Ml =dynamic_pointer_cast<MillingDetail>(ArrayDetails[0]);
        return Ml->GetShape();
    }



    /// <summary>
    /// Симуляция работы завода за месяц. Сотрудники производят детали 
    /// Сотрудникам начисляются зарплаты из бюджета. В конце все детали продают и эти деньги идут в бюджет
    /// </summary>
    string  RunFactoryForMonth()
    {
        //---------Стадия расчёта-------------------
        Report NewReport;//Отчёт о всех произведенных операциях
       

        // Рассчитываем полный расход на одного работника, использующего один станок
        int CostForOneMillingWorker = SalaryPerWorker + MillingMachineCost + (WorkpieceCost + EnergyForMillingMachine) * HoursPerWorker;
        int CostForOneGearWorker= SalaryPerWorker + GearMachineCost + (WorkpieceCost + EnergyForGearMachine) * HoursPerWorker;
        
        
        // Проверяем, сколько работников можно нанять на имеющийся бюджет
        int WorkerCount = (Budjet- SalaryPerWorker*2) / (CostForOneMillingWorker+ CostForOneGearWorker);//SalaryPerWorker*2 -зараплата мастера

        // Убеждаемся, что расходы не превышают бюджет
        if (WorkerCount <= 0)
        {
            return "Бюджет не позволяет нанять хотя бы одного работника.";
        }
        NewReport.setTotalSalaryExpense( WorkerCount * SalaryPerWorker);
        NewReport.setMoneyForMillingMachines( WorkerCount * MillingMachineCost);
        NewReport.setMoneyForGearMachines( WorkerCount * GearMachineCost);
        NewReport.setTotalMaterialExpense(WorkerCount * WorkpieceCost * HoursPerWorker);
        NewReport.setEnergyForMillingMachine(WorkerCount * EnergyForMillingMachine * HoursPerWorker);
        NewReport.setMoneyForGearMachines(WorkerCount * EnergyForGearMachine * HoursPerWorker);
            
           
        //-----стадия закупки
        for (int i = 0; i < WorkerCount; i++)
        {
            AddNewMillingMachine();
            AddMillingtWorker();
            AddNewGearMachine();
            AddGeartWorker();
        }
        for (int i = 0; i < WorkerCount*HoursPerWorker; i++)
        {
            AddWorkpiece();
        }

        

       //Стадия производаства
        for (int h = 0; h < HoursPerWorker; h++)//каждая интерация цикла это один час работы для всех рабочих
        {
            for (int w = 1; w < ArrayWorkers.size(); w++)//цикл с 1 так как 0 это мастер
            {
                if (ArrayWorkers[w]->ContainsGearMachine())
                {
                    OrderGearDetail(ArrayWorkers[w]);
                    NewReport.setCountOfCreatedGearDetails(NewReport.getCountOfCreatedGearDetails()+1);
                }
                else
                {
                    OrderMillingDetail(ArrayWorkers[w]);
                    NewReport.setCountOfCreatedGearDetails(NewReport.getCountOfCreatedGearDetails() + 1);
                }
            }
        }

        //Выплаты зарплат
        for (int w = 0; w < ArrayWorkers.size(); w++)
        {
            if(CheckIncreaseLevel(ArrayWorkers[w])) NewReport.setCountOfIncreaseLevelWorkers(NewReport.getCountOfCreatedGearDetails() + 1);
            ChangeBudjet(-(ArrayWorkers[w]->GetPay()+ ArrayWorkers[w]->GetPay()*ArrayWorkers[w]->GetLevel() * 0.01)); //Каждый разряд увеличивает 
        }

        NewReport.setRevenue(SellAllDetails());
        ArrayReports.push_back(NewReport);
        return CreateReport(NewReport);
    }

    bool CheckIncreaseLevel(shared_ptr<Worker> Worker_)
    {
        Worker_->IncreaseCountOfMonthWork();
        if (Worker_->GetCountOfMonthWork() % 2 == 0)
        {
            Worker_->IncreaseLevel();
            return true;
        }
        return false;
    }

    string CreateReport(Report R)
    {
        string Rez;
        Rez += "\n -------Отчёт за месяц "+to_string(ArrayReports.size()) + " --------";
        Rez += "\n Потрачено на закупку фрезерных станков: " + to_string(R.getMoneyForMillingMachines());
        Rez += "\n Потрачено на закупку токарных станков: " + to_string(R.getMoneyForGearMachines());
        Rez += "\n Потрачено на закупку заготовок: " + to_string(R.getTotalMaterialExpense());
        Rez += "\n Потрачено на электроэнергию для фрезерных станков: " + to_string(R.getEnergyForMillingMachine());
        Rez += "\n Потрачено на электроэнергию для токарных станков: " + to_string(R.getMoneyForGearMachines());
        Rez+= "\n Потрачено на зарплаты рабочих: " + to_string(R.getTotalSalaryExpense());
        Rez+= "\n Сделано фрезерных деталей: " + to_string(R.getCountOfCreatedMillingDetails());
        Rez += "\n Сделано токарных деталей: " + to_string(R.getCountOfCreatedGearDetails());
        Rez+= "\n Выручка от продажи деталей: " + to_string(R.getRevenue());
        shared_ptr<Master> Master_ = dynamic_pointer_cast<Master>(ArrayWorkers.front());
        Rez+= "\n Мастер чинил станки " + to_string(Master_->GetCountOfMachineFixing())+" раз";
        Rez += "\n Текущий бюджет: " + to_string(Budjet);
        return Rez;
    }

    int SellAllDetails()
    {
        int Profit=0;//прибыль
        for (int d = 0; d < ArrayDetails.size(); d++)
        {
            Budjet += ArrayDetails[d]->GetMarketPrice();
            Profit += ArrayDetails[d]->GetMarketPrice();
            ArrayDetails.erase(ArrayDetails.begin() + d);
        }
        return Profit;
    }




};

