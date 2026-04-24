#ifndef SOIL_CHIP_H
#define SOIL_CHIP_H

class SoilChip {
  private:
    float soil;

  public:
    SoilChip(float initial = 60) {
      soil = initial;
    }

    float update(int potSoil, float humidity, float light) {

    static int lastPot = 0;

    int delta = potSoil - lastPot;

    if (delta > 5) {
      soil += delta * 0.8;
    }

    lastPot = potSoil;

    float humidityFactor = (100 - humidity) / 100.0;
    float lightFactor = light / 100.0;

    float dryingRate = .6;
    dryingRate += .6 * humidityFactor;
    dryingRate += .4 * lightFactor;

    soil -= dryingRate;

    if (soil < 30) {
      soil = 60;
    }

    if (soil > 100) soil = 100;
    if (soil < 0) soil = 0;

    return soil;
  }
};

#endif
