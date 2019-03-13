#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#define MAXL 23
#define MAXC 77

using namespace std;

struct punct {
    int l;
    int c;
};

punct S[MAXL*MAXC];
int L, C, dS, lh, ch, d, viteza;
char a[MAXL+2][MAXC+2];
int dl[] = {0,1,0,-1};
int dc[] = {1,0,-1,0};

int peSarpe();
void puneHrana();
void init();
void afisare();
void mutaSarpe();
void asteapta(int sutimi);
int atinge();

/// deplasarea se face de pe tastele WASD

int main () {
    init();
    afisare();
    for (;;) {
        /// uita-te la tastatura
        /// daca s-a apasat vreo tasta, schimba directia
        /// calculeaza noua pozitie a sarpelui
        if ( kbhit() ) {
            char c = getch();
            cout<<c;
            switch(c) {
            case 'a':
                d = 2;
                break;
            case 'w':
                d = 3;
                break;
            case 's':
                d = 1;
                break;
            case 'd':
                d = 0;
                break;
            }
        }

        /// actualizam pozitia sarpelui
        mutaSarpe();
        afisare();

        /// conditie de pierdere a jocului
        if (atinge()) {
            break;
        }

        asteapta(viteza);
        /// afiseaza sarpele
        /// asteapta un numar de milisecunde
    }
    return 0;
}

int atinge() {
    /// daca sarpele se loveste de o margine sau de el insusi returnam 1
    if (S[1].l == 0 || S[1].l == L+1 || S[1].c == 0 || S[1].c == C+1){
        return 1;
    }
    for (int i=2;i<=dS;i++){
        if (S[1].l == S[i].l && S[1].c == S[i].c){
            return 1;
        }
    }

    return 0;
}

void asteapta(int sutimi) {
    /// viteza jocului
    int ti = clock();
    while (clock() - ti < sutimi);
}

void mutaSarpe() {
    /// daca suntem pe hrana, marim lungimea sarpelui
    if (S[1].l == lh && S[1].c == ch) {
        dS++;
        puneHrana();
        viteza-=2;
    }

    for (int i=dS;i>1;i--){
        S[i] = S[i-1];
    }

    S[1].l += dl[d];
    S[1].c += dc[d];
}

int peSarpe() {
    for (int i=1;i<=dS;i++)
        if (lh == S[i].l && ch == S[i].c)
            return 1;
    return 0;
}

void puneHrana() {
    /// generam la intamplare coordonatele hranei
    do {
        lh = rand() % L + 1;
        ch = rand() % C + 1;
    }
    /// verificam sa nu pozitionam hrana undeva unde se afla sarpele
    while (peSarpe() == 1);
}

void init() {
    /// functie ce initializeaza valorile utilizate ulterior
    L = 12;
    C = 20;
    d = 0;
    S[1].l = 2;S[1].c = 5;
    S[2].l = 2;S[2].c = 4;
    S[3].l = 2;S[3].c = 3;
    S[4].l = 2;S[4].c = 2;
    dS = 4;
    viteza = 300;
    srand(time(0));
    puneHrana();
}

void afisare() {
    /// 0 zona libera
    /// 1 corp sarpe
    /// 2 cap sarpe
    /// 3 hrana

    /// zonele libere
    int i, j;
    for (i=1;i<=L;i++){
        for (j=1;j<=C; j++){
            a[i][j] = ' ';
        }
    }

    /// desenam sarpele
    for (int i=2;i<=dS;i++) {
        a[ S[i].l ][ S[i].c ] = '#';
    }
    a[ S[1].l ][ S[1].c ] = '*';

    /// conturam chenarul jocului
    for (j=1;j<=C;j++) {
        a[0][j] = 205;
        a[L+1][j] = 205;
    }
    for (i=1;i<=L;i++){
        a[i][0] = a[i][C+1] = 186;
    }
    a[0][0] = 201;
    a[0][C+1] = 187;
    a[L+1][0] = 200;
    a[L+1][C+1] = 188;

    /// plasam hrana
    a[lh][ch] = 'H';

    /// stergem ecranul
    system("cls");

    for (i=0;i<=L+1;i++) {
        for (j=0;j<=C+1;j++){
            cout<<a[i][j];
        }
        cout<<"\n";
    }
}

