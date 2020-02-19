// Chris Hayden, algorithm 4
//
// Algorithm 4 will be for a flash card program similar to algorithm 3.
// The basic idea will be to take in input from the user about a concept to be
// quizzed on and display it with the answer hidden to be revealed when the user
// wishes. The program will be to hold 10 questions in memory and use class's
// instead of structs.
//
// We will be using a class's to store the info. The class will store; it's
// number, the subject, question text, date completed.
//
//
// Before taking input we will ask the
// user how many questions they will enter in. We will tell the user what they
// are to input so not to confuse them. We will use the cin variable to receive
// input from the user and save it to a given class. The class will probably be
// named something like Question. Before we continue to the next part of the
// program we will echo the given information to the user to see if it is
// correct, if it is we will continue. Once we know that we have the correct
// data containing we will then add it to a class of other class's that contain
// the users correct information. We will add more questions to the class array
// iterating until the user is done or the max amount is reached. The first
// version of the program the max will be arbitrarily 10.
//
// The class will contain a dynamically allocated array with the amount of
// class's. The member variables will be, pointer to a question class, number in
// the array and the max the array can hold. The functions to display the data
// will be members of the class that will most likely be implemented in another
// file. The functions will be something like, constructor, destructor,
// read_all, display_all, display_all_filter.
//
// Finally give the user the options to display all questions (and answers), use
// the quiz like format to display each question individually or display by only
// a given subject.
//
// Before the program ends call delete on each element / class of the array,
// then call delete on the array itself to free all the memory that was manually
// allocated by the program. The class will use the destructor function that
// will be written for the class in question. The destructor function will make
// sure that any dynamically allocated memory that was allocated by the program
// that a person programed will be freed.

#include <iostream>

#include "questions.h"

using namespace std;

int main() {
    QuestionList list = QuestionList();

    list.read_in_all_questions();

    char user_input = 'a';

    cout << "\ndo you wan to display the questions by subject or all "
            "together\n[s]ubject or [t]ogether\n (s|t) -> ";
    cin >> user_input;
    cin.ignore(1000, '\n');

    if (tolower(user_input) == 's') {
        char to_match[FIELD_SIZE];

        cout << "what subject to match\n -> ";
        cin.get(to_match, FIELD_SIZE, '\n');
        cin.clear();
        cin.ignore(FIELD_SIZE, '\n');

        list.display_type(to_match);
    } else {
        list.display_all();
    }

    return 0;
}
