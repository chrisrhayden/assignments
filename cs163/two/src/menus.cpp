#include <iostream>

#include "menus.h"
#include "queue.h"
#include "stack.h"
#include "utils.h"

using namespace std;

void file_text() {
    std::cout << "street 1$10 miles$light traffic$its a cool street$light "
                 "construction\n"
                 "street 2$20 miles$heavy traffic$note$no construction\n"
                 "-----\n"
                 "street 3$30 miles$no traffic$note$no construction\n"
                 "street 4$40 miles$light traffic$note$heavy construction\n";
}

void example_file() {
    cout << "\n\nThe default file name is queue_routes.txt\nThe route "
            "file is delimited by '$' with each street on its own "
            "line\nEach queue separated by 5 -'s like '-----'\nThe file "
            "needs both queues to work\nThe route file should look "
            "like\n\n";
    file_text();
    cout << endl;
}

TestAction load_menu() {
    cout << "\nLoad date to the queues\n"
            "   1) quit\n"
            "   2) return to last menu\n"
            "   3) load route queues from file\n"
            "   4) enter route queues by hand (fill two queues)\n ";

    int input = user_input(1, 4);

    if (input == 1) {
        return Quit;
    } else if (input == 2) {
        return Nothing;
    } else if (input == 3) {
        return LoadFromFile;
    } else if (input == 4) {
        return EnterByHand;
    } else {
        return Error;
    }
}

int print_queue_menu() {
    cout << "\nTest the queues on there own\n"
            "   1) quit\n"
            "   2) return to last menu\n"
            "   3) print both queues\n"
            "   4) peek first queue\n"
            "   5) peek second queue\n"
            "   6) dequeue one from first queue\n"
            "   7) dequeue one from second queue\n"
            "   8) dequeue all from first queue\n"
            "   9) dequeue all from second queue\n";

    return user_input(1, 9);
}

TestAction queue_menu(ActionFunc callback, Queue *&one, Queue *&two,
                      Stack *&stack) {
    TestAction action = Nothing;

    int input = 1;

    do {
        input = print_queue_menu();

        if (input == 1) {
            action = Quit;
        } else if (input == 2) {
            action = Nothing;
        } else if (input == 3) {
            action = PrintQueues;
        } else if (input == 4) {
            action = PeekOne;
        } else if (input == 5) {
            action = PeekTwo;
        } else if (input == 6) {
            action = DequeueOne;
        } else if (input == 7) {
            action = DequeueTwo;
        } else if (input == 8) {
            action = DequeueAllOne;
        } else if (input == 9) {
            action = DequeueAllTwo;
        }

        if (!callback(action, one, two, stack)) {
            action = Error;
        }

    } while (action != Quit && action != Error && action != Nothing);

    return action;
}

TestAction stack_menu(ActionFunc callback, Queue *&one, Queue *&two,
                      Stack *&stack) {
    cout << "The stack menu:\n"
            "   1) quit\n"
            "   2) return to last menu\n"
            "   3) print the stack\n"
            "   4) peek stack\n"
            "   5) pop the stack\n"
            "   6) pop the whole stack\n";

    int input = user_input(1, 3);

    TestAction action = Nothing;

    if (input == 1) {
        action = Quit;
    } else if (input == 2) {
        action = Nothing;
    } else if (input == 3) {
        action = PrintStack;
    } else if (input == 4) {
        action = PeekStack;
    } else if (input == 5) {
        action = PopStack;
    } else if (input == 6) {
        action = PopAllStack;
    }

    return action;
}

int print_test_menu() {
    cout << "\nTest the data structures ether together from here on on "
            "there own in the specific menus\n"
            "   1) quit\n"
            "   2) return to previous menu\n"
            "\n"
            "   -- menus\n"
            "   3) test queues menu\n"
            "   4) test stack menu\n"
            "\n"
            "   -- test\n"
            "   5) print both queues\n"
            "   6) print the stack\n"
            "   7) dequeue first queue to the stack\n"
            "   8) dequeue second queue to the stack\n"
            "   9) pop the whole stack\n";

    return user_input(1, 9);
}

TestAction test_menu(ActionFunc callback, Queue *&one, Queue *&two,
                     Stack *&stack) {
    if (one->is_empty()) {
        cout << "\nno data yet\n" << endl;
        return Nothing;
    }

    int input = 1;

    TestAction action = Nothing;

    bool loop = true;

    do {

        input = print_test_menu();

        if (input == 1) {
            action = Quit;
        } else if (input == 2) {
            action = Nothing;
            loop = false;
        } else if (input == 3) {
            action = queue_menu(callback, one, two, stack);
        } else if (input == 4) {
            action = stack_menu(callback, one, two, stack);
        } else if (input == 5) {
            action = PrintQueues;
        } else if (input == 6) {
            action = PrintStack;
        } else if (input == 7) {
            action = DequeueOneToStack;
        } else if (input == 8) {
            action = DequeueTwoToStack;
        } else if (input == 9) {
            action = PopStack;
        }

        if (action != Quit && action != Error) {
            if (!callback(action, one, two, stack)) {
                action = Error;
            }
        }

    } while (loop && action != Quit && action != Error);

    return action;
}

int print_main_menu() {
    cout << "\nmain menu\n"
            "   1) quit\n"
            "   2) print example file\n"
            "   3) load menu\n"
            "   4) test menu\n";

    return user_input(1, 4);
}

// print the main menu and call the sub menus
// i tried very hard to make this a struct with references but i guess
// instantiating structs like Data data = Data{one, two, struct};
// is a c++11 only thing
bool main_menu(ActionFunc callback, Queue *&one, Queue *&two, Stack *&stack) {
    cout << "welcome to the route picker thing\nPleas make use of the load "
            "from file feature\nuse the example option to print an "
            "example file to use as a template\n    (or try ./a.out -e > "
            "queue_routes.txt)\n\n";

    int user_input = 1;
    TestAction action = Nothing;

    do {
        user_input = print_main_menu();

        if (user_input == 1) {
            action = Quit;
        } else if (user_input == 2) {
            example_file();
        } else if (user_input == 3) {
            action = load_menu();
        } else if (user_input == 4) {
            action = test_menu(callback, one, two, stack);
        }

        if (action != Nothing && action != Quit && action != Error) {
            if (!callback(action, one, two, stack)) {
                action = Error;
            }
        }

    } while (action != Quit && action != Error);

    if (action == Error) {
        return false;
    } else {
        return true;
    }
}
