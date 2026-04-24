Smart Watering and Humidity Control for Indoor Plants

EECE 5155 Final Project by Timothy Davis
Northeastern University, Spring 2026

Project Overview

This project implements an end-to-end IoT plant monitoring system using a simulated ESP32 sensor node in Wokwi, MQTT messaging, Node-RED data processing, InfluxDB Cloud storage, Grafana visualization, and a machine learning warning model.

The system continuously monitors environmental conditions and estimates plant health using multiple variables including soil moisture, humidity, light level, and a calculated stress index.

Technologies Used
ESP32 (Wokwi Simulation)
MQTT (HiveMQ Public Broker)
Node-RED
InfluxDB Cloud
Grafana
Python
Scikit-learn
Features
Live sensor telemetry publishing every 2 seconds
MQTT cloud messaging pipeline
Node-RED flow for parsing, formatting, routing, and logging
CSV backup data logging
InfluxDB time-series storage
Grafana dashboard with live panels
Threshold-based plant health alerts
Random Forest classifier for warning prediction
Repository Structure
firmware/       ESP32 Wokwi source files
pipeline/       Node-RED exported flows
data/           Collected and generated datasets
analysis/       Notebooks, scripts, ML outputs
screenshots/    Dashboard and system proof images
report/         Final written report
How to Run the Project
Open the Wokwi ESP32 project in firmware/
Start the simulation
Launch Node-RED locally and import pipeline/flows.json
Confirm MQTT messages are received
Verify data is written to InfluxDB Cloud
Open Grafana dashboard and observe live panels
Run ML analysis in analysis/ml_model.ipynb
Python Setup

Install required packages:

pip install -r requirements.txt
Machine Learning Summary
Task: Binary Classification
Model: Random Forest Classifier
Features: Soil, Humidity, Light, Stress
Output: Alert / No Alert
Included Evidence
Node-RED flow screenshot
InfluxDB screenshots
Grafana dashboard screenshots
Threshold alert proof
Confusion matrix
ROC curve
Notes

This is my first time using all of these programs, including Github, some things may not be formatted correctly.

Author

Timothy Davis
