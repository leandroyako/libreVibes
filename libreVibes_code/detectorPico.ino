void detectorPico(byte notaActual) {
  if (statusNota[notaActual] == MODO_LEER) {
    if (valor[notaActual] > maxVal[notaActual]) {
      maxVal[notaActual] = valor[notaActual];
    }
    tiempoTranscurrido[notaActual] = millis() - tiempoInicio[notaActual];
    noteOn(notaActual);
  }
}
