/* botones.h
   clase TBOTON
   para crear texto como  boton
*/


#ifndef _BOTONES_H_
#define _BOTONES_H_

#include <allegro.h>


class TBOTON{
      public:
             void crear(const char* text, const FONT* bfuente);
             void pinta(BITMAP* bfondo, int x, int y, int color1, int color2);
             bool ratonb();

      private:
              int bx, by;
              int bpulsa;
              int bancho,balto;
              const char* btext;
              const FONT* bfuente;
};

// incializa las variables de la clase
void TBOTON::crear(const char* text, const FONT* fuente)
{
       btext = text;
       bpulsa = 0;
       bfuente = fuente;
       bancho = text_length(bfuente, btext);
       balto  = text_height(bfuente);
};

// muestra en pantalla el texto, sobre el fondo indicado, con la fuente indicada, en la posicion x,y
// con el color1 cuando esta señalado y color2 cuando no
void TBOTON::pinta(BITMAP* bfondo, int x, int y, int color1, int color2)
{
     bx=x;
     by=y;

     if (mouse_x >= bx && mouse_x < bx+bancho+1 && mouse_y >= by && mouse_y < by+balto+1)
     {
         textout_ex(bfondo, bfuente, btext, bx, by, color1, -1);
     }else{
         textout_ex(bfondo, bfuente, btext, bx, by, color2, -1);
     }
};

// comprueba si el raton esta situado encima de nuestro texto y a pulsado el boton del raton
bool TBOTON::ratonb()
{
     return (mouse_x >= bx && mouse_x <= bx+bancho && mouse_y >= by && mouse_y <= by+balto && mouse_b&1 );
};

#endif
