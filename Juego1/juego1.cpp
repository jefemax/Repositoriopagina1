#include <stdio.h>
#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>
#include <conio.h>
#include <time.h>

#define ANCHO_MUNDO 79
#define DERECHA 1
#define IZQUIERDA 0
//variables personaje
int g_posxPersonaje = 50;
char g_personaje_actual = '>';
char g_piso_C = '_';
char g_personaje_d = '>';
char g_personaje_i = '<';

//variables bala
int g_posxBala = 2;
int g_velBala = 2;
bool g_direccion_bala = DERECHA;
bool g_balaActiva = false;
char g_personaje_bala = 'o';

//variables enemigos
int g_posxEnem = 0;
int g_velEnem = 2;
bool g_enemActivo = false;
//al inicio se cambia la direccion por eso empiezo a la izquierda
bool g_direccion_enemigo = IZQUIERDA;
char g_personajeEnem = '|';

//variables generales
bool g_direccion = DERECHA;
bool g_mover = false;
unsigned int random = 0;
bool randomSetted = false;
int counTToShowEnem;

//Funciones
void ocultaEnemigos();

char g_key = ' ';
char *g_piso;

bool run();
bool draw();

bool getInput(char *c)
{
    if (_kbhit())
    {
        *c = _getch();
        return true;
    }
    return false;
}

int main(int argc, char* argv[])
{

    printf("\n\n\n\n\n\n\n\n\n\n\n");

    g_piso = (char*)malloc(sizeof(char) * ANCHO_MUNDO);
    g_piso[ANCHO_MUNDO] = '\0';
    for (int x = 0; x < ANCHO_MUNDO; x++){
        g_piso[x] = '_';
    }


    //printf(">");
    g_posxBala = 1;
	for (g_posxBala = 2; g_posxPersonaje < ANCHO_MUNDO - 1 && g_posxPersonaje>0;)
    {
        if (run())
            break;
        draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    /*    g_piso[ANCHO_MUNDO] = '\0';
        for (int g_posx = 0; g_posx < ANCHO_MUNDO; g_posx++){
            g_piso[g_posx] = '_';
        }*/
             //getInput(&key)
    }
    return 0;
}
bool run(){

	if (getInput(&g_key))
	{
		if (g_key == 's')
		{
			g_direccion = DERECHA;
			g_personaje_actual = g_personaje_d;
			g_posxPersonaje++;
		}
		if (g_key == 'a')
		{
			g_direccion = IZQUIERDA;
			g_personaje_actual = g_personaje_i;
			g_posxPersonaje--;
		}
		if (g_key == 'f')
		{
			if (g_direccion == IZQUIERDA){
				g_direccion_bala = IZQUIERDA;
			} 	else if (g_direccion == DERECHA){
				g_direccion_bala = DERECHA;
			}
			g_balaActiva = true;
			g_posxBala = g_posxPersonaje;

		}
	}
	if (g_balaActiva)
	{
		if (g_direccion_bala == DERECHA)
			g_posxBala += g_velBala;
		else if (g_direccion_bala == IZQUIERDA)
			g_posxBala -= g_velBala;
		if (g_posxBala > ANCHO_MUNDO || g_posxBala < 0)
			g_balaActiva = false;
	}


	if (!g_enemActivo && !randomSetted)
	{
		srand(time(NULL));
		random = rand() % 100;
		randomSetted = true;
	}

	if (randomSetted)
	{
		if (counTToShowEnem == random)
		{
            g_direccion_enemigo = !g_direccion_enemigo;

            if (g_direccion_enemigo == DERECHA)
                g_posxEnem = ANCHO_MUNDO;
            else
                g_posxEnem = 0;

			g_enemActivo = true;

		}
		counTToShowEnem++;
	}
	if (g_enemActivo)
	{
        if (g_posxEnem > ANCHO_MUNDO || g_posxEnem < 0)
        {
            ocultaEnemigos();
        }
        if (g_direccion_enemigo == DERECHA){
            g_posxEnem -= g_velEnem;
            if (g_posxEnem <= g_posxBala && g_balaActiva)
            {
                ocultaEnemigos();

                g_posxBala = 0;
                g_balaActiva = false;
            }

            if (g_posxEnem <= g_posxPersonaje)
            {
                ocultaEnemigos();

            }
        }
        else {
            g_posxEnem += g_velEnem;

            if (g_posxEnem >= g_posxBala && g_balaActiva)
            {
                ocultaEnemigos();

                g_posxBala = 0;
                g_balaActiva = false;
            }

            if (g_posxEnem >= g_posxPersonaje)
            {
                ocultaEnemigos();

            }
        }

	}

    return false;
}

void ocultaEnemigos()
{
    g_posxEnem = 0;
    g_enemActivo = false;
    randomSetted = false;
    random = 0;
    counTToShowEnem = 0;

    g_posxBala = 0;
    g_balaActiva = false;

}

bool draw()
{
	for (int x = 0; x < ANCHO_MUNDO; x++){
		g_piso[x] = '_';
	}
    for (int x = 0; x < ANCHO_MUNDO; x++){
		if (x == g_posxPersonaje)
            g_piso[x] = g_personaje_actual;
		if (g_balaActiva) {
			if (x == g_posxBala)
					g_piso[x] = g_personaje_bala;
		}
		if (g_enemActivo) {
			if (x == g_posxEnem)
				g_piso[x] = g_personajeEnem;
			}
    }
	printf("%s", g_piso);
	//printf("%d%d%s", g_posxBala, g_posxEnem, g_piso);
    printf("\r"); 

    return false;
}




