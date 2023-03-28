class player
{
    BITMAP *prota;
	int x,y;
	int direccion;
	int animacion;
    bool hablar;
    int ataca;

    int vida;
    int vidamax;

    int enivel;
    int exp;

    int inventario[12];

    // equipacion actual
    int casco;
    int armadura;
    int arma;
    int anillo;

    int dinero;

    public:
       void inicia();
       void pinta();
       void teclado();
       bool choca();
       int getx(){ return x; };
       int gety(){ return y; };
       void posiciona( int _x, int _y);
              void pon_choque();
       bool accion();
       void habla();
       void no_habla();
       bool hablando(){ return hablar; };
       bool atacando(){ return ataca>1; };
       void no_ataca(){ ataca = -3; };
       int  dire(){ return direccion; };

       int getvida(){ return vida; };
       int getvidamax(){ return vidamax; };
       void herido(int n);

       BITMAP* getimg(){ return prota; };

       void sube_experiencia( int e );

       int getnivel(){ return enivel; };
       int getexp(){ return exp; };

       void setnivel(int n ){ enivel = n; };
       void setexp(int n ){ exp = n; };

       void obtiene_objeto( int id );
       int getinventario(int id){ return inventario[id]; };

       void cambia_inventario(int p1, int p2 );
       void pon_inventario(int pos, int id){ inventario[pos]=id; };

       int getarma(){ return arma; };
       int getarmadura(){ return armadura; };
       int getcasco(){ return casco; };
       int getanillo(){ return anillo; };

       void pon_arma(int id){ arma=id; };
       void pon_armadura(int id);
       void pon_casco(int id){ casco=id; };
       void pon_anillo(int id){ anillo=id; };

       int getdinero(){ return dinero; };
       void setdinero(int n){ dinero = n; };
       void masdinero(int n){ dinero = dinero + n; };
       void menosdinero(int n){ dinero = dinero - n; };
       // devuelve cuantos objetos tienes en el inventario
       int num_inventario();
       int cuantos_objetos(int id);

       void setvida(int v){ vida = v; };
       void setvidamax(int v){ vidamax = v; };
       void curar(){ vida=vidamax;};
};


player jugador;


int player::cuantos_objetos(int id)
{
    int n=0;
    for ( int i=0; i < 12; i++)
    {
        if ( inventario[i] == id ) n++;
    }
    return n;
}

int player::num_inventario()
{
    int n=0;
    for ( int i=0; i < 12; i++)
    {
        if ( inventario[i] != 0 ) n++;
    }
    return n;
}


void player::cambia_inventario(int p1, int p2 )
{
     int t;
     t = inventario[p1];
     inventario[p1] = inventario[p2];
     inventario[p2] = t;
};


void player::pon_armadura(int id)
{
     armadura = id;
     if ( id != -1 )
          prota  = (BITMAP *)datobjeto[equipo_personaje(armadura)].dat;
     if ( id == -1 )
          prota  = (BITMAP *)datos_del_juego[dihamster0].dat;
};


void player::obtiene_objeto( int id ){
     int n = 0;
     while ( n < 12 && inventario[n] != 0 )
     {
           n++;
     }
     // tiene un hueco
     if ( inventario[n] == 0 ){
          inventario[n] = id;
     }
}


void player::sube_experiencia( int e )
{
     exp = exp + e;
     int nxp = 100 * ( enivel + 1 );

     if ( exp >= nxp  && nxp != 1 )
     {
          exp = exp - nxp;
          enivel++;
          // ha subido de nivel !!
          sonido_sube_nivel();
          lvl_up = true;

          nxp = 100 * ( enivel + 1 );
          while ( exp >= nxp )
          {
              exp = exp - nxp;
              enivel++;
              // ha subido de nivel !!
              sonido_sube_nivel();
              nxp = 100 * ( enivel + 1 );
          }
     }
}


void player::pon_choque()
{
   rectfill( cbuffer, x+4, y+17, x+28, y+30, 0xffffff);
}


bool player::accion()
{
     return key[KEY_ENTER] || key[KEY_ENTER_PAD] ;
}

void player::habla()
{
     hablar = true;
}


void player::no_habla()
{
     hablar = false;
}




void player::inicia()
{
	// inicializar vbles
	direccion = 0;
	animacion = 0;
	x = 540;
	y = 280;

    hablar = false;
    ataca = 0;

    vida = 200;
    vidamax = 200;
    exp = 0;
    enivel = 0;

    for (int i=0; i<12; i++){
        inventario[i] = 0;
    }

    casco = -1;
    armadura = -1;
    arma = -1;
    anillo = -1;

    prota  = (BITMAP *)datos_del_juego[dihamster0].dat;

    dinero = 10000;
}



void player::pinta()
{
    if ( ataca > 1 && ( direccion == 1 || direccion == 3 ) && arma != -1)
    {
           masked_blit((BITMAP *)datobjeto[equipo_personaje(arma)].dat, buffer, 0, direccion*96, x-32, y-32, 96,96);
    }


    masked_blit(prota, buffer, animacion*32, direccion*32, x, y, 32,32);

    if ( casco != -1 )
    {
         masked_blit((BITMAP *)datobjeto[equipo_personaje(casco)].dat, buffer, animacion*32, direccion*32, x, y, 32,32);
    }

    if ( ataca > 1 && ( direccion == 0 || direccion == 2 )  && arma != -1 )
    {
           masked_blit((BITMAP *)datobjeto[equipo_personaje(arma)].dat, buffer, 0, direccion*96, x-32, y-32, 96,96);
    }
    if ( ataca > 1 || ataca < 0) ataca++;
//    textprintf_ex( buffer, font, 50, 150, 0xFFFFFF, -1, "A: %d  D: %d ", ataca, direccion );
    if ( ataca >1 && ataca%2 == 0 )
    {
       animacion++;
       if ( animacion > 2 ) animacion = 0;
    }
}


bool player::choca()
{
    bool resp=false;
    for (int i=2; i < 30; i++ )
    {
        for (int j=16; j < 32; j++)
        {

                // color rojo
                if ( getpixel( cbuffer, x+i, y+j) == 0xff0000 ) resp=true;

                // color verde
                if ( getpixel( cbuffer, x+i, y+j) == 0x00ff00 )
                {
                      cambio = 1;
                      resp=true;
                }
                // color azul
                if ( getpixel( cbuffer, x+i, y+j) == 0x0000ff )
                {
                      cambio = 2;
                      resp=true;
                }
                // color amarillo
                if ( getpixel( cbuffer, x+i, y+j) == 0xffff00 )
                {
                      cambio = 3;
                      resp=true;
                }
        }
    }
    return resp;
}


void player::teclado()
{
      int ax = x;
      int ay = y;

      if ( !hablar && !swtienda )
      {
          // teclas control usuario
          if ( key[KEY_UP] )
          {
               y-=desplazamiento;
               direccion = 3;
          }
          if ( key[KEY_DOWN] )
          {
               y+=desplazamiento;
               direccion = 0;
          }
          if ( key[KEY_LEFT] )
          {
               x-=desplazamiento;
               direccion = 1;
          }
          if ( key[KEY_RIGHT] )
          {
               x+=desplazamiento;
               direccion = 2;
          }
          if ( key[KEY_SPACE] && ataca == 0 )
          {
               ataca = 1;
          }
          if ( !key[KEY_SPACE] && ataca == 1 )
          {
               ataca = 2;
               sonido_espada_aire();
          }
      }
      if ( ax != x || ay != y )
      {
           if ( choca() )
           {
                x =ax;
                y =ay;
           }else{

               int num = FRAME_RATE / 12;
               if ( tiempo_total % num == 0 )
               {
                   sonido_pasos();
                   // entra si a cambiado alguna de las variables x,y
                   animacion++;
                   if ( animacion > 2 ) animacion = 0;
               }
           }
      }
      if ( ataca > (FRAME_RATE / 4) ) ataca = 0;
}



void player::posiciona( int _x, int _y)
{
     x=_x;
     y=_y;
}
void player::herido(int n){
    vida-=n;
    if(vida<=0){
        cambio=2;
        vida=100;
        jmuerto=true;
    }

    }
