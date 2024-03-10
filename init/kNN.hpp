#include "main.hpp"

template <typename T>
class List
{
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T &get(int index) const = 0;
    virtual int length() const = 0;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
    virtual List<T> *subList(int start, int end) = 0;
    virtual void printStartToEnd(int start, int end) const = 0;
};

class Dataset
{
private:
    List<List<int> *> *data;
    List<string> *nameCol;
public:
    Dataset();
    ~Dataset();
    Dataset(const Dataset &other);
    Dataset &operator=(const Dataset &other);
    List<List<int> *> *getData() const;
    bool loadFromCSV(const char *fileName);
    void getShape(int &nRows, int &nCols) const;
    void columns() const;
    void printHead(int nRows = 5, int nCols = 5) const;
    void printTail(int nRows = 5, int nCols = 5) const;
    bool drop(int axis = 0, int index = 0, std::string columns = "");
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const;
    double distanceEuclidean(const List<int> *a, const List<int> *b) const;
    Dataset predict(const Dataset &X_train, const Dataset &Y_train, const int k) const;
    double score(const Dataset &y_predict) const;
};

class kNN
{
private:
    int k;
    Dataset X_train;
    Dataset Y_train;
public:
    kNN(int k = 5) : k(k){};
    void fit(const Dataset &X_train, const Dataset &y_train);
    Dataset predict(const Dataset &X_test);
    double score(const Dataset &y_test, const Dataset &y_pred);
};

void train_test_split(Dataset &X, Dataset &Y, double test_size, Dataset &X_train, Dataset &X_test, Dataset &Y_train, Dataset &Y_test);
