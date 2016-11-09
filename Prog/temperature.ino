/****************************************************/
/*    Gestion de la témpérature avec affichage      */
/****************************************************/

#include <LiquidCrystal.h> //Gestion de l'écran LCD
#include <OneWire.h> //Gestion de l'I2DC

// Variables sonde DS18B20 étanche(moteur)
const int DS18B20_PIN=10;
const int DS18B20_ID=0x28;

OneWire ds(DS18B20_PIN); // Déclaration objet "ds" sur pin DS18B20_PIN (10) (résistance de 4.7K )

float DS18B20_temperature; //Contiendra la température

// Initialisation des pins utilisé par l'écran (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(22, 23, 24, 25, 26, 27);

void setup() {

  lcd.begin(16, 2); //lancement de l'écran LCD 2 lignes * 16 caractères

  Serial.begin(9600); //Port série a 9600 bauds
  Serial.println("Initialisation du programme");
}

void loop() {
  // Lancement de la fonction d'acquisition de T°
  DS18B20_temperature = getTemperatureDS18b20(); 
  
  // Curseur à la colonne 0, ligne 0
  lcd.setCursor(0, 0);
  // Affichage de la température en temps réel
  lcd.print("Temp : ");
  lcd.print(DS18B20_temperature);
  lcd.print(" ");
  lcd.print((char)223);
  lcd.print("C");
}

/*#################################*/
/*# Acquisition de la température #*/
/*#################################*/
float getTemperatureDS18b20(){
byte i;
byte data[12];
byte addr[8];
float temp =0.0;

//Il n'y a qu'un seul capteur, donc on charge l'unique adresse.
ds.search(addr);

// Cette fonction sert à surveiller si la transmission s'est bien passée
if (OneWire::crc8( addr, 7) != addr[7]) {
Serial.println("getTemperatureDS18b20 : <!> CRC is not valid! <!>");
return false;
}

// On vérifie que l'élément trouvé est bien un DS18B20
if (addr[0] != DS18B20_ID) {
Serial.println("L'équipement trouvé n'est pas un DS18B20");
return false;
}

// Demander au capteur de mémoriser la température et lui laisser 850ms pour le faire (voir datasheet)
ds.reset();
ds.select(addr);
ds.write(0x44);
delay(850);
// Demander au capteur de nous envoyer la température mémorisé
ds.reset();
ds.select(addr);
ds.write(0xBE);

// Le MOT reçu du capteur fait 9 octets, on les charge donc un par un dans le tableau data[]
for ( i = 0; i < 9; i++) {
data[i] = ds.read();
}
// Puis on converti la température (*0.0625 car la température est stockée sur 12 bits)
temp = ( (data[1] << 8) + data[0] )*0.0625;

return temp;
}
