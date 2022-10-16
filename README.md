# Microclimate Measurement System
Microclimate measurement system with the esp32 microcontroller usage and graphical data visualisation.

## Getting Started
These instructions will get you a copy of the project, it will make it up and running on your local machine for development or usage.

### Microclimate measuring device construction
The device contains of:
* ESP-WROOM-32 DevKit
* DHT11 Temperature-Humidity Sensor
* Ssd1306 oled

Wiring diagram:
<div>
  <a>
    <img width="40%" src="https://raw.githubusercontent.com/Neutroo/Neutroo/main/Images/Microclimate%20Measurement%20System/WiringDiagram.png"/>
  </a>
</div>

### Prerequisites
1. Install [Docker](https://www.docker.com/products/docker-desktop/) on your system.
2. Install [sketch](https://github.com/Neutroo/Microclimate-Measurement-System/releases/download/1.0/Microclimate-device.zip) for device.
3. Open sketch in Arduino IDE.
4. Set up your wifi SSID and password.
```c++
#define WIFI_SSID "<your wifi name>"
#define WIFI_PASSWORD "your wifi password"
```
5. Set up your influxdb url, token, organization and bucket.
```c++
#define INFLUXDB_URL "http://<your influx server ip>:8086"
#define INFLUXDB_TOKEN "<your influx token>"
#define INFLUXDB_ORG "<your org name>"
#define INFLUXDB_BUCKET "<your bucket name>"
```

6. Upload a sketch to an Esp32.

### Installing
To download a copy of the project [click here](https://github.com/Neutroo/Microclimate-Measurement-System/archive/refs/tags/1.0.0.zip).

### Running the project
1. Optionally, change default credentials or Grafana provisioning.
2. Run the following command from the root of the installed project:
```
docker-compose up -d
```
3. Open InfluxDB via http://localhost:8086 or from docker and create API tokens for esp32 and Grafana.\
If you don't know how - read the [documentation](https://docs.influxdata.com/influxdb/cloud/security/tokens/create-token/).
4. Open Grafana via http://localhost:3000 and enter login and password:\
Login: admin\
Password: admin

<div>
  <a>
    <img width="40%" src="https://raw.githubusercontent.com/Neutroo/Neutroo/main/Images/Microclimate%20Measurement%20System/Screenshot%202022-10-16%20172917.png"/>
  </a>
</div>

5. Open dashboard in [dashboards menu](http://localhost:3000/dashboards)

## Results

![results](https://raw.githubusercontent.com/Neutroo/Neutroo/main/Images/Microclimate%20Measurement%20System/Screenshot%202022-10-16%20184433.png)

## Built With
* [Docker](https://www.docker.com/) - An application containerizer for automating the deployment and management of applications in containerized environments
* [InfluxDB](https://www.influxdata.com/) - Time-series database
* [Grafana](https://grafana.com/) - Data visualisation system

## Authors
* Rodion Kushnarenko - [Neutro](https://github.com/Neutroo)

## License 
This project is licensed under the MIT License - see the [LICENSE](https://github.com/neutroo/BinaryNumbers/blob/master/LICENSE) file for details.
