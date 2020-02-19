#include <cstring>
#include <iostream>

#include "menus.h"
#include "queue.h"
#include "stack.h"
#include "utils.h"

using namespace std;

// set up the arg action
enum ArgResult { NoArgs, ExampleFile, ArgError };

bool fuck() {
    return false;
}

// a basic arg parsing function
ArgResult parse_args(int argc, char *argv[]) {

    bool (*fun)() = fuck;

    // if only the cmd name arg is present then just return
    if (argc == 1) {
        return NoArgs;
    }

    // set up the return value
    ArgResult result = NoArgs;

    // loop from the first arg until the last or a bad arg
    for (int i = 1; i < argc && result != ArgError; ++i) {
        // if a -e is given print just the example text file
        if (strcmp(argv[i], "-e") == 0) {
            result = ExampleFile;

            // skip the separator
        } else if (strcmp(argv[i], "--")) {
            continue;

            // anything else for now is wrong
        } else {
            cerr << "bad args" << endl;

            result = ArgError;
        }
    }

    // return the arg action
    return result;
}

bool add_to_queue(Queue *&one) {
    Route *route = new Route();

    char *temp = new char[1000];

    cout << "pleas give street name:\n";
    user_input_str(temp, route->street);

    cout << "pleas give street length (e.g. 10 miles):\n";
    user_input_str(temp, route->length);

    cout << "pleas give traffic status (e.g. light traffic):\n";
    user_input_str(temp, route->traffic);

    cout << "pleas give a street note (e.g. lots of pot holes):\n";
    user_input_str(temp, route->note);

    cout << "pleas give a street construction status (e.g. light "
            "construction):\n";
    user_input_str(temp, route->construction);

    bool success = one->enqueue(route);

    delete route;
    delete[] temp;

    return success;
}

bool make_queues_by_hand(Queue *&one, Queue *&two) {
    bool success = false;

    cout << "how many routes for the first queue, (0 to 100)\n";
    int input = user_input(0, 100);

    for (int i = 0; i < input; ++i) {
        success = add_to_queue(one);
    }

    cout << "how many routes for the second queue, (0 to 100)\n";
    input = user_input(0, 100);

    for (int i = 0; i < input; ++i) {
        success = add_to_queue(two);
    }

    return success;
}

// test the stack pop function
// ignoring if the stack can no longer print (no data left)
// or if the node cant print (console error potently)
bool test_pop_stack(Stack *&stack) {
    bool success = true;
    Route *temp = new Route();

    // call peek with the allocated node
    success = stack->pop(temp);

    // if an error happened
    if (!success) {
        cout << "cant pop" << endl;
    } else {
        // show that it took a node but did not remove it
        cout << "got route:\n";
        temp->display();

        cout << "\n----------\nthe stack still has:\n";
        stack->display();
    }

    // free the local node
    delete temp;

    return success;
}

// pop the stack displaying each one but ignoring display errors as that not
// this test
bool test_pop_all_stack(Stack *&stack) {
    // make a temporary Route
    Route *temp = new Route();

    // set up loop break
    bool success = false;

    do {
        // pop the stack
        success = stack->pop(temp);

        // if pop failed say so
        if (!success) {
            cout << "cant pop stack" << endl;
        }

        // call display ignoring failures
        temp->display();

        // clear the temp node to get more data
        temp->clear();

        // keep looping while everything works
    } while (success);

    // remove the allocated node
    delete temp;

    // if stack is empty we are successful
    return stack->is_empty();
}

// test peek from the stack
bool test_stack_peek(Stack *&stack) {
    bool success = true;
    Route *temp = new Route();

    // call peek with the allocated node
    success = stack->peek(temp);

    // if an error happened
    if (!success) {
        cout << "cant peek" << endl;
    } else {
        // show that it toke a node but did remove it
        cout << "got route:\n";
        temp->display();

        cout << "\n----------\nthe stack still has:\n";
        stack->display();
    }

    // free the local node
    delete temp;

    return success;
}

// print whole stack
bool test_print_stack(Stack *&stack) {
    cout << "The stack is:\n";
    stack->display();
    return true;
}

// dequeue a queue to the stack
bool dequeue_to_stack(Queue *&queue, Stack *&stack) {
    Route *temp = new Route();

    bool success = false;

    do {
        success = queue->dequeue(temp);

        if (!success) {
            cerr << "cant dequeue" << endl;
            success = false;

        } else {
            if (!stack->push(temp)) {
                cerr << "cant add to stack" << endl;
                success = false;
            }
        }

        temp->clear();

    } while (success);

    delete temp;

    return queue->is_empty() && !stack->is_empty();
}

// prompted the user if they want to load form the default file
bool make_queues_from_file(Queue *&queue_one, Queue *&queue_two) {
    cout << "do you want to use the default file path (queue_routes.txt) or "
            "enter your own\n"
            "   1) default\n"
            "   2) enter by hand\n";

    // get a temp buffer
    char *path = new char[1000];

    // if the user selects 2
    if (user_input(1, 2) == 2) {
        cout << "enter route file path\n -> ";
        user_input_str(path);
    } else {
        // fill buffer with default text
        strcpy(path, "queue_routes.txt");
    }

    // try and load from a file
    bool success = load_queue_from_file(path, queue_one, queue_two);

    // delete temp buffer
    delete[] path;

    // return results of load_queue_from_file
    return success;
}

// print out both queues
bool print_queues(Queue *one, Queue *two) {
    cout << "First queue:\n";
    one->display();

    cout << "\nSecond queue:\n";
    two->display();

    return true;
}

// test the dequeue function
bool test_dequeue(Queue *&queue) {
    Route *to_fill = new Route();

    bool success = queue->dequeue(to_fill);

    if (!success) {
        cout << "failed to dequeue" << endl;

    } else {
        cout << "dequeue one route from the queue\nthe route is: \n";
        to_fill->display();

        cout << "\n----------\nthe queue has the following still in queue:\n";
        queue->display();
    }

    delete to_fill;

    return success;
}

// test the dequeue function but dequeueing all data
bool test_dequeue_all(Queue *&queue) {
    Route *to_fill = new Route();

    bool success = false;

    do {
        success = queue->dequeue(to_fill);
        cout << "\ndequeued this route:\n";

        to_fill->display();

        delete to_fill;
        to_fill = new Route();

    } while (success);

    cout << "\n----------\nthe queue is now empty, will try and display anyway "
            "to "
            "see\n";

    if (!queue->display()) {
        cout << "no more data in queue" << endl;
    }

    delete to_fill;

    return success;
}

// test peeking the queue
bool test_peek_queue(Queue *queue) {
    Route *to_fill = new Route();
    bool success = true;

    success = queue->peek(to_fill);

    if (!success) {
        cout << "cant peek" << endl;
    } else {
        cout << "got route:\n";
        to_fill->display();

        cout << "\n----------the queue still has:\n";
        queue->display();
    }

    delete to_fill;

    return success;
}

// run the corresponding function for the given TestAction
bool action_dispatch(TestAction action, Queue *&one, Queue *&two,
                     Stack *&stack) {
    // I'm not entirely sure but i dont think c++ will allow NULL references but
    // a check here should save a check every where else
    if (!one || !two || !stack) {
        return false;
    }

    // match the given action
    switch (action) {
        case LoadFromFile: {
            // dont bother with break
            return make_queues_from_file(one, two);
        }
        case EnterByHand: {
            return make_queues_by_hand(one, two);
        }
        case PrintQueues: {
            return print_queues(one, two);
        }
        case PrintStack: {
            return test_print_stack(stack);
        }
        case DequeueOne: {
            return test_dequeue(one);
        }
        case DequeueTwo: {
            return test_dequeue(two);
        }
        case DequeueAllOne: {
            return test_dequeue_all(one);
        }
        case DequeueAllTwo: {
            return test_dequeue_all(two);
        }
        case DequeueOneToStack: {
            return dequeue_to_stack(one, stack);
        }
        case DequeueTwoToStack: {
            return dequeue_to_stack(two, stack);
        }
        case PopStack: {
            return test_pop_stack(stack);
        }
        case PopAllStack: {
            return test_pop_all_stack(stack);
        }
        case PeekOne: {
            return test_peek_queue(one);
        }
        case PeekTwo: {
            return test_peek_queue(two);
        }
        case PeekStack: {
            return test_stack_peek(stack);
        }
        case Nothing: {
            // just keep going if in a menu
            return true;
        }
        default: {
            // anything else is probably an error
            return false;
        }
    }
    // <- unreachable due to default
}

int main(int argc, char *argv[]) {
    ArgResult result = parse_args(argc, argv);

    if (result == ExampleFile) {
        file_text();
        return 0;
    } else if (result == ArgError) {
        return 1;
    }

    Queue *main_q_one = new Queue();
    Queue *main_q_two = new Queue();
    Stack *main_s = new Stack(5);

    main_menu(action_dispatch, main_q_one, main_q_two, main_s);

    delete main_q_one;
    delete main_q_two;
    delete main_s;

    return 0;
}
