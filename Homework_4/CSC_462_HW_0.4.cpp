// CSC462_HOMEWORK_0.4.cpp : This file contains the 'main' function. Program
// execution begins and ends there.
//
#include <iostream>
#include <cstring>
#include <string>
#include <sys/wait.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{

    //This sets up the shell prompt.
    std::string sh_name;
    if (argc == 2 && argv[1][0] != '-')
    {
        sh_name = argv[1];
    }
    else if (argc == 2)
    {
        sh_name = "";
    }
    else
    {
        sh_name = "jsh: ";
    }

    // Setting up variables to operate on input.
    std::string sentence;
    std::string tmpSentence;
    std::string word;

    // Loop to terminate program.
    while (sentence != "exit")
    {

        // Grab sentence from input.
        std::cout << sh_name, ": \n";
        if (std::getline(std::cin, sentence))
        {
            // Create words array and nxtWord to it
            tmpSentence = sentence;

            // Create words tmpWords array.
            char *tmpWords = new char[sentence.length() + 1];
            char *words = new char[sentence.length() + 1];

            // Copy sentence into tmpWords[] and words[].
            strcpy(tmpWords, tmpSentence.c_str());
            strcpy(words, sentence.c_str());

            //Create iterators.
            char *tmpWord;
            char *nxtWord;

            //Tokenize the arrays.
            char *tmp = strtok_r(tmpWords, " ", &tmpWord);
            char *thsWord = strtok_r(words, " ", &nxtWord);

            // Loop to get word count in the array and store in wrdCnt.
            int wrdCnt = 0;
            while (tmp != 0)
            {
                tmp = strtok_r(NULL, " ", &tmpWord);
                wrdCnt++;
            }
            delete[] tmp;


            //Create cmd pointer array and populate from words[].
            char **cmd = (char **)calloc(wrdCnt + 1, sizeof(char *));
            for (int i = 0; i < wrdCnt; i++)
            {
                cmd[i] = thsWord;
                thsWord = strtok_r(NULL, " ", &nxtWord);
            }

            //NULL terminate cmd[].
            cmd[wrdCnt] = NULL;

            //Begin fork.
            pid_t rv, w;
            int wstatus;

            rv = fork();

            if (rv == -1)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }

            //This is the child process.
            if (rv == 0)
            {

                //Replace child process with cmd[0] using the rest of cmd as args.
                execvp(cmd[0], cmd);
                
                

                //Print error.
                perror("forkcat");
                exit(0);
            }
            else
            {
                do
                {
                    
                    //This is the parent.
                    w = waitpid(rv, &wstatus, WUNTRACED | WCONTINUED);
                    if (w == -1)
                    {
                        perror("waitpid");
                        exit(EXIT_FAILURE);
                    }
                    /*if (WIFEXITED(wstatus))
                    {
                        printf("exited, status=%d\n", WEXITSTATUS(wstatus));
                    }*/
                    else if (WIFSIGNALED(wstatus))
                    {
                        printf("killed by signal %d\n", WTERMSIG(wstatus));
                    }
                    else if (WIFSTOPPED(wstatus))
                    {
                        printf("stopped by signal %d\n", WSTOPSIG(wstatus));
                    }
                    else if (WIFCONTINUED(wstatus))
                    {
                        printf("continued\n");
                    }
                } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
            }

            // Cleanup.
            delete[] words;
            free(cmd);
        }
        else
        {
            exit(0);
        }
    }
}