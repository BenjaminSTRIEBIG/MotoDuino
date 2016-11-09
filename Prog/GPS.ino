#include <TinyGPS++.h> //Permet d utiliser le GPS
#include <SoftwareSerial.h> //Permet d utiliser les TxD et RxD

TinyGPSPlus gps; //Création objet Gps

SoftwareSerial gps_serial(10,0);    //Configuration du port Gps Tx sur le pin 19 (Rx1)

//Variables
int TimeHeure=0.0; //Heure de départ
int TimeMinute=0.0; //Heure de départ
double vitesseReele=0.0; //Vitesse Réelle
double coordDepartLat=0.0; //Latitude GPS
double coordDepartLng=0.0; //Longitude GPS

int verif = 0;

void setup() 
{
  Serial.begin(115200); //initialisation port série a 115200 bauds
  gps_serial.begin(9600); //initialisation port Rx1 a 9600 bauds

  Serial.println("...GPS...");
  Serial.println();
}

void loop() 
{
    while (gps_serial.available() > 0)
    {
    /************************ INITIALISATION DES VARIABLES POUR LA MOYENNE (coordoonnées et heure du départ) *************************/
      if(verif==0)
      {
        TimeHeure=(gps.time.hour()+1);
        TimeMinute=(gps.time.minute());
        coordDepartLat=gps.location.lat();
        coordDepartLng=gps.location.lng();
        vitesseReele=gps.speed.kmph();
          if(gps.location.isValid())
          {     
            // Permet d'incrémenter la variable verif afin de faire la boucle précedente une seule fois
             verif++; 
          } 
      }
    /************************ FIN INITIALISATION DES VARIABLES POUR LA MOYENNE (coordoonnées et heure du départ) *************************/
      if (gps.encode(gps_serial.read()));
    }//Fin While()

    /****Affichage****/
    Serial.print("Heure : "); Serial.print(TimeHeure); Serial.print(":"); Serial.println(TimeMinute);
    Serial.print("Vitesse : "); Serial.println(vitesseReele);
    Serial.print("Latitude : "); Serial.println(coordDepartLat);
    Serial.print("Longitude : "); Serial.println(coordDepartLng);
    Serial.println();
    /*****************/

}
