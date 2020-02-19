struct Route;

struct QNode {
    QNode();
    ~QNode();

    Route *route;
    QNode *next;
};

class Queue {
  public:
    Queue();
    ~Queue();

    bool enqueue(Route *data);
    bool dequeue(Route *&to_fill);
    bool peek(Route *&to_fill);
    bool is_empty();
    bool display();

  private:
    QNode *head;
    QNode *tail;
};

bool load_queue_from_file(char *path, Queue *&queue_one, Queue *&queue_two);
