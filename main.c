#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "color.h"
#include "kbhit.c"

#define move_cursor_to(x, y) printf("\033[%d;%dH", x, y)
#define UP_KEY 65
#define DOWN_KEY 66
#define RIGHT_KEY 67
#define LEFT_KEY 68
#define BOMB_CHAR '@'
#define TABLE_SIZE_MAX 30
#define random(min, max) rand() % max + min
#define randomize srand((unsigned)time(NULL))
#define color(color) printf(color)

unsigned short int write_element(unsigned short int, unsigned short int);

void print_number(char);

void set_terminal_backg_color(char *);

void set_terminal_foreg_color(char *);

void set_difficulty(void);

void create_grid(void);

unsigned short int start_playing(void);

unsigned short int check_position(unsigned short int, unsigned short int);

void reveal_neighbors(unsigned short int, unsigned short int);


char matrix[TABLE_SIZE_MAX][TABLE_SIZE_MAX];
char matrix2[TABLE_SIZE_MAX][TABLE_SIZE_MAX];
char *string, string2[100];

unsigned short int field_size, prob;
short int bombs;

int main() {
    randomize;
    do {
        system("clear");
        bombs = 0;
        color(STANDARD);
        set_difficulty();
        create_grid();
    } while (start_playing());
    system("clear");
    return 0;
}

void set_difficulty() {
    unsigned short int dif;
    do {
        printf("Select the difficulty (1-10), 11 for a custom value:\n");
        scanf("%hu", &dif);
    } while (dif > 11 || dif < 0);
    switch (dif) {
        case 1:
            field_size = 15;
            prob = 10;
            break;
        case 2:
            field_size = 20;
            prob = 10;
            break;
        case 3:
            field_size = 22;
            prob = 12;
            break;
        case 4:
            field_size = 24;
            prob = 14;
            break;
        case 5:
            field_size = 25;
            prob = 16;
            break;
        case 6:
            field_size = 26;
            prob = 18;
            break;
        case 7:
            field_size = 27;
            prob = 21;
            break;
        case 8:
            field_size = 28;
            prob = 22;
            break;
        case 9:
            field_size = 30;
            prob = 25;
            break;
        case 10:
            field_size = 30;
            prob = 30;
            break;
        case 11:
            do {
                printf("Select the field size by writing the amount of column and rows number (max: %d):\n",
                       TABLE_SIZE_MAX);
                scanf("%hu", &field_size);
            } while (field_size > TABLE_SIZE_MAX || field_size < 5);
            do {
                printf("Set the odds (in %%) that there is a bomb in a box:\n");
                scanf("%hu", &prob);
            } while (prob > 100 || prob < 0);
            break;
    }
}

void create_grid() {
    unsigned short int i, j;
    for (i = 0; i < field_size; ++i)
        for (j = 0; j < field_size; ++j) {
            if ((random(0, 100) < prob) && (i > 1 && j > 1)) {
                matrix[i][j] = BOMB_CHAR;
                bombs++;
            }

            matrix2[i][j] = '-';
        }
    for (i = 0; i < field_size; ++i)
        for (j = 0; j < field_size; ++j) {

            if (matrix[i][j] != BOMB_CHAR)
                matrix[i][j] = (48 + write_element(i, j));

            if (matrix[i][j] == '0')
                matrix[i][j] = ' ';

        }
}

unsigned short start_playing() {
    char car;
    unsigned short int i, j, has_won = 0, has_lost = 0, x, y, play_again;
    x = 2;
    y = 2;
    while (!has_lost && !has_won) {
        printf("\n");
        system("clear");
        color(STANDARD);
        move_cursor_to(0, 0);
        for (i = 0; i < field_size; ++i) {
            printf("\n|");
            for (j = 0; j < field_size; ++j)
                print_number(matrix2[i][j]);
            color(STANDARD);
        }
        printf("\nMove with the arrow keys and select the bombs with the spacebar, check the boxes with ENTER (bombs left: %hi)",
               bombs);
        move_cursor_to(x, y);
        car = 'Z';
        while (car != ' ' && car != UP_KEY && car != DOWN_KEY && car != RIGHT_KEY && car != LEFT_KEY && car != '\n') {
            while (!kbhit());
            car = getchar();
        }
        switch (car) {
            case UP_KEY:
                x = x - 1;
                break;
            case DOWN_KEY:
                x = x + 1;
                break;
            case RIGHT_KEY:
                y = y + 2;
                break;
            case LEFT_KEY:
                y = y - 2;
                break;
            case ' ':
                if (matrix2[x - 2][(y / 2) - 1] != '*') {
                    matrix2[x - 2][(y / 2) - 1] = '*';
                    if (matrix[x - 2][(y / 2) - 1] == BOMB_CHAR) bombs--;
                } else if (matrix2[x - 2][(y / 2) - 1] == '*') {
                    if (matrix[x - 2][(y / 2) - 1] == '/')
                        matrix2[x - 2][(y / 2) - 1] = ' ';
                    else
                        matrix2[x - 2][(y / 2) - 1] = '-';
                    if (matrix[x - 2][(y / 2) - 1] == BOMB_CHAR) bombs++;
                }

                break;
            case '\n':
                has_lost = check_position(x, y);
                break;
        }
        if (bombs == 0) has_won = 1;
        if (x < 2) x = 2;
        if (y < 2) y = 2;
        if (x > (field_size + 1)) x = (field_size + 1);
        if ((y / 2) > (field_size)) y = (field_size * 2);
    }
    system("clear");
    color(STANDARD);
    for (i = 0; i < field_size; ++i) {
        printf("\n|");
        for (j = 0; j < field_size; ++j)
            print_number(matrix[i][j]);
        color(STANDARD);
    }
    if (has_won) printf("\nYou win!");
    if (has_lost) printf("\nYou lose!");
    printf("\nPlay again? 1.Yes 0.No\n");
    scanf("%hu", &play_again);
    return play_again;
}

unsigned short check_position(unsigned short row, unsigned short column) {
    row -= 2;
    column /= 2;
    column--;
    unsigned short foundBomb = 0;
    switch (matrix[row][column]) {
        case BOMB_CHAR:
            foundBomb = 1;
            break;
        case ' ':
            reveal_neighbors(row, column);
            break;
        case '/':
            break;
        default:
            matrix2[row][column] = matrix[row][column];
            break;
    }
    return foundBomb;
}

void reveal_neighbors(unsigned short row, unsigned short column) {
    if ((matrix[row][column] != BOMB_CHAR) && (matrix[row][column] != '/') && (matrix[row][column] != '*')) {
        if (matrix[row][column] == ' ') {
            matrix2[row][column] = matrix[row][column];
            matrix[row][column] = '/';

            if ((row - 1) >= 0) {
                if (
                        (matrix[row - 1][column] != BOMB_CHAR) &&
                        (matrix[row - 1][column] != '/') &&
                        (matrix[row - 1][column] != '*')
                        ) {
                    if (matrix[row - 1][column] == ' ')
                        reveal_neighbors((row - 1), column);
                    else
                        matrix2[row - 1][column] = matrix[row - 1][column];
                }
            }

            if ((column - 1) >= 0) {
                if (
                        (matrix[row][column - 1] != BOMB_CHAR) &&
                        (matrix[row][column - 1] != '/') &&
                        (matrix[row][column - 1] != '*')
                        ) {
                    if (matrix[row][column - 1] == ' ')
                        reveal_neighbors(row, (column - 1));
                    else
                        matrix2[row][column - 1] = matrix[row][column - 1];
                }
            }

            if (((column - 1) >= 0) && ((row - 1) >= 0)) {
                if (
                        (matrix[row - 1][column - 1] != BOMB_CHAR) &&
                        (matrix[row - 1][column - 1] != '/') &&
                        (matrix[row - 1][column - 1] != '*')
                        ) {
                    if (matrix[row - 1][column - 1] == ' ')
                        reveal_neighbors((row - 1), (column - 1));
                    else
                        matrix2[row - 1][column - 1] = matrix[row - 1][column - 1];
                }
            }

            if ((row + 1) < field_size) {
                if (
                        (matrix[row + 1][column] != BOMB_CHAR) &&
                        (matrix[row + 1][column] != '/') &&
                        (matrix[row + 1][column] != '*')
                        ) {
                    if (matrix[row + 1][column] == ' ')
                        reveal_neighbors((row + 1), column);
                    else
                        matrix2[row + 1][column] = matrix[row + 1][column];
                }
            }

            if ((column + 1) < field_size) {
                if (
                        (matrix[row][column + 1] != BOMB_CHAR) &&
                        (matrix[row][column + 1] != '/') &&
                        (matrix[row][column + 1] != '*')
                        ) {
                    if (matrix[row][column + 1] == ' ')
                        reveal_neighbors(row, (column + 1));
                    else
                        matrix2[row][column + 1] = matrix[row][column + 1];
                }
            }

            if (((column + 1) < field_size) && ((row + 1) < field_size)) {
                if (
                        (matrix[row + 1][column + 1] != BOMB_CHAR) &&
                        (matrix[row + 1][column + 1] != '/') &&
                        (matrix[row + 1][column + 1] != '*')
                        ) {
                    if (matrix[row + 1][column + 1] == ' ')
                        reveal_neighbors((row + 1), (column + 1));
                    else
                        matrix2[row + 1][column + 1] = matrix[row + 1][column + 1];
                }
            }

            if (((column + 1) < field_size) && ((row - 1) >= 0)) {
                if (
                        (matrix[row - 1][column + 1] != BOMB_CHAR) &&
                        (matrix[row - 1][column + 1] != '/') &&
                        (matrix[row - 1][column + 1] != '*')
                        ) {
                    if (matrix[row - 1][column + 1] == ' ')
                        reveal_neighbors((row - 1), (column + 1));
                    else
                        matrix2[row - 1][column + 1] = matrix[row - 1][column + 1];
                }
            }

            if (((column - 1) >= 0) && ((row + 1) < field_size)) {
                if (
                        (matrix[row + 1][column - 1] != BOMB_CHAR) &&
                        (matrix[row + 1][column - 1] != '/') &&
                        (matrix[row + 1][column - 1] != '*')
                        ) {
                    if (matrix2[row + 1][column - 1] == ' ')
                        reveal_neighbors((row + 1), (column - 1));
                    else
                        matrix2[row + 1][column - 1] = matrix[row + 1][column - 1];
                }
            }
        }
    }
    return;
}

unsigned short write_element(unsigned short row, unsigned short column) {
    unsigned short int n;
    n = 0;
    if ((row - 1) >= 0)
        if (matrix[row - 1][column] == BOMB_CHAR)
            n++;

    if ((column - 1) >= 0)
        if (matrix[row][column - 1] == BOMB_CHAR)
            n++;

    if (((column - 1) >= 0) && ((row - 1) >= 0))
        if (matrix[row - 1][column - 1] == BOMB_CHAR)
            n++;

    if ((row + 1) < TABLE_SIZE_MAX)
        if (matrix[row + 1][column] == BOMB_CHAR)
            n++;

    if ((column + 1) < TABLE_SIZE_MAX)
        if (matrix[row][column + 1] == BOMB_CHAR)
            n++;

    if (((column + 1) < TABLE_SIZE_MAX) && ((row + 1) < TABLE_SIZE_MAX))
        if (matrix[row + 1][column + 1] == BOMB_CHAR)
            n++;

    if (((column + 1) < TABLE_SIZE_MAX) && ((row - 1) >= 0))
        if (matrix[row - 1][column + 1] == BOMB_CHAR)
            n++;

    if (((column - 1) >= 0) && ((row + 1) < TABLE_SIZE_MAX))
        if (matrix[row + 1][column - 1] == BOMB_CHAR)
            n++;


    return n;
}

void print_number(char point) {
/* STANDARD, BIANCO, ROSSO, VERDE, ARANCIO, BLU, VIOLA, GRIGIO, ROSSOCHIARO, VERDECHIARO, GIALLO, CELESTE, ROSA, AZZURRO
	SOTTOLINEATO, LAMPEGGIANTE, NEROSUGRIGIO, LAMPCOLORE, SOTTCOLORE, RIGA(ROSSA-VERDE-ARANCIO-BLU-VIOLA-AZZURRO) */
    switch (point) {
        case '1':
            color(SOTTOLINEATO);
            color(BLU);
            break;
        case '2':
            color(SOTTOLINEATO);
            color(VERDE);
            break;
        case '3':
            color(SOTTOLINEATO);
            color(ARANCIO);
            break;
        case '4':
            color(SOTTOLINEATO);
            color(VIOLA);
            break;
        case '5':
            color(SOTTOLINEATO);
            color(AZZURRO);
            break;
        case '6':
            color(SOTTOLINEATO);
            color(ROSA);
            break;
        case '7':
            color(SOTTOLINEATO);
            color(VERDECHIARO);
            break;
        case '8':
            color(SOTTOLINEATO);
            color(ROSSO);
            break;
        case BOMB_CHAR:
            color(STANDARD);
            break;
        case '/':
            point = ' ';
            color(CELESTE);
            break;
        case '-':
            color(AZZURRO);
            break;
        case '*':
            color(SOTTOLINEATO);
            color(GRIGIO);
            break;
        default:
            color(STANDARD);
            break;
    }
    printf("%c", point);
    color(STANDARD);
    printf("|");
}
