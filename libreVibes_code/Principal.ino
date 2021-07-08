//*******************************************************************************************************************
// Programa principal
//*******************************************************************************************************************

void loop()
{
  pedalIzq();
 // pedalDer();
  for (j = 0; j < 8; j++) { //seleccionar Pin
    r0 = bitRead(contar[j], 0);
    r1 = bitRead(contar[j], 1);
    r2 = bitRead(contar[j], 2);
    digitalWrite(2, r0);
    digitalWrite(3, r1);
    digitalWrite(4, r2);

    for (i = 0; i < sizeof(sensor); i++) { //seleccionar Mux
      byte notaActual = 8 * i + j;
      valor[notaActual] = analogRead(sensor[i]);

      apagar(notaActual);
      pasaUmbral(notaActual);
      detectorPico(notaActual);
      descartarCola(notaActual);
      noteOff(notaActual);
      resetUmbral(notaActual);
    }
  }
}
