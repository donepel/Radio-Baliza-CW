/*********************************************************
 * Radiobaliza CW que envia tonos de audio armada con Arduino Mega 
 * by @Don_Epel
 * 
 * Fecha 10/11/2019
 * Version 0.1
 *********************************************************/
 
 #define AUDIO  11 //PIN 11 como salida de audio
 #define PTT    12 //PIN 12 utilizado para pulsar el PTT de la radio
 #define FREC   700 //Defino la frecuencia FREC en herts y su correspondiente valor en 700 para el tono del CW

void setup() 
{
  // Configuro los puertos ya sean entradas o salidas
  pinMode(AUDIO,OUTPUT); //seteo AUDIO como SALIDA
  pinMode(PTT,OUTPUT); //seteo PTT como SALIDA
  digitalWrite(AUDIO,LOW); //establezco AUDIO en 0 para su nivel inicial
  digitalWrite(PTT,LOW); //establezco PTT en 0 para su nivel inicial
  Serial.begin(9600); //inicializo el puerto serie para debug
}

void loop() 
{
  // put your main code here, to run repeatedly:
Oscilador (AUDIO,FREC);
}

//Funcion de oscilador
//Recibe: El puerto a oscilar y la frecuencia
//Retorna: Nada
//Nota: Se genera una señal cuadrada por el pin PUERTO de una frecuencia dada (FREC)
//Ejemplo de llamada Oscilador(PUERTO,FREC);
void Oscilador (unsigned char salida,unsigned int frecuencia)
{
    unsigned int periodo = 100000/frecuencia; //Defino el periodo con la formula de T=1seg/frec en  ms
    //Armo un oscilador de la mitad del periodo calculado, mitad del ciclo en alto, mitad den bajo
    digitalWrite(salida,HIGH);
    delayMicroseconds(periodo/2);
    digitalWrite(salida,LOW);
    delayMicroseconds(periodo/2);
}
