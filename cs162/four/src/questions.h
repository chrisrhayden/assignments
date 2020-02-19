const int FIELD_SIZE = 1000;

class Question {
  public:
    Question();

    void read_in_question(int number);
    void display();
    bool compare_subject(char to_compare[]);

  private:
    int question_num;
    char subject[FIELD_SIZE];
    char text[FIELD_SIZE];
    char date_completed[FIELD_SIZE];
};

class QuestionList {
  public:
    QuestionList();
    ~QuestionList();
    void read_in_all_questions();
    void display_all();
    void display_type(char to_match[]);

  private:
    Question *list;
    int length;
    int max_length;
};
