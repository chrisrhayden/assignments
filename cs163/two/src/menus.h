class Queue;
class Stack;

// sigh i just want rust enums
enum TestAction {
    LoadFromFile,
    EnterByHand,
    PrintQueues,
    PrintStack,
    DequeueOne,
    DequeueTwo,
    DequeueAllOne,
    DequeueAllTwo,
    DequeueOneToStack,
    DequeueTwoToStack,
    PopStack,
    PopAllStack,
    PeekOne,
    PeekTwo,
    PeekStack,
    Nothing,
    Quit,
    Error
};

typedef bool (*ActionFunc)(TestAction, Queue *&, Queue *&, Stack *&);

struct Data {
    Data();
    Queue *&one;
    Queue *&two;
    Stack *&stack;
};

TestAction load_menu();
TestAction queue_menu(ActionFunc callback, Queue *&one, Queue *&two,
                      Stack *&stack);
TestAction stack_menu(ActionFunc callback, Queue *&one, Queue *&two,
                      Stack *&stack);
TestAction test_menu(ActionFunc callback, Queue *&one, Queue *&two,
                     Stack *&stack);
bool main_menu(ActionFunc callback, Queue *&one, Queue *&two, Stack *&stack);
int print_main_menu();
int print_queue_menu();
int print_test_menu();
void example_file();
void file_text();
