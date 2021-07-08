void pasaUmbral(byte notaActual) {
  if ( valor[notaActual] > umbral[notaActual] ) {
    if (statusNota[notaActual] == MODO_STANDBY || statusNota[notaActual] == MODO_NOTEOFF) {
      tiempoInicio[notaActual] = millis();
      statusNota[notaActual] = MODO_LEER;
      maxVal[notaActual] = valor[notaActual];
      umbralDinamico(notaActual);
    }
  }
}

void umbralDinamico(byte notaActual) {
   for (int i = 0; i < numNota; i++) {
    if (statusNota[i] != MODO_LEER) {
      umbral[i] = UMBRAL_DINAMICO; //maxVal[notaActual]/2;
      tiempoUmbral[i] = millis();
    }
  }
}

void resetUmbral(byte notaActual) {
  if (statusNota[notaActual] != MODO_LEER) {
    if (millis() - tiempoUmbral[notaActual] > TIEMPO_UMBRAL_DIN) {
      umbral[notaActual] = UMBRAL_DEFAULT;
    }
  }
}

