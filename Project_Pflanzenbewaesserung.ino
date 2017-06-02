#include <dht.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2); 
dht DHT;                          //DHT11-Modul initiallisieren
#define DHT11 7

int Bodensensor = A0;
int boden = 0;
int bodenfeuchtigkeit = 0;
int temp = 0;
int relais = 9;

void setup() {
  lcd.begin(16,2); 
  pinMode( relais, OUTPUT);
  
}

void loop() {
 boden = analogRead(Bodensensor);   //Bodenfeuchtigkeit auslesen
 temp = DHT.read11(DHT11);          //Temperatur auslesen
  lcd.setCursor(0,0);               //LCD,obere Reihe, Bodenfeuchtigkeit
  lcd.print("Bodenfeu.: ");
  bodenfeuchtigkeit = map(boden, 220, 1023, 100,0); //Sensorwert zu Prozenten umwandeln
  lcd.print(bodenfeuchtigkeit);
  lcd.print("%");
  lcd.setCursor(0,1);               //LCD,untere Reihe, Temperatur
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print((char)223);
  lcd.print("C");
  delay(1000);
  
  if(bodenfeuchtigkeit <= 30)        //Wenn zu trocken, Relais anschalten -> Pumpe an
    digitalWrite(relais, HIGH);
  else if(boden >= 50)
    digitalWrite(relais, LOW);
  else 
    digitalWrite(relais, LOW);

    
}
