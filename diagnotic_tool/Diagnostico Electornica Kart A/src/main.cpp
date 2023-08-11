#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#define chipSelect 10 // Pin CS (Chip Select) del lector de tarjetas SD
#define inputPin 3 // Pin digital para la entrada a medir (ejemplo: botón)
#define savePin 2 // Pin digital para el botón de guardado de datos

char FileName[14]; // Array para buscar archivos disponibles. Rango de trabajo 0-99.
bool isWorking = false; // Guarda el status del funcionamiento de la tarjeta SD en la sesión actuál.
bool saveBt = false; // Guarda el status del botón de guardado de datos.
int fileNumber = 0; // Variable para llevar el número del archivo

//Objetos
File dataFile; 

// Prototipos de funciones
void createDataFile();
void saveData(int state);

void setup() {
  pinMode(inputPin, INPUT); // Configurar el pin como entrada con resistencia pull-up
  pinMode(savePin, INPUT); // Configurar el pin como entrada con resistencia pull-up
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(115200);
  Serial.println("Lector de memorias SD H95 - Creación de archivos con mediciones High/Low");

  // Inicializar la comunicación con la tarjeta SD
  if (!SD.begin(chipSelect)) {
    isWorking = false;
    Serial.println("Error al inicializar la tarjeta SD.");
  }
  else{
    isWorking = true;
    Serial.println("Tarjeta SD inicializada correctamente.");
    createDataFile();
    dataFile = SD.open(FileName, FILE_WRITE);
  }
  
}

void loop() {
  int inputValue = 0;
  
  if (isWorking){
    while (!saveBt){
    // Leer el estado de la entrada (HIGH o LOW)
      inputValue = digitalRead(inputPin);

      // Imprimir estado en el monitor serial
      Serial.print("milis: ");
      Serial.print(millis());
      Serial.print("Entrada: ");
      Serial.println(inputValue);

      // Guardar datos en el archivo
      saveData(inputValue);

      // Esperar unos milisegundos antes de tomar la siguiente lectura
      delay(100);
      if (digitalRead(savePin) == HIGH){
        saveBt = true;
        dataFile.close();

        while (true){
          digitalWrite(LED_BUILTIN, HIGH);
          delay(1000);
          digitalWrite(LED_BUILTIN, LOW);
          delay(1000);
        }
        
      }
    }
  }
  else{
    Serial.println("Error al inicializar la tarjeta SD.");
    Serial.println("Reinicie el sistema.");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(3000);
  }
}

void createDataFile() {
  snprintf(FileName, 14, "datalog%d.csv", fileNumber); //concatena el nombre del archivo con un digito (0-99)
  while (SD.exists(FileName)){ // verifica si el archivo existe, en ese caso, se aumento factor de uno el numero en el nombre.
    Serial.println(FileName);
    fileNumber++; // Al existir un archivo con ese nombre, se aumenta el digito por un factor de 1.
    snprintf(FileName, 14, "datalog%d.csv", fileNumber); //concatena el nombre del archivo con nuevo digito.
  }
  // Al encontrar un nombre disponible:
  Serial.println("Se encotro un nombre desocupado");
  Serial.println(FileName);
  dataFile = SD.open(FileName, FILE_WRITE);
  if (dataFile){
    Serial.println("Archivo nuevo, Escribiendo en cabezado(fila 1)");
    dataFile.println("Tiempo (ms), Estado");
    dataFile.close();
    Serial.println("Archivo Creado");
  }
  else{
    Serial.println("Error creando el archivo datalog.csv");
  }
}

void saveData(int state) {
    digitalWrite(LED_BUILTIN, HIGH);
    // Obtener el tiempo en milisegundos
    unsigned long currentTime = millis();

    // Escribir datos en el archivo
    dataFile.print(currentTime);
    dataFile.print(", ");
    dataFile.println(0);
    digitalWrite(LED_BUILTIN, LOW);
}