#ifndef HEALTH_CHIP_H
#define HEALTH_CHIP_H

class HealthChip {
  public:
    float compute(float soil, float humidity, float light) {
      float health =
        0.6 * soil +
        0.25 * humidity +
        0.15 * light;

      if (health > 100) health = 100;
      if (health < 0) health = 0;

      return health;
    }
};

#endif