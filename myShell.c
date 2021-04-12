#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <stdbool.h>

// -----------------------------------------------------
// Title: CMPE 382 - Project #1: A Unix Shell
// Authors: Atakan Sevinçli & Öykü Çise Bilik
// Section: 1
// -----------------------------------------------------

void *funcThread(void *arg)
{
    system(arg);
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    FILE *fp;

    char input[512];
    char *inputptr;
    char *arr[50]; // this array keeps separated strings.
    char *sep;     //temporarily keeps separated strings.
    inputptr = input;
    char finput[512];

    if (argc > 1)
    //if you give an argument with argv, try to open this argument as a file.
    {
        fp = fopen(argv[1], "r");
        if (fp == NULL) // print error message when you cant open bat file for some reason.
        {
            printf("%s\n", strerror(errno));
            argc--;
        }
    }

    if (argc < 2)
    {
        // if argc < 2  so you have choosed interactive mode. and print prompt
        printf("ATAKAN@OYKU:>");
        fgets(inputptr, 512, stdin); // for first input .
    }
    else
    {
        // batch mode take first line as input to start the while loop.
        fgets(input, 512, fp);
    }

    while (strcmp(inputptr, "quit\n") != 0)
    {

        bool isQuit = false;
        /*
        In theese lines , We are parsing the inputs according to existing of (|) and (;) characters.

        There are three cases : 
        1) input contains only (;)
        2) input contains only (|)
        3) input contains (;) and (|) both.

        In first case , we just parse them according to (;)  and send all of them to threads.
        In second case , we just parse them according to (|)  and send all of them to system.
        In third case ; First of all , we parse them according to (|).
                        Secondly, We check that Does the splitted inputs according to (|) contains any (;).
                        So, if contains (;) then we parse them again and send to the threads if not contains (;) send them to directly system.


            */
        if (strstr(inputptr, ";") != NULL) // IF true input contain (;).
        {

            if (strstr(inputptr, "|") != NULL) // is (;) and (|) exist in input?
            {
                char *token = strtok(input, "|");
                while (token != NULL) // split input according to (|)
                {

                    if (strstr(token, ";") == NULL) // split input corresponding to (;)
                    {
                        if (strstr(token, "quit") != NULL)
                        {
                            isQuit = true;
                        }
                        else
                        {
                            // if there is no any (;) in input , So send to system.
                            system(token);
                        }
                    }
                    else
                    {
                        pthread_t newthread;
                        char *found;
                        while ((found = strsep(&token, ";")) != NULL)
                        {
                            if (strstr(found, "quit") != NULL) // that token is QUIT ?
                            {
                                isQuit = true;
                            }
                            else
                            {
                                pthread_create(&newthread, NULL, funcThread, (void *)found);
                            }
                        }
                    }
                    token = strtok(NULL, "|");
                }
            }
            else
            { // contain (;) characters but does not contain (|) .
                char *token2 = strtok(input, ";");

                while (token2 != NULL)
                {

                    if (strstr(token2, "quit") != NULL) // that token is QUIT ?
                    {
                        isQuit = true;
                    }
                    else
                    {
                        pthread_t newthread;
                        pthread_create(&newthread, NULL, funcThread, (void *)token2);
                    }
                    token2 = strtok(NULL, ";");
                }
            }
        }
        else
        // Input does not contain any (;) so parse them with respect to (|) and send to the system.
        {
            char *token = strtok(inputptr, "|");

            while (token != NULL)
            {
                if (strstr(token, "quit") != NULL) // that token is QUIT ?
                {
                    isQuit = true;
                }
                else
                {
                    system(token);
                }

                token = strtok(NULL, "|");
            }
        }

        sleep(1); // wait main thread when other threads executing
        if (isQuit)
        {
            // input contains quit so execute all of commands and them quit the program.
            strcpy(inputptr, "quit\n");
        }
        else
        {
            if (argc < 2)
            {
                // print prompt for interactive mode
                printf("ATAKAN@OYKU:>");
                fgets(inputptr, 512, stdin);
            }
            else
            {
                if (fp != NULL)
                {
                    if ((fgets(input, 512, fp)) == NULL)
                    {
                        fclose(fp);
                        fp = NULL; // if .bat file does not contain quit , So continue as interactive mode.
                    }
                }

                if (fp == NULL)
                {
                    // if .bat file does not contain quit , So continue as interactive mode.
                    // print prompt for interactive mode
                    printf("ATAKAN@OYKU:>");
                    fgets(inputptr, 512, stdin);
                }
            }
        }
    }

    return 0;
}
