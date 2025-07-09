#include "stdafx.h"
#include "DataStruct.h"

float DataStruct::rateOfFire = 1;
float DataStruct::clipSize = 1;
int DataStruct::maxHealth = 100;
float DataStruct::runSpeed = 50;
int DataStruct::healAmount = 15;
int DataStruct::ammoAmount = 15;

void DataStruct::DecreaseRateOfFire(float amount)
{
    if (rateOfFire - amount > 0.1f)
    {
        rateOfFire -= amount;
    }
    else
    {
        rateOfFire = 0.1f; // 발사 시간 최솟값
    }
}

void DataStruct::IncreaseClipSize(int amount)
{
    if (amount > 0)
    {
        clipSize += amount;
    }
    else
    {
        std::cout << "양수만 입력" << std::endl;
    }
}

void DataStruct::IncreaseMaxHealth(int amount)
{
    if (amount > 0)
    {
        maxHealth += amount;
    }
    else
    {
        std::cout << "양수만 입력" << std::endl;
    }
}

void DataStruct::IncreaseRunSpeed(float amount)
{
    if (amount > 0)
    {
        runSpeed += amount;
    }
    else
    {
        std::cout << "양수만 입력" << std::endl;
    }
}

void DataStruct::IncreaseHealAmount(int amount)
{
    if (amount > 0)
    {
        healAmount += amount;
    }
    else
    {
        std::cout << "양수만 입력" << std::endl;
    }
}

void DataStruct::IncreaseAmmoAmount(int amount)
{
    if (amount > 0)
    {
        ammoAmount += amount;
    }
    else
    {
        std::cout << "양수만 입력" << std::endl;
    }
}