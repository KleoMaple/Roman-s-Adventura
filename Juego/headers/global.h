/* GLOBAL.H

*/
//definamos el arhicvo .dat
DATAFILE *datos_del_juego;
DATAFILE *datobjeto;
DATAFILE *datotiendas;
bool jmuerto=false;
int bossesmuertos=0;
// Ancho y alto de la pantalla
const int PANTALLA_ANCHO = 800;
const int PANTALLA_ALTO  = 600;
bool lvl_up;
int nlvlup;
int lux, luy;
int swinv;
//control raton en inventario
int swraton;
int nsel;
int nid;
int swtienda;
int sel_obj;
int swerror;
// En este BITMAP dibujaremos todo
BITMAP *buffer;
// controla el bucle principal
bool salir;

int hablando;
int cambio;

// indicará en que lugar estamos
// 1: casa
// 2: bosque
// 3: ciudad
int lugar;

int desplazamiento_map_x;
int desplazamiento_map_y;

BITMAP *fondo;
BITMAP *choque;
BITMAP *alt;
BITMAP *cbuffer;
BITMAP *menufondo;
BITMAP *menufondo2;

// Variable usada para la velocidad
volatile unsigned int contador_tiempo_juego = 0;
volatile unsigned int tiempo_total = 0;

const int FRAME_RATE =12;

// es el espacio en pixel que recorre el jugador al andar
const int desplazamiento= 120 / FRAME_RATE;

// Función para controlar la velocidad
void inc_contador_tiempo_juego()
{
    contador_tiempo_juego++;
    tiempo_total++;
}
END_OF_FUNCTION(inc_contador_tiempo_juego)
