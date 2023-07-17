// CSC462_HOMEWORK_1.cpp : This file contains the 'main' function. Program 
//execution begins and ends there.
//
#include <iostream>
#include <string>
#include <cstring>

int main(int argc, char** argv)
{
    //Setting up prompt to be decided from command line args. 
    std::string sh_name; 
    if(argc == 2 && argv[1][0] != '-'){
        sh_name = argv[1];
    }
    else if(argc == 2 ){
        sh_name = "";
    }
    else{
        sh_name = "jsh: ";
    }

    //Setting up variables to operate on input.
    std::string sentence;
    std::string word;
    
    //Loop to terminate program.
    while (word != "exit") {
        
        //Grab sentence from input.
        std::cout << sh_name, ": \n";
        std::getline(std::cin, sentence);
        //Create words array and nxtWord to iterate.
        char* words = new char[sentence.length() + 1];
        char* nxtWord;
        
        //Copy sentence into words[], tokenize words[].
        strcpy(words, sentence.c_str());
        char* thsWord = strtok_r(words, " ", &nxtWord);
        
        //Loop to iterate through words[].
        while (thsWord != 0)
        {
             
            //Check for exit.
            word = thsWord;
            if (word == "exit") {
                break;
            }
            
            //Print out tokenized words.
            std::cout << thsWord << '\n';
            thsWord = strtok_r(NULL, " ", &nxtWord);
            
        }
        //Cleanup.
        delete[] words;
    }
}