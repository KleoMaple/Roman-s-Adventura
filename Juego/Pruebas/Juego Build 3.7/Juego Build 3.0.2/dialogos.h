// dialogos.h

#ifndef _DIALOGOS_H_
#define _DIALOGOS_H_

#define espaciado 4

#include <allegro.h>
#include <string>
using namespace std;

class MENSAJE{

      string stexto;

      FONT *fuente;

      // ancho total del texto enviado
      int tancho;
      int talto;

      // para delimitar el rectangulo de vision
      int mx1,my1;
      int mx2,my2;
      // ancho y alto del rectangulo
      int ancho, alto;

      // numero de lineas totales q caben en el rectangulo
      int nlineas;

      void numlineas();

   public:

      void crea(const char* t, FONT* f, int x1, int y1, int x2, int y2);

      void pinta(BITMAP* b);

      void cambia_texto( const char* t );

};


int menor(int x, int y){
    if ( x < y ){
       return x;
    }else{
       return y;
    }
}


int mayor(int x, int y){
    if ( x < y ){
       return y;
    }else{
       return x;
    }
}


void MENSAJE::numlineas(){
     int cont;
     int espacio = 0;
     char* mtexto = (char*)stexto.c_str();
     nlineas=1;

     if ( tancho+espaciado > ancho ){
        // no cabe en una linea
        string resto = stexto;
        string trozo;
        char caracter[] = " ";
        char* caracter2;
        int nuevoancho = 0;
        int nc = 0;
        int restoancho = 0;
        do{
                cont=1;
                trozo = resto.substr(0,cont);
                mtexto = (char*)trozo.c_str();
                nuevoancho = text_length( fuente, mtexto );
                espacio = 0;
                while ( nuevoancho+espaciado < ancho ){
                      trozo = resto.substr(cont,1);
                      caracter2 = (char*)trozo.c_str();
                      if ( strcmp(caracter2,caracter)==0 ){
                           espacio = cont;
                      }
                      cont++;
                      trozo = resto.substr(0,cont);
                      mtexto = (char*)trozo.c_str();
                      nuevoancho = text_length( fuente, mtexto );
                }
                nc = resto.length();
                trozo = resto.substr(cont,1);
                caracter2 = (char*)trozo.c_str();
                nlineas++;
                if ( espacio >0 && cont < nc && strcmp(caracter2,caracter)!=0 )
                {
                     resto = resto.substr(espacio);
                }else{
                     resto = resto.substr(cont);
                }
                restoancho = text_length( fuente, resto.c_str() );
        }while( restoancho+espaciado > ancho );

     }
}


void MENSAJE::crea(const char* t, FONT* f, int x1, int y1, int x2, int y2){
   stexto = t;
   tancho = text_length( f, t );
   talto  = text_height(f) + espaciado;
   fuente = f;

   mx1 = menor(x1,x2);
   mx2 = mayor(x1,x2);
   my1 = menor(y1,y2);
   my2 = mayor(y1,y2);
   ancho = abs( mx1 - mx2 );
   alto  = abs( my1 - my2 );

   numlineas();

};


void MENSAJE::pinta(BITMAP* b){
     int cont;
     int espacio = 0;
     char* mtexto = (char*)stexto.c_str();
     int linea=0;
     int ni;
     int altura = 0;
     float exacto;
     BITMAP *cuadro = create_bitmap(ancho,alto);


    clear_to_color(cuadro, 0x222222);
    set_trans_blender(0,0,0,130);
    draw_trans_sprite(b, cuadro, mx1, my1);
    set_trans_blender(0,0,0,255);

    rect(b, mx1-1, my1-1, mx2-1, my2-1, 0xfcf902);
    rect(b, mx1+1, my1+1, mx2+1, my2+1, 0x363712);
    rect(b, mx1, my1, mx2, my2, 0x222222);


     if ( tancho+espaciado > ancho ){
        // no cabe en una linea
        string resto = stexto;
        string trozo;
        char caracter[] = " ";
        char* caracter2;
        int nuevoancho = 0;
        int nc = 0;
        int restoancho = 0;

         do{
                cont=1;
                trozo = resto.substr(0,cont);
                mtexto = (char*)trozo.c_str();
                nuevoancho = text_length( fuente, mtexto );
                espacio = 0;
                while ( nuevoancho+espaciado < ancho ){
                      trozo = resto.substr(cont,1);
                      caracter2  = (char*)trozo.c_str();
                      if ( strcmp(caracter2,caracter)==0 ){
                           // LOG_MENSAJE( "una palabra a partir " );
                           espacio = cont;
                      }
                      cont++;
                      trozo = resto.substr(0,cont);
                      mtexto = (char*)trozo.c_str();
                      nuevoancho = text_length( fuente, mtexto );
                }
                nc = resto.length();
                trozo = resto.substr(cont,1);
                caracter2  = (char*)trozo.c_str();

                if ( espacio >0 && cont < nc && strcmp(caracter2,caracter)!=0 ){
                     trozo = resto.substr(0,espacio);
                     mtexto = (char*)trozo.c_str();
                     resto = resto.substr(espacio);
                     // LOG_MENSAJE( "una palabra que no se ha partido " );
                }else{
                     trozo = resto.substr(0,cont);
                     mtexto = (char*)trozo.c_str();
                     resto = resto.substr(cont);
                }


                altura = alto - (talto*nlineas);
                exacto = ( alto / nlineas );
                ni = int( exacto );

                textout_centre_ex(b, fuente, mtexto, mx1+1+int(ancho/2), my1+2+(ni*linea)-(talto/2)+(ni/2) , 0x363712, -1);
                textout_centre_ex(b, fuente, mtexto, mx1+int(ancho/2), my1+1+(ni*linea)-(talto/2)+(ni/2) , 0xffffff, -1);

                linea++;
                restoancho = text_length( fuente, resto.c_str() );
         }while( restoancho+espaciado > ancho );

        mtexto = (char*)resto.c_str();
        textout_centre_ex(b, fuente, mtexto, mx1+1+int(ancho/2), my1+2+(ni*linea)-(talto/2)+(ni/2) , 0x363712, -1);
        textout_centre_ex(b, fuente, mtexto, mx1+int(ancho/2), my1+1+(ni*linea)-(talto/2)+(ni/2) , 0xffffff, -1);

     }else{

         textout_centre_ex(b, fuente, mtexto, mx1+(ancho/2)+1, my1+1+((alto-talto)/2), 0x363712, -1);
         textout_centre_ex(b, fuente, mtexto, mx1+(ancho/2), my1+((alto-talto)/2), 0xffffff, -1);

     }


     destroy_bitmap(cuadro);

};


void MENSAJE::cambia_texto( const char* t){
   stexto = t;
   tancho = text_length( fuente, t );

   numlineas();
};


#endif
