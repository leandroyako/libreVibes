void descartarCola(byte notaActual) {
  if (statusNota[notaActual] == MODO_DESCARTAR) {
    tiempoTranscurrido[notaActual] = millis() - tiempoInicio[notaActual];
    if (tiempoTranscurrido[notaActual] > TIEMPO_DESCARTE) {
      statusNota[notaActual] = MODO_NOTEOFF;
      maxVal[notaActual] = 0;
    }
  }
}
