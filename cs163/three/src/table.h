// #include "house_data.h"
struct ToParse;

class HouseData;

class List;

class Table {
  public:
    Table(int size);
    ~Table();

    bool add(char *key, HouseData *to_add);
    bool get(char *key, HouseData &to_fill);
    bool display(char *key);
    bool display_all();
    bool remove(char *key, HouseData &to_fill);
    bool fill_data_from_file(char *path);

  private:
    bool parse_line_and_add_to_data(ToParse *to_parse);
    int table_size;
    List **table;
};

// a quick wrapper around an array and its size
struct ToParse {
    ToParse(int size);
    ~ToParse();
    char *source;
    int max_size;
};
