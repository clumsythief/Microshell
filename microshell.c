#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>

char prev_dir[255];

void say_hello() {
    printf("\x1b[1m\n\n...Microshell running...\n\x1b[0m");
    sleep(1);
    printf("Naciśnij Ctrl+C lub wpisz \"exit\" żeby wyjść z programu\n\n");
    sleep(1);
    printf("Wpisz \"help\" żeby uzyskać dodatkowe informacje\n\n\n");
    sleep(1);
}

void help() {
    printf("\x1b[35m\n\n***Microshell***\n***Systemy Operacyjne 2022***\n\x1b[0m");
    printf("Autor: Palina Baihot\n\n");
    printf("\x1b[1mPolecenia:\n");
    printf("help\x1b[0m - wyświetla informację o autorze i oferowanych funkcjonalnościach;\n");
    printf("\x1b[1mexit\x1b[0m - kończy działanie programu;\n");
    printf("\x1b[1mcd [nazwa_katalogu]\x1b[0m - zmienia katalog roboczy;\n");
    printf("          \x1b[1mopcje:\x1b[0m\n          \x1b[1m.\x1b[0m - bieżący katalog;\n          \x1b[1m..\x1b[0m - nadrzędna lokalizacja;\n");
    printf("          \x1b[1m~\x1b[0m - katalog domowy;\n          \x1b[1m-\x1b[0m - poprzedni katalog;\n");
    printf("\x1b[1mmkdir [nazwa_katalogu]\x1b[0m - tworzy nowy katalog (do 9 na raz);\n");
    printf("          \x1b[1mopcje:\x1b[0m\n          \x1b[1m-p [nowy_katalog1]/[nowy_katalog2]\x1b[0m - tworzy podkatalogi (do 4 na raz);\n\n\n");
}

void change_directory(char *directory) {
    if(strstr(directory, "~")) {
        chdir(getenv("HOME"));
    } else {
        chdir(directory);
    }
}

void make_directory(char *directory) {
    mkdir(directory, 0777);
}

int main() {

    say_hello();

    errno = 0;
    getcwd(prev_dir, 255);
    char *string = NULL;
    char separator[10] = " \n";
    int number_of_elem = 10;
    int i;

    char **polecenia = NULL;
    polecenia = (char **) malloc(number_of_elem * sizeof(char *));

    do {
        char username[255];
        char directory[255];

        getcwd(directory, 255);
        printf("[\x1b[32m%s\x1b[0m:", getlogin());
        printf("\x1b[36m%s\x1b[0m]\n", getcwd(username, 255));

        string = readline("$ ");
        add_history(string);

        polecenia[0] = strtok(string, separator);

        for (i = 1; i < number_of_elem; i++) {
            polecenia[i] = strtok(NULL, separator);
        }

        if(polecenia[0] == NULL) {
            polecenia[0] = "nie_dziala";
        }
/*CHANGE_DIRECTORY*/
        if (strstr(polecenia[0], "cd")) {
            if (polecenia[1] == NULL) {
                polecenia[1] = "~";
            }
            if (strcmp(polecenia[1], "-") == 0) {
                strcpy(polecenia[1], prev_dir);
            }
            getcwd(prev_dir, 255);
            change_directory(polecenia[1]);
        }
/*HELP*/
        else if (strstr(polecenia[0], "help") && polecenia[1] == NULL) {
            help();
        } else if (strstr(polecenia[0], "help") && polecenia[1] != NULL){
            errno = 2;
        }
/*MAKE DIRECTORY */
        else if (strstr(polecenia[0], "mkdir")) {

            if(polecenia[1] == NULL) {
                errno = 2;
            }
            else if(strstr(polecenia[1], "-p")) {
                char *first_dir;
                char *second_dir;
                char *third_dir;
                char *fourth_dir;
                char current_dir[255];

                first_dir = strtok(polecenia[2], "/\n");
                if(first_dir!=NULL) {
                    getcwd(current_dir, 255);
                    make_directory(first_dir);
                    change_directory(first_dir);
                    second_dir = strtok(NULL, "/\n");
                    if(second_dir!=NULL) {
                        make_directory(second_dir);
                        change_directory(second_dir);
                        third_dir = strtok(NULL, "/\n");
                        if(third_dir!=NULL) {
                            make_directory(third_dir);
                            change_directory(third_dir);
                            fourth_dir = strtok(NULL, "/\n");
                            if(fourth_dir!=NULL) {
                                make_directory(third_dir);
                            }
                        }
                    }
                } else {
                    errno = 2;
                }
                change_directory(current_dir);
            } else if (polecenia[1] != NULL) {
                make_directory(polecenia[1]);
                int j;
                for(j = 2; j<number_of_elem; j++) {
                    if(polecenia[j] != NULL) {
                        make_directory(polecenia[j]);
                    }
                }
            }
        }
/*EXEC*/
        else if(!strstr(polecenia[0], "help") && !strstr(polecenia[0], "cd") && !strstr(polecenia[0], "exit") && !strstr(polecenia[0], "mkdir")) {
            pid_t process_id = fork();

            if(process_id == 0) {
                if(execvp(polecenia[0], polecenia) < 0) {
                    fprintf(stderr, "Błąd polecenia (%d): %s\n", errno, strerror(errno));
                    exit(EXIT_FAILURE);
                } else {
                    exit(0);
                }
            } else {
                wait(NULL);
            }
        }
/*ERRORS*/
        if(errno>0) {
            fprintf(stderr, "Błąd polecenia (%d): %s\n", errno, strerror(errno));
        }
    } while (!strstr(polecenia[0], "exit"));

    return 0;
}