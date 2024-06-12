#include "RTClib.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>




#define motor 2 
#define humedad 6 
#define flotador 16
#define horaInicio 3
#define minutoInicio 45
#define horaFin 4
#define minutoFin 45

#define OLED_RESET 13 
Adafruit_SSD1306 display(OLED_RESET);
/*Se define una condición para saber si en la librería esta definida la altura de 32 de lo contrario 
 *no dejara compilar el código hasta que se cambie la altura correcta desde la librería*/
#if (SSD1306_LCDHEIGHT != 32)
#error("Altura incorrecta, cambie en la librería de Adafruit_SSD1306.h!");
#endif


#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C 

// para la hora usamos el pin 4 y 5
RTC_DS1307 rtc;

int minuto,hora;
DateTime HoraFecha;

void setup() 
{
  Serial.begin(9600);
  rtc.begin();
  pinMode(motor, OUTPUT);
  pinMode(humedad, INPUT);
  pinMode(flotador, INPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  


}

void loop() 
{
  HoraFecha = rtc.now(); //obtenemos la hora y fecha actual
    
  minuto=HoraFecha.minute();
  hora=HoraFecha.hour();

  if(hora == horaInicio && minuto == minutoInicio && digitalRead(humedad)==1)
  {
    digitalWrite(motor, 1);
  }

  if(hora == horaFin && minuto == minutoFin)
  {
    digitalWrite(motor,0);
  }

  
  display.clearDisplay();
  display.setTextSize(1); //Establece el tamaño de fuente, admite tamaños de 1 a 8
  display.setTextColor(WHITE); //Establece el color 

  display.setCursor(0,0); //Establecer las coordenadas para mostrar la posición del texto
  display.println("HORA ACTUAL:");
  
  display.setCursor(50,10); //Establecer las coordenadas para mostrar la posición del texto
  display.println(hora);

  display.setCursor(50,20); //Establecer las coordenadas para mostrar la posición del texto
  display.println(":");

  display.setCursor(50,30); //Establecer las coordenadas para mostrar la posición del texto
  display.println(minuto);

  display.display(); //Muestra el texto 

}
