#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define lenght 30

#define ifInull if (i == 0)
#define ifJnull if (j == 0)
#define ifInine if ( i == 29)
#define ifJnine if (j == 29)



typedef struct State {
    int isBomb;
    int isFlag;
    int isSafe;
    int isDiscover;
    int zeroPosX;
    int zeroPosY;
} State;

struct Game {
    char game[lenght][lenght];
    char hide[lenght][lenght];
};

void showBoard(char board[lenght][lenght]);
void randPos(int pRow, int pCol, int* randRow, int* randCol);
void placeBomb(char bomb[lenght][lenght], State state[lenght][lenght]);
int aroundCheck(char board[lenght][lenght], int i, int j, char charCheck);
int aroundBomb(char board[lenght][lenght], int i, int j);
void wherePlay(int* rowInput, int* colInput);
void aroundDiscover(int i, int j, State[lenght][lenght], char game[lenght][lenght],char hide[lenght][lenght]);
void autoDiscover(char game[lenght][lenght], char hide[lenght][lenght], State state[lenght][lenght]);
int boxDiscover(int rowInput, int colInput, char game[lenght][lenght],char hide[lenght][lenght], State state[lenght][lenght]);
int playing(char game[lenght][lenght], char hide[lenght][lenght], State state[lenght][lenght], int* beginReveal);
void setCase(int posRow, int posCol, struct State state[lenght][lenght], char game[lenght][lenght], char hide[lenght][lenght]);
void appendFunc(struct State state[lenght][lenght], int posRow, int posCol);
void firstDiscover(int posI, int posJ, char game[lenght][lenght], char hide[lenght][lenght], State state[lenght][lenght], int* beginReveal);
int playing(char game[lenght][lenght], char hide[lenght][lenght], State state[lenght][lenght], int* beginReveal);
void placeFlag(State state[lenght][lenght], char game[lenght][lenght]);
void revealAtBomb(char game[lenght][lenght], char hide[lenght][lenght]);



void showBoard(char board[lenght][lenght]) {
    printf("%s","    ");
    int i = 0;
    int j = 0;
    for (int k = 0; k < lenght; k++) {
        if (k >= 10 && k < 20) {
            printf("|%d|",k-10);
        }
        else if (k >= 20) {
            printf("|%d|", k - 20);
        }
        else {
            printf("|%d|", k);
        } 
    }
    printf("\n\n");
    for (i = 0; i < lenght; i++) {
        if (i >= 10 && i < 20) {
            printf("|%d| ", i - 10);
        }
        else if (i >= 20) {
            printf("|%d| ", i - 20);
        }
        else {
            printf("|%d| ", i);
        }



        for (j = 0; j < lenght; j++) {
            if (board[i][j] == '0') {
                printf("\033[0;15m");
                printf("|%c|", ' ');
            }
            else if (board[i][j] == 'o') {
                printf("\033[0;35m");
                printf("|%c|", 'o');
            }
            else if (board[i][j] == '1') {
                printf("\033[0;32m");
                printf("|%c|", '1');
            }
            else if (board[i][j] == '2') {
                printf("\033[0;33m");
                printf("|%c|", '2');
            }
            else if (board[i][j] == '3') {
                printf("\033[0;31m");
                printf("|%c|", '3');
            }
            else if (board[i][j] == '4') {
                printf("\033[0;31m");
                printf("|%c|", '4');
            }
            else if (board[i][j] == '?') {
                printf("\033[0;15m");
                printf("|%c|", '?');
            }
            else {
                printf("\033[0;34m");
                printf("|%c|", board[i][j]);
            }
        }
        printf("\n");
    }
}

void randPos(int pRow, int pCol, int* randRow, int* randCol) {
    *randRow = rand() % pRow;
    *randCol = rand() % pCol;
}

void placeBomb(char bomb[lenght][lenght], State state[lenght][lenght]) {
    int pRow = lenght;
    int pCol = lenght;
    int randRow = 0;
    int randCol = 0;
    randPos(pRow, pCol, &randRow, &randCol);
    if (bomb[randRow][randCol] == 'o' || state[randRow][randCol].isSafe) {
        randPos(pRow, pCol, &randRow, &randCol);
    }
    else {
        state[randRow][randCol].isBomb = 1;
        bomb[randRow][randCol] = 'o';
    }
}

int aroundCheck(char board[lenght][lenght], int i, int j, char charCheck) {
    int nbrChar = 0;
    if (board[i - 1][j - 1] == charCheck) {
        nbrChar += 1;
    }
    if (board[i + 1][j + 1] == charCheck) {
        nbrChar += 1;
    }
    if (board[i - 1][j + 1] == charCheck) {
        nbrChar += 1;
    }
    if (board[i + 1][j - 1] == charCheck) {
        nbrChar += 1;
    }
    if (board[i + 1][j] == charCheck) {
        nbrChar += 1;
    }
    if (board[i - 1][j] == charCheck) {
        nbrChar += 1;
    }
    if (board[i][j + 1] == charCheck) {
        nbrChar += 1;
    }
    if (board[i][j - 1] == charCheck) {
        nbrChar += 1;
    }
    return nbrChar;
}

int aroundBomb(char board[lenght][lenght], int i, int j) {
    int nbrBomb = 0;
    char charCheck = 'o';
    if (board[i][j] != 'o') {
        nbrBomb = aroundCheck(board, i, j, charCheck);
        char charNbrBomb = nbrBomb + '0';
        return charNbrBomb;
    }
    return 'a';
}


int main() {



    struct Game structGame;
    struct State state[lenght][lenght];
    int i = 0;
    int j = 0;


    srand(time(NULL));


    for (i = 0; i < lenght; i++) {
        for (j = 0; j < lenght; j++) {
            state[i][j].isBomb = 0;
            state[i][j].isFlag = 0;
            state[i][j].isDiscover = 0;
            state[i][j].isSafe = 0;
            structGame.game[i][j] = '?';
            structGame.hide[i][j] = '0';
        }
    }

    int gameOver = 0;
    int beginReveal = 0;
    do {
        gameOver = playing(structGame.game, structGame.hide, state, &beginReveal);
        beginReveal = 1;
    } while (gameOver == 0);
    return 0;
}

void wherePlay(int* rowInput, int* colInput) {
    int error = 0;
    do {
        printf("Sur quel ligne voulez-vous jouer ?\n");
        error = scanf_s("%d", rowInput);
        if (error != 0 && *rowInput < lenght) {
            printf("%s %d\n", "Vous avez choisi de jouer a la ligne", *rowInput);
        }
        char c = getchar();
        while (c != '\n') {
            c = getchar();
        };
    } while (error == 0 || *rowInput > lenght);
    error = 0;
    do {
        printf("Sur quel colonne voulez-vous jouer ?\n");
        error = scanf_s("%d", colInput);
        if (error != 0 && *colInput < lenght) {
            printf("%s %d\n", "Vous avez choisi de jouer a la colonne", *colInput);
        }
        char c = getchar();
        while (c != '\n') {
            c = getchar();
        };
    } while (error == 0 || *colInput > lenght);


}

void appendFunc(struct State state[lenght][lenght], int posRow, int posCol) {
    for (int i = 0; i < lenght; i++) {
        for (int j = 0; j < lenght; j++) {
            if (state[i][j].zeroPosX == 10000) {
                state[i][j].zeroPosX = posRow;
                state[i][j].zeroPosY = posCol;
                return;
            }
        }
    }
}

void setCase(int posRow, int posCol, struct State state[lenght][lenght], char game[lenght][lenght], char hide[lenght][lenght]) {
    if (state[posRow][posCol].isBomb != 1 && state[posRow][posCol].isDiscover != 1) {
        if (hide[posRow][posCol] == '0') {
            appendFunc(state, posRow, posCol);
        }
        state[posRow][posCol].isDiscover = 1;
        game[posRow][posCol] = hide[posRow][posCol];
    }
}

void aroundDiscover(int i, int j, struct State state[lenght][lenght], char game[lenght][lenght],char hide[lenght][lenght]) {

  int ij = 0;
  int posRow = 0;
  int posCol = 0;

  ifInull {
    posRow = i;
  }
  else {
    posRow = i - 1;
  }
  ifJnull {
    posCol = j;
  }
  else {
    posCol = j - 1;
  }
  setCase(posRow, posCol,state, game,hide);

  ifInine {
    posRow = i;
  }
  else {
    posRow = i + 1;
  }
  ifJnine {
    posCol = j;
  }
  else {
    posCol = j + 1;
  }
  setCase(posRow, posCol,state, game,hide);

  ifInull {
    posRow = i;
  }
  else {
    posRow = i - 1;
  }
  ifJnine {
    posCol = j;
  }
  else {
    posCol = j + 1;
  }
  ij = (posRow)*10+(posCol);

  setCase(posRow, posCol,state, game,hide);

  ifInine {
    printf("%s\n","i 9");
    posRow = i;
  }
  else {
    posRow = i + 1;
  }
  ifJnull {
    posCol = j;
  }
  else {
    posCol = j - 1;
  }
  ij = (posRow)*10+(posCol);
  setCase(posRow, posCol,state, game,hide);

  posRow = i;
  ifJnull {
    posCol = j;
  }
  else {
    posCol = j - 1;
  }
  setCase(posRow, posCol,state, game,hide);

  posRow = i;
  ifJnine {
    posCol = j;
  }
  else {
    posCol = j + 1;
  }
  setCase(posRow, posCol,state, game,hide);

  
  ifInull {
    posRow = i;
  }
  else {
    posRow = i - 1;
  }
  setCase(posRow, posCol,state, game,hide);

  ifInine {
    posRow = i;
  }
  else {
    posRow = i + 1;
  }
  posCol = j;


  setCase(posRow, posCol,state, game,hide);
}

void autoDiscover(char game[lenght][lenght], char hide[lenght][lenght], State state[lenght][lenght]) {
    for (int k = 0; k < lenght; k++) {
        for (int l = 0; l < lenght; l++) {
            if (state[k][l].zeroPosX != 10000 && state[k][l].zeroPosX != 20000) {
                int intPosX = state[k][l].zeroPosX;
                int intPosY = state[k][l].zeroPosY;
                aroundDiscover(intPosX, intPosY, state, game, hide);
                state[k][l].zeroPosX = 20000;
                autoDiscover(game, hide, state);
            }
        }
    }

}

int boxDiscover(int rowInput, int colInput, char game[lenght][lenght], char hide[lenght][lenght], State state[lenght][lenght]) {

    int i = 0;
    int j = 0;
    for (i = 0; i < lenght; i++) {
        for (j = 0; j < lenght; j++) {
            state[i][j].zeroPosX = 10000;
        }
    }
    char playerChoice = hide[rowInput][colInput];
    if (playerChoice == '0') {
        state[rowInput][colInput].isDiscover = 1;
        game[rowInput][colInput] = playerChoice;
        state[rowInput][colInput].zeroPosX = rowInput;
        state[rowInput][colInput].zeroPosY = colInput;
        autoDiscover(game, hide, state);
    }
    else if (playerChoice == 'o') {
        return 1;
    }
    else {
        printf("%s\n", "NUMBER");
        state[rowInput][colInput].isDiscover = 1;
        game[rowInput][colInput] = playerChoice;
    }
    return 0;
}

void firstDiscover(int posI, int posJ, char game[lenght][lenght], char hide[lenght][lenght], State state[lenght][lenght], int* beginReveal) {
    state[posI][posJ].isSafe = 1;
}

void placeFlag(State state[lenght][lenght], char game[lenght][lenght]) {
    int yesOrNo = 0;
    int rowInput = 0;
    int colInput = 0;
    printf("%s\n", "Voulez-vous placer un flag ? (0 = non, 1 = oui)");
    scanf_s("%d", &yesOrNo);

    if (yesOrNo == 1) {
        int error = 0;
        do {
            printf("%s\n", "Sur quel ligne voulez-vous placer le flag ?");
            error = scanf_s("%d", &rowInput);
            if (error != 0 && rowInput < lenght) {
                printf("%s %d\n", "Vous avez choisi de jouer a la ligne", rowInput);
            }
            char c = getchar();
            while (c != '\n') {
                c = getchar();
            };
        } while (error == 0 || rowInput > lenght);
        error = 0;
        do {
            printf("%s\n", "Sur quel colonne voulez-vous placer le flag ?");
            error = scanf_s("%d", &colInput);
            if (error != 0 && colInput < lenght) {
                printf("%s %d\n", "Vous avez choisi de jouer a la colonne", colInput);
            }
            char c = getchar();
            while (c != '\n') {
                c = getchar();
            };
        } while (error == 0 || colInput > lenght);


        if (game[rowInput][colInput] == '?') {
            game[rowInput][colInput] = 'F';
            state[rowInput][colInput].isFlag = 1;
            showBoard(game);
        }
        else {
            printf("%s\n", "il y a quelque chose ici !");
            placeFlag(state, game);
        }
    }


    yesOrNo = 0;
    printf("%s\n", "Voulez-vous retirer un flag ? (0 = non, 1 = oui)");
    scanf_s("%d", &yesOrNo);

    if (yesOrNo == 1) {
        int error = 0;
        do {
            printf("%s\n", "Sur quel ligne voulez-vous retirer le flag ?");
            error = scanf_s("%d", &rowInput);
            if (error != 0 && rowInput < lenght) {
                printf("%s %d\n", "Vous avez choisi de jouer a la ligne", rowInput);
            }
            char c = getchar();
            while (c != '\n') {
                c = getchar();
            };
        } while (error == 0 || rowInput > lenght);
        error = 0;
        do {
            printf("%s\n", "Sur quel colonne voulez-vous retirer le flag ?");
            error = scanf_s("%d", &colInput);
            if (error != 0 && colInput < lenght) {
                printf("%s %d\n", "Vous avez choisi de jouer a la colonne", colInput);
            }
            char c = getchar();
            while (c != '\n') {
                c = getchar();
            };
        } while (error == 0 || colInput > lenght);


        if (game[rowInput][colInput] == 'F') {
            game[rowInput][colInput] = '?';
            state[rowInput][colInput].isFlag = 0;
            showBoard(game);
        }
        else {
            printf("%s\n", "il y a deja un flag ou quelque chose ici");
            placeFlag(state, game);
        }
    }
}


// reveal bomb

void revealAtBomb(char game[lenght][lenght], char hide[lenght][lenght]) {
    for (int i = 0; i < lenght; i++) {
        for (int j = 0; j < lenght; j++) {
            if (hide[i][j] == 'o') {
                game[i][j] = hide[i][j];
            }
        }
    }
    showBoard(game);
    printf("\n%s\n", "game over");
}


int playing(char game[lenght][lenght], char hide[lenght][lenght], State state[lenght][lenght], int* beginReveal) {
    
    int rowInput = 0;
    int colInput = 0;
    int nbrBomb = 800;

    

    showBoard(game);
    if (*beginReveal == 1) {
        placeFlag(state, game);
        rowInput = 0;
        colInput = 0;
    }

    
    // ask choice
    wherePlay(&rowInput, &colInput);
    while (game[rowInput][colInput] != '?') {
        printf("%s", "cette case est déja prise");
        wherePlay(&rowInput, &colInput);
    }

    // if first reveal init safe zone 
    if (*beginReveal == 0) {
        /*printf("%d\n", *beginReveal);*/
        int posI = rowInput;
        int posJ = colInput;
        firstDiscover(posI, posJ, game, hide, state, beginReveal);
        posI = rowInput + 1;
        posJ = colInput + 1;
        firstDiscover(posI, posJ, game, hide, state, beginReveal);
        posI = rowInput - 1;
        posJ = colInput - 1;
        firstDiscover(posI, posJ, game, hide, state, beginReveal);
        posI = rowInput + 1;
        posJ = colInput - 1;
        firstDiscover(posI, posJ, game, hide, state, beginReveal);
        posI = rowInput - 1;
        posJ = colInput + 1;
        firstDiscover(posI, posJ, game, hide, state, beginReveal);
        posI = rowInput;
        posJ = colInput - 1;
        firstDiscover(posI, posJ, game, hide, state, beginReveal);
        posI = rowInput;
        posJ = colInput + 1;
        firstDiscover(posI, posJ, game, hide, state, beginReveal);
        posI = rowInput - 1;
        posJ = colInput;
        firstDiscover(posI, posJ, game, hide, state, beginReveal);
        posI = rowInput + 1;
        posJ = colInput;
        firstDiscover(posI, posJ, game, hide, state, beginReveal);

        

        // place bomb loop
        for (int i = 0; i < nbrBomb; i++) {
            placeBomb(hide, state);
        }

        // place number
        for (int i = 0; i < lenght; i++) {
            for (int j = 0; j < lenght; j++) {
                char nbrBomb = aroundBomb(hide, i, j);
                if (nbrBomb != 'a') {
                    hide[i][j] = nbrBomb;
                }
            }
        }


        game[rowInput][colInput] = hide[rowInput][colInput];
        game[rowInput + 1][colInput + 1] = hide[rowInput + 1][colInput + 1];
        game[rowInput - 1][colInput - 1] = hide[rowInput - 1][colInput - 1];
        game[rowInput + 1][colInput - 1] = hide[rowInput + 1][colInput - 1];
        game[rowInput - 1][colInput + 1] = hide[rowInput - 1][colInput + 1];
        game[rowInput][colInput + 1] = hide[rowInput][colInput + 1];
        game[rowInput][colInput - 1] = hide[rowInput][colInput - 1];
        game[rowInput + 1][colInput] = hide[rowInput + 1][colInput];
        game[rowInput - 1][colInput] = hide[rowInput - 1][colInput];



        boxDiscover(rowInput, colInput, game, hide, state);
        return 0;

    }

    else {
        int isWin = 1;
        if (boxDiscover(rowInput, colInput, game, hide, state)) {
            revealAtBomb(game, hide);
            return 1;
        }
        else {
            for (int i = 0; i < lenght; i++) {
                for (int j = 0; j < lenght; j++) {
                    if (game[i][j] == '?') {
                        isWin = 0;
                        return 0;
                    }
                }
            }
        }
        
        if (isWin == 1) {
            for (int i = 0; i < lenght; i++) {
                for (int j = 0; j < lenght; j++) {
                    game[i][j] = hide[i][j];
                }
            }
            showBoard(game);
            printf("\n%s\n", "WIN");
            return 1;
        }
        return 0;
    }
}