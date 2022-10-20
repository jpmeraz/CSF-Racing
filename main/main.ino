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


//U8G2LIB_ST7920_128X64 u8g2(10, 11, 13, U8G_PIN_NONE);
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R2, /* clock=*/ 10, /* data=*/ 11, /* CS=*/ 13, /* reset=*/ U8X8_PIN_NONE); // Feather HUZZAH ESP8266, E=clock=14, RW=data=13, RS=CS
Adafruit_MLX90614 termometroIR = Adafruit_MLX90614();


/*Array para almacenar los códigos de estatus:
[0] --> Termómetro
[1] --> Pantalla LCD*/
int estatus [2]; //Espacio para 2 códigos de estatus.
int intento = 0; //Contador interno de void setup()


// Logotipo de la escudería
#define BORREGOS_SF_RACING_TEAM_W 64
#define BORREGOS_SF_RACING_TEAM_H 95
static const unsigned char BORREGOS_SF_RACING_TEAM[] U8X8_PROGMEM = {
   0x00, 0x7f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x00, 0xe0, 0x7f, 0xfe, 0xff,
   0xff, 0xff, 0xff, 0x07, 0xf0, 0x7f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x0f,
   0xf8, 0x3f, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xfc, 0x3f, 0xfc, 0xff,
   0xff, 0xff, 0xff, 0x3f, 0xfe, 0x1f, 0xf8, 0xff, 0xff, 0xff, 0xff, 0x7f,
   0xfe, 0x1f, 0xf8, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0x0f, 0xf2, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x4f, 0xe2, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x67, 0xe6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x73, 0xce, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x71, 0x1e, 0xff, 0xff, 0xff, 0xff, 0xff,
   0x7f, 0x78, 0x3e, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x7e, 0x7e, 0xf8,
   0x1f, 0xc0, 0xff, 0xff, 0x00, 0x7f, 0xfe, 0x81, 0x07, 0x00, 0xff, 0x0f,
   0xc0, 0x7f, 0xfe, 0xc7, 0x01, 0x00, 0xfc, 0x01, 0xff, 0x3f, 0xfc, 0x7f,
   0x00, 0x00, 0x70, 0xf0, 0xff, 0x3f, 0xfc, 0x3f, 0xff, 0x07, 0x60, 0xfe,
   0xff, 0x1f, 0xf8, 0xdf, 0xff, 0x1f, 0xc0, 0xff, 0xff, 0x1f, 0xf8, 0xff,
   0xff, 0x7f, 0x80, 0xff, 0xff, 0x4f, 0xf2, 0xff, 0xff, 0xff, 0x00, 0xff,
   0xff, 0x4f, 0xe2, 0xff, 0xff, 0xff, 0x01, 0xfe, 0xff, 0x67, 0xc6, 0xff,
   0xff, 0xff, 0x03, 0xfc, 0xff, 0x73, 0x8e, 0xff, 0x01, 0xfe, 0x07, 0xf8,
   0xff, 0x79, 0x1e, 0x7f, 0x00, 0xf8, 0x0f, 0xf0, 0x7f, 0x7c, 0x3e, 0x1e,
   0x00, 0xf0, 0x1f, 0xe0, 0x1f, 0x7e, 0x7e, 0x0c, 0x00, 0xe0, 0x3f, 0xc0,
   0x00, 0x7f, 0xfe, 0x07, 0x00, 0xc0, 0x7f, 0x00, 0xe0, 0x7f, 0xfe, 0x03,
   0x00, 0x80, 0x7f, 0x00, 0xff, 0x3f, 0xfc, 0x01, 0x00, 0x00, 0xff, 0x00,
   0xff, 0x3f, 0xfc, 0x01, 0x00, 0x00, 0xfe, 0x01, 0xff, 0x1f, 0xf8, 0x00,
   0x00, 0x00, 0xfc, 0x01, 0xff, 0x1f, 0xf8, 0x00, 0x3c, 0x00, 0xfc, 0x00,
   0xff, 0x4f, 0xf2, 0x80, 0xff, 0x00, 0x78, 0x00, 0xff, 0x47, 0xe2, 0xc0,
   0xff, 0x03, 0x30, 0x00, 0xff, 0x67, 0xc6, 0xe0, 0xff, 0x07, 0x00, 0x00,
   0xff, 0x73, 0xce, 0xe0, 0xff, 0x07, 0x00, 0x00, 0xff, 0x78, 0xde, 0xf0,
   0xff, 0x0f, 0x00, 0x00, 0x7f, 0x7c, 0xfe, 0xf0, 0xff, 0x1f, 0x00, 0x00,
   0x1f, 0x7e, 0xfe, 0xf0, 0xff, 0x3f, 0x00, 0x00, 0x80, 0x7f, 0xfe, 0xf0,
   0xfb, 0x3f, 0x00, 0x00, 0xe0, 0x7f, 0xfc, 0xf0, 0xe3, 0x7f, 0x00, 0x00,
   0xff, 0x3f, 0xfc, 0xf0, 0xc3, 0x7f, 0x00, 0x00, 0xff, 0x3f, 0xfc, 0xf0,
   0x87, 0x3f, 0x00, 0x00, 0xff, 0x1f, 0xf8, 0xf0, 0x87, 0x3f, 0x00, 0x00,
   0xff, 0x1f, 0xf8, 0xf1, 0x07, 0x1f, 0x00, 0x00, 0xff, 0x0f, 0xf2, 0xf1,
   0x0f, 0x1e, 0x00, 0x00, 0xff, 0x47, 0xe2, 0xe1, 0x0f, 0x1e, 0x00, 0x00,
   0xff, 0x67, 0xc6, 0xe3, 0x1f, 0x1c, 0x00, 0x00, 0xff, 0x73, 0x8e, 0xe3,
   0x1f, 0x3c, 0x00, 0x00, 0xff, 0x78, 0x1e, 0xc3, 0x1f, 0xf8, 0x01, 0x00,
   0x7f, 0x7c, 0x3e, 0xc6, 0x1f, 0xf8, 0x07, 0x00, 0x1f, 0x7e, 0x7e, 0xc4,
   0x3f, 0x78, 0x1e, 0x00, 0x80, 0x7f, 0xfe, 0x8d, 0x3f, 0x70, 0x3c, 0x00,
   0xe0, 0x7f, 0xfc, 0x8f, 0x3f, 0x70, 0x7c, 0x00, 0xff, 0x3f, 0xfc, 0x1f,
   0x3f, 0x70, 0x78, 0x00, 0xff, 0x3f, 0xfc, 0x3f, 0x3f, 0xf0, 0xf0, 0x00,
   0xff, 0x1f, 0xf8, 0x3f, 0x1e, 0xf0, 0x00, 0x00, 0xff, 0x1f, 0xf0, 0x7f,
   0x1e, 0xe0, 0x00, 0x00, 0xff, 0x4f, 0xf2, 0xff, 0x1c, 0xe0, 0x00, 0x00,
   0xff, 0x47, 0xe6, 0xff, 0x0d, 0xe0, 0x00, 0x00, 0xff, 0x63, 0xc6, 0xfd,
   0x01, 0xf0, 0x00, 0x00, 0xff, 0x71, 0x8e, 0xf1, 0x03, 0xf0, 0x00, 0x00,
   0xff, 0x78, 0x1e, 0x03, 0x00, 0xf0, 0x00, 0x00, 0x7f, 0x7c, 0x3e, 0x06,
   0x00, 0xf8, 0x00, 0x00, 0x0f, 0x7e, 0x7e, 0x06, 0x00, 0xf8, 0x01, 0x00,
   0x80, 0x7f, 0xfe, 0x0d, 0x00, 0x7c, 0x03, 0x00, 0xf0, 0x7f, 0xfc, 0x1f,
   0x00, 0x7e, 0x03, 0x00, 0xff, 0x3f, 0xfc, 0x7f, 0x80, 0x7f, 0x06, 0x00,
   0xff, 0x3f, 0xfc, 0xff, 0xf3, 0x7d, 0x0e, 0x00, 0xff, 0x9f, 0xf9, 0xff,
   0xff, 0x78, 0x1e, 0x00, 0xff, 0x9f, 0xf1, 0xff, 0xff, 0x73, 0x1e, 0x00,
   0xff, 0xcf, 0xf3, 0xff, 0xff, 0x63, 0x16, 0x00, 0xff, 0xc7, 0xe7, 0xff,
   0xff, 0x47, 0x32, 0x00, 0xff, 0xe3, 0xc7, 0xff, 0xff, 0x4f, 0x32, 0x00,
   0xff, 0xf1, 0x8f, 0xff, 0xff, 0x1f, 0x38, 0x00, 0xff, 0xf8, 0x1f, 0xff,
   0xff, 0x1f, 0x38, 0x00, 0x7f, 0xfc, 0x3f, 0xfc, 0xff, 0x3f, 0x3c, 0x00,
   0x0f, 0xfe, 0xff, 0xf0, 0xff, 0x3f, 0x7c, 0x00, 0x80, 0xff, 0xff, 0x01,
   0xe0, 0x7f, 0x7e, 0x00, 0xf0, 0xff, 0xff, 0x0f, 0x00, 0x7f, 0x7e, 0x80,
   0xff, 0xff, 0xff, 0xff, 0x1f, 0x7e, 0xfe, 0xf8, 0xff, 0xff, 0xff, 0xff,
   0x7f, 0x7c, 0xde, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x78, 0x9e, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x73, 0xce, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x67, 0xe6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x47, 0xe2, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x4f, 0xf0, 0xff, 0xfe, 0xff, 0xff, 0xff,
   0xff, 0x1f, 0xf8, 0x7f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xf8, 0x7f,
   0xfc, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xfc, 0x3f, 0xf8, 0xff, 0xff, 0xff,
   0xff, 0x3f, 0xfc, 0x1f, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfe, 0x0f,
   0xe0, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfe, 0x07, 0x00, 0xff, 0xff, 0xff,
   0xff, 0x7f, 0xfe, 0x00 };


void setup()
{
  Serial.begin(9600);
  /*BOOTUP TERMOMETRO IR*/
  //Sí el código de estatus del termómetro es 200, se ejecuta el código correspondiente.
  while (intento < 3) {
    if (termometroIR.begin() == 1){
      estatus[0] = 200;
      error_handling("Termometro", 200); //Imprime código de estatus
      intento = 3;
    }
    else{
      estatus[0] = 401;
      error_handling("Termometro", 401); //Imprime código de estatus
    }
    intento++;
    delay(5000);
  }

  intento = 0; // Se reinicia el contador de intentos.

  /*BOOTUP LCD*/
  /* Se intenta iniciar el LCD 3 veces, si no se obtiene respuesta de u8g.begin(), se matiene el código de estatus 401
  y se continúa con el programa.*/
  while (intento < 3){
    if (u8g2.begin() != 0){
      u8g2.setColorIndex(1); // pixels on
      u8g2.enableUTF8Print();
      estatus[1] = 200;
      error_handling("LCD", 200); //Imprime código de estatus
      bootUp_screen();
      intento = 3;
      delay(5000);
      clear_screen();
    }
    else{
      estatus[1] = 501;
      //error_handling("LCD", 501); //Imprime código de estatus
    }
    intento++;
  }
delay(500);
}


void loop()
{
  float temperaturaAmbiente = termometroIR.readAmbientTempC();
  float temperaturaObjeto = termometroIR.readObjectTempC();
  /*LECTURA DE TEMPERATURA*/
  if (estatus[0] == 200){
    if (!(isnan(temperaturaAmbiente))){
      delay(5);
    }
    else{
      estatus[0] = 402; // El modificar el estatus, loop no volverá a ejecutar el código del termometro.
      error_handling("Termometro", 402); //Imprime código de estatus
    }
  }

  /*IMPRIMIR EN LCD*/
  if (estatus[1] == 200){
      u8g2.firstPage();  
    do {
      mostrar_display(temperaturaObjeto);
    } while(u8g2.nextPage());
  }
  delay(100);
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
    u8g2.drawXBMP(16, 0, BORREGOS_SF_RACING_TEAM_W, BORREGOS_SF_RACING_TEAM_H, BORREGOS_SF_RACING_TEAM); // (x, y, width*8, height)
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

void mostrar_display(float temperaturaObjeto)
{
    u8g2.setFont(u8g2_font_helvB10_tf);
    u8g2.setColorIndex(1);
    u8g2.setCursor(10, 43);
    u8g2.print(20, 1); //32 px
    u8g2.setCursor(50, 43);
    u8g2.print(temperaturaObjeto, 1); //32 px

    u8g2.setFont(u8g_font_7x14B);
    u8g2.drawStr(10, 14, "#10 - SERGIO Z.");
    u8g2.drawStr(10, 60, "KM/H"); //32 Px de ancho
    u8g2.drawStr(66, 60, "°C"); //16 Px de ancho

}


// Función para imprimir los códigos de estatus.
void error_handling(String componente, int debug){
  Serial.print(componente + ": ");
  Serial.println(debug);
}
