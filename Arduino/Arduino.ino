// https://github.com/espressif/arduino-esp32
// https://esp32io.com/tutorials/esp32-lm35-temperature-sensor
// https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/
// https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/
// https://www.utmel.com/blog/categories/resistor/photoresistor-basics-types-principles-and-applications
// https://learn.sparkfun.com/tutorials/sik-experiment-guide-for-arduino---v32/experiment-6-reading-a-photoresistor
// https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/

int AnalogTemp = A3;
int DigitalTemp = 0;
double Temperature = 0;

int AnalogLight = A6;
int DigitalLight = 0;
int LightLevel =0 ;

int AnalogHum = A0;
int DigitalHum = 0;
int Humidity = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);       // setup serial

}

void loop() {
  // put your main code here, to run repeatedly:
  DigitalTemp = analogRead(AnalogTemp);     // read the analog value
  Temperature = (DigitalTemp / 4096.0) * 3300 * 0.1;  // 3.3v reference and 12 bits resolution
  DigitalLight = analogRead(AnalogLight);
  LightLevel = map(DigitalLight, 0, 4095, 0, 100);
  DigitalHum = analogRead(AnalogHum);
  Humidity = map(DigitalHum, 0, 4095, 100, 0);
  Serial.print("Raw value: ");
  Serial.print(DigitalTemp);
  Serial.print("\t Temperature : ");
  Serial.print(Temperature, 2);
  Serial.print("\t Raw value: ");
  Serial.print(DigitalLight);
  Serial.print("\t Light : ");
  Serial.print(LightLevel);
  Serial.print("\t Raw value: ");
  Serial.print(DigitalHum);
  Serial.print(" \t Humidity: ");
  Serial.println(Humidity);
  
  delay(1000);
}
