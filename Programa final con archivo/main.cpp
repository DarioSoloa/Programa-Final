#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX 50

using namespace std;

int ultPos=0; //ULTIMA POSICION LIBRE

typedef struct libro // DEFINICION DE ESTRUCTURA DE TIPO LIBRO
{
    int id;
    char titulo[50];
    char autor[30];
    int paginas;
    char estado[20];
} libro;

void gotoxy(int x,int y) //PROCEDIMIENTO PARA POSICIONAR EL CURSOR
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y= y;
    SetConsoleCursorPosition(hcon,dwPos);
}

void inicializarLista(libro *p); // PROCEDIMIENTO PARA INICIALIZAR EL ARREGLO DE LIBROS

int menu1();

int menu2();

int menu3();

void nuevoLibro(libro *p);

void verLibrosDeArray(libro *p);

void buscarNro(libro *p);

void buscarTitulo(libro *p);

void buscarAutor(libro *p);

void buscarEstado(libro *p);

void eliminarLibro(libro *p);

void insertarPrinc(libro *p);

void insertarManual(libro *p);

void editarLibro(libro *p);

void marcarLibro(libro *p);

void cargaDeDatos(libro *p); //PROCEDIMIENTO PARA CARGAR DATOS DEL ARCHIVO AL ARREGLO

void guardarDatos(libro *p); //PROCEDIMIENTO PARA GUARDAR DATOS EN EL ARCHIVO DESDE EL ARREGLO

int main()
{
    int opc1,opc2,opc3;
    libro listaDeLibros[MAX]; //ARREGLO DE LIBROS QUE CONTENDRA LA LISTA DE LIBROS
    libro *puntero=NULL;
    FILE *archivo;
    libro comprobacion;
    puntero = listaDeLibros;
    archivo=fopen("listaDeLibros","r");
    if(archivo==NULL) //COMPROBACION DE SI SE PUDO O NO LEER EL ARCHIVO
    {
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"|     ADVERTENCIA! NO SE HA PODIDO ABRIR EL ARCHIVO!     |"<<endl;
        cout<<"|    -> Se creara un archivo nuevo a continuacion <-     |"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        system("pause");
        system("cls");
    }
    else
    {
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| ARCHIVO ABIERTO CON EXITO!                             |"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        while(fread(&comprobacion,sizeof(libro),1,archivo))
        {
            ultPos++; //SI SE PUDO LEER, SE AUMENTA LA ULTIMA POSICION SEGUN CUANTOS LIBROS SE GUARDARON

        }
        fclose(archivo);
        system("pause");
        system("cls");
        if(ultPos>0)
        {
            cargaDeDatos(puntero); //SI SE PUDO LEER Y HAY LIBROS, SE CARGAN EN EL ARREGLO
        }
        else
        {
            inicializarLista(puntero); //SI NO SE PUDO LEER O NO HAY LIROS, SE INICIALIZA EL ARREGLO DE LIBROS
        }
    }
    do
    {
        opc1=menu1(); // LLAMADA AL MENU PRINCIPAL
        switch (opc1)
        {
        case 0: // PRINCIPAL/ SALIR
            guardarDatos(puntero);
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"| Fin del programa...                                    |"<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            exit(0);
            break;
        case 1: // PRINCIPAL/ AGREGAR NUEVO LIBRO
            nuevoLibro(puntero);
            guardarDatos(puntero);
            break;
        case 2: // PRINCIPAL/ VER LISTADO DE LIBROS DESDE EL ARREGLO
            verLibrosDeArray(puntero);
            guardarDatos(puntero);
            break;
        case 3: // PRINCIPAL/ BUSQUEDA DE LIBROS
            if(ultPos<1) // SI ULTIMA POSICION NO CAMBIO DE CERO ENTONCES EL ARREGLO ESTA VACIO
            {
                cout<<"----------------------------------------------------------"<<endl;
                cout<<"| El listado de libros esta vacio...                     |"<<endl;
                cout<<"| Primero debe agregar nuevos libros                     |"<<endl;
                cout<<"----------------------------------------------------------"<<endl;
                system("pause");
                system("cls");
            }
            else
            {
                do
                {
                    opc2=menu2(); // LLAMADA AL MENU DE BUSQUEDA DE LIBROS
                    switch (opc2)
                    {
                    case 0: // BUSQUEDA/ SALIR
                        guardarDatos(puntero);
                        system("cls");
                        break;
                    case 1:// BUSQUEDA/ BUSCAR POR NRO
                        buscarNro(puntero);
                        guardarDatos(puntero);
                        break;
                    case 2:// BUSQUEDA/ BUSCAR POR TITULO
                        buscarTitulo(puntero);
                        guardarDatos(puntero);
                        break;
                    case 3:// BUSQUEDA/ BUSCAR POR AUTOR
                        buscarAutor(puntero);
                        guardarDatos(puntero);
                        break;
                    case 4:// BUSQUEDA/ BUSCAR POR ESTADO
                        buscarEstado(puntero);
                        guardarDatos(puntero);
                        break;
                    default:// BUSQUEDA/ OPCION NO VALIDA
                        guardarDatos(puntero);
                        cout<<"----------------------------------------------------------"<<endl;
                        cout<<"| Por favor ingrese una opcion valida...                 |"<<endl;
                        cout<<"----------------------------------------------------------"<<endl;
                        system("pause");
                        system("cls");
                        break;
                    }
                }
                while(opc2!=0);
            }
            break;
        case 4:// PRINCIPAL/ ELIMINAR LIBRO
            if(ultPos<1)
            {
                cout<<"----------------------------------------------------------"<<endl;
                cout<<"| El listado de libros esta vacio...                     |"<<endl;
                cout<<"| Primero debe agregar nuevos libros                     |"<<endl;
                cout<<"----------------------------------------------------------"<<endl;
                system("pause");
                system("cls");
            }
            else
            {
                eliminarLibro(puntero);
                guardarDatos(puntero);
            }
            break;
        case 5: // PRINCIPAL/ INSERTAR LIBROS
            if(ultPos<1)
            {
                cout<<"----------------------------------------------------------"<<endl;
                cout<<"| El listado de libros esta vacio...                     |"<<endl;
                cout<<"| Primero debe agregar nuevos libros                     |"<<endl;
                cout<<"----------------------------------------------------------"<<endl;
                system("pause");
                system("cls");
            }
            else
            {
                do
                {
                    opc3=menu3(); // LLAMADA AL MENU DE INSERTAR LIBROS
                    switch (opc3)
                    {
                    case 0: // INSERTAR/ SALIR
                        system("cls");
                        guardarDatos(puntero);
                        break;
                    case 1: // INSERTAR/ INSERTAR AL PRINCIPIO
                        insertarPrinc(puntero);
                        guardarDatos(puntero);
                        break;
                    case 2: // INSERTAR/ INSERTAR EN NRO MANUAL
                        insertarManual(puntero);
                        guardarDatos(puntero);
                        break;
                    default: // INSERTAR/ OPCION NO VALIDA
                        cout<<"----------------------------------------------------------"<<endl;
                        cout<<"| Por favor ingrese una opcion valida...                 |"<<endl;
                        cout<<"----------------------------------------------------------"<<endl;
                        system("pause");
                        system("cls");
                        break;
                    }
                }
                while(opc3!=0);
            }
            break;
        case 6: // PRINCIPAL/ EDITAR LIBRO
            if(ultPos<1)
            {
                cout<<"----------------------------------------------------------"<<endl;
                cout<<"| El listado de libros esta vacio...                     |"<<endl;
                cout<<"| Primero debe agregar nuevos libros                     |"<<endl;
                cout<<"----------------------------------------------------------"<<endl;
                system("pause");
                system("cls");
            }
            else
            {
                editarLibro(puntero);
                guardarDatos(puntero);
            }
            break;
        case 7: // PRINCIPAL/ MARCAR LIBRO COMO...
            if(ultPos<1)
            {
                cout<<"----------------------------------------------------------"<<endl;
                cout<<"| El listado de libros esta vacio...                     |"<<endl;
                cout<<"| Primero debe agregar nuevos libros                     |"<<endl;
                cout<<"----------------------------------------------------------"<<endl;
                system("pause");
                system("cls");
            }
            else
            {
                marcarLibro(puntero);
                guardarDatos(puntero);
            }
            break;
        default: // PRINCIPAL/ OPCION NO VALIDA
            guardarDatos(puntero);
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"| Por favor ingrese una opcion valida...                 |"<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            system("pause");
            system("cls");
            break;
        }
    }
    while(opc1!=0);
    guardarDatos(puntero);
    return 0;
}

void inicializarLista(libro *p)
{
    char copiar[]="Vacio";
    for(int i=0; i<MAX; i++)
    {
        p->id=0;
        strcpy(p->titulo,copiar);
        strcpy(p->autor,copiar);
        p->paginas=0;
        strcpy(p->estado,copiar);
        p++;
    }
}

int menu1()
{
    int opc;
    cout<<"---- MENU PRINCIPAL --------------------------------------"<<endl;
    cout<<"|                                                        |"<<endl;
    cout<<"| 1. Agregar un nuevo libro (al final)                   |"<<endl;
    cout<<"| 2. Ver listado de libros                               |"<<endl;
    cout<<"| 3. Busqueda de libros                                  |"<<endl;
    cout<<"| 4. Eliminar libro                                      |"<<endl;
    cout<<"| 5. Insertar libros                                     |"<<endl;
    cout<<"| 6. Editar libro                                        |"<<endl;
    cout<<"| 7. Marcar libro como...                                |"<<endl;
    cout<<"| 0. Salir                                               |"<<endl;
    cout<<"|                                                        |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| Su eleccion ->                                         |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"\n"<<endl;
    gotoxy(17,12);
    cin>>opc;
    system("cls");
    return opc;
}

int menu2()
{
    int opc;
    cout<<"---- BUSQUEDA DE LIBROS ----------------------------------"<<endl;
    cout<<"|                                                        |"<<endl;
    cout<<"| 1. Buscar libro por numero                             |"<<endl;
    cout<<"| 2. Buscar libro por titulo                             |"<<endl;
    cout<<"| 3. Buscar libro/s por autor                            |"<<endl;
    cout<<"| 4. Buscar libro/s por estado                           |"<<endl;
    cout<<"| 0. Regresar                                            |"<<endl;
    cout<<"|                                                        |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| Su eleccion ->                                         |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"\n"<<endl;
    gotoxy(17,9);
    cin>>opc;
    system("cls");
    return opc;
}

int menu3()
{
    int opc;
    cout<<"---- INSERTAR LIBROS -------------------------------------"<<endl;
    cout<<"|                                                        |"<<endl;
    cout<<"| 1. Insertar libro al principio (Nro. 1)                |"<<endl;
    cout<<"| 2. Insertar libro en posicion manual                   |"<<endl;
    cout<<"| 0. Regresar                                            |"<<endl;
    cout<<"|                                                        |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| Su eleccion ->                                         |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"\n"<<endl;
    gotoxy(17,7);
    cin>>opc;
    system("cls");
    return opc;
}

void nuevoLibro(libro *p)
{
    char opc;
    char estado[]="DISPONIBLE"; // STRING PARA COPIAR EN EL ESTADO DEL NUEVO LIBRO
    do
    {
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| AGREGAR NUEVO LIBRO                                    |"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        p=p+ultPos;
        p->id=ultPos+1;
        cout<<"\nLIBRO Nro. "<<p->id<<endl;
        fflush(stdin);
        cout<<"\nTitulo: ";
        cin.get(p->titulo,50);
        fflush(stdin);
        cout<<"\nAutor: ";
        cin.get(p->autor,30);
        fflush(stdin);
        cout<<"\nPaginas: ";
        cin>>p->paginas;
        fflush(stdin);
        strcpy(p->estado,estado); // TODO LIBRO NUEVO INGRESA CON ESTADO DISPONIBLE
        p=p-ultPos; // REINICIO DEL PUNTERO
        ultPos++; // SE INCREMENTA LA ULTIMA POSICION YA QUE SE AÑADIO UN NUEVO LIBRO
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| Desea agregar otro libro? S/N ->                       |"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        gotoxy(35,12);
        cin>>opc;
        system("cls");
    }
    while(opc=='S'||opc=='s');
    system("cls");
}

void verLibrosDeArray(libro *p)
{
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| LISTADO DE LIBROS                                      |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    if(ultPos<1)
    {
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| El listado de libros esta vacio...                     |"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        system("pause");
        system("cls");
    }
    else
    {
        for(int i=0; i<ultPos; i++)
        {
            cout<<"\nLIBRO Nro. "<<p->id<<endl;
            cout<<"\nTitulo: "<<p->titulo<<endl;
            cout<<"\nAutor: "<<p->autor<<endl;
            cout<<"\nPaginas: "<<p->paginas<<endl;
            cout<<"\nEstado: "<<p->estado<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            p++;
        }
        system("pause");
        system("cls");
    }
}

void buscarNro(libro *p)
{
    int nro;
    bool aux=false;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| BUSQUEDA DE LIBRO POR NUMERO                           |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| Que numero de libro desea buscar? ->                   |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    gotoxy(39,3);
    cin>>nro;
    for(int i=0; i<ultPos && !aux; i++)
    {
        if(p->id==nro)
        {
            cout<<"\nEl libro Nro. "<<p->id<<" es:"<<endl;
            cout<<"\nTitulo: "<<p->titulo<<endl;
            cout<<"\nAutor: "<<p->autor<<endl;
            cout<<"\nPaginas: "<<p->paginas<<endl;
            cout<<"\nEstado: "<<p->estado<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            aux=true;
        }
        p++;
    }
    if(aux==false)
    {
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| NO SE ENCONTRO EL NRO. DE LIBRO INGRESADO...           |"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
    }
    system("pause");
    system("cls");
}

void buscarTitulo(libro *p)
{
    char titulo1[50];
    char titulo2[50];
    bool aux=false;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| BUSQUEDA DE LIBRO POR TITULO                           |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| Titulo del libro desea buscar? ->                       "<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    gotoxy(36,3);
    fflush(stdin);
    cin.get(titulo1,50);
    strlwr(titulo1); // PASA TITULO1 A MINUSCULA
    for(int i=0; i<ultPos; i++)
    {
        strcpy(titulo2,p->titulo); // GUARDA EN TITULO2 EL TITULO DEL PUNTERO
        strlwr(titulo2); // PASA TITULO2 A MINUSCULA
        if(strcmp(titulo1,titulo2)==0) // COMPARACION DE AMBOS STRINGS
        {
            cout<<"\nEl libro de titulo | "<<p->titulo<<" | es:"<<endl;
            cout<<"\nEl libro Nro. "<<p->id<<endl;
            cout<<"\nAutor: "<<p->autor<<endl;
            cout<<"\nPaginas: "<<p->paginas<<endl;
            cout<<"\nEstado: "<<p->estado<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            aux=true;
        }
        p++;
    }
    if(aux==false)
    {
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| NO SE ENCONTRO EL LIBRO INGRESADO...                   |"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
    }
    system("pause");
    system("cls");
}

void buscarAutor(libro *p)
{
    char autor1[30];
    char autor2[30];
    bool aux=false;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| BUSQUEDA DE LIBRO/S POR AUTOR                          |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| Autor del libro desea buscar? ->                        "<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    gotoxy(35,3);
    fflush(stdin);
    cin.get(autor1,30);
    strlwr(autor1);
    for(int i=0; i<ultPos; i++)
    {
        strcpy(autor2,p->autor);
        strlwr(autor2);
        if(strcmp(autor1,autor2)==0)
        {
            cout<<"\nLibro cuyo autor es | "<<p->autor<<" | :"<<endl;
            cout<<"\nLibro Nro. "<<p->id<<endl;
            cout<<"\nTitulo: "<<p->titulo<<endl;
            cout<<"\nPaginas: "<<p->paginas<<endl;
            cout<<"\nEstado: "<<p->estado<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            aux=true;
        }
        p++;
    }
    if(aux==false)
    {
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| NO SE ENCONTRO LIBRO DEL AUTOR INGRESADO...            |"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
    }
    system("pause");
    system("cls");
}

void buscarEstado(libro *p)
{
    int opc;
    bool salir=false;
    bool aux;
    char copiar1[]="DISPONIBLE";
    char copiar2[]="RESERVADO";
    char copiar3[]="PRESTADO";
    do
    {
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| BUSQUEDA DE LIBRO/S POR ESTADO                         |"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| Mostrar libro/s de estado:                             |"<<endl;
        cout<<"| 1.DISPONIBLE  2.RESERVADO  3.PRESTADO  0.Volver        |"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| Su eleccion ->                                         |"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        gotoxy(17,6);
        cin>>opc;
        switch(opc)
        {
        case 0:
            salir=true;
            system("cls");
            break;
        case 1:
            system("cls");
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"| BUSQUEDA DE LIBRO/S POR ESTADO                         |"<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"| Libro/s de estado DISPONIBLE:                          |"<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            for(int i=0; i<ultPos; i++)
            {
                if(strcmp(copiar1,p->estado)==0)
                {
                    cout<<"\nLibro Nro. "<<p->id<<endl;
                    cout<<"\nTitulo: "<<p->titulo<<endl;
                    cout<<"\nAutor: "<<p->autor<<endl;
                    cout<<"\nPaginas: "<<p->paginas<<endl;
                    cout<<"----------------------------------------------------------"<<endl;
                    aux=true;
                }
                p++;
            }
            if(aux==false)
            {
                cout<<"----------------------------------------------------------"<<endl;
                cout<<"| NO SE ENCONTRARON LIBROS DE ESTADO DISPONIBLE...       |"<<endl;
                cout<<"----------------------------------------------------------"<<endl;
            }
            salir=true;
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"| BUSQUEDA DE LIBRO/S POR ESTADO                         |"<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"| Libro/s de estado RESERVADO:                           |"<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            for(int i=0; i<ultPos; i++)
            {
                if(strcmp(copiar2,p->estado)==0)
                {
                    cout<<"\nLibro Nro. "<<p->id<<endl;
                    cout<<"\nTitulo: "<<p->titulo<<endl;
                    cout<<"\nAutor: "<<p->autor<<endl;
                    cout<<"\nPaginas: "<<p->paginas<<endl;
                    cout<<"----------------------------------------------------------"<<endl;
                    aux=true;
                }
                p++;
            }
            if(aux==false)
            {
                cout<<"----------------------------------------------------------"<<endl;
                cout<<"| NO SE ENCONTRARON LIBROS DE ESTADO RESERVADO...        |"<<endl;
                cout<<"----------------------------------------------------------"<<endl;
            }
            salir=true;
            system("pause");
            system("cls");
            break;
        case 3:
            system("cls");
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"| BUSQUEDA DE LIBRO/S POR ESTADO                         |"<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"| Libro/s de estado PRESTADO:                            |"<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            for(int i=0; i<ultPos; i++)
            {
                if(strcmp(copiar3,p->estado)==0)
                {
                    cout<<"\nLibro Nro. "<<p->id<<endl;
                    cout<<"\nTitulo: "<<p->titulo<<endl;
                    cout<<"\nAutor: "<<p->autor<<endl;
                    cout<<"\nPaginas: "<<p->paginas<<endl;
                    cout<<"----------------------------------------------------------"<<endl;
                    aux=true;
                }
                p++;
            }
            if(aux==false)
            {
                cout<<"----------------------------------------------------------"<<endl;
                cout<<"| NO SE ENCONTRARON LIBROS DE ESTADO PRESTADO...         |"<<endl;
                cout<<"----------------------------------------------------------"<<endl;
            }
            salir=true;
            system("pause");
            system("cls");
            break;
        default:
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"| Por favor ingrese una opcion valida...                 |"<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            system("pause");
            system("cls");
            break;
        }
    }
    while(salir==false);
}

void eliminarLibro(libro *p)
{
    libro eliminado; // VARIABLE DE TIPO LIBRO PARA GUARDAR EL LIBRO ELIMINADO PARA MOSTRARLO POSTERIORMENTE
    int id;
    int cont=0; // CONTADOR QUE USARE PARA REINICIAR EL PUNTERO
    char opc;
    bool aux=false;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| ELIMINAR LIBRO                                         |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| Numero del libro que desea eliminar? ->                |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    gotoxy(42,3);
    cin>>id;
    for(int i=0; i<ultPos; i++)
    {
        if(p->id==id)
        {
            aux=true;
        }
        p++;
        cont++; // EL PUNTERO Y EL CONTADOR AUMENTAN DURANTE LA BUSQUEDA
    }
    if(aux==false)
    {
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| NO SE ENCONTRO EL NRO. DE LIBRO INGRESADO...           |"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
    }
    else
    {
        system("cls");
        p=p-cont; // SE REINICIA EL PUNTERO QUE AUMENTO EN LA BUSQUEDA
        p=p+id-1; // SE POSICIONA EL PUNTERO EN LA POSICION INGRESADA
        eliminado.id=p->id; // SE COMIENZA A COPIAR EL LIBRO A ELIMINAR
        strcpy(eliminado.titulo,p->titulo);
        strcpy(eliminado.autor,p->autor);
        eliminado.paginas=p->paginas;
        strcpy(eliminado.estado,p->estado);
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| ELIMINAR LIBRO                                         |"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"Desea eliminar el siguiente libro?"<<endl;
        cout<<"\nLIBRO Nro. "<<eliminado.id<<endl;
        cout<<"\nTitulo: "<<eliminado.titulo<<endl;
        cout<<"\nAutor: "<<eliminado.autor<<endl;
        cout<<"\nPaginas: "<<eliminado.paginas<<endl;
        cout<<"\nEstado: "<<eliminado.estado<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| S/N ->                                                 |"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        gotoxy(9,14);
        cin>>opc;
        system("cls");
        if(opc=='s'||opc=='S')
        {
            for(int i=0; i<ultPos; i++) // TODOS LOS LIBROS POSTERIORES AL LIBRO ELIMINADO SE MUEVEN A UNA POSICION ANTERIOR
            {
                p->id=(p+1)->id-1;
                strcpy(p->titulo,(p+1)->titulo);
                strcpy(p->autor,(p+1)->autor);
                p->paginas=(p+1)->paginas;
                strcpy(p->estado,(p+1)->estado);
                p++;
            }
            ultPos--; // SE DECREMENTA LA ULTIMA POSICION LIBRE YA QUE SE ELIMINO UN LIBRO
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"| ELIMINAR LIBRO                                         |"<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"El siguiente libro:"<<endl; // SE MUESTRA EL LIBRO ELIMINADO
            cout<<"\nLIBRO Nro. "<<eliminado.id<<endl;
            cout<<"\nTitulo: "<<eliminado.titulo<<endl;
            cout<<"\nAutor: "<<eliminado.autor<<endl;
            cout<<"\nPaginas: "<<eliminado.paginas<<endl;
            cout<<"\nEstado: "<<eliminado.estado<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"| Fue eliminado...                                       |"<<endl;
            cout<<"----------------------------------------------------------"<<endl;
        }
    }
    system("pause");
    system("cls");
}

void insertarPrinc(libro *p)
{
    char copiar[]="DISPONIBLE";
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| INSERTAR LIBRO AL PRINCIPIO                            |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    for(int i=ultPos+1; i>=0; i--) // SE MUEVEN TODOS LOS LIBROS UNA POSICION POSTERIOR DESDE EL PRINCIPIO
    {
        (p+i+1)->id=(p+i)->id+1;
        strcpy((p+i+1)->titulo,(p+i)->titulo);
        strcpy((p+i+1)->autor,(p+i)->autor);
        (p+i+1)->paginas=(p+i)->paginas;
        strcpy((p+i+1)->estado,(p+i)->estado);
    }
    ultPos++; // SE INCREMENTA LA ULTIMA POSICION DISPONIBLE YA QUE SE AGREGO UN LIBRO
    fflush(stdin);
    cout<<"\nTitulo: ";
    cin.get(p->titulo,50);
    fflush(stdin);
    cout<<"\nAutor: ";
    cin.get(p->autor,30);
    fflush(stdin);
    cout<<"\nPaginas: ";
    cin>>p->paginas;
    strcpy(p->estado,copiar);
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| Libro insertado al principio como Nro. 1               |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    system("pause");
    system("cls");
}

void insertarManual(libro *p)
{
    int nro;
    char copiar[]="DISPONIBLE";
    do
    {
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| INSERTAR LIBRO EN POSICION MANUAL                      |"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| En que Nro. desea insertar el nuevo libro -> ";
        cin>>nro;
        if(nro>=1 && nro<=ultPos+1) // CONTROL DE QUE EL NRO AL QUE SE DESEA AGREGAR EL LIBRO ESTE DENTRO DEL RANGO
        {
            for(int i=ultPos+1; i>=nro-1; i--) // TODOS LOS LIBROS POSTERIORES A LA POSICION INGRESADA SE MUEVEN AL SIGUIENTE COMENZANDO POR EL ULTIMO
            {
                (p+i+1)->id=(p+i)->id+1;
                strcpy((p+i+1)->titulo,(p+i)->titulo);
                strcpy((p+i+1)->autor,(p+i)->autor);
                (p+i+1)->paginas=(p+i)->paginas;
                strcpy((p+i+1)->estado,(p+i)->estado);
            }
            p=p+nro-1; // SE POSICIONA EL PUNTERO
            p->id=nro;
            cout<<"\nLIBRO Nro. "<<p->id<<endl; // SE COMIENZA A GUARDAR EL NUEVO LIBRO
            fflush(stdin);
            cout<<"\nTitulo: ";
            cin.get(p->titulo,50);
            fflush(stdin);
            cout<<"\nAutor: ";
            cin.get(p->autor,30);
            fflush(stdin);
            cout<<"\nPaginas: ";
            cin>>p->paginas;
            fflush(stdin);
            strcpy(p->estado,copiar);
            ultPos++;
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"| Libro insertado como Nro. "<<p->id<<"                            |"<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            system("pause");
            system("cls");
        }
        else
        {
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"| El Nro. Ingresado esta fuera del rango...              |"<<endl;
            cout<<"| Por favor ingrese un Nro. valido                       |"<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            system("pause");
            system("cls");
        }
    }
    while(nro<1 || nro>ultPos);
}

void editarLibro(libro *p)
{
    int nro;
    do
    {
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| EDITAR LIBRO                                           |"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| Que libro desea editar? Ingrese el Nro. -> ";
        cin>>nro;
        if(nro>=1 && nro<=ultPos)
        {
            p=p+nro-1;
            cout<<"\nLIBRO Nro. "<<p->id<<endl;
            fflush(stdin);
            cout<<"\nTitulo: ";
            cin.get(p->titulo,50);
            fflush(stdin);
            cout<<"\nAutor: ";
            cin.get(p->autor,30);
            fflush(stdin);
            cout<<"\nPaginas: ";
            cin>>p->paginas;
            fflush(stdin);
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"| Libro Nro. "<<p->id<<" editado                                   |"<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            system("pause");
            system("cls");
        }
        else
        {
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"| El Nro. Ingresado esta fuera del rango...              |"<<endl;
            cout<<"| Por favor ingrese un Nro. valido                       |"<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            system("pause");
            system("cls");
        }
    }
    while(nro<1 || nro>ultPos);
}

void marcarLibro(libro *p)
{
    int nro,opc;
    bool salir=false;
    char copiar1[]="DISPONIBLE"; // STRINGS QUE SE USARAN PARA CAMBIAR EL ESTADO SEGUN LA ELECCION
    char copiar2[]="RESERVADO";
    char copiar3[]="PRESTADO";
    do
    {
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| MARCAR LIBRO                                           |"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| Que libro desea marcar? Ingrese el Nro. -> ";
        cin>>nro;
        if(nro>=1 && nro<=ultPos)
        {
            p=p+nro-1;
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"\nMarcar el libro Nro. "<<p->id<<" :"<<endl;
            cout<<"\nTitulo: "<<p->titulo<<endl;
            cout<<"\nAutor: "<<p->autor<<endl;
            cout<<"\nPaginas: "<<p->paginas<<endl;
            cout<<"\nEstado actual: "<<p->estado<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"|Como->  1.DISPONIBLE  2.RESERVADO  3.PRESTADO  0.Volver |"<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"|Su eleccion -> ";
            cin>>opc;
            do
            {
                switch(opc)
                {
                case 0:
                    salir=true;
                    system("cls");
                    break;
                case 1:
                    strcpy(p->estado,copiar1); // SE CAMBIA EL ESTADO DEL LIBRO SEGUN LA ELECCION
                    cout<<"----------------------------------------------------------"<<endl;
                    cout<<"| Libro Nro. "<<p->id<<" marcado como "<<p->estado<<endl;
                    cout<<"----------------------------------------------------------"<<endl;
                    salir=true;
                    system("pause");
                    system("cls");
                    break;
                case 2:
                    strcpy(p->estado,copiar2);
                    cout<<"----------------------------------------------------------"<<endl;
                    cout<<"| Libro Nro. "<<p->id<<" marcado como "<<p->estado<<endl;
                    cout<<"----------------------------------------------------------"<<endl;
                    salir=true;
                    system("pause");
                    system("cls");
                    break;
                case 3:
                    strcpy(p->estado,copiar3);
                    cout<<"----------------------------------------------------------"<<endl;
                    cout<<"| Libro Nro. "<<p->id<<" marcado como "<<p->estado<<endl;
                    cout<<"----------------------------------------------------------"<<endl;
                    salir=true;
                    system("pause");
                    system("cls");
                    break;
                default:
                    cout<<"----------------------------------------------------------"<<endl;
                    cout<<"| Por favor ingrese una opcion valida...                 |"<<endl;
                    cout<<"----------------------------------------------------------"<<endl;
                    system("pause");
                    system("cls");
                    break;
                }
            }
            while(salir==false);
        }
        else
        {
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"| El Nro. Ingresado esta fuera del rango...              |"<<endl;
            cout<<"| Por favor ingrese un Nro. valido                       |"<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            system("pause");
            system("cls");
        }
    }
    while(nro<1 || nro>ultPos);
}


void cargaDeDatos(libro *p)
{
    FILE *archivo;
    libro cargaDeDatos;
    archivo=fopen("listaDeLibros","r");
    while(fread(&cargaDeDatos,sizeof(libro),1,archivo))
    {
        p->id=cargaDeDatos.id;
        strcpy(p->titulo,cargaDeDatos.titulo);
        strcpy(p->autor,cargaDeDatos.autor);
        p->paginas=cargaDeDatos.paginas;
        strcpy(p->estado,cargaDeDatos.estado);
        p++;
    }
    fclose(archivo);
}

void guardarDatos(libro *p)
{
    FILE *archivo;
    libro guardarDatos;
    archivo=fopen("listaDeLibros","w+");
    for(int i=0; i<ultPos; i++)
    {
        guardarDatos.id=p->id;
        strcpy(guardarDatos.titulo,p->titulo);
        strcpy(guardarDatos.autor,p->autor);
        guardarDatos.paginas=p->paginas;
        strcpy(guardarDatos.estado,p->estado);
        fwrite(&guardarDatos,sizeof(libro),1,archivo);
        p++;
    }
    fclose(archivo);
}

