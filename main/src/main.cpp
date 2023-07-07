/*Códigos de error:
200 --> Ok
401 --> Error al iniciar termómetro
402 --> Error al leer la temperatura
501 --> Error al iniciar la pantalla LCD
*/

/*Librerías*/
//Pantalla
#include <U8g2lib.h>
#include <SPI.h>

//Termómetro
#include <Wire.h>
#include <Adafruit_MLX90614.h>

//GPS
#include <TinyGPSPlus.h>
#include <Arduino.h>
#include <TimeLib.h> 


/*Protitipos de funciones*/
void bootUp_screen();
void clear_screen();
void mostrar_display(float temperaturaObjeto, float temperaturaAmbiente);
void error_handling(int componente, int debug);
bool newData();
int Velocidad();
char* Tiempo();
bool Switches(int Switch, int Relay);


/*Variables*/
#define lcdE 36
#define lcdRW 34
#define lcdRS 35
#define gpsTX 15
#define gpsRX 14
#define Switch1 31
#define Switch2 32
#define Switch3 33
#define Relay1 37
#define Relay2 38
#define Relay3 39

float temperaturaAmbiente = 0;
float temperaturaObjeto = 0;
int velocidad = 0;
bool isSwitch1 = false;
bool isSwitch2 = false;
bool isSwitch3 = false;
char Time[]  = "HORA: 00:00:00";
char NoTime[] = "HORA: --:--:--";

/*Objetos*/
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ lcdE, /* data=*/ lcdRW, /* CS=*/ lcdRS, /* reset=*/ U8X8_PIN_NONE); //E=clock=14, RW=data=13, RS=CS
Adafruit_MLX90614 termometroIR = Adafruit_MLX90614();
TinyGPSPlus gps;

/*Array para almacenar los códigos de estatus:
[0] --> Termómetro
[1] --> Pantalla LCD
[2] --> GPS
*/
int estatus [3]; //Espacio para 2 códigos de estatus.
String componentes [3] = {"Termómetro", "Pantalla LCD", "GPS"}; //Array para almacenar los nombres de los componentes.
int intento = 0; //Contador interno de void setup()

// Logotipo de la escudería
#define BORREGOS_SF_RACING_TEAM_W 43
#define BORREGOS_SF_RACING_TEAM_H 64
static const unsigned char BORREGOS_SF_RACING_TEAM[] U8X8_PROGMEM = {
   0xe0, 0xf3, 0xff, 0xff, 0x3f, 0x00, 0xf8, 0xf3, 0xff, 0xff, 0xff, 0x00,
   0xfc, 0xf3, 0xff, 0xff, 0xff, 0x01, 0xfe, 0xf1, 0xff, 0xff, 0xff, 0x03,
   0xfe, 0xe1, 0xff, 0xff, 0xff, 0x07, 0xff, 0xc2, 0xff, 0xff, 0xff, 0x07,
   0x7f, 0xda, 0xff, 0xff, 0xff, 0x07, 0x3f, 0xbb, 0xff, 0xff, 0xff, 0x07,
   0x9f, 0x7b, 0xfe, 0xff, 0xff, 0x07, 0xc3, 0xf3, 0xf8, 0x00, 0xff, 0x07,
   0xf0, 0xf3, 0x33, 0x00, 0x3c, 0x00, 0xff, 0xf3, 0x9f, 0x0f, 0x98, 0x07,
   0xff, 0xe1, 0xff, 0x3f, 0xf0, 0x07, 0xff, 0xe0, 0xff, 0xff, 0xe0, 0x07,
   0xff, 0xca, 0xff, 0xff, 0xc1, 0x07, 0x7f, 0x9a, 0xff, 0xfc, 0x83, 0x07,
   0x3f, 0x3b, 0x1f, 0xf0, 0x07, 0x07, 0x8f, 0x7b, 0x06, 0xc0, 0x0f, 0x06,
   0xe0, 0xf3, 0x03, 0x80, 0x1f, 0x00, 0xfc, 0xf3, 0x01, 0x00, 0x1f, 0x00,
   0xff, 0xf1, 0x01, 0x00, 0x3e, 0x00, 0xff, 0xe1, 0x00, 0x00, 0x3c, 0x00,
   0xff, 0xe0, 0xe0, 0x07, 0x1c, 0x00, 0xff, 0xda, 0xf0, 0x0f, 0x08, 0x00,
   0x7f, 0x9b, 0xf8, 0x1f, 0x00, 0x00, 0x9f, 0xbb, 0xf8, 0x3f, 0x00, 0x00,
   0xcf, 0xfb, 0xf8, 0x7f, 0x00, 0x00, 0xe0, 0xf3, 0x78, 0x7f, 0x00, 0x00,
   0xff, 0xf3, 0x78, 0xfe, 0x00, 0x00, 0xff, 0xf1, 0x78, 0x7c, 0x00, 0x00,
   0xff, 0xe1, 0xf9, 0x78, 0x00, 0x00, 0xff, 0xc0, 0xf9, 0x38, 0x00, 0x00,
   0x7f, 0xda, 0xf9, 0x31, 0x00, 0x00, 0x3f, 0xbb, 0xf3, 0x61, 0x00, 0x00,
   0x9f, 0x7b, 0xf2, 0xe1, 0x03, 0x00, 0xc3, 0xfb, 0xf2, 0x61, 0x0e, 0x00,
   0xf0, 0xf3, 0xe7, 0xc1, 0x1c, 0x00, 0xff, 0xf3, 0xef, 0xc1, 0x1c, 0x00,
   0xff, 0xe1, 0xcf, 0xc1, 0x30, 0x00, 0xff, 0xe0, 0xdf, 0xc1, 0x00, 0x00,
   0xff, 0xca, 0xbf, 0xc0, 0x00, 0x00, 0x7f, 0x9a, 0x7d, 0xc0, 0x00, 0x00,
   0x3f, 0x3b, 0x31, 0xe0, 0x00, 0x00, 0x8f, 0x7b, 0x02, 0xe0, 0x00, 0x00,
   0xe0, 0xfb, 0x06, 0xf0, 0x01, 0x00, 0xf8, 0xf3, 0x0f, 0x78, 0x02, 0x00,
   0xff, 0xf1, 0x3f, 0xfe, 0x06, 0x00, 0xff, 0xe5, 0xff, 0xe7, 0x06, 0x00,
   0xff, 0xec, 0xff, 0xcf, 0x0e, 0x00, 0xff, 0xde, 0xff, 0x9f, 0x0a, 0x00,
   0x7f, 0x9f, 0xff, 0x3f, 0x08, 0x00, 0x9f, 0x3f, 0xff, 0x3f, 0x0c, 0x00,
   0xcf, 0x7f, 0xfc, 0x7f, 0x1e, 0x00, 0xe0, 0xff, 0x01, 0x7e, 0x1e, 0x00,
   0xff, 0xff, 0xff, 0xf8, 0x1e, 0x06, 0xff, 0xff, 0xff, 0xf3, 0xfe, 0x07,
   0xff, 0xff, 0xff, 0xef, 0xe6, 0x07, 0xff, 0xff, 0xff, 0xcf, 0xf2, 0x07,
   0xff, 0xff, 0xff, 0x9f, 0xf8, 0x07, 0xfe, 0xff, 0xff, 0x3f, 0xfc, 0x07,
   0xfe, 0xff, 0xff, 0x7f, 0xfc, 0x03, 0xfc, 0xff, 0xff, 0x7f, 0xfe, 0x01,
   0xf8, 0xff, 0xff, 0x7f, 0xfe, 0x00, 0xe0, 0xff, 0xff, 0x7f, 0x3e, 0x00 };



void setup()
{
  Wire.begin();
  Serial.begin(115200);
  
  /*BOOTUP LCD
  Se intenta iniciar el LCD 3 veces, si no se obtiene respuesta de u8g.begin(), se da el código de estatus 401
  y se continúa con el programa.*/
  while (intento < 3){
    if (u8g2.begin() != 0){
      u8g2.setColorIndex(1); // pixels on
      u8g2.enableUTF8Print();
      error_handling(1, 200); // Se almacena e imprime el código de estatus.
      bootUp_screen();
      intento = 4;
    }
    else{
      estatus[1] = 501;
    }
    intento++;
  }
  intento = 0; // Se reinicia el contador de intentos.

  /*BOOTUP TERMOMETRO IR
  Se intenta iniciar el termómetro 3 veces, si no se obtiene respuesta de termometroIR.begin(), se da el 
  código de estatus 401*/
  while (intento < 3) {
    if (termometroIR.begin() == 1){
      error_handling(0, 200); // Se almacena e imprime el código de estatus.
      intento = 4;
    }
    else{
      estatus[0] = 401;
      error_handling(0, 401); // Se almacena e imprime el código de estatus.
    }
    intento++;
    delay(5000);
  }
  intento = 0; // Se reinicia el contador de intentos.

  /*BOOTUP GPS*/
  Serial3.begin(9600);

  /*BOOTUP SWITCHES*/
  pinMode(Switch1, INPUT);
  pinMode(Switch2, INPUT);
  pinMode(Switch3, INPUT);
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);

  delay(5000);
  clear_screen();
}


void loop()
{
  /*LECTURA DE TEMPERATURA*/
  if (estatus[0] == 200){
    temperaturaAmbiente = termometroIR.readAmbientTempC();
    temperaturaObjeto = termometroIR.readObjectTempC();
    if (!(isnan(temperaturaAmbiente))){
      delay(5);
    }
    else{
      estatus[0] = 402; // El modificar el estatus, loop no volverá a ejecutar el código del termometro.
      error_handling(0, 402); //Imprime código de estatus
    }
  }

  /*LECTURA DE VELOCIDAD*/
  if (newData())
  {
    velocidad = Velocidad();
  }

  /*SWITCHES*/
  isSwitch1 = Switches(Switch1, Relay1);
  isSwitch2 = Switches(Switch2, Relay2);
  isSwitch3 = Switches(Switch3, Relay3);

  /*IMPRIMIR EN LCD*/
  if (estatus[1] == 200){
      u8g2.firstPage();  
    do {
      mostrar_display(temperaturaObjeto, velocidad);
    } while(u8g2.nextPage());
  }

}

/*FUNCIONES*/
void bootUp_screen()
{
  // graphic commands to redraw the complete screen should be placed here
  // u8g.setFont(u8g_font_unifont);
  // u8g.setFont(u8g_font_helvB24);
  u8g2.setFont(u8g_font_profont17);
  u8g2.firstPage();
  do
  {
    u8g2.drawXBMP(0, 0, BORREGOS_SF_RACING_TEAM_W, BORREGOS_SF_RACING_TEAM_H, BORREGOS_SF_RACING_TEAM); // (x, y, width*8, height)
    u8g2.setFont(u8g2_font_helvB10_tf);
    u8g2.drawStr(46, 31, "MARI");
    u8g2.setFont(u8g2_font_6x13_tf);
    u8g2.drawStr(46, 45, "By SF RACING");
  } while (u8g2.nextPage());
  delay(6000);
} 

void clear_screen()
{
  u8g2.firstPage();
  do
  {
    u8g2.setColorIndex(0); // Clear pixel value
    u8g2.drawBox(0, 0, 64, 128); // Draw clear pixel in all LCD
  } while (u8g2.nextPage());
}

void mostrar_display(float temperaturaObjeto, float velocidad)
{
    u8g2.setFont(u8g2_font_helvB18_tf);
    u8g2.setColorIndex(1);
    u8g2.setCursor(7, 43);
    u8g2.print(velocidad, 1); //32 px
    u8g2.setCursor(71, 43);
    u8g2.print(temperaturaObjeto, 1); //32 px

    
    u8g2.setFont(u8g2_font_6x13_tf);
    u8g2.drawStr(20, 14, /*"#10 - SERGIO Z."*/Tiempo());

    u8g2.drawStr(13, 60, "KM/H");

    //u8g2.drawStr(10, 60, "KM/H"); //32 Px de ancho
    u8g2.drawStr(72, 60, "MOTOR");
    u8g2.drawUTF8(102, 60, "°");
    u8g2.drawStr(110, 60, "C"); //16 Px de ancho -- 8 pixeles mas que el simbolo °

}

// Función para imprimir los códigos de estatus.
void error_handling(int componente, int debug){
  estatus[componente] = debug; //Se guarda el código de estatus en el array.
  Serial.print(componentes[componente] + ": "); //Se imprime el nombre del componente.
  Serial.println(debug); //Se imprime el código de estatus.
}

bool newData(){
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial3.available())
    {
      if (gps.encode(Serial3.read()))
        return true;
    }
  }
  return false;
}

int Velocidad()
{
  if (gps.location.isValid() == 1)
  {
    return gps.speed.kmph();
  }
  else
  {
    return 0;
  }
}

char* Tiempo()
{
  if (gps.time.isValid() == 1)
  {
    // set current UTC time
    setTime(gps.time.hour(), gps.time.minute(), gps.time.second(), gps.date.day(), gps.date.month(), gps.date.year());
    // add the offset to get local time
    //adjustTime(-21600);

    Time[12] = second() / 10 + '0';
    Time[13] = second() % 10 + '0';
    Time[9]  = minute() / 10 + '0';
    Time[10] = minute() % 10 + '0';
    Time[6]  = (hour()-6)   / 10 + '0';
    Time[7]  = (hour()-6)  % 10 + '0';
    Serial.println(Time);
    return Time;
  }
  else
  {
    return NoTime;
  }
}

bool Switches(int Switch, int Relay){
    if (digitalRead(Switch) == HIGH)
  {
    digitalWrite(Relay, HIGH);
    return true;
  }
  else
  {
    digitalWrite(Relay, LOW);
    return false;
  }
}