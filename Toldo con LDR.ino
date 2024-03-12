/************************************************************************+************************************************
*  Por outra parte, o control da velocidade do pregado/despregado faise tamén empregando un sensor de luminosidade (LDR),
*  de maneira que canto maior é a luminosidade, máis veloz é o motor no despregado e canto menor é a luminosidade,
*  menos veloz é o motor no pregado. O valor obtido do sensor de luminosidade categorízase en 5 niveis: 0, 1, 2, 3, 4 e 5,
*  de maneira que no nivel 1 a velocidade do motor será do 20%, no nivel 2 do 40% e así sucesivamente até que no nivel 5
*  a velocidade do motor é do 100%. No nivel 0 a velocidade do motor é do 5%.
*
*
*  Autor: Javier Figueiro Resúa
*  Data: Marzo 2024
*
**************************************************************************************************************************/

//Definir pins de entrada e saída
const int pinEntrada = 13;
const int pinSalida1 = 8;
const int pinSalida2 = 7;
const int pinFinal1 = 11;
const int pinFinal2 = 12;
const int ldr = A0;
const int salidaAlimentacion = 5;

const int valorMaximo = 679;
const int valor1 = 34;
const int valor2 = 136;
const int valor3 = 271;
const int valor4 = 407;
const int valor5 = 543;

const int velocidadMaxima = 255;
const int velocidad1 = 12;
const int velocidad2 = 51;
const int velocidad3 = 102;
const int velocidad4 = 153;
const int velocidad5 = 204;

// 12, 51, 102, 153, 204

//Variabel para almacenar o estado da entrada
int estadoEntradaAnterior = LOW;
//Variabel para controlar que a saída está activa
int salidaActiva = 0;
int estadoEntrada = 0;
int direccion = 0; // 0 abajo 1 arriba
int valorPinFinal1 = 0;
int valorPinFinal2 = 0;
int valorLdr = 0;
int velocidadActual = 0;

void setup(){
  //Iniciar os pins
  pinMode(pinEntrada, INPUT);
  pinMode(pinFinal1, INPUT);
  pinMode(pinFinal2, INPUT);
  
  pinMode(pinSalida1, OUTPUT);
  pinMode(pinSalida2, OUTPUT);
  pinMode(salidaAlimentacion, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  //Ler o estado actual da entrada
  // int estadoEntrada = digitalRead(pinEntrada);
  valorPinFinal1 = digitalRead(pinFinal1);
  valorPinFinal2 = digitalRead(pinFinal2);
  valorLdr = analogRead(ldr);
	
  while(digitalRead(pinEntrada)) {
  	estadoEntrada = 1;
  }
  
  if (estadoEntrada) { // Si se ha detectado una pulsación
    estadoEntrada = 0; // Se resetea el valor del pulsador
    if (salidaActiva) { // Revisa si se está moviendo la ventanaa
      	direccion = !direccion;	// Se cambia la dirección
      
    	digitalWrite(pinSalida1, LOW); // Se apagan los dos motores
      	digitalWrite(pinSalida2, LOW);
      	
      	salidaActiva = 0; // Se indica que se dejo de mover la ventana
    } else {
    	salidaActiva = 1; // Se indica que se mueve la ventana
   		
    	if (direccion) { // Si dirrecion es 1 (arriba)
    		digitalWrite(pinSalida1, HIGH); // Se enciende el motor
   		} else { // Si no (abajo)
    		digitalWrite(pinSalida2, HIGH); // Se enciende el otro motor
    	}
   	  }
  }
  
  if (valorPinFinal1) { // Si se detecta una pulsación del final de carrera de arriba
    direccion = 0; // Se cambia la dirección
    salidaActiva = 0; // Se indica que se deja de mover la ventana
  	digitalWrite(pinSalida1, LOW); // Se apaga el motor
  }
  
  if (valorPinFinal2) { // Si se detecta una pulsación del final de carrera de abajo
    direccion = 1; // Se cambia la dirección
    salidaActiva = 0; // Se indica que se dejó de mover la ventana
  	digitalWrite(pinSalida2, LOW); // Se apaga el motor
  }
  
  if (valorLdr <= valor1)  {
		velocidadActual = velocidad1;
  } else if (valorLdr <= valor2) {
  		velocidadActual = velocidad2;
  } else if (valorLdr <= valor3) {
  		velocidadActual = velocidad3;
  } else if (valorLdr <= valor4) {
  		velocidadActual = velocidad4;
  } else if (valorLdr <= valor5) {
  		velocidadActual = velocidad5;
  } else {
  		velocidadActual = velocidadMaxima;
  }
  
  analogWrite(salidaAlimentacion, velocidadActual);
  
  delay (10);
  //actualizamos estado anterior da entrada
  estadoEntradaAnterior = estadoEntrada;
}
  
