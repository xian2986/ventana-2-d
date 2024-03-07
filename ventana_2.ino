// Fecha: 07/3/2024
// Automatismo Ventana de coche
// Este programa controla una ventana de coche utilizando un Arduino.
// El botón conectado al pin 11 se utiliza para controlar la dirección de
// movimiento de la ventana este ira en un sentido u otro intermitentemente y
//pasando por paro, es decir un pulso, va hacia arriba, siguiente pulso, para, 
//siguiente, va hacia abajo... Los motores están conectados a los pines 12 y 13.
// y los finales de carrera o FDC estaran conectados a los pines 9 y 10
// Definición de los pines utilizados
#define FDC 9      // Pin para el final de carrera superior
#define FDC2 10    // Pin para el final de carrera inferior
#define boton 11   // Pin para el botón de control
#define abajo 12   // Pin para el motor de bajar la ventana
#define arriba 13  // Pin para el motor de subir la ventana

// Variables globales
int estado = 0;    // Variable para almacenar el estado del botón
int Direccion = 1; // Variable para almacenar la dirección del movimiento de la ventana (1 para subir, -1 para bajar)
bool run = false;  // Variable para controlar si el motor está en funcionamiento o no

// Configuración inicial
void setup() {
  // Configuración de los pines
  pinMode(FDC, INPUT);     // Pin del final de carrera superior como entrada
  pinMode(FDC2, INPUT);    // Pin del final de carrera inferior como entrada
  pinMode(boton, INPUT);   // Pin del botón como entrada
  pinMode(arriba, OUTPUT); // Pin del motor de subir como salida
  pinMode(abajo, OUTPUT);  // Pin del motor de bajar como salida
}

// Bucle principal
void loop() {
  // Espera a que se presione el botón
  while (digitalRead(boton)) {
    estado = HIGH; // Almacena que el botón ha sido presionado
  }

  // Si el botón está presionado
  if (estado == HIGH) {
    // Si el motor está en funcionamiento
    if (run == true) {
      digitalWrite(arriba, LOW); // Detiene el motor de subir la ventana
      digitalWrite(abajo, LOW);  // Detiene el motor de bajar la ventana
      run = false;               // Establece que el motor está parado
      Direccion *= -1;           // Invierte la dirección del movimiento
    } else {
      // Si el motor no está en funcionamiento
      if (Direccion == 1) {
        digitalWrite(arriba, HIGH); // Activa el motor de subir la ventana
      } else {
        digitalWrite(abajo, HIGH);  // Activa el motor de bajar la ventana
      }
      run = true; // Establece que el motor está en funcionamiento
    }
    estado = LOW; // Restablece el estado del botón
  }

  // Si se alcanza el final de carrera superior mientras la ventana sube
  if (digitalRead(FDC) && Direccion == 1) {
    digitalWrite(arriba, LOW); // Detiene el motor de subir la ventana
    run = false;                // Establece que el motor está parado
    Direccion *= -1;            // Invierte la dirección del movimiento
  }

  // Si se alcanza el final de carrera inferior mientras la ventana baja
  if (digitalRead(FDC2) && Direccion == -1) {
    digitalWrite(abajo, LOW); // Detiene el motor de bajar la ventana
    run = false;               // Establece que el motor está parado
    Direccion *= -1;           // Invierte la dirección del movimiento
  }
}
