#include <MIDI.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>
#include <midi_Defs.h>
#include <midi_Message.h>
MIDI_CREATE_DEFAULT_INSTANCE();

//*******************************************************************************************************************
// Defines
//*******************************************************************************************************************

#define TIEMPO_UMBRAL_DIN 100 // millis
#define TIEMPO_LECTURA 4 // millis
#define TIEMPO_DESCARTE 50 // millis
#define TIEMPO_NOTEOFF 10000 // millis
//#define TIEMPO_APAGADO 200 // millis
#define UMBRAL_DINAMICO 150
#define UMBRAL_DEFAULT 60
#define UMBRAL_APAGADO_MIN 8
#define UMBRAL_APAGADO_MAX 30
#define MODO_LEER 0
#define MODO_DESCARTAR 1
#define MODO_NOTEOFF 2
#define MODO_STANDBY 3
//#define MAX_VAL 1000

int pedalIzquierdo = 5; //los pines que estan mas lejos del arduino
int pedalDerecho = 6;


//*******************************************************************************************************************
// Variables globales
//*******************************************************************************************************************

const byte sensor[6] = {
  A0, A1, A2, A3, A4, A5
};  // Entrada de los multiplexers

byte i, j;
int r0 = 0;      //valor del select pin (s0)
int r1 = 0;      //valor del select pin (s1)
int r2 = 0;      //valor del select pin (s2)
byte contar[8] = {
  4, 6, 7, 5, 2, 1, 0, 3
};   //orden de lectura de los pins (para evitar exceso de jumpers en el PCB)


const byte numNota = sizeof(sensor) * 8;
const byte transponer = 36;
byte canal;
int valor[numNota];
int maxVal[numNota];
unsigned int tiempoInicio[numNota];
unsigned int tiempoTranscurrido[numNota];
unsigned int tiempoUmbral[numNota];
unsigned int tiempoApagado[numNota];
int statusNota[numNota];
int umbral[numNota];

/* 
  const int maxAmp[numNota] = {
  1005, 985, 1004, 1000, 970, 990, 1020, 990, 990, 1005, 985, 930,
  920, 700, 945, 825, 970, 1005, 830, 985, 840, 990, 985, 930,
  985, 1000, 980, 980, 980, 930, 990, 985, 990, 820, 600, 1000,
  1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
};
*/
const int maxAmp[numNota] = {
  1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
  1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
  1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
  1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
};

/*const byte cantValApagado = 3;
byte apagadoVal[numNota * cantValApagado];
*/
int index = 0; //damp
int historial[2]; //damp
boolean noteOnFlag[numNota]; //damp

// Define various ADC prescaler
const unsigned char PS_16 = (1 << ADPS2);
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0);
const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

//*******************************************************************************************************************
// Setup
//*******************************************************************************************************************

void setup()
{
  MIDI.begin();
  //Serial.begin(115200);
  Serial.begin(31250); //MIDI baud rate

  //Multiplexer
  pinMode(2, OUTPUT);    // s0
  pinMode(3, OUTPUT);    // s1
  pinMode(4, OUTPUT);    // s2
  
  pinMode(pedalIzquierdo, INPUT_PULLUP);
  pinMode(pedalDerecho, INPUT_PULLUP);

  // set up the ADC
  ADCSRA &= ~PS_128;  // remove bits set by Arduino library
  ADCSRA |= PS_32; // you can choose a prescaler from above. // PS_16, PS_32, PS_64 or PS_128
}
