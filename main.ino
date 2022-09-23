
// Libs Pantalla
#include "U8glib.h"

// Pins luz, ventilador, sonido
int luz_out = A3;
int vent_out = A2;
int s0und_out = 12;
//

U8GLIB_ST7920_128X64 u8g(13, 11, 10, U8G_PIN_NONE);
// LOGOTIPO DE LA ESCUDERÍA
const unsigned char BORREGOS_SF_TEAM_RACING[] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xE1, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xC1, 0x00, 0x00, 0x7C, 0x0F, 0x80, 0xE0, 0x78, 0x1F, 0x01, 0x80, 0xE0, 0x38, 0x1F, 0xFF, 0xFF,
    0xC1, 0x00, 0x00, 0x38, 0x07, 0x80, 0x40, 0x78, 0x0F, 0x01, 0x80, 0xE0, 0x30, 0x1F, 0xFF, 0xFF,
    0x83, 0x00, 0x00, 0x38, 0x07, 0x80, 0x40, 0x38, 0x0F, 0x01, 0x80, 0xC0, 0x10, 0x1F, 0xFF, 0xFF,
    0x83, 0x80, 0x00, 0x38, 0x03, 0x80, 0x40, 0x38, 0x07, 0x01, 0x00, 0xC0, 0x10, 0x1F, 0xFF, 0xFF,
    0x85, 0x80, 0x00, 0x18, 0xE3, 0x9E, 0x47, 0x19, 0xC7, 0x3F, 0x1F, 0xC7, 0x13, 0xFF, 0xFF, 0xFF,
    0x85, 0x40, 0x00, 0x18, 0xF3, 0x9C, 0x47, 0x19, 0xE3, 0x3F, 0x1F, 0xC7, 0x13, 0xFF, 0xFF, 0xFF,
    0x89, 0x40, 0x00, 0x18, 0xE3, 0x9C, 0x47, 0x99, 0xE3, 0x3F, 0x1F, 0xC7, 0x13, 0xFF, 0xFF, 0xFF,
    0x99, 0x20, 0xE0, 0x18, 0x07, 0x9C, 0x47, 0x99, 0xE3, 0x03, 0x18, 0x47, 0x10, 0x3F, 0xFF, 0xFF,
    0xF1, 0x19, 0xF8, 0x78, 0x07, 0x9C, 0x47, 0x19, 0xE3, 0x03, 0x18, 0x47, 0x10, 0x1F, 0xFF, 0xFF,
    0xC1, 0x03, 0xFD, 0xF8, 0x03, 0x9C, 0x47, 0x19, 0xC7, 0x03, 0x18, 0x47, 0x10, 0x0F, 0xFF, 0xFF,
    0x83, 0x04, 0x3D, 0x18, 0x03, 0x9C, 0x40, 0x38, 0x07, 0x3F, 0x18, 0x47, 0x18, 0x0F, 0xFF, 0xFF,
    0x83, 0x80, 0x1E, 0x18, 0xF1, 0x9C, 0x40, 0x38, 0x0F, 0x3F, 0x1E, 0x47, 0x1F, 0x8F, 0xFF, 0xFF,
    0x83, 0x80, 0x0F, 0x18, 0xF1, 0x9C, 0x40, 0x78, 0x0F, 0x3F, 0x1C, 0x47, 0x1F, 0x8F, 0xFF, 0xFF,
    0x85, 0x80, 0x07, 0x18, 0xF1, 0x9E, 0x40, 0x38, 0x0F, 0x3F, 0x1C, 0x47, 0x1F, 0x8F, 0xFF, 0xFF,
    0x85, 0x43, 0x83, 0x98, 0xF3, 0x9C, 0x46, 0x39, 0xC7, 0x01, 0x10, 0x47, 0x1F, 0x8F, 0xFF, 0xFF,
    0x89, 0x67, 0xC3, 0x98, 0x03, 0x80, 0x47, 0x39, 0xC7, 0x01, 0x00, 0x40, 0x10, 0x0F, 0xFF, 0xFF,
    0xB1, 0x2F, 0xE1, 0xF8, 0x07, 0x80, 0x47, 0x19, 0xE7, 0x01, 0x80, 0x40, 0x30, 0x0F, 0xFF, 0xFF,
    0xE1, 0x1F, 0xF1, 0xF8, 0x07, 0x80, 0xC7, 0x19, 0xE3, 0x01, 0x80, 0x60, 0x30, 0x1F, 0xFF, 0xFF,
    0x83, 0x1F, 0xF0, 0xFD, 0xFF, 0xFF, 0xEF, 0x99, 0xF3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x83, 0x1F, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x83, 0xBC, 0x79, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x85, 0xB8, 0x3D, 0xFC, 0x0E, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x85, 0x70, 0x3F, 0xFC, 0x0E, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x89, 0x70, 0x1F, 0xFC, 0x0E, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x99, 0x30, 0x1F, 0xF8, 0x0E, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xF1, 0x32, 0x0F, 0xF8, 0xFE, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x81, 0x31, 0x0F, 0xF8, 0xFE, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x83, 0x11, 0x1F, 0xF8, 0xFE, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x83, 0x91, 0x9F, 0xF8, 0x0E, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x83, 0x91, 0x9F, 0xFC, 0x06, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x85, 0x90, 0xDF, 0xFC, 0x06, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x8D, 0x58, 0xCF, 0xFE, 0x06, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x89, 0x28, 0xC7, 0xFF, 0xE6, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xB1, 0x28, 0xCB, 0xFF, 0xE6, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xE1, 0x08, 0xE9, 0xFF, 0xE6, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x83, 0x04, 0xE9, 0xFF, 0x86, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x83, 0x04, 0xEF, 0xF8, 0x06, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x83, 0x84, 0xEF, 0xF8, 0x06, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x85, 0x83, 0xEF, 0xF8, 0x0E, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x85, 0x53, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x89, 0x5F, 0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x99, 0x2F, 0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xF1, 0x0F, 0xC7, 0xF8, 0x0F, 0xF3, 0xF0, 0x11, 0x3C, 0xC0, 0x7E, 0x00, 0x80, 0x78, 0xF9, 0xF9,
    0x81, 0x07, 0x87, 0xF8, 0x07, 0xE1, 0xE0, 0x11, 0x3C, 0xC0, 0x7E, 0x00, 0x80, 0x78, 0xF9, 0xF9,
    0x83, 0x02, 0x4B, 0xF8, 0x07, 0xE1, 0xE0, 0x11, 0x1C, 0xC0, 0x7E, 0x00, 0x80, 0x78, 0x78, 0xF1,
    0x82, 0x80, 0x4B, 0xF8, 0x07, 0xE1, 0xE3, 0xF1, 0x1C, 0xC7, 0xFF, 0xC7, 0x8F, 0xF8, 0x78, 0xF1,
    0x82, 0x80, 0x23, 0xF8, 0xE3, 0xE1, 0xE3, 0xF1, 0x0C, 0xCF, 0xFF, 0xC7, 0x8F, 0xF8, 0x78, 0x71,
    0x84, 0x80, 0x3D, 0xF8, 0xE3, 0xE1, 0xE3, 0xF1, 0x0C, 0xCF, 0xFF, 0xC7, 0x8F, 0xF0, 0x78, 0x61,
    0x8C, 0x40, 0x19, 0xF8, 0xF1, 0xC0, 0xE3, 0xF1, 0x04, 0xCF, 0xFF, 0xC7, 0x8F, 0xF0, 0x78, 0x61,
    0x88, 0x20, 0x19, 0xF8, 0xF3, 0xC0, 0xE3, 0xF1, 0x04, 0xCC, 0x3F, 0xC7, 0x80, 0xF2, 0x38, 0x01,
    0xB0, 0x38, 0x19, 0xF8, 0xE3, 0xC8, 0xE3, 0xF1, 0x04, 0xCC, 0x3F, 0xC7, 0x80, 0xF2, 0x38, 0x01,
    0xE0, 0x0F, 0x89, 0xF8, 0xE3, 0xCC, 0xE3, 0xF1, 0x20, 0xCC, 0x3F, 0xC7, 0x80, 0xF2, 0x39, 0x09,
    0x80, 0x00, 0xC9, 0x98, 0x07, 0xCC, 0xE3, 0xF1, 0x20, 0xCE, 0x3F, 0xC7, 0x8F, 0xE3, 0x39, 0x09,
    0x80, 0x00, 0x4A, 0x18, 0x07, 0x8C, 0x63, 0xF1, 0x30, 0xCF, 0x3F, 0xC7, 0x8F, 0xE3, 0x39, 0x99,
    0x80, 0x00, 0x2E, 0x18, 0x07, 0x80, 0x63, 0xF1, 0x30, 0xCF, 0x3F, 0xC7, 0x8F, 0xE0, 0x19, 0x99,
    0x80, 0x00, 0x24, 0x18, 0xC7, 0x80, 0x63, 0xF1, 0x38, 0xCF, 0x3F, 0xC7, 0x8F, 0xE0, 0x19, 0xF9,
    0x80, 0x00, 0x1C, 0x38, 0xE7, 0x80, 0x60, 0x11, 0x38, 0xC0, 0x3F, 0xC7, 0x80, 0x60, 0x19, 0xF9,
    0x80, 0x00, 0x18, 0x38, 0xE3, 0x80, 0x60, 0x11, 0x3C, 0xC0, 0x3F, 0xC7, 0x80, 0x40, 0x19, 0xF9,
    0xC0, 0x00, 0x18, 0x38, 0xE3, 0x1E, 0x70, 0x11, 0x3C, 0xC0, 0x3F, 0xC7, 0x80, 0x47, 0x99, 0xF9,
    0xC0, 0x00, 0x08, 0x78, 0xF3, 0x1E, 0x30, 0x11, 0x3E, 0xE0, 0x3F, 0xC7, 0x80, 0x47, 0x89, 0xF9,
    0xE0, 0x00, 0x08, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
const unsigned char signogrados[] = {
    0x00,
    0x00,
    0x00,
    0x00,
};

// Libs Temperatura
#include <Wire.h>
#include <Adafruit_MLX90614.h>

// Instanciar objeto
Adafruit_MLX90614 termometroIR = Adafruit_MLX90614();

// Variable
float temperaturaAmbiente = 0;
float temperaturaObjeto = 0;

//

// velocidad
int encoder_pin = 2;                        // Pin 2, donde se conecta el encoder
unsigned int rpm = 0;                       // Revoluciones por minuto calculadas del motor
unsigned int rpm_wheel = 0;                 // Revoluciones por minuto calculadas de la rueda
float velocity = 0;                         // Velocidad en [Km/h]
volatile byte pulses = 0;                   // Número de pulsos leidos por el Arduino en un segundo
unsigned long timeold = 0;                  // Tiempo
unsigned int pulsesperturn = 20;            // Número de muescas que tiene el disco del encoder.
const int wheel_diameter = 250;             // Diámetro de la rueda [mm]
int engrane_motor = 16;                     // Dientes del engrane que va al motor
int engrane_rueda = 38;                     // Dientes del engrane que va a la rueda
int mechanical_adv = 0;                     // Numero de vueltas que da la rueda comparada con el motor
static volatile unsigned long debounce = 0; // Tiempo del rebote.
//

void setup()
{

  // LCD

  // flip screen, if required
  u8g.setRot180();

  // Initialize mlx sensor
  //  set SPI backup if required
  // u8g.setHardwareBackup(u8g_backup_avr_spi);

  // assign default color value
  if (u8g.getMode() == U8G_MODE_R3G3B2)
  {
    u8g.setColorIndex(255); // white
  }
  else if (u8g.getMode() == U8G_MODE_GRAY2BIT)
  {
    u8g.setColorIndex(3); // max intensity
  }
  else if (u8g.getMode() == U8G_MODE_BW)
  {
    u8g.setColorIndex(1); // pixel on
  }
  else if (u8g.getMode() == U8G_MODE_HICOLOR)
  {
    u8g.setHiColorByRGB(255, 255, 255);
  }
  bootUp_screen();

  clear_screen();

  // luz, ventilador, sonido
  pinMode(luz_out, OUTPUT);
  pinMode(vent_out, OUTPUT);
  pinMode(s0und_out, OUTPUT);

  digitalWrite(luz_out, HIGH);
  digitalWrite(vent_out, HIGH);
  //

  // tempeatura
  // Iniciar comunicación serie
  Serial.begin(9600);
  // Iniciar termómetro infrarrojo con Arduino
  termometroIR.begin();
  //

  // velocidad
  Serial.begin(9600);                  // Configuración del puerto serie
  pinMode(encoder_pin, INPUT);         // Configuración del pin nº2
  attachInterrupt(0, counter, RISING); // Configuración de la interrupción 0, donde esta conectado.
  pulses = 0;
  rpm = 0;
  timeold = 0;
  Serial.print("Seconds ");
  Serial.print("RPM");
  Serial.print("Pulses ");
  Serial.println("Velocity[Km/h]");
}
//

void loop()
{
  // put your main code here, to run repeatedly:
  // LCD
  mostrar_display();

  // temperatura
  //  Obtener temperaturas grados Celsius
  float temperaturaAmbiente = termometroIR.readAmbientTempC();
  float temperaturaObjeto = termometroIR.readObjectTempC();

  // Mostrar información
  Serial.print("Temp. ambiente => ");
  Serial.print(temperaturaAmbiente);
  Serial.println("ºC");

  Serial.print("Temp. objeto => ");
  Serial.print(temperaturaObjeto);
  Serial.println("ºC");

  delay(2000);

  // Si quieres mostrar la información en grados Fahrenheit utiliza las funciones
  // readAmbientTempF() para temperatura ambiente
  // readObjectTempF() para temperatura del objeto
  //

  // velocidad
  if (millis() - timeold >= 1000)
  {                                                                    // Se actualiza cada segundo
    noInterrupts();                                                    // Don’t process interrupts during calculations // Desconectamos la interrupción para que no actué en esta parte del programa.
    rpm = (60 * 1000 / pulsesperturn) / (millis() - timeold) * pulses; // Calculamos las revoluciones por minuto
    mechanical_adv = engrane_motor / engrane_rueda;
    rpm_wheel = mechanical_adv * rpm;
    velocity = rpm_wheel * 3.1416 * wheel_diameter * 60 / 1000000; // Cálculo de la velocidad en [Km/h]
    timeold = millis();                                            // Almacenamos el tiempo actual.
    Serial.print(millis() / 1000);
    Serial.print("       "); // Se envia al puerto serie el valor de tiempo, de las rpm y los pulsos.
    Serial.print(rpm_wheel, DEC);
    Serial.print("   ");
    Serial.print(pulses, DEC);
    Serial.print("     ");
    Serial.println(velocity, 2);
    pulses = 0;   // Inicializamos los pulsos.
    interrupts(); // Restart the interrupt processing // Reiniciamos la interrupción
  }
}

void counter()
{

  if (digitalRead(encoder_pin) && (micros() - debounce > 500) && digitalRead(encoder_pin))
  {                      // Vuelve a comprobar que el encoder envia una señal buena y luego comprueba que el tiempo es superior a 1000 microsegundos y vuelve a comprobar que la señal es correcta.
    debounce = micros(); // Almacena el tiempo para comprobar que no contamos el rebote que hay en la señal.
    pulses++;
  } // Suma el pulso bueno que entra.
  else
    ;
}
//

// -----------------------------------------------IMPRIME LOGOTIPO DE LA ESCUDERÍA----------------------------------------------------------------------
void bootUp_screen()
{
  // graphic commands to redraw the complete screen should be placed here
  // u8g.setFont(u8g_font_unifont);
  // u8g.setFont(u8g_font_helvB24);
  u8g.setFont(u8g_font_profont17);
  u8g.firstPage();
  do
  {
    u8g.drawBitmap(0, 0, 16, 64, BORREGOS_SF_TEAM_RACING);
  } while (u8g.nextPage());

  delay(6000);
}

//-------------------------------------------------LIMPIA LA PANTALLA------------------------------------------------------------------------
void clear_screen()
{
  u8g.firstPage();
  do
  {
    u8g.setColorIndex(0);
    u8g.drawBox(0, 0, 64, 128);
  } while (u8g.nextPage());
}

//------------------------------------------------------MOSTRAR INFORMACIÓN EN LCD 128X64 CON COMUNICACIÓN SPI---------------------------------------------------------

void mostrar_display()
{
  u8g.firstPage();
  do
  {
    u8g.setFont(u8g_font_7x14B);
    u8g.setColorIndex(1);

    u8g.drawBitmap(35, 35, 1, 4, signogrados);
    u8g.drawStr(38, 38, "C");
    u8g.setPrintPos(0, 38);
    u8g.print(temperaturaObjeto, 1);

    delay(10);
  } while (true);
}
