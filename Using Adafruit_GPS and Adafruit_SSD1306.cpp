#include <Adafruit_GPS.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

SoftwareSerial gpsSerial(9, 10); // RX, TX
Adafruit_GPS GPS(&gpsSerial);

double lat1, lon1, lat2, lon2, distance, charge;
const double meterRate = 0.5;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.print("starting..");
  display.clearDisplay();
  
  GPS.begin(9600);
  GPS.sendCommand("$PGCMD,33,0*6D"); 
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  delay(1000);
}

void loop() {
  if (GPS.available()) {
    GPS.read();
    if (GPS.fix) {
      lat2 = GPS.latitudeDegrees;
      lon2 = GPS.longitudeDegrees;

      if (lat1 != 0 && lon1 != 0) {
        distance += calculateDistance(lat1, lon1, lat2, lon2);
        charge = distance * meterRate;
        display.clearDisplay();
        display.setCursor(0,0);
        display.println("Distance: " + String(distance, 2) + " meters");
        display.println("Charge: Rs." + String(charge, 2));
        display.display();
      }

      lat1 = lat2;
      lon1 = lon2;
    }
  }
}

double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
  double radius = 6371000;
  double deltaLat = (lat2 - lat1) * PI / 180;
  double deltaLon = (lon2 - lon1) * PI / 180;
  double a = sin(deltaLat / 2) * sin(deltaLat / 2) +
             cos(lat1 * PI / 180) * cos(lat2 * PI / 180) *
             sin(deltaLon / 2) * sin(deltaLon / 2);
  double c = 2 * atan2(sqrt(a), sqrt(1-a));
  double distance = radius * c;
  return distance;
}






