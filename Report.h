#pragma once
class Report
{
private:
    int CreatedDetailsCount;
    int Revenue;//выручка
    int SoldDetailsCount;
    int TotalSalaryExpense;
    int MoneyForWorkpieces;
    int MoneyForMillingMachines;
    int MoneyForGearMachines;
    int TotalMaterialExpense;
    int EnergyForMillingMachine;
    int CountOfCreatedMillingDetails = 0;
    int CountOfCreatedGearDetails = 0;
    int CountOfIncreaseLevelWorkers = 0;

public:
    int getCreatedDetailsCount() const {
        return CreatedDetailsCount;
    }

    void setCreatedDetailsCount(int value) {
        CreatedDetailsCount = value;
    }

    int getRevenue() const {
        return Revenue;
    }

    void setRevenue(int value) {
        Revenue = value;
    }

    int getSoldDetailsCount() const {
        return SoldDetailsCount;
    }

    void setSoldDetailsCount(int value) {
        SoldDetailsCount = value;
    }

    int getTotalSalaryExpense() const {
        return TotalSalaryExpense;
    }

    void setTotalSalaryExpense(int value) {
        TotalSalaryExpense = value;
    }

    int getMoneyForWorkpieces() const {
        return MoneyForWorkpieces;
    }

    void setMoneyForWorkpieces(int value) {
        MoneyForWorkpieces = value;
    }

    int getMoneyForMillingMachines() const {
        return MoneyForMillingMachines;
    }

    void setMoneyForMillingMachines(int value) {
        MoneyForMillingMachines = value;
    }

    int getMoneyForGearMachines() const {
        return MoneyForGearMachines;
    }

    void setMoneyForGearMachines(int value) {
        MoneyForGearMachines = value;
    }

    int getTotalMaterialExpense() const {
        return TotalMaterialExpense;
    }

    void setTotalMaterialExpense(int value) {
        TotalMaterialExpense = value;
    }

    int getEnergyForMillingMachine() const {
        return EnergyForMillingMachine;
    }

    void setEnergyForMillingMachine(int value) {
        EnergyForMillingMachine = value;
    }

    int getCountOfCreatedMillingDetails() const {
        return CountOfCreatedMillingDetails;
    }

    void setCountOfCreatedMillingDetails(int value) {
        CountOfCreatedMillingDetails = value;
    }

    int getCountOfCreatedGearDetails() const {
        return CountOfCreatedGearDetails;
    }

    void setCountOfCreatedGearDetails(int value) {
        CountOfCreatedGearDetails = value;
    }

    int getCountOfIncreaseLevelWorkers() const {
        return CountOfIncreaseLevelWorkers;
    }

    void setCountOfIncreaseLevelWorkers(int value) {
        CountOfIncreaseLevelWorkers = value;
    }
};

