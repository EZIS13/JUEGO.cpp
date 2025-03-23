#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

void pantalla_lim() { cout << "\033[2J\033[H"; }
void gotoxy(int x, int y) { cout << "\033[" << y + 1 << ";" << x + 1 << "H"; }
void esperar(int ms) {
    for (clock_t t = clock(); (clock() - t) * 1000 / CLOCKS_PER_SEC < ms;)
        ;
}

const int filas = 20;
const int columnas = 40;

void inicializar_matriz(bool matriz[filas][columnas]) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = false;
        }
    }
}
void imprimir_matriz(bool matriz[filas][columnas]) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            gotoxy(j, i);
            if (matriz[i][j]) {
                cout << "#";
            }
            else {
                cout << " ";
            }
        }
    }
    cout << flush;
}

/**
 *Cuenta los vecinos vivos de una celda en el tablero.
 */
int Con_Vecinos(bool matrizActual[filas][columnas], int i, int j) {
    /// Almacena la cantidad de vecinos q hay alrededor
    int contador = 0;

    /// TOROIDAL
    const int arriba = (i + (-1) + filas) % filas;
    const int abajo = (i + +1) % filas;
    const int izquierda = (j + (-1) + columnas) % columnas;
    const int derecha = (j + +1) % columnas;

    // Contar
    contador += matrizActual[arriba][izquierda];
    contador += matrizActual[arriba][j];
    contador += matrizActual[arriba][derecha];

    contador += matrizActual[i][izquierda];
    contador += matrizActual[i][derecha];

    contador += matrizActual[abajo][izquierda];
    contador += matrizActual[abajo][j];
    contador += matrizActual[abajo][derecha];

    return contador;
}
bool reglas(bool celulaActual, int vecinosVivos) {
    if (celulaActual && vecinosVivos > 3) {
        return false;
    }
    if (celulaActual && vecinosVivos < 2) {
        return false;
    }
    if (!celulaActual && vecinosVivos == 3) {
        return true;
    }

    return celulaActual;
}
void GeneracionesNue(bool matrizActual[filas][columnas],
    bool matrizSiguiente[filas][columnas]) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            /// cuenta los vecinos que hay alrededor
            int vecinosContados = Con_Vecinos(matrizActual, i, j);
            matrizSiguiente[i][j] =
                reglas(matrizActual[i][j], vecinosContados);
        }
    }
}
void copiar_matriz(bool matrizActual[filas][columnas],
    bool matrizSiguiente[filas][columnas]) {

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matrizActual[i][j] = matrizSiguiente[i][j];
        }
    }
}
int main() {
    srand(time(nullptr));
    bool matrizActual[filas][columnas];
    bool matrizSiguiente[filas][columnas];

    inicializar_matriz(matrizActual);

    matrizActual[0][0] = false;
    matrizActual[0][1] = true;
    matrizActual[0][2] = true;

    matrizActual[1][0] = true;
    matrizActual[1][1] = true;
    matrizActual[1][2] = false;

    matrizActual[2][0] = false;
    matrizActual[2][1] = true;
    matrizActual[2][2] = false;

    pantalla_lim();

    while (true) {
        imprimir_matriz(matrizActual);
        GeneracionesNue(matrizActual, matrizSiguiente);
        copiar_matriz(matrizActual, matrizSiguiente);
        esperar(1000);
    }

    return 0;
}