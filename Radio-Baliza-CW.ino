/******************************************************************
 * Radiobaliza CW que envia tonos de audio para ser modulados en FM. 
 * Diseñado para ser armada con Arduino 
 * by @Don_Epel
 * ,
 * Fecha 10/11/2019
 * Version 0.1
 *****************************************************************/

/////////////////////////////////// DEFINICIONES //////////////////////////////////// 
 #define AUDIO  11 //PIN 11 como salida de audio
 #define PTT    12 //PIN 12 utilizado para pulsar el PTT de la radio
 #define FREC   700 //Defino la frecuencia FREC en herts y su correspondiente valor en 700 para el tono del CW
  #define DURACIONPTO 80 //duracion de cada punto, las rayas duran 3 puntos
///////////////////////////////////// SETUP ////////////////////////////////////////

void setup() 
{
  // Configuro los puertos ya sean entradas o salidas
  pinMode(AUDIO,OUTPUT); //seteo AUDIO como SALIDA
  pinMode(PTT,OUTPUT); //seteo PTT como SALIDA
  digitalWrite(AUDIO,LOW); //establezco AUDIO en 0 para su nivel inicial
  digitalWrite(PTT,LOW); //establezco PTT en 0 para su nivel inicial
  
  
}

///////////////////////////////////// MAIN /////////////////////////////////////////////
void loop() 
{
  
String textomorse = codificar( "CQ CQ CQ DE XE1KK XE1KK XE1KK QUE LLAMA Y QUEDA ATENTO QRZ " );
  for(int i=0; i<=textomorse.length(); i++)
  {
    switch( textomorse[i] )
    {
      case '.': //punto
        for (unsigned int n=0; n<=DURACIONPTO*1; n++)
          Oscilador (AUDIO,FREC);
        
        delay( DURACIONPTO );
        break;

      case '-': //raya
        for (unsigned int n=0; n<=DURACIONPTO*3; n++)
          Oscilador (AUDIO,FREC);
        
        delay( DURACIONPTO );
        break;

      case ' ': //espacio
        delay( DURACIONPTO );
    }
  }
  delay (10000);
}



/////////////////////////////////// FUNCIONES //////////////////////////////////////////

//Funcion de oscilador
//Recibe: El puerto a oscilar y la frecuencia
//Retorna: Nada
//Nota: Se genera una señal cuadrada por el pin PUERTO de una frecuencia dada (FREC)
//Ejemplo de llamada Oscilador(PUERTO,FREC);
void Oscilador (unsigned char salida,unsigned int frecuencia)
{
    unsigned int periodo = 1000000/frecuencia; //Defino el periodo con la formula de T=1seg/frec en  ms
    //Armo un oscilador de la mitad del periodo calculado, mitad del ciclo en alto, mitad den bajo
    digitalWrite(salida,HIGH);
    delayMicroseconds(periodo/2);
    digitalWrite(salida,LOW);
    delayMicroseconds(periodo/2);
}

//Tabla de Morse
static const struct {const char letra, *codigo;} TablaMorse[] =
{
  //Letras
  { 'A', ".-" },
  { 'B', "-..." },
  { 'C', "-.-." },
  { 'D', "-.." },
  { 'E', "." },
  { 'F', "..-." },
  { 'G', "--." },
  { 'H', "...." },
  { 'I', ".." },
  { 'J', ".---" },
  { 'K', "-.-" },
  { 'L', ".-.." },
  { 'M', "--" },
  { 'N', "-." },
  { 'O', "---" },
  { 'P', ".--." },
  { 'Q', "--.-" },
  { 'R', ".-." },
  { 'S', "..." },
  { 'T', "-" },
  { 'U', "..-" },
  { 'V', "...-" },
  { 'W', ".--" },
  { 'X', "-..-" },
  { 'Y', "-.--" },
  { 'Z', "--.." },
  { ' ', "     " },//Espacio entre palabras, 7 unidades    
  //Numeros
  { '1', ".----" },
  { '2', "..---" },
  { '3', "...--" },
  { '4', "....-" },
  { '5', "....." },
  { '6', "-...." },
  { '7', "--..." },
  { '8', "---.." },
  { '9', "----." },
  { '0', "-----" },
  //Caracteres especiales  
  { '.', "·–·–·–" },
  { ',', "--..--" },
  { '?', "..--.." },
  { '!', "-.-.--" },
  { ':', "---..." },
  { ';', "-.-.-." },
  { '(', "-.--." },
  { ')', "-.--.-" },
  { '"', ".-..-." },
  { '@', ".--.-." },
  { '&', ".-..." },
};

//Funcion de codificar
//Recibe: string de texto para codificar a CW
//Retorna: string de texto codificado en CW
//Ejemplo codificar("CQ CQ CQ ");
String codificar(const char *string)
{
  size_t i, j;
  String textomorse = "";
  
  for( i = 0; string[i]; ++i )
  {
    for( j = 0; j < sizeof TablaMorse / sizeof *TablaMorse; ++j )
    {
      if( toupper(string[i]) == TablaMorse[j].letra )
      {
        textomorse += TablaMorse[j].codigo;
        break;
      }
    }
    textomorse += " "; //Agrego un espacio adicional para separar los caracteres
   }

  return textomorse;  
}
