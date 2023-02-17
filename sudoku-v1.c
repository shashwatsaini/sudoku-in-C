//Program for Sudoku

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include <string.h>

#define MAX_LINE_LENGTH 82

char game[9][9];
struct tm* time_ptr;

int check(char key, int row, int col){
    if(game[row-1][col-1]!='_')
        return 0;
    int box;
    int check_row, check_col;
    if(row<=3&&col<=3)
        box=1;
    else if(row<=3&&col<=6)
        box=2;
    else if(row<=3&&col<=9)
        box=3;
    else if(row<=6&&col<=3)
        box=4;
    else if(row<=6&&col<=6)
        box=5;
    else if(row<=6&&col<=9)
        box=6;
    else if(row<=9&&col<=3)
        box=7;
    else if(row<=9&&col<=6)
        box=8;
    else if(row<=9&&col<=9)
        box=9;
    
    for(int i=0; i<9; i++){
        if(game[i][col-1]==key)
            return 0;
    }

    for(int i=0; i<9; i++){
        if(game[row-1][i]==key)
            return 0;
    }
    switch(box){
        case 1:
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(game[i][j]==key)                    
                    return 0;
        break;

        case 2:
        for(int i=0;i<3;i++)
            for(int j=3;j<6;j++)
                if(game[i][j]==key)                    
                    return 0;
        break;

        case 3:
        for(int i=0;i<3;i++)
            for(int j=6;j<9;j++)
                if(game[i][j]==key)                    
                    return 0;
        break;

        case 4:
        for(int i=3;i<6;i++)
            for(int j=0;j<3;j++)
                if(game[i][j]==key)                    
                    return 0;
        break;

        case 5:
        for(int i=3;i<6;i++)
            for(int j=3;j<6;j++)
                if(game[i][j]==key)                    
                    return 0;
        break;

        case 6:
        for(int i=3;i<6;i++)
            for(int j=6;j<9;j++)
                if(game[i][j]==key)                    
                    return 0;
        break;

        case 7:
        for(int i=6;i<9;i++)
            for(int j=0;j<3;j++)
                if(game[i][j]==key)                    
                    return 0;
        break;

        case 8:
        for(int i=6;i<9;i++)
            for(int j=3;j<6;j++)
                if(game[i][j]==key)                    
                    return 0;
        break;

        case 9:
        for(int i=6;i<9;i++)
            for(int j=6;j<9;j++)
                if(game[i][j]==key)                    
                    return 0;
        break;
    }

    return 1;
}

void getgame(int choice){
    FILE* game_file;
    if(choice==2){
        game_file= fopen("sudoku-savegame.txt","r");
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char check = (char)getc(game_file);
                if (isdigit(check) && check!=EOF && check!='e') {
                    int temp_val = check;
                    game[i][j] = temp_val;
                } else {
                    game[i][j] = '_';
                }
            }
        }
    }
    else{
        int current_line=0;
        srand(time(0));
        int game_no = (rand() % 6) + 1;
        printf("%d", game_no);
        game_file=fopen("sudoku_puzzles.txt","r");
        char temp='0';
        int count_char=0;
        int count_games=0;
        if(game_no==1){
            ;
        } else{
            temp= getc(game_file);
            while(count_games<6){
                if(count_games==game_no-1)
                    break;
                if(temp=='e')
                    count_games++;
                temp= getc(game_file);
                count_char++;
            }
        }
        int count=0;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char check = getc(game_file);
                if (isdigit(check) && check!=EOF) {
                    game[i][j] = check;
                } else {
                    game[i][j] = '_';
                }
                count++;
            }
            if(count==81)
                break;
        }
    }

    fclose(game_file);

}

void savegame(){
    FILE* savefile;
    savefile=fopen("sudoku-savegame.txt", "w");
    char stream[120];
    int count=0;
    for(int i=0; i<9; i++){
        for(int j =0; j<9; j++){
            stream[count]=game[i][j];
            count++;
        }
    }
    stream[81]='e';
    time_t current_time;
    time(&current_time);

    char time_string[18];
    strftime(time_string, sizeof(time_string), "%c", localtime(&current_time));
    strncat(stream,time_string,17);

    stream[99]='\0';

    //printf("%s", stream);

    fprintf(savefile, stream);
    fclose(savefile);

}

char *gettime(){
    FILE* getfile=fopen("sudoku-savegame.txt", "r");
    char check= getc(getfile);
    while(check!='e' && check!=EOF)
        check=getc(getfile);
    static char time_stream[18];
    int count=0;
    while(check!=EOF){
        check=getc(getfile);
        time_stream[count]=check;
        count++;
    }
    time_stream[17]='\0';
    //printf("%s", time_stream);
    fclose(getfile);
    return time_stream;
}

int check_win(){
    for(int i=0;i<9;i++){
        for(int j=0; j<9;j++){
            if(game[i][j]=='_')
                return 0;
        }
    }

    return 1;
}

void print_game(){
    bool check_print=false;
    for(int i=0;i<9;i++){
        if(i==3 ||i==6)
            check_print=false;
        for(int j=0;j<9;j++){
            if (j==3 || j==6)
                printf("| ");
            if (check_print==false){
                printf("_____________________\n");
                check_print=true;
            }
            printf("%c ", game[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int row, col;
    char key;
    int choice;
    char* save_time;
    save_time= gettime();
    printf("Choose a game\n");
    printf("1. New game\n");
    printf("2. Saved game: Last played on %s\n", save_time);
    scanf("%d", &choice);
    if(choice==1 || choice==2)
        getgame(choice);
    else{
        printf("Invalid Choice!\n");
        exit(0);
    }
    do{
        savegame();
        print_game(game);
        printf("Enter the grid slot\n");
        scanf("%d %d", &row, &col);
        fflush(stdin);
        printf("Enter the number\n");
        scanf("%c", &key);
        if (check(key, row, col)==1)
            game[row-1][col-1]=key;
        else 
            printf("Incorrect entry! Try again.\n");

    } while(check_win()!=1);

    printf("You have successfully solved the puzzle.\n");
    return 0;
}
