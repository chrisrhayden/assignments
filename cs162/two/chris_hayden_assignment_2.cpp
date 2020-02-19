// chris hayden
//
// Start the program greeting the user and tell them its function.
// Prompt the user for a phrase reminding them that the computer will remove
// double white space and that it will capitalize the first words and will check
// for punctuation.
// Get input from the user in the form of at most 130 characters in an array.
//
// Make sure the first letter of the last given phrase is capitalized.
// Check if the phrase ends with the correct punctuation.
// If punctuation is missing prompt the user for a character, get the input from
// the user adding it to the last given phrase. Remove any double spaces leaving
// only a single space between words.
//
// Repeat the steps from prompt user for a phrase until this step 3 more times
// equaling a total of 4 phrases.
// Prompt the user to enter a signature and that the format is a short phrase
// with a comma followed by a full name. (e.g. Sincerely, Hunter Stockton
// Thompson)
//
// Make sure the first letter of the last given phrase is capitalized.
// Check if the phrase ends with the correct punctuation.
// If punctuation is missing prompt the user for a character, get the input from
// the user adding it to the last given phrase. Remove any double spaces leaving
// only a single space between words.
//
// After the comma capitalize every word, if no comma ask the user to reenter
// the phrase. Display the newly cleaned phrase and signature along side a
// number to easily identify the phrases to the user. Ask the user to give the
// order of the phrases on a single line space separated, remind the user that
// they can leave any number (phrase), potentially providing a way to leave out
// the signature as well but thats not specified, or just a 'c' (continue) to
// leave it as is or just continue to the next menu. Display the phrases by the
// given order, with a new line between each of the phrases followed by the
// signature. Prompt the user telling them that the can reorder the document if
// they like, if so start over from displaying the phrases along side a number
// to identify the phrases. They can also start this program over again if they
// like, staring from first time we get input. They may also feel like this is
// getting ridiculous and just wants to quit, so they can just pres the 'q'
// character that is on the keyboard, this will end the program.

#include <cctype>
#include <cstring>
#include <iostream>

using namespace std;

const int SIZE = 131;
const int PHRASES_SIZE = 5;

void capitalize_signature(char work_array[]);
void clean_array(int size_of_array, char clean_array[], char dirty_array[]);
void order_document(int array_size, char phrases[][SIZE]);
void get_char_array(int size_of_array, char work_array[]);
char get_punctuation();
bool is_correct_punct(char given_char);
void phrases_printer(int dis_size, char display_order[], char phrases[][SIZE]);
void run_logic();

// run the program logic and ask the user if they want to try again
int main()
{
    char user_input;

    do
    {
        run_logic();
        cout << "do you want to do this again\n (y|n) -> ";
        cin >> user_input;
        cin.ignore(1000, '\n');
    } while (tolower(user_input) != 'n');
}

// the main program logic, can be called rapidity
void run_logic()
{
    // a 2d array to collect user input
    char user_phrases[PHRASES_SIZE][SIZE];

    // another 2d array to clean the user input
    char clean_phrases[PHRASES_SIZE][SIZE];

    // the phrases exuding the signature or the last index
    int phrase_amount = PHRASES_SIZE - 1;

    cout << "pleas enter " << phrase_amount
         << " phrases\nto be organized in to a document" << endl;

    // run for all but the signature
    for (int i = 0; i < phrase_amount; ++i)
    {
        cout << "\nOn phrase number " << i + 1 << '\n' << endl;

        // fill the current array
        get_char_array(SIZE, user_phrases[i]);

        int arr_size = strlen(user_phrases[i]);
        clean_array(arr_size, clean_phrases[i], user_phrases[i]);
    }

    cout << "\n\npleas give a signature, make sure there is a coma to "
            "capitalize your name anding with punctuation."
         << endl;

    // do the same as above for the signature
    get_char_array(SIZE, user_phrases[phrase_amount]);

    int sig_size = strlen(user_phrases[phrase_amount]);
    clean_array(sig_size, clean_phrases[phrase_amount],
                user_phrases[phrase_amount]);

    // run this only on the signature
    capitalize_signature(clean_phrases[phrase_amount]);

    // send clean phrases to be ordered and printed
    order_document(PHRASES_SIZE, clean_phrases);
}

// fill an array with characters
void get_char_array(int size, char work[])
{
    char user_input = 'n';

    do
    {
        cout << "pleas enter text no more then " << size << "\n -> ";
        // take characters out of stdin, entering them in to the given array
        cin.get(work, size, '\n');
        // clear buffer of characters
        cin.ignore(1000, '\n');
        // reset the error state to receive input again
        cin.clear();
        // draw a new new line no mater what after ->, mostly for when using
        // a file as std in `./a.out < test.txt`
        cout << endl;

        cout << "the given was phrases: " << work
             << "\nis this correct (y|n) -> ";

        // skip all white space `\n,\s\t,etc` until a valid character is meat
        cin >> user_input;
        cin.ignore(1000, '\n');
        cout << endl;

        // run until the user give a Y or y  to the second input
    } while (tolower(user_input) != 'y');
}

// this will clean an array of chars according to the basic algorithm
void clean_array(int phrase_size, char clean_array[], char dirty_array[])
{
    // keep an index for the clean array
    int clean_index = 0;

    // phrase_size the length of the string so we dont iterate over garbage
    for (int i = 0; i < phrase_size; ++i)
    {
        if (i == 0)
        {
            // just make the first character upper anyway
            clean_array[0] = toupper(dirty_array[0]);
            // increment to keep up with the characters in the array
            ++clean_index;
        }
        else if (dirty_array[i] == ' ' && dirty_array[i - 1] == ' ')
        {
            // ignore any space that follows another
            continue;
        }
        // the last character of the phrase
        else if (i + 1 == phrase_size)
        {
            // add the last character to the clean_array
            clean_array[clean_index] = dirty_array[i];
            ++clean_index;

            // if the last character is not one of the specified punctuations
            if (is_correct_punct(clean_array[clean_index - 1]) == false)
            {
                // add a punctuation to the array
                clean_array[clean_index] = get_punctuation();
                ++clean_index;
            }
        }
        else
        {
            // this should just be normal characters
            clean_array[clean_index] = dirty_array[i];
            ++clean_index;
        }
    }

    // finish the array with a null terminator
    clean_array[clean_index] = '\0';
}

// capitalize all words after the `,` as they are par of a name
void capitalize_signature(char work[])
{
    // we got to th comma in the signature
    bool got_to_comma = false;

    int str_len = strlen(work);
    for (int i = 0; i < str_len; ++i)
    {
        if (',' == work[i])
        {
            got_to_comma = true;
        }

        // capitalize any character after a space
        if (' ' == work[i - 1] && got_to_comma)
        {
            work[i] = toupper(work[i]);
        }
    }
}

// ask the user for punctuation as they didn't give any
char get_punctuation()
{
    char user_input = 'n';
    char punct_char = '.';

    do
    {
        cout << "pleas give a punctuation mark\n -> ";

        cin >> punct_char;
        cin.ignore(1000, '\n');
        cin.clear();
        cout << endl;

        cout << "is this the punctuation you want " << punct_char
             << "\n (y|n) -> ";

        cin >> user_input;
        cin.ignore(1000, '\n');
    } while (tolower(user_input) != 'y');

    // return the users character
    return punct_char;
}

// true or false; if the given character is a desired punctuation character
bool is_correct_punct(char punctuation)
{
    switch (punctuation)
    {
        case '.':
        {
            return true;
        }
        case '?':
        {
            return true;
        }
        case '!':
        {
            return true;
        }
        default:
        {
            return false;
        }
    }
}

// ask the user to put the document in order and send the phrases and desired
// order to the printer
void order_document(int amount, char phrases[][SIZE])
{
    char user_input = 'n';
    const int display_order_size = 8;
    char display_order[display_order_size];

    do
    {

        int up_to_amount = amount - 1;

        cout
            << "\n\n\n\npleas order the following phrases phrases in a space "
               "separated list\nyou can leave any out if you like but can only "
               "enter 4 numbers\n "
            << endl;

        // show all the phrases and the number with which to print them
        for (int i = 0; i < up_to_amount; ++i)
        {
            cout << ' ' << i + 1 << ") -- " << phrases[i] << endl;
        }

        cout << "\n\n (e.g. 4 2 1) -> ";
        cin.get(display_order, display_order_size, '\n');
        cin.ignore(1000, '\n');
        cout << endl;

        // print the given phrases
        phrases_printer(display_order_size, display_order, phrases);

        cout << "would you like to reorder: (y|n) -> ";
        cin >> user_input;
        cin.ignore(1000, '\n');
        cout << endl;

        user_input = tolower(user_input);

        if (user_input != 'n')
        {
            // fill an array with spaces to make sure that we dont ascendantly
            // print an unwanted phrase
            fill_n(display_order, display_order_size, ' ');
        }

    } while (user_input != 'n');
}

// print the phrase according the user
void phrases_printer(int display_size, char display_order[],
                     char phrases[][SIZE])
{
    cout << "\n\n\nThe Document:\n" << endl;

    for (int i = 0; i < display_size; ++i)
    {
        // only run on numbers
        if (isdigit(display_order[i]) == 0)
        {
            continue;
        }
        else
        {
            // only match and print 1 - 4
            if (display_order[i] == '1')
            {
                cout << phrases[0] << endl;
            }
            if (display_order[i] == '2')
            {
                cout << phrases[1] << endl;
            }
            if (display_order[i] == '3')
            {
                cout << phrases[2] << endl;
            }
            if (display_order[i] == '4')
            {
                cout << phrases[3] << endl;
            }
        }
    }

    // print the signature
    cout << phrases[4] << "\n\n" << endl;
}
