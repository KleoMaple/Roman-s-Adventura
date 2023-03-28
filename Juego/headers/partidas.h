#ifndef PARTIDAS_H_INCLUDED
#define PARTIDAS_H_INCLUDED
void guarda_partida(){
    char contenido[255];

    packfile_password("antiotakus");
    PACKFILE *fichero;

    fichero = pack_fopen("partida.sav","w");
    // datos del jugador

    pack_fputs(itoa(jugador.getx(),contenido,10), fichero);
    pack_fputs("\n", fichero);

    pack_fputs(itoa(jugador.gety(),contenido,10), fichero);
    pack_fputs("\n", fichero);

    pack_fputs(itoa(jugador.getvida(),contenido,10), fichero);
    pack_fputs("\n", fichero);

    pack_fputs(itoa(jugador.getvidamax(),contenido,10), fichero);
    pack_fputs("\n", fichero);

    pack_fputs(itoa(jugador.getexp(),contenido,10), fichero);
    pack_fputs("\n", fichero);

    pack_fputs(itoa(jugador.getnivel(),contenido,10), fichero);
    pack_fputs("\n", fichero);

    pack_fputs(itoa(jugador.getdinero(),contenido,10), fichero);
    pack_fputs("\n", fichero);

    pack_fputs(itoa(jugador.getcasco(),contenido,10), fichero);
    pack_fputs("\n", fichero);

    pack_fputs(itoa(jugador.getarmadura(),contenido,10), fichero);
    pack_fputs("\n", fichero);

    pack_fputs(itoa(jugador.getarma(),contenido,10), fichero);
    pack_fputs("\n", fichero);

    pack_fputs(itoa(jugador.getanillo(),contenido,10), fichero);
    pack_fputs("\n", fichero);

    for (int i=0; i < 12; i++)
    {
        pack_fputs(itoa(jugador.getinventario(i),contenido,10), fichero);
        pack_fputs("\n", fichero);
    }
    // datos del escenario

    pack_fputs(itoa(lugar,contenido,10), fichero);
    pack_fputs("\n", fichero);

    pack_fputs(itoa(desplazamiento_map_x,contenido,10), fichero);
    pack_fputs("\n", fichero);

    pack_fputs(itoa(desplazamiento_map_y,contenido,10), fichero);
    pack_fputs("\n", fichero);

 // npc y enemigos

    pack_fputs(itoa(npersonaje,contenido,10), fichero);
    pack_fputs("\n", fichero);

    for( int i=0; i < npersonaje; i++)
    {
        pack_fputs(itoa(personajes[i].getimg(),contenido,10), fichero);
        pack_fputs("\n", fichero);

        pack_fputs(itoa(personajes[i].getx(),contenido,10), fichero);
        pack_fputs("\n", fichero);

        pack_fputs(itoa(personajes[i].gety(),contenido,10), fichero);
        pack_fputs("\n", fichero);

        pack_fputs(itoa(personajes[i].getdir(),contenido,10), fichero);
        pack_fputs("\n", fichero);

        pack_fputs(itoa(personajes[i].getestado(),contenido,10), fichero);
        pack_fputs("\n", fichero);

        pack_fputs(itoa(personajes[i].getlugar(),contenido,10), fichero);
        pack_fputs("\n", fichero);
    }

    pack_fputs(itoa(nmalos,contenido,10), fichero);
    pack_fputs("\n", fichero);

    for( int i=0; i < nmalos; i++)
    {
        pack_fputs(itoa(malos[i].getimg(),contenido,10), fichero);
        pack_fputs("\n", fichero);

        pack_fputs(itoa(malos[i].getx(),contenido,10), fichero);
        pack_fputs("\n", fichero);

        pack_fputs(itoa(malos[i].gety(),contenido,10), fichero);
        pack_fputs("\n", fichero);

        pack_fputs(itoa(malos[i].getdir(),contenido,10), fichero);
        pack_fputs("\n", fichero);

        pack_fputs(itoa(malos[i].getestado(),contenido,10), fichero);
        pack_fputs("\n", fichero);

        pack_fputs(itoa(malos[i].getlugar(),contenido,10), fichero);
        pack_fputs("\n", fichero);

        pack_fputs(itoa(malos[i].getvida(),contenido,10), fichero);
        pack_fputs("\n", fichero);

    }

    pack_fclose(fichero);
};
void carga_partida(){
    char contenido[255];

    packfile_password("kodaygames2015");
    PACKFILE *fichero;

    fichero = pack_fopen("partida.sav","r");
    // datos del jugador

    pack_fgets( contenido, 255, fichero);
    int jx = atoi( contenido );

    pack_fgets( contenido, 255, fichero);
    int jy = atoi( contenido );

    jugador.posiciona(jx,jy);

    pack_fgets( contenido, 255, fichero);
    jugador.setvida( atoi( contenido ));

    pack_fgets( contenido, 255, fichero);
    jugador.setvidamax( atoi( contenido ));

    pack_fgets( contenido, 255, fichero);
    jugador.setexp( atoi( contenido ));

    pack_fgets( contenido, 255, fichero);
    jugador.setnivel( atoi( contenido ));

    pack_fgets( contenido, 255, fichero);
    jugador.setdinero( atoi( contenido ));

    pack_fgets( contenido, 255, fichero);
    jugador.pon_casco( atoi( contenido ));

    pack_fgets( contenido, 255, fichero);
    jugador.pon_armadura( atoi( contenido ));

    pack_fgets( contenido, 255, fichero);
    jugador.pon_arma( atoi( contenido ));

    pack_fgets( contenido, 255, fichero);
    jugador.pon_anillo( atoi( contenido ));

    for (int i=0; i < 12; i++)
    {
    pack_fgets( contenido, 255, fichero);
    jugador.pon_inventario( i, atoi( contenido ) );

    }

// datos del escenario

    pack_fgets( contenido, 255, fichero);
    lugar = atoi( contenido );

    pack_fgets( contenido, 255, fichero);
    desplazamiento_map_x = atoi( contenido );
    pack_fgets( contenido, 255, fichero);
    desplazamiento_map_y = atoi( contenido );

// npc y enemigos

    pack_fgets( contenido, 255, fichero);
    npersonaje = atoi( contenido );

    int timg;
    int tx;
    int ty;
    int tdir;
    int testado;
    int tlugar;
    int tvida;

    for ( int i = 0; i < npersonaje; i++)
    {

        pack_fgets( contenido, 255, fichero);
        timg = atoi( contenido );

        pack_fgets( contenido, 255, fichero);
        tx = atoi( contenido );

        pack_fgets( contenido, 255, fichero);
        ty = atoi( contenido );

        pack_fgets( contenido, 255, fichero);
        tdir = atoi( contenido );

        pack_fgets( contenido, 255, fichero);
        testado = atoi( contenido );

        pack_fgets( contenido, 255, fichero);
        tlugar = atoi( contenido );

        personajes[i].crea( timg, tx, ty, tdir, testado, tlugar );

    }

    pack_fgets( contenido, 255, fichero);
    nmalos = atoi( contenido );

    for ( int i = 0; i < nmalos; i++)
    {
        pack_fgets( contenido, 255, fichero);
        timg = atoi( contenido );

        pack_fgets( contenido, 255, fichero);
        tx = atoi( contenido );

        pack_fgets( contenido, 255, fichero);
        ty = atoi( contenido );

        pack_fgets( contenido, 255, fichero);
        tdir = atoi( contenido );

        pack_fgets( contenido, 255, fichero);
        testado = atoi( contenido );

        pack_fgets( contenido, 255, fichero);
        tlugar = atoi( contenido );

        pack_fgets( contenido, 255, fichero);
        tvida = atoi( contenido );

        malos[i].crea( timg, tx, ty, tdir, testado, tlugar, tvida );
    }

    pack_fclose(fichero);
};
#endif // PARTIDAS_H_INCLUDED
