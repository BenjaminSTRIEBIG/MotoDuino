#include <TinyGPS++.h> //Permet d utiliser le GPS
#include <SoftwareSerial.h> //Permet d utiliser les TxD et RxD
#include <LiquidCrystal.h> //Permet affichage sur écran lcd

TinyGPSPlus gps; //Création objet Gps

SoftwareSerial gps_serial(10,0);    //Configuration du port Gps Tx sur le pin 10

//LiquidCrystal lcd(8,9,4,5,6,7); //Initialise l'écran sur les pins

/*********Variables*********/
unsigned short dateAnnee=0; //Année en cours
unsigned short dateMois=0; //Mois en cours
unsigned short dateJour=0; //Jour en cours 

unsigned short timeHeure=0; //Heure de départ
unsigned short timeMinute=0; //Minutes de départ
unsigned short timeSec=0; //Secondes

double vitesseReele=0.0; //Vitesse Réelle

double altitudeKms=0.0; //Altitude

double locationLatitude=0.0; //Latitude
double locationLongitude=0.0; //Longitude

int nbrGPS=0; //Nombre de GPS en liaison

int verif = 0; //
/******* FIN VARIABLES *******/



void setup() 
{
  Serial.begin(115200); //initialisation port série a 115200 bauds
  gps_serial.begin(9600); //initialisation port Rx1 GPS a 9600 bauds

  //lcd.begin(16, 2); //Initialise l'écran lcd
}//Fin Void Setup

void loop() 
{
    while (gps_serial.available() > 0) //Verifie que le GPS est branché
    {
        gps.encode(gps_serial.read());

        
        if((gps.time.second())!=timeSec)
      {   
      /************************ PRISE DES INFORMATIONS DU GPS *****************************/
            dateAnnee=(gps.date.year());
            dateMois=(gps.date.month());
            dateJour=(gps.date.day());
    
            timeHeure=(gps.time.hour()+1);
            timeMinute=(gps.time.minute());
            timeSec=(gps.time.second());
    
            vitesseReele=(gps.speed.kmph());
    
            altitudeKms=(gps.altitude.meters()); //Fonctionne pas 
    
            locationLatitude=(gps.location.lat());
            locationLongitude=(gps.location.lng());
    
            nbrGPS=(gps.satellites.value()); //Fonctionne pas
            
            affichage(); 
      /************************ FIN PRISE DES INFORMATIONS DU GPS **************************/
      }//Fin if
    }//Fin While()





}//Fin Void Loop


void affichage()
{ 
  Serial.print("DATE : "); Serial.print(dateJour); Serial.print("/"); Serial.print(dateMois); Serial.print("/"); Serial.println(dateAnnee);
  Serial.print("HEURE : "); Serial.print(timeHeure); Serial.print(":"); Serial.println(timeMinute);
  Serial.print("VITESSE : "); Serial.println(vitesseReele);
  Serial.print("ALTITUDE : "); Serial.println(altitudeKms);
  Serial.print("LATITUDE : "); Serial.println(locationLatitude);
  Serial.print("LONGITUDE : "); Serial.println(locationLongitude);
  Serial.print("NBR GPS : "); Serial.println(nbrGPS);
  Serial.println();
  Serial.println();
}//Fin Affichage
