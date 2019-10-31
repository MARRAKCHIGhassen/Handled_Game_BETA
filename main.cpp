/*____________________________________________________________________________________________________________________________________*/
/**
* _Author    : MARRAKCHI Ghassen.
*
* _Version   : BETA.
*
* _Language  : CPP.
*
* _Paradigm  : Procedural.
*
* _Libraries : "iostream"/"string"/"ctime"/"cstdlib"/"fstream".
*
* _Functions :         Arguments      / Returning type.
**
** __ "choisirMot"   : NONE           / string.
**
** __ "melangerMots" : string, string /   NONE.
**
** __ "toUpper"      : char           /   char.
**
* _Files : "main.cpp".
*
**/

/*PARAMETERS*/
//Inclusion
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>

//Namespace
using namespace std;

//Prototypes
string selectWord();
void mixLetters(string entered, string &mixed);
char toUpper(char character);


/*MAIN FUNCTION*/
int main()
{
    /*WELCOMING*/
    //Initializing
    srand(time(0));

    //Global Variables
    int roundNbre(0);
    char newRound('Y');

    //Welcome Printing
    cout << endl << "---------" << endl;
    cout << "MYSTERY WORD" << endl;
    cout << "You're going to find the word from the mixed printed letters!" << endl;
    cout << "YOU HAVE TO WRITE IN UPPERCASE !!" << endl;
    cout << "---------" << endl << endl;


    /*PROGRAM BODY*/
    do{
        //Round Variables
        string selectedWord, mixedWord, foundWord;
        int chanceNbre(10);

        //Round Announcing
        roundNbre++;
        cout << "//Round N: " << roundNbre << endl << endl;

        //Word Selecting
        cout << "***" << endl;
        cout << "Selecting the targeted word from dictionary ..." << endl;
        selectedWord=selectWord();
        cout << "***" << endl << endl;

        //Letters Mixing
        mixLetters(selectedWord, mixedWord);

        //User Interaction
        cout << "***" << endl;
        cout << "It's your turn NOW !!" << endl;

        do{
            if(chanceNbre == 1)
                cout << "You have only one chance !" << endl;
            else
                cout << "You have " << chanceNbre << " chances !" << endl;
            cout << "Letters : " << mixedWord << endl;
            cout << "Your try : _ ";
            cin >> foundWord;
            cin.ignore();   //Buffer Cleaning
            cout << endl;

            chanceNbre--;
        }while((foundWord != selectedWord) && (chanceNbre != 0));

        if(chanceNbre != 0)   //Succeeding Verification
            cout << "Congratulations !" << endl;
        else
            cout << "So Sorry !" << endl;
        cout << "The targeted word was : " << selectedWord << endl;

        //New Round
        cout << endl << "//Played rounds: " << roundNbre << endl;
        cout << "//Try Again ? [(Y)es / (n)o] _ ";
        cin >> newRound;
        cin.ignore();
        cout << endl;
    }while(toUpper(newRound) == 'Y');


    /*PROGRAM QUITTING*/
    cout << "---------" << endl;
    cout << "THANKS FOR VISITING US!" << endl;
    cout << "---------" << endl;
    return 0;
}


/*FUNCTIONS DEFINITIONS*/
string selectWord(){
    /**
    * _Author : MARRAKCHI Ghassen.
    * _Purpose : Selecting a random word from a Dictionary file.
    **/

    /*FUNCTION VARIABLES*/
    ifstream file("Dictionary.txt");
    string readWord;


    /*FUNCTION BODY*/
    if(file){    //Opening Verification
        int length(0), firstLength(0);
        char character(0);

        file.seekg(0, ios::beg); //Initializing Cursor
        do{
            file.get(character);
            if(character != '/')
                firstLength++;
        }while(character != '/');
        character=0;    //Initializing Character

        file.seekg(0, ios::end);
        length=file.tellg();
        file.seekg(rand() % length, ios::beg);     //Random Character Choice

        if(file.tellg() < firstLength){  //First Word Verification
            file.seekg(0, ios::beg);

            do{ //Reading File
                file.get(character);
                if(character != '/')
                    readWord.push_back(character);
            }while(character != '/');
        }
        else{

            do{ //Word's Begin Verification
                file.get(character);
                if(character != '/')
                    file.seekg(-2, ios::cur);
            }while(character != '/');

            do{ //Reading File
                file.get(character);
                if(character != '/')
                    readWord.push_back(character);
            }while(character != '/');
        }

        file.close();
    }
    else{
        cout << "Dictionary not found!" << endl;
    }

    return readWord;
}

void mixLetters(string entered, string &mixed){
    /**
    * _Author : MARRAKCHI Ghassen.
    * _Purpose : Mixing word's letters randomly.
    **/

    /*FUNCTION VARIABLES*/
    int length(entered.size());

    /*FUNCTION BODY*/
    for(int i=0; i<length; i++){
        int nbre(rand() % entered.size());   //Randomly Generated Index

        mixed.push_back(entered[nbre]);
        entered.erase(nbre,1);
    }
}

char toUpper(char character){
    /**
    * _Author : MARRAKCHI Ghassen.
    * _Purpose : Transforming any Alphabet Character to Uppercase.
    **/

    /*FUNCTION BODY*/
    if((character > 'a') && (character < 'z'))
        character+=32;
    return character;
}

/*____________________________________________________________________________________________________________________________________*/
