#include <stdio.h>
#include <stdlib.h>

#define GROESSE_MATRIX 6

// Koordinate in der Matrix
struct structKoordinate{
    int x;
    int y;
};

typedef struct structKoordinate Koordinate;

Koordinate S, Z = {0,0};


void eingabeS();
void eingabeZ();
void matrixAusgeben();
void findeLeereNachbarn(Koordinate k);
void printListe();
void matrixfuellen();

char matrix[GROESSE_MATRIX][GROESSE_MATRIX];
//hardcoded, 2do
//char matrix[GROESSE_MATRIX][GROESSE_MATRIX] = {
//    {'0','0','0','0','0','0'},
//    {'0','0','0','0','0','0'},
//    {'0','0','0','0','0','0'},
//    {'0','0','0','0','0','0'},
//    {'0','0','0','0','0','0'},
//    {'0','0','0','0','0','0'}
//};

int index = 0;
int runde = 1;
int zielgefunden = 0; //Abbruchbedingung Ziel gefunden

/**
    Array, das gefundene freie Felder aufnimmt.
    Wenn die Felder dort eingetragen wurden, bekommen sie
    den Wert des Durchlaufs zugeornet.
*/
Koordinate ListeFelderGefunden[(GROESSE_MATRIX*GROESSE_MATRIX)*4]; //Dynamisch bspw. 6*6*4=144 ecken ausser acht gelassen

int main()
{
    matrixfuellen();
    // Hilfsindizes fuer ListeFelderGefunden, die fuer
    // jede Runde die jeweilige Anzahl der Berechnungsschritte bestimmen
    int h;
    int hindex;
    int merkeIndex = index;

    // Eingabe des Start- und Zielpunkts
    eingabeS();
    eingabeZ();

    // Ausgabe der Matrix mit Start und Ziel-Eintrag
    matrixAusgeben();

    // Erste Eingabe von gefundenem Startfeld
    ListeFelderGefunden[0] = S;

    if(!zielgefunden) // Schliesst hier den Fall aus, dass Start und Ziel identisch sind
    {
        findeLeereNachbarn(ListeFelderGefunden[index]);
    }

    printf("\nAusgabe nach erster Welle von der Liste der gefundenen Koordinaten");
    printf("\nund der Matrix.");

    printListe();
    matrixAusgeben();

    while(!zielgefunden)
    {
        //runde startet hier bei 2, erste Runde ist vor der Schleife
        runde++;
        hindex = index;
        for (h = merkeIndex + 1; h < hindex - merkeIndex + 1; h++)
        {
            findeLeereNachbarn(ListeFelderGefunden[h]);
            //matrixAusgeben();
        }
    }

    printf("\nEs folgen die endgueltige Liste der Koordinaten, die gefunden wurden,");
    printf("\nund die mit den Wellenwerten gefuellte Matrix.");

    printListe();
    matrixAusgeben();

    return 0;
}

/**
*   Startpunkt setzen
*/
void eingabeS()
{
    while(1)
    {
        int eingabe;

        printf("\nGeben Sie Y von S ein (zwischen 0 und %d):\n",GROESSE_MATRIX-1);
        scanf("%d", &eingabe);

        if ((eingabe < 0) || (eingabe >= GROESSE_MATRIX))
        {
            printf("\nFehler in der Eingabe von S\n");
            continue;
        }
        else
        {
            S.y = eingabe;
        }

        printf("\nGeben Sie X von S ein (zwischen 0 und %d):\n",GROESSE_MATRIX-1);
        scanf("%d", &eingabe);

        if ((eingabe < 0) || (eingabe >= GROESSE_MATRIX))
        {
            printf("\nFehler in der Eingabe von S\n");
            continue;
        }
        else
        {
            S.x = eingabe;
        }

        matrix[S.y][S.x]= 'S';

        break;
    } // Ende der While-Schleife
}

/**
*   Zielpunkt setzen
*/
void eingabeZ()
{
    while(1)
    {
        int eingabe;

        printf("\nGeben Sie Y von Z ein (zwischen 0 und %d):\n",GROESSE_MATRIX-1);
        scanf("%d", &eingabe);

        if ((eingabe < 0) || (eingabe >= GROESSE_MATRIX ))
        {
            printf("\nFehler in der Eingabe von Z\n");
            continue;
        }
        else
        {
            Z.y = eingabe;
        }

        printf("\nGeben Sie X von Z ein (zwischen 0 und %d):\n",GROESSE_MATRIX-1);
        scanf("%d", &eingabe);

        if ((eingabe < 0) || (eingabe >= GROESSE_MATRIX))
        {
            printf("\nFehler in der Eingabe von Z\n");
            continue;
        }
        else
        {
            Z.x = eingabe;
        }

        // Pruefe, ob das die Koordinaten von S sind.
        // Setze Z nur, wenn das Feld leer ist.
        if (matrix[Z.y][Z.x] == '0')
        {
            matrix[Z.y][Z.x] = 'Z';
        }
        // Wenn nicht Null, dann muss es S sein
        else
        {
            printf("\nStart und Zielwert sind identisch.\n");
            zielgefunden = 1;
        }
        break;
    } // Ende der While-Schleife
}

/**
    Matrix auf der Konsole ausgeben
*/
void matrixAusgeben()
{
    int i;
    int j;
    printf("\nAusgabe Matrix:\n");
    for(i = 0; i < GROESSE_MATRIX; i++)
    {
        for(j = 0; j < GROESSE_MATRIX; j++)
        {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

/**
    Funktion: findeLeereNachbarn
    Bestimmt fuer eine Koordinate k die Nachbarn, die den Wert 0
    enthalten und schreibt sie in das Array ListeFelderGefunden.
    Dazu wird die Indexvariable index verwendet, die den aktuellen
    Stand der Anzahl der gefundenen/besuchten Felder angibt.
*/
void findeLeereNachbarn(Koordinate k)
{
    Koordinate N = {0,0};

    // finde rechten Nachbarn, falls nicht an Martixgrenze
    if (k.x < GROESSE_MATRIX - 1)
    {
        // und Nachbarfeld noch Null ist
        if (matrix[k.y][k.x+1] == '0')
        {
            N.y = k.y;
            N.x = k.x+1;
            index++;
            ListeFelderGefunden[index] = N;
            matrix[k.y][k.x+1] = (char)runde+48;
        }
        if (matrix[k.y][k.x+1] == 'Z')
        {
            zielgefunden = 1;
            printf("\nZiel gefunden!");
        }
    }

    // finde linken Nachbarn, falls nicht an Matrixgrenze
    if (k.x > 0)
    {
        // und Nachbarfeld noch Null ist
        if (matrix[k.y][k.x-1] == '0')
        {
            N.y = k.y;
            N.x = k.x-1;
            index++;
            ListeFelderGefunden[index] = N;
            matrix[k.y][k.x-1] = (char)runde+48;
        }
        if (matrix[k.y][k.x-1] == 'Z')
        {
            zielgefunden = 1;
            printf("\nZiel gefunden!");
        }
    }

    // finde unteren Nachbarn, falls nicht an Martixgrenze
    if (k.y < GROESSE_MATRIX - 1)
    {
        // und Nachbarfeld noch Null ist
        if (matrix[k.y+1][k.x] == '0')
        {
            N.y = k.y+1;
            N.x = k.x;
            index++;
            ListeFelderGefunden[index] = N;
            matrix[k.y+1][k.x] = (char)runde+48;
        }
        if (matrix[k.y+1][k.x] == 'Z')
        {
            zielgefunden = 1;
            printf("\nZiel gefunden!");
        }
    }

    // finde oberen Nachbarn, falls nicht an Matrixgrenze
    if (k.y > 0)
    {
        // und Nachbarfeld noch Null ist
        if (matrix[k.y-1][k.x] == '0')
        {
            N.y = k.y-1;
            N.x = k.x;
            index++;
            ListeFelderGefunden[index] = N;
            matrix[k.y-1][k.x] = (char)runde+48;
        }
        if (matrix[k.y-1][k.x] == 'Z')
        {
            zielgefunden = 1;
            printf("\nZiel gefunden!");
        }
    }
}

/**
    Hilfs-Funktion printListe
    wird benutzt, um den aktuellen Stand des Arrays ListeFelderGefunden
    auszugeben.
*/
void printListe()
{
    int j;
    printf("\nDas ist die Liste der bisher gefundenen Felder: \n");
    for (j = 0; j < index + 1; j++)
    {
        printf("(%d, %d)\n", ListeFelderGefunden[j].y,
                             ListeFelderGefunden[j].x);
    }
}

void matrixfuellen(void)
{
    int i;
    int j;
    for (i=0;i<GROESSE_MATRIX;i++){
            for (j=0;j<GROESSE_MATRIX;j++){
                matrix[i][j] = '0';
        }
    }
}
