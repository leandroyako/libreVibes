int estadoPedIzq;
int ultimoEstadoPedIzq;
int ccPedIzq = 16;

void pedalIzq(){
  estadoPedIzq = digitalRead(pedalIzquierdo);
  if( estadoPedIzq == 1 && ultimoEstadoPedIzq == 0){
      MIDI.sendControlChange(ccPedIzq,0,1);
  } 
  if (estadoPedIzq == 0 && ultimoEstadoPedIzq == 1) {
        MIDI.sendControlChange(ccPedIzq,127,1);
      } 
      ultimoEstadoPedIzq = estadoPedIzq;
}

int estadoPedDer;
int ultimoEstadoPedDer;
int ccPedDer = 17;

void pedalDer(){
  estadoPedDer = digitalRead(pedalDerecho);
  if( estadoPedDer == 1 && ultimoEstadoPedDer == 0){
      MIDI.sendControlChange(ccPedDer,0,1);
  } 
  if (estadoPedDer == 0 && ultimoEstadoPedDer == 1) {
        MIDI.sendControlChange(ccPedDer,127,1);
      } 
      ultimoEstadoPedDer = estadoPedDer;
}



 
