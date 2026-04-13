#ifndef PLANT_CHIP_H
#define PLANT_CHIP_H

#include "soil_chip.h"
#include "stress_chip.h"
#include "health_chip.h"

class PlantChip {
  private:
    SoilChip soilChip;
    StressChip stressChip;
    HealthChip healthChip;

    float soil;
    float stress;
    float health;

  public:
    PlantChip() : soilChip(60) {}

  void update(int potSoil, float humidity, float light) {
    soil = soilChip.update(potSoil, humidity, light);
    stress = stressChip.compute(soil, humidity, light);
    health = healthChip.compute(soil, humidity, light);
}

    float getSoil() { return soil; }
    float getStress() { return stress; }
    float getHealth() { return health; }
};

#endif
