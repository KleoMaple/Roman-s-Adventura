class npc {
    protected:
      // posicion
      int x,y;
      int ax,ay;

      int direccion;

      int animacion;

      int escena;

      int estado;

      int img;
      BITMAP* imagen;

    public:

      void crea( int i, int _x, int _y, int dir, int _estado, int _lugar );
      void pinta();
      void actualiza();
      bool chocanpc();
      bool posicion_cerca(int num=0);
      void cambia_estado(int _estado){ estado = _estado; };
      bool frente();
      bool alineado_vertical();

      const int getimg()   { return img; };
      const int getx()     { return x; };
      const int gety()     { return y; };
      const int getdir()   { return direccion; };
      const int getestado(){ return estado; };
      const int getlugar() { return escena; };
};


void npc::crea( int i, int _x, int _y, int dir, int _estado, int _lugar)
{
     x = _x;
     y = _y;
     direccion = dir;
     animacion = 0;
     escena = _lugar;

     img = i;
     BITMAP *_img = (BITMAP *)datos_del_juego[i].dat;

     imagen = create_bitmap(_img->w, _img->h);

     blit( _img, imagen, 0,0, 0,0, _img->w, _img->h);

     estado = _estado;
}


void npc::pinta()
{
     if ( lugar == escena )
     {

        actualiza();

        int vx = x - desplazamiento_map_x;
        int vy = y - desplazamiento_map_y;

        rectfill( cbuffer, vx+2, vy+1, vx+30, vy+31, 0xff0000);

        masked_blit(imagen, buffer, animacion*32, direccion*32, vx, vy, 32,32);
     }
}


bool npc::chocanpc()
{
    int ninix,niniy;
    int nfinx,nfiny;

    if ( direccion == 0 )
    {
         // abajo
         ninix = 0;
         niniy = 32 - desplazamiento;
         nfinx = 32;
         nfiny = 32;
    }
    if ( direccion == 1 )
    {
         // izquierda
         ninix = 0;
         niniy = 0;
         nfinx = desplazamiento;
         nfiny = 32;
    }
    if ( direccion == 2 )
    {
         // derecha
         ninix = 32 - desplazamiento;
         niniy = 0;
         nfinx = 32;
         nfiny = 32;
    }
    if ( direccion == 3 )
    {
         // arriba
         ninix = 0;
         niniy = 0;
         nfinx = 32;
         nfiny = desplazamiento;
    }

          int vx;
          int vy;
    // comprobar si colisiona con el mapa
    for ( int ci=ninix; ci < nfinx; ci++)
    {
        for (int cj=niniy; cj < nfiny; cj++)
        {

           vx = x - desplazamiento_map_x;
           vy = y - desplazamiento_map_y;
            // color rojo
            if ( getpixel( cbuffer, vx+ci, vy+cj) == 0xff0000 ||
                 getpixel( choque, x+ci, y+cj) == 0xff0000 ){
                 return true;
            }
            // color blanco prota
            if ( getpixel( cbuffer, vx+ci, vy+cj) == 0xffffff ){
                 return true;
            }
        }
    }
    return false;
}


 bool npc::alineado_vertical(){
      int jx = jugador.getx() + desplazamiento_map_x;
      int jy = jugador.gety() + desplazamiento_map_y;

      return (  y+desplazamiento*2 < jy   && abs(jx-x) <= desplazamiento*2  );
 }

bool npc::frente()
{
    int jx = jugador.getx() + desplazamiento_map_x;
    int jy = jugador.gety() + desplazamiento_map_y;

    int d =  jugador.dire();

    if ( jx > x )
    {
        if ( abs ( jy - y ) < desplazamiento*2 )
        {
             if ( d == 1 )
             {
                  return true;
             }else{
                  return false;
             }
        }
    }

    if ( jx < x )
    {
        if ( abs ( jy - y ) < desplazamiento*2 )
        {
             if ( d == 2 )
             {
                  return true;
             }else{
                  return false;
             }
        }
    }

    if ( jy < y )
    {
        if ( abs ( jx - x ) < desplazamiento*2 )
        {
             if ( d == 0 )
             {
                  return true;
             }else{
                  return false;
             }
        }
    }

    if ( jy > y )
    {
        if ( abs ( jx - x ) < desplazamiento*2 )
        {
             if ( d == 3 )
             {
                  return true;
             }else{
                  return false;
             }
        }
    }

    return false;
}


// num distancia considerada cercana en pasos
bool npc::posicion_cerca(int num)
{
     int _x = jugador.getx() + desplazamiento_map_x;
     int _y = jugador.gety() + desplazamiento_map_y;
     int d = 32 + (desplazamiento*(2+num));
     int d2 =abs ( _x - x ) + abs ( _y - y );
     return d2 <= d && lugar == escena ;
}


void npc::actualiza()
{
    // para indicar que se ejecuta dos veces
    int num = FRAME_RATE / 6;

    if ( tiempo_total % num == 0 )
    {
        if ( estado != 0 )
        {
           animacion++;
           if ( animacion > 2 ) animacion = 0;
        }

        switch ( estado )
        {
        case 1: // camina horizontal
             ax = x;
             ay = y;
             if ( direccion == 1 )
             {
                  // camina izquierda
                  x-=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       x = ax;
                       direccion = 2;
                  }
             }
             if ( direccion == 2 )
             {
                  // camina derecha
                  x+=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       x = ax;
                       direccion = 1;
                  }
             }

             break;
        case 2: // camina vertical
             ax = x;
             ay = y;
             if ( direccion == 0 )
             {
                  // camina abajo
                  y+=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       y = ay;
                       direccion = 3;
                  }
             }
             if ( direccion == 3 )
             {
                  // camina arriba
                  y-=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       y = ay;
                       direccion = 0;
                  }
             }

             break;
        case 3: // camina giro derecha
             ax = x;
             ay = y;
             if ( direccion == 0 )
             {
                  // camina abajo
                  y+=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       y = ay;
                       direccion = 1;
                  }
             }
             if ( direccion == 1 )
             {
                  // camina izquierda
                  x-=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       x = ax;
                       direccion = 3;
                  }
             }
             if ( direccion == 2 )
             {
                  // camina derecha
                  x+=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       x = ax;
                       direccion = 0;
                  }
             }
             if ( direccion == 3 )
             {
                  // camina arriba
                  y-=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       y = ay;
                       direccion = 2;
                  }
             }

         break;
         case 4: // camina giro izquierda
             ax = x;
             ay = y;
             if ( direccion == 0 )
             {
                  // camina abajo
                  y+=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       y = ay;
                       direccion = 2;
                  }
             }
             if ( direccion == 1 )
             {
                  // camina izquierda
                  x-=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       x = ax;
                       direccion = 0;
                  }
             }
             if ( direccion == 2 )
             {
                  // camina derecha
                  x+=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       x = ax;
                       direccion = 3;
                  }
             }
             if ( direccion == 3 )
             {
                  // camina arriba
                  y-=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       y = ay;
                       direccion = 1;
                  }
             }
             break;
        case 5: // camina libre
             if ( tiempo_total % 200 == 0 )
             {
                  direccion = rand()%4;
             }
             ax = x;
             ay = y;
             if ( direccion == 0 )
             {
                      // camina abajo
                      y+=desplazamiento;
                      if ( chocanpc() )
                      {
                           // posicion no valida
                           y = ay;
                           direccion = rand()%4;
                      }
                 }
             if ( direccion == 1 )
             {
                  // camina izquierda
                  x-=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       x = ax;
                       direccion = rand()%4;
                  }
             }
             if ( direccion == 2 )
             {
                  // camina derecha
                  x+=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       x = ax;
                       direccion = rand()%4;
                  }
             }
             if ( direccion == 3 )
             {
                  // camina arriba
                  y-=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       y = ay;
                       direccion = rand()%4;
                  }

             }

             break;
        default: // parado
             if ( tiempo_total % 300 == 0 )
             {
                  direccion = rand()%4;
             }
             break;
        }

    }
}


// ENEMIGO

class enemigo : public npc {
      int vida;
      int v_actual;
      bool muerto;
      int golpeado;
      int exp;
     public:
        void crea( int i, int _x, int _y, int dir, int _estado, int _lugar, int v );
        void herida( int d );
        void pinta();
        bool ha_muerto() { return muerto; };
        void movimiento();
        void daexp(int e){ exp = e; };
        const int getvida()     { return vida; };
};


void enemigo::crea( int i, int _x, int _y, int dir, int _estado, int _lugar, int v )
{
    x = _x;
    y = _y;
    direccion = dir;
    animacion = 0;
    escena = _lugar;

    img=i;
    BITMAP *_img = (BITMAP *)datos_del_juego[i].dat;
    imagen = create_bitmap(_img->w, _img->h);

    blit( _img, imagen, 0,0, 0,0, _img->w, _img->h);

    estado = _estado;

    vida = v;
    v_actual = vida;
    muerto = false;
    golpeado=0;
    exp = 50;
};

void enemigo::herida( int d )
{
  if ( !muerto )
  {
     int num = FRAME_RATE / 2;
     v_actual-=d;
     if ( v_actual <= 0 )
     {
            muerto = true;
            int vx = x - desplazamiento_map_x;
            int vy = y - desplazamiento_map_y;
            rectfill( cbuffer, vx+2, vy+1, vx+30, vy+31, 0x000000);
            sonido_muere();
            jugador.sube_experiencia(exp);
           // siempre obtiene un objeto aleatorio
           int q2 = lobj.size();
           int q = lobj[rand()%q2].id;
           jugador.obtiene_objeto( q );

     }else{
        // daño defensivo del enemigo
        if ( tiempo_total % num == 0 )
        {
             if ( rand()%2 == 1 )
             {
                 sonido_herido();
                 jugador.herido(5+rand()%5);
             }
        }
     }

  }
};


void enemigo::pinta()
{
     if ( lugar == escena && !muerto )
     {

          if ( v_actual == vida )
          {
               actualiza();
          }else{
               movimiento();
          }

          int vx = x - desplazamiento_map_x;
          int vy = y - desplazamiento_map_y;

          rectfill( cbuffer, vx+2, vy+1, vx+30, vy+31, 0xff0000);

          masked_blit(imagen, buffer, animacion*32, direccion*32, vx, vy, 32,32);

        if ( golpeado == 1 )
        {
            int xn = 2 + rand()%2;
            jugador.no_ataca();
            if ( rand()%10 != 1 )
            {
               sonido_espada_da();
               herida(xn);
            }else{
               sonido_espada_choca();
            }
            golpeado = 0;

        }

        if ( golpeado == 0 && jugador.atacando() && posicion_cerca()
             && frente() )
        {
              golpeado = 1;
        }

        if ( !muerto )
        {
            int nm = (v_actual * 30 ) / vida;
            rectfill( buffer, vx+1, vy, vx+nm, vy+5, 0x00ff00);
            rect( buffer, vx, vy, vx+31, vy+5, 0x000000);
        }
     }
     if ( lugar != escena && v_actual < vida )
     {
        int num = FRAME_RATE / 5;
        if ( tiempo_total % num == 0 )
        {
            v_actual++;
        }
     }
}


void enemigo::movimiento()
{
    ax = x;
    ay = y;
    int jx = jugador.getx() + desplazamiento_map_x;
    int jy = jugador.gety() + desplazamiento_map_y;

    // para indicar que se ejecuta dos veces
    int num = FRAME_RATE / 6;

    int esta = 0;

    // mira hacia donde este el jugador
    if ( jx > x )
    {
         direccion = 2;
    }else{
         direccion = 1;
    }

    if ( jy > y )
    {
        if ( abs ( jx - x ) < desplazamiento*3 )
        {
            direccion = 0;
        }
    }else{
        if ( abs ( jx - x ) < desplazamiento*3 )
        {
            direccion = 3;
        }
    }

    // enemigo te persigue

    if ( tiempo_total % num == 0 )
    {

        if ( x+32 < jx )
        {
             x+=desplazamiento;
             esta = 1;
        }

        if ( x > jx+32 )
        {
             x-=desplazamiento;
             esta = 1;
        }
        if ( y+32 < jy )
        {
             y+=desplazamiento;
             esta = 1;
        }

        if ( y > jy+32  )
        {
             y-=desplazamiento;
             esta = 1;
        }

    }


    if ( ax != x || ay != y )
    {
      // se ha movido en una de las direcciones

      if ( chocanpc() )
      {
           x = ax;
           y = ay;
           esta = 0;
      }
      if ( esta != 0 )
      {
           animacion++;
           if ( animacion > 2 ) animacion = 0;
      }

    }


    if ( posicion_cerca() )
    {
        int num = FRAME_RATE / 3;
        if ( tiempo_total % num == 0 )
        {
             if ( rand()%3 == 1 )
             {
                 sonido_herido();
                 jugador.herido(2+rand()%2);
                 animacion++;
                 if ( animacion > 2 ) animacion = 0;
             }
        }
    }

}

class jefe: public npc{
    int vidajefe;
      int v_actualjefe;
      bool muertojefe;
      int golpeadojefe;
      int expjefe;
      int vgolpeado=0;

     public:
        void creajefe( int i, int _x, int _y, int dir, int _estado, int _lugar, int v );
        void heridajefe( int d );
        void pintajefe();
        bool ha_muertojefe() { return muertojefe; };
        void movimientojefe();
        void daexpjefe(int e){ expjefe = e; };
        const int getvidajefe()     { return vidajefe; };
};
void jefe::creajefe( int i, int _x, int _y, int dir, int _estado, int _lugar, int v )
{
    x = _x;
    y = _y;
    direccion = dir;
    animacion = 0;
    escena = _lugar;

    img=i;
    BITMAP *_img = (BITMAP *)datos_del_juego[i].dat;
    imagen = create_bitmap(_img->w, _img->h);

    blit( _img, imagen, 0,0, 0,0, _img->w, _img->h);

    estado = _estado;

    vidajefe = v;
    v_actualjefe = vidajefe;
    muertojefe = false;
    golpeadojefe=0;
    expjefe = 1000;
};

void jefe::heridajefe( int d )
{
  if ( !muertojefe )
  {
     int num = FRAME_RATE / 2;
     v_actualjefe-=d;
     if ( v_actualjefe <= 0 )
     {
            muertojefe = true;
            int vx = x - desplazamiento_map_x;
            int vy = y - desplazamiento_map_y;
            rectfill( cbuffer, vx+2, vy+1, vx+30, vy+31, 0x000000);
            sonido_muere();
            vgolpeado=0;
            musica_bosque();
            jugador.sube_experiencia(expjefe);
           // siempre obtiene un objeto aleatorio
           int q2 = lobj.size();
           int q = lobj[rand()%q2].id;
           jugador.obtiene_objeto( q );
           bossesmuertos++;

     }else{
        // daño defensivo del enemigo
        if ( tiempo_total % num == 0 )
        {
             if ( rand()%2 == 1 )
             {
                 sonido_herido();
                 jugador.herido(5+rand()%5);
             }
        }
     }

  }
};


void jefe::pintajefe()
{
     if ( lugar == escena && !muertojefe )
     {

          if ( v_actualjefe == vidajefe )
          {
               actualiza();
          }else{
               movimientojefe();
          }

          int vx = x - desplazamiento_map_x;
          int vy = y - desplazamiento_map_y;

          rectfill( cbuffer, vx+2, vy+1, vx+30, vy+31, 0xff0000);

          masked_blit(imagen, buffer, animacion*32, direccion*32, vx, vy, 32,32);

        if ( golpeadojefe == 1 )
        {
            int xn = 2 + rand()%2;
            jugador.no_ataca();
            if ( rand()%10 != 1 )
            {
               sonido_espada_da();
               heridajefe(xn);
            }else{
               sonido_espada_choca();
            }
            golpeadojefe = 0;

        }

        if ( golpeadojefe == 0 && jugador.atacando() && posicion_cerca()
             && frente() )
        {
              golpeadojefe = 1;
        }

        if ( !muertojefe )
        {
            int nm = (v_actualjefe* 30 ) / vidajefe;
            rectfill( buffer, vx+1, vy, vx+nm, vy+5, 0x00ff00);
            rect( buffer, vx, vy, vx+31, vy+5, 0x000000);
        }
     }
     if ( lugar != escena && v_actualjefe < vidajefe )
     {
        int num = FRAME_RATE / 5;
        if ( tiempo_total % num == 0 )
        {
            v_actualjefe++;
        }
     }
}


void jefe::movimientojefe()
{
    ax = x;
    ay = y;
    int jx = jugador.getx() + desplazamiento_map_x;
    int jy = jugador.gety() + desplazamiento_map_y;

    // para indicar que se ejecuta dos veces
    int num = FRAME_RATE / 6;

    int esta = 0;

    // mira hacia donde este el jugador
     if(vgolpeado==0) {
            musica_batalla();
            vgolpeado=1;
    }
    if ( jx > x )
    {
         direccion = 2;
    }else{
         direccion = 1;
    }

    if ( jy > y )
    {
        if ( abs ( jx - x ) < desplazamiento*3 )
        {
            direccion = 0;
        }
    }else{
        if ( abs ( jx - x ) < desplazamiento*3 )
        {
            direccion = 3;
        }
    }

    // enemigo te persigue

    if ( tiempo_total % num == 0 )
    {

        if ( x+32 < jx )
        {
             x+=desplazamiento;
             esta = 1;
        }

        if ( x > jx+32 )
        {
             x-=desplazamiento;
             esta = 1;
        }
        if ( y+32 < jy )
        {
             y+=desplazamiento;
             esta = 1;
        }

        if ( y > jy+32  )
        {
             y-=desplazamiento;
             esta = 1;
        }

    }


    if ( ax != x || ay != y )
    {
      // se ha movido en una de las direcciones

      if ( chocanpc() )
      {
           x = ax;
           y = ay;
           esta = 0;
      }
      if ( esta != 0 )
      {
           animacion++;
           if ( animacion > 2 ) animacion = 0;
      }

    }


    if ( posicion_cerca() )
    {
        int num = FRAME_RATE / 3;
        if ( tiempo_total % num == 0 )
        {
             if ( rand()%3 == 1 )
             {
                 sonido_herido();
                 jugador.herido(2+rand()%2);
                 animacion++;
                 if ( animacion > 2 ) animacion = 0;
             }
        }
    }

}
