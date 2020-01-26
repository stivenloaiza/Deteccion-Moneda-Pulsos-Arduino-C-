
  /***********************************************************************************************/
    const int limite_pulsos = 100; /* EDITAR ESTE VALOR PARA CAMBIAR EL DELAY ENTRE DETECCION DE PULSOS-nesecito poner un DELAY es como una pausa entre la deteccion de pulsos para que el arduino me lea los pulsos sin arrojar basura, eh calado multiples valores y 500 es el mas estable*/
  /***********************************************************************************************/
    const int coin_pin = 2; /*Asigno el valor de 2 para la variable donde conectare el pin que va a recibir los pulsos del monedero*/
    volatile byte cont_pulsos_moneda = 0;
    volatile byte pulsosTiempo = 0;
    volatile unsigned long tiempo_pulso;
    volatile unsigned long mili1=0;
    volatile unsigned long mili2=0;
    byte pulsos_total; 
    byte nueva_moneda=0;
   
   void setup(){
    Serial.begin(9600);
    Serial.println("Cargando Setup, por favor esperar...");
  
  
    pinMode(coin_pin, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(coin_pin), sumar_contador_moneda, RISING);

    Serial.println("Morralla Setup Cargado correctamente.");
  }/*fin de void setup()*/
  
    void sumar_contador_moneda() 
  {
    cont_pulsos_moneda++;
    tiempo_pulso = millis();
  }/*fin sumar_cont_moneda()*/

  void loop() {
  /*dejar de contar pulsos si hubo una interrupcion y el contador se incremento entonces hubo una moneda detectada (cont_pulsos_moneda>0) && si el tiempo actual menos el tiempo del ultimo pulso es mayor a los 500 milisegundos entonces hacer lo siguiente*/
    if (cont_pulsos_moneda >0 && millis()-tiempo_pulso > limite_pulsos){
      cli();/*disable interrupts*/
      nueva_moneda = cont_pulsos_moneda; /*Guardo el valor del total de pulsos en esta variable para liberar espacio en la variable cont_pulsos_moneda*/
      sei();/*enable interrupts*/
      Serial.print("Nueva moneda detectada ");/*me alerta en consola que hubo una moneda detectada*/
      Serial.println(nueva_moneda); /* imprime en consola el valor de esa moneda*/
      cli();/*disable interrupts*/
      cont_pulsos_moneda = 0; /*reseteo a 0 el contador de pulsos del interruptor*/
      sei();/*enable interrupts*/ 
      mili1=millis();
      if (mili1==0)
      {
        mili1=millis();
        
      }
      pulsosTiempo++;
    }
    
    if (mili1>0)
    {
      mili2=millis();
      if (mili2 > (mili1+2400))
      {
        switch (pulsosTiempo) {
    
          case 3:
          Serial.println("$100 vieja"); /*muestro en consola el valor de la moneda segun los pulsos leidos*/
          cli();/*disable interrupts*/
          nueva_moneda = 0; /*reseteo*/
          sei();/*enable interrupts*/
          break;
          
          case 7:
          Serial.println("$100 nueva "); /*muestro en consola el valor de la moneda segun los pulsos leidos*/
          cli();/*disable interrupts*/
          nueva_moneda = 0; /*reseteo*/
          sei();/*enable interrupts*/
          break;
          
          case 11:
          Serial.println("$200 vieja"); /*muestro en consola el valor de la moneda segun los pulsos leidos*/
          cli();/*disable interrupts*/
          nueva_moneda = 0; /*reseteo*/
          sei();/*enable interrupts*/
          break;
          
          case 15:
          Serial.println("$200 nueva"); /*muestro en consola el valor de la moneda segun los pulsos leidos*/
          cli();/*disable interrupts*/
          nueva_moneda = 0; /*reseteo*/
          sei();/*enable interrupts*/    
          break;
      
          case 19:
          Serial.println("$500"); /*muestro en consola el valor de la moneda segun los pulsos leidos*/
          cli();/*disable interrupts*/
          nueva_moneda = 0; /*reseteo*/
          sei();/*enable interrupts*/    
          break;
      
          case 23:
          Serial.println("$1000"); /*muestro en consola el valor de la moneda segun los pulsos leidos*/
          cli();/*disable interrupts*/
          nueva_moneda = 0; /*reseteo*/
          sei();/*enable interrupts*/    
          break;
          
          }/*fin de switch*/
          pulsosTiempo=0;
          mili1=0;
          mili2=0;
      }
    }
    
   
  }/*fin de void loop()*/
