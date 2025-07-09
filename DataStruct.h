#pragma once

struct DataStruct
{
private:
    static float rateOfFire;
    static int clipSize;
    static int maxHealth;
    static float runSpeed;
    static int healAmount;
    static int ammoAmount;

public:
    static float GetRateOfFire() { return rateOfFire; }
    static float GetClipSize() { return clipSize; }
    static int GetMaxHealth() { return maxHealth; }
    static float GetRunSpeed() { return runSpeed; }
    static int GetHealAmount() { return healAmount; }
    static int GetAmmoAmount() { return ammoAmount; }

    static void IncreaseRateOfFire(float amount);
    static void IncreaseClipSize(int amount);
    static void IncreaseMaxHealth(int amount);
    static void IncreaseRunSpeed(float amount);
    static void IncreaseHealAmount(int amount);
    static void IncreaseAmmoAmount(int amount);
};