#include "stdafx.h"

int main()
{
    FRAMEWORK.Init(1280, 720, "Zombie Game");
    FRAMEWORK.Do();
    FRAMEWORK.Release();

    return 0;
}