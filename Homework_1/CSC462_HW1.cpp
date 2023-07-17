// CSC462_HOMEWORK_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cstring>

int main()
{

    //Setting up variables to operate on input.
    std::string sentence;
    std::string word;
    

    //Loop to terminate program.
    while (word != "exit") {
        

        //Grab sentence from input.
        std::cout << "Write a sentence: \n";
        std::getline(std::cin, sentence);


        //Create words array and nxtWord to iterate.
        char* words = new char[sentence.length() + 1];
        char* nxtWord;
        

        //Copy sentence into words[], tokenize words[].
        strcpy_s(words, sentence.length() + 1, sentence.c_str());
        char* thsWord = strtok_s(words, " ", &nxtWord);
        

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
            thsWord = strtok_s(NULL, " ", &nxtWord);
            
        }


        //Cleanup.
        delete[] words;
    }
    return 0;
    
}