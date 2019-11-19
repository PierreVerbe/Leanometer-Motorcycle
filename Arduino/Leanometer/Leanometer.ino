#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int MPU = 0x68; // I2C address of the MPU-6050
const int OLED = 0x3C; // I2C address of the OLED

int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

int16_t compteur = 90;

void setup()
{
  Serial.begin(9600);
  Serial.println(" _                                           _              ");
  Serial.println("| |                                         | |             ");
  Serial.println("| |     ___  __ _ _ __   ___  _ __ ___   ___| |_ ___ _ ___  ");
  Serial.println("| |    / _ \\/ _` | '_ \\ / _ \\| '_ ` _ \\ / _ \\ __/ _ \\ '__ | ");
  Serial.println("| |___|  __/ (_| | | | | (_) | | | | | |  __/ ||  __/ |     ");
  Serial.println("|______\\___|\\__,_|_| |_|\\___/|_| |_| |_|\\___|\\__\\___|_|     ");

  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  /*display.display();
  delay(500); // Pause for 0.5 seconde*/
  display.clearDisplay();// Clear the buffer

  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start at top-left corner
  display.println(F("Leanometre"));
  display.setTextSize(1);
  display.println(F("from Pierre Verbe"));
  display.println(compteur);
  display.display();      // Show initial text
  delay(500);

  /*Wire.endTransmission(OLED);*/

  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void loop()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(true);
  Wire.requestFrom(MPU, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
   Serial.println("Test terminal");
  Serial.print("AcX = ");
  Serial.println(AcX / 180);
  Serial.print("AcY = ");
  Serial.println(AcY / 180);
  Serial.print("AcZ = ");
  Serial.println(AcZ / 180);
  Serial.println();
  Serial.println();
  
  /*printAngleOLED(AcX / 180);*/
  /*compteur++;
    if (compteur == 255)compteur = 0;

    display.clearDisplay();
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(WHITE);        // Draw white text
    display.setCursor(0, 0);            // Start at top-left corner
    if (compteur == 1)
    {
    display.println(F("ma première ligne"));
    display.println(F("ma deux ligne"));
    }

    if (compteur == 2)
    {
    display.println(F(";)"));
    }*/
  /*Serial.println(compteur);*/

  /*while (compteur > 0) {
    printAngleOLED(compteur);
    display.display();
    delay(200);
    compteur--;
    }
    while (compteur < 90) {
    printAngleOLED(compteur);
    display.display();
    delay(200);
    compteur++;
    }*/


  /*printInfo();*/

  /*lcd.begin(16, 2);
    lcd.setCursor(1,1);
    lcd.print(AcX);
    lcd.setCursor(1,0);
    lcd.print(GyX);*/
  display.display();
  delay(2000);
}

void testdrawstyles(void) {
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0, 0);           // Start at top-left corner
  display.println(F("Hello, world!"));

  display.setTextColor(BLACK, WHITE); // Draw 'inverse' text
  display.println(3.141592);

  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.print(F("0x")); display.println(0xDEADBEEF, HEX);

  display.display();
  delay(2000);
}

// function to print on the OLED the actual angle
void printAngleOLED(int16_t angle) {
  display.clearDisplay();
  display.setTextSize(9);
  display.setTextColor(WHITE);
  display.setCursor(15, 0);
  display.println(angle);
}

// function to print stats on the OLED
void statsLeanometre(int16_t angle_r, int16_t angle_l) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("MAX ANGLE R: ");
  display.println(angle_r);
  display.print("MAX ANGLE L: ");
  display.println(angle_l);
  display.print("TIME TRAVEL : ");
  display.println();
}

// function use leds
void ledIndication(int16_t angle) {
  // middle green
  if (angle >= -10 && angle <= 10) {

  }

  // soft right yellow
  else if (angle > 10 && angle <= 45) {

  }

  // hard right red
  else if (angle > 45) {

  }

  // soft left yellow
  else if (angle < -10 && angle >= -45) {

  }

  // hard left red
  else if (angle < -45) {

  }
}

// function to print all the axis of the MP6050
void printGyro(int16_t AcX, int16_t AcY, int16_t AcZ) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(F("GYRO MPU6050"));
  display.print(F("AcX = "));
  display.println(AcX);
  display.print(F("AcY = "));
  display.println(AcY);
  display.print(F("AcZ = "));
  display.println(AcZ);
}

// function to print info about the angles
void printInfo(void) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(F("Scooter -> 40 deg"));
  display.println(F("Street Bike -> 50 deg"));
  display.println(F("Super sport -> 55 deg"));
  display.println(F("SBK -> 61 deg"));
  display.println(F("MotoGP -> 64 deg"));
}
