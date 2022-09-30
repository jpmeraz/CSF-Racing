/*Código para el termómetro infrarrojo modelo GY-906 MLX90614.*/

/*Códigos de error:
200 --> Ok
401 --> Error al iniciar termómetro*/

//Librerías
#include <Wire.h>
#include <Adafruit_MLX90614.h>


/*Array para almacenar los códigos de estatus:
[0] --> Termómetro*/
int estatus [5]; //Espacio para 5 códigos de estatus.


//Se asignan los valores de la función Adafruit_MLX90614() al objeto termometroIR
Adafruit_MLX90614 termometroIR = Adafruit_MLX90614();


void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  
  //Sí el código de estatus del termómetro es 200, se ejecuta el código correspondiente.
  if (termometroIR.begin() == 1){
    estatus[0] = 200;
    error_handeling("Termometro", 200); //Imprime código de estatus
  }
  else{
    estatus[0] = 401;
    error_handeling("Termometro", 401); //Imprime código de estatus
  }

  delay(5000);
}


void loop() {
  if (estatus[0] == 200){
  float temperaturaAmbiente = termometroIR.readAmbientTempC();
  float temperaturaObjeto = termometroIR.readObjectTempC();

  Serial.print("Temp. ambiente => ");
  Serial.print(temperaturaAmbiente);
  Serial.println("ºC");

  Serial.print("Temp. objeto => ");
  Serial.print(temperaturaObjeto);
  Serial.println("ºC");
  }

  delay(500);
}


// Función para imprimir los códigos de estatus.
void error_handeling(String componente,int debug){
  Serial.print(componente + ": ");
  Serial.println(debug);
}
