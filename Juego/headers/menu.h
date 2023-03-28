#define NUMOP       3

class MIMENU {
    private:
       int op;
       int max_op;
       bool salidamenu;
       bool pulsa;

    public:
       MIMENU();
       void pinta();
       int teclado();
       bool salir();
};


MIMENU::MIMENU(){
    op = 1;
    max_op = NUMOP;
    salidamenu = false;
    pulsa = false;
};



void MIMENU::pinta()
{
   if ( op == 1 )  blit(menufondo2, buffer, 0, 220, 0, 220, PANTALLA_ANCHO, 70);

   if ( op == 2 )  blit(menufondo2, buffer, 0, 310, 0, 310, PANTALLA_ANCHO, 70);

   if ( op == 3 )  blit(menufondo2, buffer, 0, 400, 0, 400, PANTALLA_ANCHO, 70);
};


int MIMENU::teclado(){

    if (key[KEY_DOWN] && !pulsa ){ op++; pulsa = true; sonido_boton(); }

    if (key[KEY_UP] && !pulsa) {op--; pulsa=true; sonido_boton(); }

    if ( pulsa && !key[KEY_DOWN] && !key[KEY_UP] ) pulsa=false;

    if (op > max_op) op=1;
    if (op < 1) op=max_op;

    // comprueba si esta en la opcion de salir
    if ((key[KEY_ENTER] || key[KEY_ENTER_PAD]) && op == max_op ) salidamenu = true;

    if (key[KEY_ESC]) op=max_op;

    return op;
};

bool MIMENU::salir(){
     return salidamenu;
};
