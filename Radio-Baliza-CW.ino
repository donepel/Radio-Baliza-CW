/******************************************************************
 * Radiobaliza CW que envia tonos de audio para ser modulados en FM. 
 * Diseñado para ser armada con Arduino 
 * by @Don_Epel
 * ,
 * Fecha 12/11/2019
 * 
 *****************************************************************/

/////////////////////////////////// DEFINICIONES //////////////////////////////////// 
 //Definiciones de puertos
 #define LED_TX      8   //PIN 08 como salida luminica testico de estado de TX
 #define LED_PAUSA    9   //PIN 09 como salida luminica testigo de pausa o estado de reposo
 #define LED_CW       10  //PIN 10 como salida luminica en CW testigo del audio emitido
 #define AUDIO        11  //PIN 11 como salida de audio
 #define PTT          12  //PIN 12 utilizado para pulsar el PTT de la radio
 
  //Definiciones de estados
 #define TRANSMISION  10  //Estado de transmision, pulsa el ptt y genera el tono audible
 #define REPOSO       20  //Estado de reposo, solo es una pausa hasta que vuelve a transmitir
 
 //Definiciones de variables
 #define PAUSA        1     //tiempo de pausa en minutos
 #define FREC         1000  //Defino la frecuencia FREC en herts y su correspondiente valor en 700 para el tono del CW
 #define DURACIONPTO  70   //duracion de cada punto, las rayas duran 3 puntos


 
///////////////////////////////////// SETUP ////////////////////////////////////////
void setup() 
{
  // Configuro los puertos ya sean entradas o salidas
  pinMode(AUDIO,OUTPUT); //seteo AUDIO como SALIDA
  pinMode(PTT,OUTPUT); //seteo PTT como SALIDA
  digitalWrite(AUDIO,LOW); //establezco AUDIO en 0 para su nivel inicial
  digitalWrite(PTT,LOW); //establezco PTT en 0 para su nivel inicial
  pinMode(LED_CW,OUTPUT); //seteo LED_CW como SALIDA
  digitalWrite(LED_CW,LOW); //establezco LED_CW en 0 para su nivel inicial
  pinMode(LED_CW,OUTPUT); //seteo LED_CW como SALIDA
  digitalWrite(LED_CW,LOW); //establezco LED_CW en 0 para su nivel inicial
  pinMode(LED_PAUSA,OUTPUT); //seteo LED_PAUSA como SALIDA
  digitalWrite(LED_PAUSA,LOW); //establezco LED_PAUSA en 0 para su nivel inicial 
  pinMode(LED_TX,OUTPUT); //seteo LED_PTT como SALIDA
  digitalWrite(LED_TX,LOW); //establezco LED_PTT en 0 para su nivel inicial
   
}

///////////////////////////////////// MAIN /////////////////////////////////////////////
void loop() 
{
 unsigned char estado=TRANSMISION;
 while(1)
 {
    switch(estado)
    {
      case TRANSMISION:
                        //Caso de transmision
                        digitalWrite(PTT,HIGH); //pulso el PTT de la radio
                        digitalWrite(LED_TX,HIGH);//Enciendo testigo TX
                        delay(500); // mantengo una pausa por si en el equipo transmisor existe alguna latencia interna
                                    // para no perder los primeros caracteres que se transmiten
                        //Genero los tonos de cw audibles
                        String textomorse = codificar("HOLA MUNDO ");
                        for(int i=0; i<=textomorse.length(); i++)
                        {
                          switch( textomorse[i] )
                            {
                              case '.': //punto
                                        for (unsigned int n=0; n<=DURACIONPTO; n++)
                                        {
                                          digitalWrite(LED_CW,HIGH); //Enciendo LED_CW CW
                                          Oscilador (AUDIO,FREC);
                                          digitalWrite(LED_CW,LOW); //Apago LED_CW CW
                                        }
                                        delay(DURACIONPTO);
                                        break;
                          
                              case '-': //raya
                                        for (unsigned int n=0; n<=DURACIONPTO*3; n++)
                                        {   
                                          digitalWrite(LED_CW,HIGH); //Enciendo LED_CW CW
                                          Oscilador (AUDIO,FREC);
                                          digitalWrite(LED_CW,LOW); //Enciendo LED_CW CW
                                         }
                                         delay(DURACIONPTO);
                                         break;
                                
                              case ' ': //espacio
                                        delay(DURACIONPTO);
                                        break;
                            }
                          }
                          estado=REPOSO; //Finalizada la transmision, paso a la etapa de reposo.
                          delay(500); //mantengo una pausa por si en el equipo transmisor existe alguna latencia interna
                          digitalWrite(PTT,LOW); //suelto el PTT de la radio
                          digitalWrite(LED_TX,LOW);//apago testigo TX
    case REPOSO:
                //Caso de reposo, espo durante la pausa 
               digitalWrite(LED_PAUSA,HIGH); //Aviso mediante testigo que me encuentro en periodo de pausa
               for(unsigned int n=0;n<=60*PAUSA ;n++) //la pausa da la cantidad de minutos
                  destello(LED_PAUSA);//delay de 1 segundo
               estado=TRANSMISION; //Finalizada la etapa re reposo, regreso a transmision.
               break;
    }
 }
}

/////////////////////////////////// FUNCIONES //////////////////////////////////////////

//Funcion de oscilador
//Descripcion: Se genera una señal cuadrada por el pin PUERTO de una frecuencia dada (FREC)
//Recibe: El puerto a oscilar y la frecuencia
//Retorna: Nada
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
//Descripcion: Codifica un texto en letras a morse (puntos y rayas)
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
    textomorse += "  "; //Agrego dos espacios de tiempo adicional para separar los caracteres
   }
  return textomorse;  
}

//Funcion destello
//Descripcion: Hace destellar un led por 1 vez segundo.
//Recibe: Nada.
//Retorna: Nada.
void destello(unsigned char led)
{
  digitalWrite(led,HIGH);
  delay(200);
  digitalWrite(led,LOW);
  delay(800);
}
