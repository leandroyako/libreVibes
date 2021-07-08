void noteOff(byte notaActual) {
  if (statusNota[notaActual] == MODO_NOTEOFF) {
    tiempoTranscurrido[notaActual] = millis() - tiempoInicio[notaActual];
    if (tiempoTranscurrido[notaActual] > TIEMPO_NOTEOFF) {
     // MIDI.sendNoteOff(transponer + notaActual, 0, canal); //enviar nota midi OFF
      statusNota[notaActual] = MODO_STANDBY;
      noteOnFlag[notaActual] = false;
    }
  }
}
/*
void apagar(byte notaActual) {
  if (valor[notaActual] > UMBRAL_APAGADO_MIN && valor[notaActual] < UMBRAL_APAGADO_MAX) {
    apagadoVal[notaActual] = valor[notaActual];
    indiceApagado++;
    if (indiceApagado > notaActual + cantValApagado) {
      i = 0;
    }
    if (apagadoVal[0] == apagadoVal[1] && apagadoVal[1] == apagadoVal[2] && statusNota[notaActual] != MODO_DESCARTAR) {
    //  if (millis() - tiempoApagado[notaActual] < TIEMPO_APAGADO) {
        //noteOff(notaActual);
        MIDI.sendNoteOff(39 + notaActual, 0, canal); //enviar nota midi OFF
    //    tiempoApagado[notaActual] = millis();
    //  }
    }
  }

}
*/

void apagar(byte notaActual) {
  if (valor[notaActual] > UMBRAL_APAGADO_MIN && valor[notaActual] < UMBRAL_APAGADO_MAX) {
    if (noteOnFlag[notaActual] == true) {
      tiempoApagado[notaActual] = millis();
      historial[index] = valor[notaActual];
      index++;
      if (index > 3) {
        index = 0;
      }
      if (historial[0] == historial[1]) {
        //     if (millis() - tiempoApagado[notaActual] < TIEMPO_APAGADO) {
        if (statusNota[notaActual] == MODO_STANDBY || statusNota[notaActual] == MODO_NOTEOFF) {
          MIDI.sendNoteOff(transponer + notaActual, 0, canal); //enviar nota midi OFF
          index = 0;
          noteOnFlag[notaActual] = false;
          //        tiempoApagado[notaActual] = millis();
        }
      }
    }
  }
}


