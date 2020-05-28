#include <iostream>
#include <stdlib.h>
using namespace std;
typedef char TipoCaracter;
typedef string TipoStr;
typedef int TipoEntero;
const char caracter_principal='_';
void Limpiar_Pantalla(){
    cout<<"\e[2J\e[0;0H";
}
void Limpiar_Pantalla_Titulo(){
    cout<<"\e[2J\e[0;0H";
    cout<<"\t\t\t\t\t\tJuego Tic Tac Toe UTEC"<<endl<<endl;
}
void Finalizar_Juego(TipoCaracter **&Tablero, TipoEntero dimension, TipoStr **&Jugadores, TipoEntero dimension_jugadores){
    for(TipoEntero i=0; i<dimension; i++){
        delete [] Tablero[i];
    }
    delete [] Tablero;
    Tablero = nullptr;
    for(TipoEntero i=0; i<dimension_jugadores; i++){
        delete [] Jugadores[i];
    }
    delete [] Jugadores;
    Jugadores = nullptr;
}
void Limpiar_Tablero(TipoCaracter **&Tablero , TipoEntero dimension){
    for(TipoEntero i=0; i<dimension ;i++){
        for(TipoEntero j=0; j< dimension ; j++){
            Tablero[i][j] = caracter_principal;
        }
    }
}
bool Verificar_Si_Todo_esta_lleno(TipoCaracter **& Tablero, TipoEntero dimension, bool &seguir_jugando){
    bool esta_lleno = true;
    for(TipoEntero i=0; i<dimension ;i++){
        for(TipoEntero j=0; j< dimension ; j++){
            if(Tablero[i][j] == caracter_principal){
                esta_lleno = false;
            }
        }
    }

    if (esta_lleno){
        seguir_jugando = false;
        return true;
    }else{
        return false;
    }
}
void Imprimir_Tablero(TipoCaracter **&Tablero, TipoEntero dimension){
    cout<<endl;
    cout<<"\t\t\t\t\t\t\tTablero"<<endl<<endl;
    for(int z = 0 ; z<dimension ; z ++ ){
        if (z==0){
            cout<<"\t\t\t\t\t\t\ti"<<' '<<"\t";
        }else{
            cout<<' '<<"\t";
        }
    }
    cout<<endl;

    for(int z = 0 ; z<dimension ; z ++ ){
        if (z==0){
            cout<<"\t\t\t\t\t\t   j    "<<z<<"\t";
        }else{
            cout<<z<<"\t";
        }
    }
    cout<<endl;

    for(int i=0 ; i<dimension ; i++){
        for(int j=-2 ; j<dimension ; j++){
            if(j==-1){
                cout<<"\t\t\t\t\t\t"<<i<<"\t";
            }else{
                cout<<Tablero[i][j]<<"\t";
            }
        }
        cout<<endl;
    }
}
void Imprimir_Jugador_Ganador(TipoStr**&Jugadores, TipoEntero posicion_Jugador, TipoCaracter**&Tablero, TipoEntero dimension_tablero){
    Imprimir_Tablero(Tablero, dimension_tablero);
    cout<<"Gano el Jugador :"<<endl;
    cout<<"Nombre : "<<Jugadores[posicion_Jugador][0]<<endl;
    cout<<"Caracter : "<<Jugadores[posicion_Jugador][1]<<endl;
}
void Imprimir_Tablero_Sin_Ganador(TipoCaracter**&Tablero, TipoEntero dimension_tablero){
    Imprimir_Tablero(Tablero, dimension_tablero);
    cout<<endl<<endl<<"Ningun jugador Gano =( , puedes jugar de nuevo vamos "<<endl;
}
void Imprimir_Jugadores(TipoStr **&Jugadores, TipoEntero dimension){
    cout<<endl;
    for(int i=0 ; i<dimension ; i++){
        cout<<i+1<<". Nombre : ";
        cout<<Jugadores[i][0]<<"\t";
        cout<<endl;
        cout<<"  Caracter : "<<Jugadores[i][1]<<endl;
    }
    cout<<endl;
}
void Crear_Tablero(TipoCaracter **&Tablero, TipoEntero dimension){
    Tablero = new TipoCaracter*[dimension];
    for(TipoEntero i=0;i<dimension;i++){
        Tablero[i] = new TipoCaracter[dimension];
    }
    for(TipoEntero i=0 ; i<dimension ; i++){
        for(int j=0 ; j<dimension ; j++){
            Tablero[i][j]= caracter_principal;
        }
    }
}
void Crear_Jugadores(TipoStr **&Jugadores , TipoEntero dimension){
    Limpiar_Pantalla_Titulo();
    cout<<"\t\t\t\t\tCreacion de Personajes"<<endl<<endl;
    cout<<"Siga las Instrucciones : "<<endl<<endl;
    Jugadores = new TipoStr*[dimension];
    for(TipoEntero i=0;i<dimension;i++){
        Jugadores[i] = new TipoStr[2];
    }
    for(TipoEntero i=0 ; i<dimension ; i++){
        cout<<"Ingrese el nombre del Jugador "<<i+1<<" : ";
        cin>>Jugadores[i][0];
        do{
            cout<<"Ingrese el caracter para "<<Jugadores[i][0]<<" : ";
            TipoCaracter caracter_jugador;
            cin>>caracter_jugador;
            bool caracter_utilizado = false;
            for(TipoEntero j=0 ; j<dimension ;j++){
                if(Jugadores[j][1][0] == caracter_jugador){
                    caracter_utilizado = true;
                }
            }
            if(caracter_utilizado){cout<<"El caracter ya esta siendo utilizado."<<endl;}else{Jugadores[i][1]=caracter_jugador; break;}
        }while(true);
        cout<<endl;
    }
}
bool Verificar_Tablero(TipoCaracter **&Tablero, TipoEntero dimension_tablero,TipoStr**&Jugadores, TipoEntero posicion_jugador, bool &SeguimosJugando){
    bool ganador = true;
    for(TipoEntero i=0 ; i<dimension_tablero ;i ++){
        if(Tablero[i][i] != Jugadores[posicion_jugador][1][0]){
            ganador = false;
            break;
        }
    }
    if(ganador){Imprimir_Jugador_Ganador(Jugadores, posicion_jugador, Tablero, dimension_tablero);SeguimosJugando = false;return true;}else{ganador = true;}

    for(TipoEntero i=0 ; i<dimension_tablero ;i ++){
        for(TipoEntero j=0 ; j<dimension_tablero ;j++){
            if(i+j == dimension_tablero-1){
                if(Tablero[i][j] != Jugadores[posicion_jugador][1][0]){
                    ganador = false;
                    break;
                }
            }
        }
    }

    if(ganador){Imprimir_Jugador_Ganador(Jugadores, posicion_jugador, Tablero, dimension_tablero);SeguimosJugando=false;return true;}else{ganador = true;}


    for(TipoEntero i=0 ; i<dimension_tablero ; i++){
        for(TipoEntero j=0;j<dimension_tablero;j++){
            if(Tablero[i][j] != Jugadores[posicion_jugador][1][0]){
                ganador = false;
            }
            if(j == dimension_tablero -1 ){
                if(ganador){
                    Imprimir_Jugador_Ganador(Jugadores, posicion_jugador, Tablero, dimension_tablero);
                    SeguimosJugando = false;
                    return true;
                }else{
                    ganador = true;

                }
            }
        }
    }

    for(TipoEntero j=0 ; j<dimension_tablero ; j++){
        for(TipoEntero i=0 ; i<dimension_tablero;i++){
            if(Tablero[i][j] != Jugadores[posicion_jugador][1][0]){
                ganador = false;
            }
            if(i == dimension_tablero - 1){
                if(ganador){
                    Imprimir_Jugador_Ganador(Jugadores, posicion_jugador, Tablero, dimension_tablero);
                    SeguimosJugando = false;
                    return true;
                }else{
                    ganador = false;
                }
            }
        }
    }
    return ganador;

}

void Empezar_Juego(TipoCaracter **&Tabla,TipoEntero dimension_tabla, TipoStr **&Jugadores, TipoEntero dimension_Jugadores);

void Juegar_Juego(){
    TipoCaracter **Tablero = nullptr;
    TipoStr **Jugadores = nullptr;
    TipoEntero dimension;
    cout << "\t\t\t\t\t\tBienvenido al juego TIC TAC TOE" << endl<<endl;
    do{
        cout << "Ingrese la dimension del tablero (N): ";
        TipoEntero dimension_1;
        cin >> dimension_1;
        if(dimension_1 >= 1){
            dimension = dimension_1;
            break;
        }else{
            cout<<endl<<"Ingrese una dimension positiva y mayor que 0"<<endl<<endl;
        }
    }while(true);
    Limpiar_Pantalla();
    Crear_Tablero(Tablero, dimension);
    Crear_Jugadores(Jugadores, 2);
    Limpiar_Pantalla_Titulo();
    Imprimir_Tablero(Tablero, dimension);
    Imprimir_Jugadores(Jugadores, 2);
    cout<<endl<<endl<<"\t\t\t\t\t\tCargando Juego....."<<endl;
    TipoEntero contador_n = 0;
    do{
        if(contador_n == 999990000){break;}
        contador_n+=1;
    }while(true);
    Limpiar_Pantalla_Titulo();
    Empezar_Juego(Tablero, dimension, Jugadores, 2);
    TipoEntero eleccion_final;
    do{
        TipoEntero eleccion;
        cout<<endl;
        cout<<"1. Seguir Jugando ( Limpiar Tablero ) "<<endl;
        cout<<"2. Ir al Menu"<<endl;
        cin>>eleccion;
        if(eleccion >=1 && eleccion <=2){
            eleccion_final = eleccion;
            if(eleccion == 1){
                Limpiar_Tablero(Tablero, dimension);
                Limpiar_Pantalla_Titulo();
                Empezar_Juego(Tablero, dimension, Jugadores, 2);
            }else{
                Finalizar_Juego(Tablero, dimension, Jugadores, 2);
                Limpiar_Pantalla();
                break;
            }
        }
    }while(true);
}
void Menu(){
    do {
        TipoEntero eleccion;
        do{
            cout<<endl<<endl;
            cout << "\t\t\t\t\t\tBienvenidos a TIC TAC TOE" <<endl<<endl;
            cout << "\t\t\t\t\t\t\t\t   Menu" << endl;
            cout << "1. Jugar" << endl;
            cout << "2. Salir del Juego" << endl<<endl;
            cout<<"Elija una opcion : ";
            cin>>eleccion;
            if(eleccion>=1 &&eleccion<=2){
                break;
            }else{
                Limpiar_Pantalla();
            }
        }while(true);
        Limpiar_Pantalla();
        if(eleccion == 1 ){
            Juegar_Juego();
        }else{
            cout<<endl<<endl<<"t\t\t\t\t\t\t\tMuchas Gracias";
            break;
        }
    }while (true);
}
int main() {
    Menu();
    return 0;
}

void Empezar_Juego(TipoCaracter **&Tabla,TipoEntero dimension_tabla, TipoStr **&Jugadores, TipoEntero dimension_Jugadores){
    cout<<endl;
    bool sigue_jugando = true;
    do{
        for(TipoEntero i=0 ; i<dimension_Jugadores;i++){
            Imprimir_Tablero(Tabla, dimension_tabla);cout<<endl;
            cout<<"Turno de "<<Jugadores[i][0]<<" :"<<endl;
            do {
                TipoEntero posicion_en_i=0, posicion_en_j=0;
                cout << "Ingrese las coordenadas de su posicion : "<<endl;
                cout << "Coordenada en el eje i : ";
                cin >> posicion_en_i;
                cout << "Coordenada en el eje j : ";
                cin >> posicion_en_j;
                if(posicion_en_i >= dimension_tabla || posicion_en_j >= dimension_tabla){
                    cout<<endl<<"Posicion no admitida";
                }else if (Tabla[posicion_en_i][posicion_en_j] == caracter_principal) {
                    Tabla[posicion_en_i][posicion_en_j] = Jugadores[i][1][0];
                    break;
                }else{
                    cout<<endl<<"La posicion ya esta ocupada ";
                }
            }while (true);
            Limpiar_Pantalla_Titulo();
            if(Verificar_Si_Todo_esta_lleno(Tabla, dimension_tabla, sigue_jugando)){
                Imprimir_Tablero_Sin_Ganador(Tabla, dimension_tabla);
                break;
            }else if(Verificar_Tablero(Tabla, dimension_tabla, Jugadores, i, sigue_jugando)){
                break;
            }
        }
    }while(sigue_jugando);
}
