#include "npcprueba.h"

npc personajes[30];
int npersonaje;
enemigo malos[30];
int nmalos;
int mision;
bool desplaza;
jefe boss[3];
MENSAJE dialogo, texto;

const int scroll_rango1 = 200;
const int scroll_rango2 = 90;

void carga_escenario();

void carga_inicio()
{

    datos_del_juego = load_datafile("datos_del_juego.dat");
    if ( !datos_del_juego ){
       allegro_message("Error: archivo datosjuego.dat no encontrado\n%s\n", allegro_error);
    }

    datobjeto = load_datafile("datobjeto.dat");
    if ( !datobjeto ){
       allegro_message("Error: archivo objetos.dat no encontrado\n%s\n", allegro_error);
    }

    datotiendas = load_datafile("datotiendas.dat");
    if ( !datotiendas){
       allegro_message("Error: archivo datostienda.dat no encontrado\n%s\n", allegro_error);
    }

    lee_objetos();


    menufondo = (BITMAP *)datos_del_juego[dimenu].dat;
    menufondo2 = (BITMAP *)datos_del_juego[dimenu2].dat;
}


void carga_mapa_choque()
{
    clear_to_color( cbuffer, makecol(0, 0, 0));
    blit ( choque, cbuffer, desplazamiento_map_x, desplazamiento_map_y,0,0, PANTALLA_ANCHO, PANTALLA_ALTO);
    jugador.pon_choque();
}

// carga todo lo necesario antes de empezar el juego
void carga_juego()
{
    cambio = 0;
    carga_escenario();

    dialogo.crea("", (FONT *)datos_del_juego[dftextos].dat, 10, PANTALLA_ALTO-100, PANTALLA_ANCHO-10, PANTALLA_ALTO-10);
    hablando = 0;

    mision = 1;
    swraton=-1;

    swinv=0;
    muestra_tienda = false;
    swtienda=0;

}



void control_inventario(){
     if ( swinv == 0 && key[KEY_I] ){
          swinv = 1;
     }

     if ( swinv == 3 && !key[KEY_I] ) swinv=0;

     if ( swinv == 2 && key[KEY_I] ){
          swinv = 3;
     }
}

// carga los datos del escenario segun lugar
void carga_escenario()
{
    switch ( lugar )
    {
    case 1:// casa
              fondo  = (BITMAP *)datos_del_juego[dicasa].dat;
              choque = (BITMAP *)datos_del_juego[dicasachoque].dat;
              alt  = (BITMAP *)datos_del_juego[dicasasup].dat;

              carga_mapa_choque();
              desplaza = false;
              if ( cambio != 0 ) sonido_abrirpuerta();
              musica_casa();
         break;

    case 2:// bosque
              fondo  = (BITMAP *)datos_del_juego[dibosque].dat;
              choque = (BITMAP *)datos_del_juego[dibosquechoque].dat;
              alt  = (BITMAP *)datos_del_juego[dibosquesup].dat;

              desplaza=true;
              carga_mapa_choque();
              sonido_ambiente();
              musica_bosque();
         break;

    case 3:// ciudad
              fondo  = (BITMAP *)datos_del_juego[diciudad1].dat;
              choque = (BITMAP *)datos_del_juego[diciudad1choque].dat;
              alt  = (BITMAP *)datos_del_juego[diciudad1sup].dat;

              desplaza=true;
              carga_mapa_choque();
              if ( cambio == 0 ) musica_ciudad1();
         break;
    case 4:// tienda1
              fondo  = (BITMAP *)datos_del_juego[ditienda1].dat;
              choque = (BITMAP *)datos_del_juego[ditienda1choque].dat;
              alt  = (BITMAP *)datos_del_juego[ditienda1sup].dat;
              carga_mapa_choque();
              desplaza=false;
              if ( cambio != 0 ) sonido_abrirpuerta();
              if ( cambio == 0 ) musica_ciudad1();
         break;
    }
}

// ***** inicio scroll

void scroll_escenario()
{

    int ax,ay;

    ax = jugador.getx();
    ay = jugador.gety();

    if ( desplaza )
    {
         int d = desplazamiento / 2;
         // controla el desplazamiento del mapa si esta en los bordes
         if ( ax < scroll_rango1 && desplazamiento_map_x > 0 )
         {
              desplazamiento_map_x-=d;
              jugador.posiciona(ax+d,ay);
              ax = jugador.getx();
              ay = jugador.gety();
              if ( ax < scroll_rango2 && desplazamiento_map_x > 0  )
              {
                  desplazamiento_map_x-=d;
                  jugador.posiciona(ax+d,ay);
                 ax = jugador.getx();
                 ay = jugador.gety();
              }
         }
         if ( ay < scroll_rango1 && desplazamiento_map_y > 0 )
         {
              desplazamiento_map_y-=d;
              jugador.posiciona(ax,ay+d);
              ax = jugador.getx();
              ay = jugador.gety();
              if ( ay < scroll_rango2 && desplazamiento_map_y > 0 )
             {
                  desplazamiento_map_y-=d;
                  jugador.posiciona(ax,ay+d);
                 ax = jugador.getx();
                 ay = jugador.gety();
             }
         }
         if ( ax > PANTALLA_ANCHO-scroll_rango1 && desplazamiento_map_x < fondo->w-PANTALLA_ANCHO )
         {
              desplazamiento_map_x+=d;
              jugador.posiciona(ax-d,ay);
              ax = jugador.getx();
              ay = jugador.gety();
              if ( ax > PANTALLA_ANCHO-scroll_rango2 && desplazamiento_map_x < fondo->w-PANTALLA_ANCHO  )
              {
                  desplazamiento_map_x+=d;
                  jugador.posiciona(ax-d,ay);
                 ax = jugador.getx();
                 ay = jugador.gety();
              }
         }
         if ( ay > PANTALLA_ALTO-scroll_rango1 && desplazamiento_map_y < fondo->h-PANTALLA_ALTO )
         {
              desplazamiento_map_y+=d;
              jugador.posiciona(ax,ay-d);
              ax = jugador.getx();
              ay = jugador.gety();
              if ( ay > PANTALLA_ALTO-scroll_rango2 && desplazamiento_map_y < fondo->h-PANTALLA_ALTO )
              {
                  desplazamiento_map_y+=d;
                  jugador.posiciona(ax,ay-d);
                 ax = jugador.getx();
                 ay = jugador.gety();
              }
         }

    }

}

//****** fin scroll


//***** inicia cambio escenario

void cambia_escenario()
{

    switch ( lugar )
    {
    case 1:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 2;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=0;
              desplazamiento_map_y=160;
              cambio = 0;
                if(jmuerto){
                    jmuerto=false;
                }

         }
         break;
    case 2:   // bosque
         if ( cambio == 2 )
         {
              // cambiamos a otro lugar
              // casa
              lugar = 1;
              carga_escenario();
              // situamos al prota cerca de la puerta
              jugador.posiciona( 290,440 );
              desplazamiento_map_x=-160;
              desplazamiento_map_y=-160;
              sonido_abrirpuerta();
              para_sonido_ambiente();
              cambio = 0;

         }
         if ( cambio == 3 )
         {
              // cambiamos a otro lugar
              // ciudad
              lugar = 3;
              carga_escenario();
              // situamos al prota en el camino
              jugador.posiciona( 500,540 );
              desplazamiento_map_x=950;
              desplazamiento_map_y=508;
              para_sonido_ambiente();
              musica_ciudad1();
              cambio = 0;
         }
         break;
    case 3:   // ciudad
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 2;
              carga_escenario();
              // situamos al prota en el camino del bosque
              jugador.posiciona( 650,30 );
              desplazamiento_map_x=200;
              desplazamiento_map_y=0;
              cambio = 0;
         }
         // color amarillo que existen muchos
         if ( cambio == 3 && desplazamiento_map_x > 800 )
         {
              // cambiamos a otro lugar
              // tienda1
              lugar = 4;
              carga_escenario();
              // situamos al prota en el camino del bosque
              jugador.posiciona( 376,460 );
              desplazamiento_map_x=-170;
              desplazamiento_map_y=-100;

              cambio = 0;
         }
         break;
    case 4:   // tienda1
         if ( cambio == 1)
         {
              // cambiamos a la ciudad
              lugar=3;
              carga_escenario();
              jugador.posiciona( 400,300 );
              desplazamiento_map_x=1090;
              desplazamiento_map_y=85;
              cambio = 0;
              sonido_abrirpuerta();
         }


    default:
         break;
    }
    carga_mapa_choque();
}

//***** fin cambio escenario


//*** inicia eventos escenario
void evento_escenario()
{
    int pzx = jugador.getx() + desplazamiento_map_x;
    int pzy = jugador.gety() + desplazamiento_map_y;


    switch ( lugar )
    {
    case 1:// casa
        if ( personajes[10].posicion_cerca()
               && jugador.accion() && !jugador.hablando() )
         {
            if(jugador.getvida()<jugador.getvidamax()){
                dialogo.cambia_texto("Dejame curarte");
                jugador.curar();
            }
            else{
              dialogo.cambia_texto("America: Hola, segun tu identificacion eres Roman, cierto? Soy America, te encontre a las afueras de este refugio, aqui ayudamos a las personas que quieren llegar a Narnia, la ciudad despues del bosque. Narnia es una ciudad que utiliza mucho combustibles fosiles, y es una de las ciudades mas contamidas desgraciadamente, pero creo que es mejor que tu experimentes esto");}
              hablando = 1;
         }
         if ( personajes[11].posicion_cerca()&& jugador.accion() && !jugador.hablando() ){
          dialogo.cambia_texto("Hola Roman, America me hablo de ti 7u7, te mostrare lo basico para que sobrevivas alla afuera y no termines de nuevo aqui, con la tecla 'espacio' atacas, con la tecla 'I' abres tu inventario agradece a mi hija por ese inventario, con la tecla espacio puedes interactuar con las personas hazlo mas de una vez y eso es basicamente todo. Buena suerte Roman");

          hablando=1;
         }
         if ( hablando == 1 && !jugador.accion() )
         {
              hablando = 2;
              jugador.habla();
         }

         // obliga a esperar minimo 1 segundo
         if ( hablando > FRAME_RATE && jugador.accion() ){
              hablando = 0;
         }

         if ( hablando == 0 && !jugador.accion() && jugador.hablando() )
         {
              jugador.no_habla();
         }
         break;
    case 2:   // bosque
         break;
    case 3:   // ciudad


         if ( personajes[0].posicion_cerca()
               && jugador.accion() && !jugador.hablando() )
         {
              dialogo.cambia_texto(" Pueblerina: Cof* Cof* este maldito humo me tiene arta, no puedo vivir asi, me siento cansada con mucha velocidad y tengo pulmones de fumador, sabes que es lo peor? Que ni siquiera fumo y estos haciendo mis quehaceres");
              hablando = 1;
         }

         if ( personajes[4].posicion_cerca()
               && jugador.accion() && !jugador.hablando() )
         {
              dialogo.cambia_texto("Guardia: Hoy acaba de salir nuevamente el vagon 777, en seguida de que salio el ambiente del aire empeoro, creo que apartir de hoy caminare para venir a mi trabajo" );
              hablando = 1;
         }

         if ( personajes[5].posicion_cerca()
               && jugador.accion() && !jugador.hablando() )
         {
              dialogo.cambia_texto("Pueblerino: Hoy sucedio algo horrible, me estaba duchando y el agua de la llave salio sucia, me pregunto por que sera?" );
              hablando = 1;
         }


         if ( personajes[6].posicion_cerca()
               && jugador.accion() && !jugador.hablando() )
         {
             if(bossesmuertos==0){
              dialogo.cambia_texto("Guardia: Escuchaste ese ruido, fue un gran estruendo y empieza a salir humo del refugio, avisare a mis compañeros" );
              mision=2;
              }
              if(bossesmuertos==1){
                dialogo.cambia_texto("Guardia: Eh escuchado que hay alguien contaminando nuestro lago, puedes encargarte? La vez anterior lo hiciste muy bien");
              mision=3;
              }
              if(bossesmuertos==2){
                dialogo.cambia_texto("Muy bine hecho, ahora tenemos un problema de calentamiento solar muy grave, es causado por un murcielago que emite gases invernadero, ve y eliminalo");
                mision=4;
              }
              hablando = 1;
         }

         if ( hablando == 1 && !jugador.accion() )
         {
              hablando = 2;
              jugador.habla();
         }

         // obliga a esperar minimo 1 segundo
         if ( hablando > FRAME_RATE && jugador.accion() ){
              hablando = 0;
         }

         if ( hablando == 0 && !jugador.accion() && jugador.hablando() )
         {
              jugador.no_habla();
         }

         break;

    case 4: // en la tienda

         if ( personajes[8].getestado() == 6 && cambio == 0 && !personajes[8].posicion_cerca())
         {
              personajes[8].cambia_estado(0);
         }
         if ( personajes[9].getestado() == 6 && cambio == 0 && !personajes[9].posicion_cerca())
         {
              personajes[9].cambia_estado(0);
         }

         if ( cambio == 2 && jugador.getx()< 400 )
         {
              personajes[9].cambia_estado(6);
              cambio = 0;
         }
         if ( cambio == 2 && jugador.getx()> 400 )
         {
              personajes[8].cambia_estado(6);
              cambio = 0;
         }

         if ( personajes[8].posicion_cerca() )
         {
              personajes[8].cambia_estado(6);
         }

         if ( personajes[9].posicion_cerca() )
         {
              personajes[9].cambia_estado(6);
         }

         if ( personajes[8].posicion_cerca(9) &&  personajes[8].alineado_vertical()
              && jugador.accion() && !personajes[8].posicion_cerca(2) )
         {
              lee_tienda(2);
              muestra_tienda = true;
         }

         if ( personajes[9].posicion_cerca(9) &&  personajes[9].alineado_vertical()
              && jugador.accion() && !personajes[9].posicion_cerca(2) )
         {
              lee_tienda(1);
              muestra_tienda = true;
         }


         if (  personajes[8].frente() && jugador.accion() &&
               !jugador.hablando() && personajes[8].posicion_cerca())
         {
                  dialogo.cambia_texto("Encargada: Disculpe señor, se compra del otro lado" );
                  hablando = 1;
         }

         if ( personajes[9].frente() && jugador.accion() &&
              !jugador.hablando() && personajes[9].posicion_cerca())
         {
                  dialogo.cambia_texto(" Encargada: Disculpe señor, se compra del otro lado" );
                  hablando = 1;
         }

         if ( hablando == 1 && !jugador.accion() )
         {
              hablando = 2;
              jugador.habla();
         }

         // obliga a esperar minimo 1 segundo
         if ( hablando > FRAME_RATE && jugador.accion() ){
              hablando = 0;
         }

         if ( hablando == 0 && !jugador.accion() && jugador.hablando() )
         {
              jugador.no_habla();
         }

         break;

    default:
         break;
    }
}

//*** fin eventos escenario


// nuevo actualiza
void actualiza_juego()
{

    scroll_escenario();

    evento_escenario();

    jugador.teclado();

    control_inventario();

    cambia_escenario();
}


void pinta_inventario()
{
     if ( swinv >  0 )
     {

          int jx = jugador.getx();
          int jy = jugador.gety();
          int posx;
          int posy;

          if ( jx > PANTALLA_ANCHO/2 ){
               jx = (PANTALLA_ANCHO/4) - 160;
          }else{
               jx = (PANTALLA_ANCHO*3/4) - 160;
          }

          if ( jy > PANTALLA_ALTO/2 ){
               jy = (PANTALLA_ALTO/4) - 81;
          }else{
               jy = (PANTALLA_ALTO*3/4) - 81;
          }

          // se muestra fondo inventario
          masked_blit( (BITMAP *)datos_del_juego[diinventario].dat, buffer, 0,0, jx,jy, 320,162);

    if ( swraton == 1 && mouse_b&2 )
    {
         swraton = -2;
    }

          masked_blit( jugador.getimg(), buffer, 32,0, jx+65,jy+60, 32,32);

    if ( jugador.getcasco() != -1 )
    {
         masked_blit((BITMAP *)datobjeto[equipo_personaje(jugador.getcasco())].dat, buffer, 32, 0, jx+65, jy+60, 32,32);
    }


          posx=jx+116;
          posy=jy+40;
          if ( mouse_x > posx && mouse_x < posx+32 && mouse_y > posy && mouse_y < posy+32 )
          {
              if ( mouse_b&1 && swraton != -2)
               {
                    // se ha pulsado dentro de un hueco
                    if ( swraton == -1 )
                    {
                         // primer clic
                         swraton = 1;
                         nsel = -4;
                         nid = jugador.getanillo();
                         if ( nid == -1 ){
                               swraton = -1;
                         }else{
                            sonido_boton2();
                         }
                    }else{

                         if ( nid != jugador.getanillo() && tipo(nid) == 4 )
                         {
                              // cambia objeto de sitio
                              if ( jugador.getanillo() != -1 ){
                                 jugador.pon_inventario(nsel,jugador.getanillo());
                              }else{
                                 jugador.pon_inventario(nsel,0);
                              }


                              jugador.pon_anillo(nid);
                              sonido_boton();

                              swraton = -2;
                          }
                    }
               }
          }


          if ( jugador.getanillo() != -1 )
          {
             masked_blit( (BITMAP *)datobjeto[id_img_objeto( jugador.getanillo())].dat, buffer, 0,0, jx+116,jy+40, 32,32);
          }

          posx=jx+116;
          posy=jy+74;
          if ( mouse_x > posx && mouse_x < posx+32 && mouse_y > posy && mouse_y < posy+32 )
          {
              if ( mouse_b&1 && swraton != -2)
               {
                    // se ha pulsado dentro de un hueco
                    if ( swraton == -1 )
                    {
                         // primer clic

                         swraton = 1;
                         nsel = -1;
                         nid = jugador.getarmadura();
                         if ( nid == -1 ){
                               swraton = -1;
                         }else{
                            sonido_boton2();
                         }
                    }else{

                         if ( nid != jugador.getarmadura() && tipo(nid) == 3 )
                         {
                              // cambia objeto de sitio
                              if ( jugador.getarmadura() != -1 ){
                                 jugador.pon_inventario(nsel,jugador.getarmadura());
                              }else{
                                 jugador.pon_inventario(nsel,0);
                              }


                              jugador.pon_armadura(nid);
                              sonido_boton();

                              swraton = -2;
                          }
                    }
               }
          }

          if ( jugador.getarmadura() != -1 )
          {
             masked_blit( (BITMAP *)datobjeto[id_img_objeto( jugador.getarmadura())].dat, buffer, 0,0, jx+116,jy+74, 32,32);
          }


          posx=jx+13;
          posy=jy+74;
          if ( mouse_x > posx && mouse_x < posx+32 && mouse_y > posy && mouse_y < posy+32 )
          {
              if ( mouse_b&1 && swraton != -2)
               {
                    // se ha pulsado dentro de un hueco
                    if ( swraton == -1 )
                    {
                         // primer clic

                         swraton = 1;
                         nsel = -2;
                         nid = jugador.getarma();
                         if ( nid == -1 ){
                               swraton = -1;
                         }else{
                            sonido_boton2();
                         }
                    }else{

                         if ( nid != jugador.getarma() && tipo(nid) == 1 )
                         {
                              // cambia objeto de sitio
                              if ( jugador.getarma() != -1 ){
                                 jugador.pon_inventario(nsel,jugador.getarma());
                              }else{
                                 jugador.pon_inventario(nsel,0);
                              }


                              jugador.pon_arma(nid);
                              sonido_boton();

                              swraton = -2;
                          }
                    }
               }
          }


          if ( jugador.getarma() != -1 )
          {
             masked_blit( (BITMAP *)datobjeto[id_img_objeto( jugador.getarma())].dat, buffer, 0,0, jx+13,jy+74, 32,32);
          }

          posx=jx+13;
          posy=jy+40;
          if ( mouse_x > posx && mouse_x < posx+32 && mouse_y > posy && mouse_y < posy+32 )
          {
              if ( mouse_b&1 && swraton != -2)
               {
                    // se ha pulsado dentro de un hueco
                    if ( swraton == -1 )
                    {
                         // primer clic

                         swraton = 1;
                         nsel = -3;
                         nid = jugador.getcasco();
                         if ( nid == -1 ){
                               swraton = -1;
                         }else{
                            sonido_boton2();
                         }
                    }else{

                         if ( nid != jugador.getcasco() && tipo(nid) == 2 )
                         {
                              // cambia objeto de sitio
                              if ( jugador.getcasco() != -1 ){
                                 jugador.pon_inventario(nsel,jugador.getcasco());
                              }else{
                                 jugador.pon_inventario(nsel,0);
                              }


                              jugador.pon_casco(nid);
                              sonido_boton();

                              swraton = -2;
                          }
                    }
               }
          }

          if ( jugador.getcasco() != -1 )
          {
             masked_blit( (BITMAP *)datobjeto[id_img_objeto( jugador.getcasco())].dat, buffer, 0,0, jx+13,jy+40, 32,32);
          }

          int id;
          for ( int i=0; i< 4; i++){
              for ( int j=0; j<3; j++){
                  int num = (j*4) + i ;
                  id = jugador.getinventario( num );
                  posx = jx + 172 + i*34;
                  posy = jy + 40 + j*34;
                  if ( id != 0 ){
                      masked_blit( (BITMAP *)datobjeto[id_img_objeto( id)].dat, buffer, 0,0, posx,posy, 32,32);
                  }
                  if ( mouse_x > posx && mouse_x < posx+32 && mouse_y > posy && mouse_y < posy+32 )
                  {
                       if ( mouse_b&1 && swraton != -2)
                       {
                            // se ha pulsado dentro de un hueco
                            if ( swraton == -1 )
                            {
                                 // primer clic
                                 if ( id != 0 )
                                 {
                                      swraton = 1;
                                      nsel = num;
                                      nid  = id;
                                      sonido_boton2();
                                 }
                            }else{

                               if ( nsel >= 0 )
                               {
                                 if ( nsel != num && nsel != -1)
                                 {
                                      // cambia objeto de sitio
                                      jugador.cambia_inventario(nsel,num);
                                      sonido_boton();
                                      swraton = -2;
                                  }
                               }else{

                                 // ha quitado algo del equipo
                                 if ( nsel == -1 && (tipo(id) == 3 || id == 0) )
                                 {
                                      // armadura
                                      jugador.pon_inventario( num, nid );
                                      if ( id == 0 ) id = -1;
                                      jugador.pon_armadura( id );
                                      sonido_boton();
                                      swraton = -2;
                                 }
                                 if ( nsel == -2 && (tipo(id) == 1 || id == 0) )
                                 {
                                      // arma
                                      jugador.pon_inventario( num, nid );
                                      if ( id == 0 ) id = -1;
                                      jugador.pon_arma( id );
                                      sonido_boton();
                                      swraton = -2;
                                 }
                                 if ( nsel == -3 && (tipo(id) == 2 || id == 0) )
                                 {
                                      // arma
                                      jugador.pon_inventario( num, nid );
                                      if ( id == 0 ) id = -1;
                                      jugador.pon_casco( id );
                                      sonido_boton();
                                      swraton = -2;
                                 }

                                 if ( nsel == -4 && (tipo(id) == 4 || id == 0) )
                                 {
                                      // arma
                                      jugador.pon_inventario( num, nid );
                                      if ( id == 0 ) id = -1;
                                      jugador.pon_anillo( id );
                                      sonido_boton();
                                      swraton = -2;
                                 }
                               }
                            }
                       }

                  }
                  if ( swraton == -2 && !mouse_b&1 ) swraton=-1;
              }
          }

          if ( !key[KEY_I]) swinv = 2;
     }
}


void pinta_lvlup()
{
     if ( lvl_up )
     {
          nlvlup = 1;
          lux = jugador.getx();
          luy = jugador.gety();
          lvl_up = false;
     }
     if ( nlvlup > 0 )
     {
          masked_blit ( (BITMAP *)datos_del_juego[dilvup].dat, buffer, 0,0, lux, luy - nlvlup*2, 32,32 );
          int num = FRAME_RATE / 10;
           if ( tiempo_total % num == 0 )
           {
              nlvlup++;
           }
           if  ( nlvlup > 40 ) nlvlup = 0;
     }
}


void pinta_barra_vida()
{
    int n = (jugador.getvida()*150) / jugador.getvidamax() ;

    rectfill( buffer, PANTALLA_ANCHO-162, 10, PANTALLA_ANCHO-8, 25, 0x003300);
    rectfill( buffer, PANTALLA_ANCHO-160, 12, PANTALLA_ANCHO-160+n, 23, 0x00ff00);
    rectfill( buffer, PANTALLA_ANCHO-160, 12, PANTALLA_ANCHO-160+n, 15, 0xbbffaa);
    rect( buffer, PANTALLA_ANCHO-162, 10, PANTALLA_ANCHO-8, 25, 0x000000);

    int nxp = 100 * ( jugador.getnivel() + 1 );
    int n2 = (jugador.getexp()*150) / nxp ;

    rectfill( buffer, PANTALLA_ANCHO-162, 30, PANTALLA_ANCHO-8, 45, 0x000033);
    rectfill( buffer, PANTALLA_ANCHO-160, 32, PANTALLA_ANCHO-160+n2, 43, 0x0000ff);
    rectfill( buffer, PANTALLA_ANCHO-160, 32, PANTALLA_ANCHO-160+n2, 35, 0xbbaaff);
    rect( buffer, PANTALLA_ANCHO-162, 30, PANTALLA_ANCHO-8, 45, 0x000000);
    textprintf_centre_ex( buffer, font, PANTALLA_ANCHO - 80, 34, 0xFFFFFF, -1, "Niv: %d",
                    jugador.getnivel() );
}



// Se encarga de pintar todo sobre el buffer
void pinta_juego()
{
    int ancho, alto;
    int ax=0;
    int ay=0;
    int bx=0;
    int by=0;

    switch ( lugar )
    {
    case 1:   // casa
             bx=160;
             by=160;
             ancho = 480;
             alto = 325;
             break;
    case 2:   // bosque
             ax = desplazamiento_map_x;
             ay = desplazamiento_map_y;
             ancho = PANTALLA_ANCHO;
             alto  = PANTALLA_ALTO;
             break;
    case 3:  // ciudad1
             ax = desplazamiento_map_x;
             ay = desplazamiento_map_y;
             ancho = PANTALLA_ANCHO;
             alto  = PANTALLA_ALTO;
             break;
  case 4: // tienda1
             bx = 170;
             by = 100;
             ancho = 448;
             alto = 416;
             break;
    default:
         break;
    }


    blit( fondo, buffer, ax, ay, bx, by, ancho, alto);
    for ( int z=0; z < npersonaje; z++ )
    {
         personajes[z].pinta();
    }

    for ( int z=0; z < nmalos; z++ )
    {
        malos[z].pinta();
    }
    if(mision==2){
        boss[0].pintajefe();
    }
    if(mision==3){
        boss[1].pintajefe();
    }
    if(mision==4){
        boss[2].pintajefe();
    }
    jugador.pinta();

    masked_blit( alt, buffer, ax, ay, bx, by, ancho, alto);

    if ( hablando > 1 )
    {
         dialogo.pinta(buffer);
         hablando++;
    }

    pinta_barra_vida();
    pinta_lvlup();
    pinta_inventario();

    pinta_tienda();
    if(jmuerto){
        textprintf(buffer,font,100,40,palette_color[12],"HAS MUERTO");

    }
}
