#include <Arduino.h>
#define PIN_DS 8    //pin 14 74HC595
#define PIN_STCP 9  //pin 12 74HC595
#define PIN_SHCP 10 //pin 11 74HC595

//Nombre de registres a décalage
#define NB_DMX 1
//Nombre total de pin de registre a décalage
#define NB_PIN_DMX NB_DMX * 8
//Créé un tableau contenant des booléen de la taille du nombre de pin des registres
boolean registers[NB_PIN_DMX];

void clearRegisters()
{
  for (int i = NB_PIN_DMX; i > 0; i--)
  {
    registers[i] = LOW;
  }
}

//Application des valeurs engregistrées dans le tableau "registers" et application (visualisation) des valeurs à la fin
void writeRegisters()
{
  digitalWrite(PIN_STCP, LOW);
  //Boucle pour affecter chaque pin des registres
  for (int i = NB_PIN_DMX; i > 0; i--)
  {
    digitalWrite(PIN_SHCP, LOW);
    int val = registers[i];
    digitalWrite(PIN_DS, val);
    digitalWrite(PIN_SHCP, HIGH);
  }
  //On applique toutes les valeurs au registres
  digitalWrite(PIN_STCP, HIGH);
}

void setup()
{
  pinMode(PIN_DS, OUTPUT);
  pinMode(PIN_STCP, OUTPUT);
  pinMode(PIN_SHCP, OUTPUT);
  //Remise à 0 des registres
  clearRegisters();
  //On applique les valeurs au registre à décalage
  writeRegisters();
}

void setRegisterPin(int index, int value)
{
  registers[index] = value;
}

void loop()
{
  for (int i = 0; i < 8; i++)
  {
    setRegisterPin(i, HIGH);
    writeRegisters();
    delay(500);
  }

  delay(2000);

  for (int i = 0; i < 8; i++)
  {
    setRegisterPin(i, LOW);
    writeRegisters();
    delay(500);
  }

  delay(2000);
}
