//audio.h
void sonido_pasos(){
     play_sample ( (SAMPLE *)datos_del_juego[dspasos].dat, 70,128, 3300, 0 );
}

void sonido_abrirpuerta(){
     play_sample ( (SAMPLE *)datos_del_juego[dsabrir_puerta].dat, 100,128, 1300, 0 );
}

void sonido_ambiente(){
     play_sample ( (SAMPLE *)datos_del_juego[dsbosque].dat, 50,128, 900, 1 );
}

void para_sonido_ambiente(){
     stop_sample( (SAMPLE *)datos_del_juego[dsbosque].dat );
}
void musica_casa(){
     play_midi((MIDI *)datos_del_juego[dmcasa].dat,1);
}
void sonido_sube_nivel(){
    play_sample ( (SAMPLE *)datos_del_juego[dssubedenivel].dat, 110,128, 1300, 0 );
}
void musica_menu(){
     play_midi((MIDI *)datos_del_juego[dmmenu].dat,1);
}

void musica_bosque(){
     play_midi((MIDI *)datos_del_juego[dmbosque].dat,1);
}
void musica_ciudad1(){
     play_midi((MIDI *)datos_del_juego[dmciudad].dat,1);
}
void sonido_espada_aire(){
    play_sample ( (SAMPLE *)datos_del_juego[dsespada1].dat, 100,128, 1200, 0 );
}

void sonido_espada_da(){
    play_sample ( (SAMPLE *)datos_del_juego[dsespada2].dat, 160,128, 2300, 0 );
}

void sonido_muere(){
    play_sample ( (SAMPLE *)datos_del_juego[dsmuerte01].dat, 120,128, 1000, 0 );
}
void musica_batalla(){
    play_midi((MIDI *)datos_del_juego[dmbatalla].dat,1);
}
void sonido_espada_choca(){
    play_sample ( (SAMPLE *)datos_del_juego[dsespada3].dat, 110,128, 900, 0 );
}

void sonido_herido(){
    play_sample ( (SAMPLE *)datos_del_juego[dsaa].dat, 160,128, 900, 0 );
}
void sonido_boton(){
    play_sample ( (SAMPLE *)datos_del_juego[dsboton1].dat, 110,128, 1100, 0);
}
void sonido_boton2(){
    play_sample ( (SAMPLE *)datos_del_juego[dsboton2].dat, 110,128, 1400, 0);
}
void sonido_error(){
    play_sample ( (SAMPLE *)datos_del_juego[dserror].dat, 110,128, 1000, 0);
}
