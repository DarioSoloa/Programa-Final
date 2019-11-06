#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <algorithm>
#define MAX 50

using namespace std;

int ultPos=0;

typedef struct libro
{
    int id;
    string titulo;
    string autor;
    int paginas;
} libro;

void stringToLower(string &s)
{
    for(unsigned int l = 0; l < s.length(); l++)
    {
        s[l] = tolower(s[l]);
    }
}

void gotoxy(int x,int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y= y;
    SetConsoleCursorPosition(hcon,dwPos);
}

int menu1();

int menu2();

int menu3();

void nuevoLibro(libro *p);

void verLibrosDeArray(libro *p);

void buscarNro(libro *p);

void buscarTitulo(libro *p);

void buscarAutor(libro *p);

void eliminarLibro(libro *p);

void insertarPrinc(libro *p);

void insertarUlt(libro *p);

void insertarManual(libro *p);

void editarLibro(libro *p);

void cargaDeDatos(libro *p);

void guardarDatos(libro *p);

int main()
{
    int opc1,opc2,opc3;
    libro listaDeLibros[MAX];
    libro *puntero=NULL;
    FILE *archivo;
    libro comprobacion;
    puntero = listaDeLibros;
    archivo=fopen("listaDeLibros","r");
    if(archivo==NULL)
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
            cout<<comprobacion.titulo;
            ultPos++;

        }
        fclose(archivo);
        system("pause");
        system("cls");
        if(ultPos>0)
        {
            cargaDeDatos(puntero);
        }
    }
    do
    {
        opc1=menu1();
        switch (opc1)
        {
        case 0:
            guardarDatos(puntero);
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"| Fin del programa...                                    |"<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            exit(0);
            break;
        case 1:
            nuevoLibro(puntero);
            guardarDatos(puntero);
            break;
        case 2:
            verLibrosDeArray(puntero);
            guardarDatos(puntero);
            break;
        case 3:
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
                    opc2=menu2();
                    switch (opc2)
                    {
                    case 0:
                        guardarDatos(puntero);
                        system("cls");
                        break;
                    case 1:
                        buscarNro(puntero);
                        guardarDatos(puntero);
                        break;
                    case 2:
                        buscarTitulo(puntero);
                        guardarDatos(puntero);
                        break;
                    case 3:
                        buscarAutor(puntero);
                        guardarDatos(puntero);
                        break;
                    default:
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
        case 4:
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
            }
            guardarDatos(puntero);
            break;
        case 5:
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
                    opc3=menu3();
                    switch (opc3)
                    {
                    case 0:
                        system("cls");
                        guardarDatos(puntero);
                        break;
                    case 1:
                        insertarPrinc(puntero);
                        guardarDatos(puntero);
                        break;
                    case 2:
                        insertarUlt(puntero);
                        guardarDatos(puntero);
                        break;
                    case 3:
                        insertarManual(puntero);
                        guardarDatos(puntero);
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
                while(opc3!=0);
            }
            break;
        case 6:
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
        default:
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

int menu1()
{
    int opc;
    cout<<"---- MENU PRINCIPAL --------------------------------------"<<endl;
    cout<<"|                                                        |"<<endl;
    cout<<"| 1. Agregar un nuevo libro                              |"<<endl;
    cout<<"| 2. Ver listado de libros                               |"<<endl;
    cout<<"| 3. Busqueda de libros                                  |"<<endl;
    cout<<"| 4. Eliminar libro                                      |"<<endl;
    cout<<"| 5. Insertar libros                                     |"<<endl;
    cout<<"| 6. Editar libro                                        |"<<endl;
    cout<<"| 0. Salir                                               |"<<endl;
    cout<<"|                                                        |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| Su eleccion ->                                         |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"\n"<<endl;
    gotoxy(17,11);
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
    cout<<"| 0. Regresar                                            |"<<endl;
    cout<<"|                                                        |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| Su eleccion ->                                         |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"\n"<<endl;
    gotoxy(17,8);
    cin>>opc;
    system("cls");
    return opc;
}

int menu3()
{
    int opc;
    cout<<"---- INSERTAR LIBROS --------------------------------------"<<endl;
    cout<<"|                                                        |"<<endl;
    cout<<"| 1. Insertar libro al principio (Nro. 1)                |"<<endl;
    cout<<"| 2. Insertar libro al final                             |"<<endl;
    cout<<"| 3. Insertar libro en posicion manual                   |"<<endl;
    cout<<"| 0. Regresar                                            |"<<endl;
    cout<<"|                                                        |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| Su eleccion ->                                         |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"\n"<<endl;
    gotoxy(17,8);
    cin>>opc;
    system("cls");
    return opc;
}

void nuevoLibro(libro *p)
{
    char opc;
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
        getline(cin,p->titulo);
        fflush(stdin);
        cout<<"\nAutor: ";
        getline(cin,p->autor);
        fflush(stdin);
        cout<<"\nPaginas: ";
        cin>>p->paginas;
        fflush(stdin);
        p=p-ultPos;
        ultPos++;
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
    cout<<"| LISTADO DE LIBROS DESDE ARRAY                          |"<<endl;
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
    for(int i=0; i<ultPos; i++)
    {
        if(p->id==nro)
        {
            cout<<"\nEl libro Nro. "<<p->id<<" es:"<<endl;
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
        cout<<"| NO SE ENCONTRO EL NRO. DE LIBRO INGRESADO...           |"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
    }
    system("pause");
    system("cls");
}

void buscarTitulo(libro *p)
{
    string titulo1,titulo2;
    bool aux=false;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| BUSQUEDA DE LIBRO POR TITULO                           |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| Titulo del libro desea buscar? ->                       "<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    gotoxy(36,3);
    fflush(stdin);
    getline(cin,titulo1);
    fflush(stdin);
    stringToLower(titulo1);
    for(int i=0; i<ultPos && !aux; i++)
    {
        titulo2=p->titulo;
        stringToLower(titulo2);
        if(titulo1==titulo2)
        {
            cout<<"\nEl libro de titulo | "<<p->titulo<<" | es:"<<endl;
            cout<<"\nEl libro Nro. "<<p->id<<endl;
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
        cout<<"| NO SE ENCONTRO EL LIBRO INGRESADO...                   |"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
    }
    system("pause");
    system("cls");
}

void buscarAutor(libro *p)
{
    string autor1,autor2;
    bool aux=false;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| BUSQUEDA DE LIBRO/S POR AUTOR                          |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| Autor del libro desea buscar? ->                        "<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    gotoxy(35,3);
    fflush(stdin);
    getline(cin,autor1);
    fflush(stdin);
    stringToLower(autor1);
    for(int i=0; i<ultPos; i++)
    {
        autor2=p->autor;
        stringToLower(autor2);
        if(autor1==autor2)
        {
            cout<<"\nLibro cuyo autor es | "<<p->autor<<" | :"<<endl;
            cout<<"\nLibro Nro. "<<p->id<<endl;
            cout<<"\nTitulo: "<<p->titulo<<endl;
            cout<<"\nPaginas: "<<p->paginas<<endl;
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

void eliminarLibro(libro *p)
{
    libro eliminado;
    int id;
    int cont=0;
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
        cont++;
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
        p=p-cont;
        p=p+id-1;
        eliminado.id=p->id;
        eliminado.titulo=p->titulo;
        eliminado.autor=p->autor;
        eliminado.paginas=p->paginas;
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| ELIMINAR LIBRO                                         |"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"Desea eliminar el siguiente libro?"<<endl;
        cout<<"\nLIBRO Nro. "<<eliminado.id<<endl;
        cout<<"\nTitulo: "<<eliminado.titulo<<endl;
        cout<<"\nAutor: "<<eliminado.autor<<endl;
        cout<<"\nPaginas: "<<eliminado.paginas<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| S/N ->                                                 |"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        gotoxy(9,13);
        cin>>opc;
        system("cls");
        if(opc=='s'||opc=='S')
        {
            for(int i=0; i<ultPos; i++)
            {
                p->id=(p+1)->id-1;
                p->titulo=(p+1)->titulo;
                p->autor=(p+1)->autor;
                p->paginas=(p+1)->paginas;
                p++;
            }
            ultPos--;
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"| ELIMINAR LIBRO                                         |"<<endl;
            cout<<"----------------------------------------------------------"<<endl;
            cout<<"El siguiente libro:"<<endl;
            cout<<"\nLIBRO Nro. "<<eliminado.id<<endl;
            cout<<"\nTitulo: "<<eliminado.titulo<<endl;
            cout<<"\nAutor: "<<eliminado.autor<<endl;
            cout<<"\nPaginas: "<<eliminado.paginas<<endl;
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
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| INSERTAR LIBRO AL PRINCIPIO                            |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    for(int i=ultPos+1; i>=0; i--)
    {
        (p+i+1)->id=(p+i)->id+1;
        (p+i+1)->titulo=(p+i)->titulo;
        (p+i+1)->autor=(p+i)->autor;
        (p+i+1)->paginas=(p+i)->paginas;
    }
    ultPos++;
    fflush(stdin);
    cout<<"\nTitulo: ";
    getline(cin,p->titulo);
    fflush(stdin);
    cout<<"\nAutor: ";
    getline(cin,p->autor);
    fflush(stdin);
    cout<<"\nPaginas: ";
    cin>>p->paginas;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| Libro insertado al principio como Nro. 1               |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    system("pause");
    system("cls");
}

void insertarUlt(libro *p)
{
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| INSERTAR LIBRO AL FINAL                                |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    p=p+ultPos;
    p->id=ultPos+1;
    cout<<"\nLIBRO Nro. "<<p->id<<endl;
    fflush(stdin);
    cout<<"\nTitulo: ";
    getline(cin,p->titulo);
    fflush(stdin);
    cout<<"\nAutor: ";
    getline(cin,p->autor);
    fflush(stdin);
    cout<<"\nPaginas: ";
    cin>>p->paginas;
    fflush(stdin);
    ultPos++;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"| Libro insertado al principio como Nro. "<<p->id<<"               |"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    system("pause");
    system("cls");
}

void insertarManual(libro *p)
{
    int nro;
    do
    {
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| INSERTAR LIBRO EN POSICION MANUAL                      |"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"| En que Nro. desea insertar el nuevo libro -> ";
        cin>>nro;
        if(nro>=1 && nro<=ultPos+1)
        {
            for(int i=ultPos+1; i>=nro-1; i--)
            {
                (p+i+1)->id=(p+i)->id+1;
                (p+i+1)->titulo=(p+i)->titulo;
                (p+i+1)->autor=(p+i)->autor;
                (p+i+1)->paginas=(p+i)->paginas;
            }
            p=p+nro-1;
            p->id=nro;
            cout<<"\nLIBRO Nro. "<<p->id<<endl;
            fflush(stdin);
            cout<<"\nTitulo: ";
            getline(cin,p->titulo);
            fflush(stdin);
            cout<<"\nAutor: ";
            getline(cin,p->autor);
            fflush(stdin);
            cout<<"\nPaginas: ";
            cin>>p->paginas;
            fflush(stdin);
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
            getline(cin,p->titulo);
            fflush(stdin);
            cout<<"\nAutor: ";
            getline(cin,p->autor);
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

void cargaDeDatos(libro *p)
{
    FILE *archivo;
    libro cargaDeDatos;
    archivo=fopen("listaDeLibros","r");
    while(fread(&cargaDeDatos,sizeof(libro),1,archivo))
    {
        p->id=cargaDeDatos.id;
        p->titulo=cargaDeDatos.titulo;
        cout<<cargaDeDatos.titulo;
        p->autor=cargaDeDatos.autor;
        p->paginas=cargaDeDatos.paginas;
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
        guardarDatos.titulo=p->titulo;
        guardarDatos.autor=p->autor;
        guardarDatos.paginas=p->paginas;
        cout<<guardarDatos.autor;
        p++;
        fwrite(&guardarDatos,sizeof(libro),1,archivo);
    }
    fclose(archivo);
}
