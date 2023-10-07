#pragma once

#include "Detail.h"

class Detail;

using namespace std;
//������ - ����������� �����, ��� ���������� ����������� �� �����, ������ ����������
class Machine
{
protected:
    bool Available;//true ���� �� ���� ������� �� ����������

    //������ 5 ��������� ������� ������ ����� ������. 
    //����� �������� 30 ������� ������ ������������ ������� �� ����� 
    int CountOfCreatedDetails=0;

    bool Broken = false; // ���������� true �����   ������ ����� ������ 

public:
    virtual shared_ptr<Detail> Processing(shared_ptr<Detail> Detail_) = 0; //��������� ������
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

