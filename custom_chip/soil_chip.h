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

      // blend real input + simulation
      soil = 0.7 * soil + 0.3 * potSoil;

      // ---------- ENVIRONMENTAL DRYING MODEL ----------

      // normalize inputs
      float humidityFactor = (100 - humidity) / 100.0; // dry air → higher
      float lightFactor = light / 100.0;               // bright → higher

      // base drying rate
      float dryingRate = 0.2;

      // environmental influence
      dryingRate += 0.6 * humidityFactor;
      dryingRate += 0.4 * lightFactor;

      // apply drying
      soil -= dryingRate;

      // ---------- WATERING EVENT ----------
      if (soil < 20) {
        soil = 60;
      }

      return soil;
    }

    float get() {
      return soil;
    }
};

#endif
