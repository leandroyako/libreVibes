void noteOn(byte notaActual) {
  if (tiempoTranscurrido[notaActual] > TIEMPO_LECTURA) { // ventana para deteccion de pico
    canal = i + 1;
    byte vel = map(maxVal[notaActual], umbral[notaActual], maxAmp[notaActual], 1, 127); //ajustar rango de velocity
    MIDI.sendNoteOn(transponer + notaActual, vel, canal); //enviar nota midi ON
    statusNota[notaActual] = MODO_DESCARTAR;
    tiempoInicio[notaActual] = millis();
    noteOnFlag[notaActual] = true;
  }
}
