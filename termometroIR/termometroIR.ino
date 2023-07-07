/*Código para el termómetro infrarrojo modelo GY-906 MLX90614.*/

/*Códigos de error:
200 --> Ok
401 --> Error al iniciar termómetro
402 --> Error al leer la temperatura
*/

//Librerías
#include <Wire.h>
#include <Adafruit_MLX90614.h>


/*Array para almacenar los códigos de estatus:
[0] --> Termómetro*/
int estatus [5]; //Espacio para 5 códigos de estatus.
int intento = 0; //Contador interno de void setup()


//Se asignan los valores de la función Adafruit_MLX90614() al objeto termometroIR
Adafruit_MLX90614 termometroIR = Adafruit_MLX90614();


void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  
  //Sí el código de estatus del termómetro es 200, se ejecuta el código correspondiente.
  while (intento < 1500) {
    if (termometroIR.begin() == 200) {
      estatus[0] = 200;
      Serial.println("Termómetro iniciado correctamente.");
      break;
    }
    else {
      estatus[0] = 401;
      Serial.println("Error al iniciar termómetro.");
      intento++;
    }
  }
}


void loop() {
  
}


// Función para imprimir los códigos de estatus.
void error_handling(String componente,int debug){
  Serial.print(componente + ": ");
  Serial.println(debug);
}
