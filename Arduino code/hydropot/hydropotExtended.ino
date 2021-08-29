#include <LiquidCrystal.h>
#include <dht.h>

class HydroLight{
  private:
  int red;
  int blue;
    public:

  // x red to 1 blue proportions
  HydroLight(int x){
    red= 255;
    blue=255/x;
  }
  int getBlue(){return blue;}
  int getRed(){return red;}
};

class HydroSensors{
    private:
  int waterPin;
    int photoResPin;
    int tempPin;
        dht DHT;

  public:
  HydroSensors(int waterPin,int photoResPin,int tempPin){
    this->waterPin=waterPin;
    this->photoResPin=photoResPin;
    this->tempPin=tempPin;
    pinMode(photoResPin, INPUT_PULLUP);

  }
  float readWaterLevel()
  {
    return map(((analogRead(waterPin))), 0,1023, 0, 100);
  }
    float readLight(){
     int res=map(((analogRead(photoResPin))), 0,1024, 0, 100);
    return res;
  }
    float readTemp() {
DHT.read11(tempPin);
      return DHT.temperature;
    }
    float readhumidity() {
      return DHT.humidity;
    }
    void readSensors(float *arr)
    {
      
      arr[0] = readWaterLevel();
      arr[1] = readLight();
      arr[2] = readTemp();
      arr[3] = readhumidity();
    }
  
};
int buttonState = 0;    
int proportions=5;
float values[4];
HydroLight light={proportions};
HydroSensors sensor={14,15,16};

void setup()
{
  Serial.begin(9600);
}

void readSensorsVerbose(){
    Serial.print("water level = ");
    Serial.print(values[0]);
    Serial.print("\t");
    Serial.print(" luminance = ");
    Serial.print(values[1]);
    Serial.print("\t");
    Serial.print(" temperature = ");
    Serial.print(values[2]);
    Serial.print("C  ");
    Serial.print("\t");
    Serial.print(" humidity = ");
    Serial.print(values[3]);
    Serial.print("%  ");
    Serial.print("\t");
    Serial.print(" light proportions = ");
    Serial.println(proportions);
}

void readSensors(){
    Serial.print(values[0]);// water
    Serial.print("\t");
    Serial.print(values[1]);// light 
    Serial.print("\t");
    Serial.print(values[2]);// temp
    Serial.print("\t");
    Serial.print(values[3]);// humidity
    Serial.print("\t");
    Serial.println(proportions);
}
void loop()
{
  proportions=map((analogRead(A3)), 0,1023, 1, 9);

  light=HydroLight(proportions);

  if(values[1]>75){
            analogWrite(10,light.getBlue());
      analogWrite(11,light.getRed());
  }
  else{
      analogWrite(10,0);
      analogWrite(11,0);
  }
    sensor.readSensors(values);
  readSensorsVerbose();  
  delay(5000);
}
