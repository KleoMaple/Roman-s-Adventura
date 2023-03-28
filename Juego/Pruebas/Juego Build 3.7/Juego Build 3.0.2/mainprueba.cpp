#include <iostream>
#include <allegro.h>
#include "datos_del_juego.h"
#include "botones.h"
#include "global.h"
#include "audio.h"
#include "menu.h"
#include "misobjetos.h"
#include "dialogos.h"
#include "players.h"
#include "tiendas.h"
#include "mijuegoprueba.h"
#include "partidas.h"


void inicia_allegro()
{
	allegro_init();
	install_timer();
	install_keyboard();
	install_mouse();

	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, PANTALLA_ANCHO, PANTALLA_ALTO, 0, 0);

    // incializa el audio en allegro
    if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) {
       allegro_message("Error: inicializando sistema de sonido\n%s\n", allegro_error);
    }

	set_volume(230, 90);

	buffer = create_bitmap(PANTALLA_ANCHO, PANTALLA_ALTO);
	cbuffer = create_bitmap(PANTALLA_ANCHO, PANTALLA_ALTO);

    LOCK_VARIABLE(contador_tiempo_juego);
    LOCK_FUNCTION(inc_contador_tiempo_juego);

    // Iniciamos el limitador de FPS
    install_int_ex(inc_contador_tiempo_juego, BPS_TO_TIMER( FRAME_RATE ));

    srand (time(NULL));
}


// Copiar el buffer a la pantalla del juego (screen)
void pintar_pantalla()
{

    if ( swinv > 0 || swtienda > 0 )
    {
         masked_blit( (BITMAP *)datos_del_juego[dicursor].dat, buffer, 0,0,mouse_x, mouse_y, 16,16);
    }
    if ( swinv > 0 && swraton > -1 )
    {
         masked_blit( (BITMAP *)datobjeto[id_img_objeto( nid)].dat, buffer, 0,0,mouse_x, mouse_y, 32,32);
    }

    blit(buffer, screen, 0, 0, 0, 0, PANTALLA_ANCHO, PANTALLA_ALTO);
}


// programa principal
int main()
{

    inicia_allegro();

    carga_inicio();

    musica_menu();

    int op;
    MIMENU menu;

    do{

    blit(menufondo, buffer, 0, 0, 0, 0, PANTALLA_ANCHO, PANTALLA_ALTO);
	menu.pinta();
	op = menu.teclado();

    // se a seleccionado una opcion
       if (key[KEY_ENTER] || key[KEY_ENTER_PAD])
       {
          if ( op == 2 )
          {
                // carga partida
                carga_partida();
                sonido_sube_nivel();
          }
          if ( op == 1 )
          {
                jugador.inicia();
                lugar = 1;
                desplazamiento_map_x=-160;
                desplazamiento_map_y=-160;
                sonido_sube_nivel();

                npersonaje = 12;

                personajes[0].crea( diper001, 1300,700, 1,1,3);
                personajes[1].crea( diper005, 280, 450, 0,2,3);
                personajes[2].crea( diper005, 230, 280, 3,2,3);
                personajes[3].crea( diper003, 960, 310, 2,3,3);
                personajes[4].crea( diper005, 1120, 450, 0,4,3);
                personajes[5].crea( diper004, 900, 650, 1,5,3);
                personajes[6].crea( diper006, 850, 800, 0,0,3);
                personajes[7].crea( diper001, 530, 280, 1,5,3);
                personajes[8].crea( diper007, 334, 170, 0,0,4);
                personajes[9].crea( diper008, 142, 170, 0,0,4);
                personajes[10].crea( diper007, 350, 150, 0,0,1);
                personajes[11].crea( diper004, 200, 140, 2,3,1);
                nmalos = 3;
                malos[0].crea( diene001, 380, 280, 3,5,2,50);
                malos[1].crea( diene001, 400, 720, 0,5,2,50);
                malos[2].crea( diene001, 380, 240, 0,5,2,50);
                boss[0].creajefe( dijefe01, 440, 720, 3,5,2,150);
                boss[1].creajefe(dijefe02, 440, 720, 3, 5, 2, 200);
                boss[2].creajefe(dijefe03, 440, 720, 3, 5, 2, 250);
          }

          if ( op == 1 || op == 2 )
          {
               carga_juego();

            // juego
            	salir = false;

            	while ( !salir )
            	{

                	  // tecla de salida
                	  if ( key[KEY_ESC] ) salir = true;

                      if ( contador_tiempo_juego )
                      {
                            while ( contador_tiempo_juego )
                            {
                                actualiza_juego();
                                contador_tiempo_juego--;
                            }

                            clear_to_color(buffer, 0x00000);

                            pinta_juego();
                            pintar_pantalla();
                      }else{
                           rest(1);
                      }
                }

            if ( lugar == 2 ) para_sonido_ambiente();
            // fin juego
            guarda_partida();
            musica_menu();
            op=2;
       }
    }

 	pintar_pantalla();
    }while ( !menu.salir() );



    destroy_bitmap(fondo);
    destroy_bitmap(choque);
    destroy_bitmap(alt);

    destroy_bitmap(menufondo);
    destroy_bitmap(menufondo2);
    destroy_bitmap(cbuffer);
	destroy_bitmap(buffer);

	return 0;
}
END_OF_MAIN();
