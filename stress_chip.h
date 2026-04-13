#ifndef STRESS_CHIP_H
#define STRESS_CHIP_H

class StressChip {
  public:
    float compute(float soil, float humidity, float light) {
      float stress =
        0.5 * (1 - soil / 100.0) +
        0.3 * (1 - humidity / 100.0) +
        0.2 * (1 - light / 100.0);

      if (stress < 0) stress = 0;
      if (stress > 1) stress = 1;

      return stress;
    }
};

#endif