// misobjetos.h

#include <vector>
using namespace std;

struct m_objetos{
    int nid;
    int id;
    int tipo;
    char nombre[50];
    char descripcion [255];
    int img;
    int precio;
};

vector< m_objetos > lobj;

int id_img_objeto(int id)
{
    for(int i = 0;i < lobj.size();i++)
    {
        if(lobj[i].nid==id)return lobj[i].id;
    }
    return 0;
}
char* descripcion_objeto(int id)
{
    for(int i = 0;i<lobj.size();i++)
    {
        if(lobj[i].nid==id)return lobj[i].descripcion;
    }
    return "";
}
char* nombre_objeto( int id)
{
    for(int i = 0;i<lobj.size();i++)
    {
        if(lobj[i].nid==id)return lobj[i].nombre;
    }
    return "";
}
int precio_objeto(int id)
{
    for(int i= 0;i<lobj.size();i++)
    {
        if(lobj[i].nid==id)return lobj[i].precio;
    }
}
int tipo( int id ){
    for(int i = 0; i < lobj.size(); i++)
    {
            if ( lobj[i].id == id ) return lobj[i].tipo;
    }
    return -1;
}

int equipo_personaje( int id ){
    for(int i = 0; i < lobj.size(); i++)
    {
            if ( lobj[i].id == id && lobj[i].tipo < 5 ) return lobj[i].img;
    }
    return -1;
}

void lee_objetos(){
    char contenido[255];

    m_objetos temp;

    packfile_password(NULL);
    PACKFILE *fichero;

    fichero = pack_fopen("objetos.txt","r");

    while ( !pack_feof(fichero) )
    {
        pack_fgets( contenido, 255, fichero);
        temp.nid = atoi( contenido );

        pack_fgets( contenido, 255, fichero);
        temp.id = atoi( contenido );

        pack_fgets( contenido, 255, fichero);
        temp.tipo = atoi( contenido );

        pack_fgets( contenido, 255, fichero);
        strncpy(temp.nombre,contenido,29);
        temp.nombre[30]='\0';

        pack_fgets( temp.descripcion, 255, fichero);

        pack_fgets( contenido, 255, fichero);
        temp.img = atoi( contenido );

        pack_fgets( contenido, 255, fichero);
        temp.precio = atoi( contenido );

        lobj.push_back( temp );
    }

    pack_fclose(fichero);
};
