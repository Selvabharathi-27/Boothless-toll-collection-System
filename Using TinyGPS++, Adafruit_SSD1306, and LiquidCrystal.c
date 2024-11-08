#include <Adafruit_SSD1306.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

static const int RXPin = 7, TXPin = 8;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

float lat1 = 0.0, lon1 = 0.0, lat2 = 0.0, lon2 = 0.0;
float distance = 0.0, totalDistance = 0.0;
float pricePerKm = 5.0;

const int rs = 4, rw = 3, en = 2, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, rw, en, d4, d5, d6, d7);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("starting..");
  display.display();

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GPS Initializing...");
  lcd.setCursor(0,1);

  Serial.begin(9600);
  ss.begin(GPSBaud);
}

void loop() {
  while (ss.available() > 0) {
    gps.encode(ss.read());
  }

  if (gps.location.isUpdated()) {
    lat2 = gps.location.lat();
    lon2 = gps.location.lng();

    if (lat1 != 0.0 && lon1 != 0.0) {
      distance = TinyGPSPlus::distanceBetween(lat1, lon1, lat2, lon2) / 1000.0;
      totalDistance += distance;
      float price = totalDistance * pricePerKm;

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Distance:");
      lcd.print(totalDistance, 4);
      lcd.setCursor(0,1);
      lcd.print("Price: ");
      lcd.print(price, 2);

      String gps_speed = String(gps.speed.kmph());
      lcd.setCursor(0,1);
      lcd.print("speed:");
      lcd.print(gps.speed.kmph());
      lcd.print("km/hr");

      display.setCursor(75, 20);
      display.setTextSize(1);
      display.print("speed:");
      display.print(gps.speed.kmph());
      display.setCursor(16, 50);
      display.setTextSize(1);
      display.print(" Km/h");
    }

    lat1 = lat2;
    lon1 = lon2;
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






