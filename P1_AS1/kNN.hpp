
#include "main.hpp"


/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

template <typename T>
class List {
public:
    //! Hàm của thầy
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;

    //! Hàm hỗ trợ thêm
    virtual List<T>* subList(int start, int end) = 0;
    virtual void printStartToEnd(int start, int end) const = 0; 
    virtual double distanceEuclidean(const List<T>* image) = 0;
};

template <typename T>
class Image : public List<T>
{
private:
    class Node {
    public:
        T pointer;
        Node* next;
    public:
        Node(T pointer, Node* next = nullptr) : pointer(pointer), next(next) {}
    };
private:
    Node* head;
    Node* tail;
    int size;
public:
    Image() { head = tail = nullptr; size = 0; }
    ~Image() { this->clear(); }
    void push_back(T value);
    void push_front(T value);
    void insert(int index, T value);
    void remove(int index);
    T& get(int index) const;
    int length() const;
    void clear();
    void print() const;
    void reverse();
    void printStartToEnd(int start, int end) const;
    List<T>* subList(int start, int end);
    double distanceEuclidean(const List<T>* image);
};


class Dataset {
private:
    List<List<int>*>* data;
    string* NameCol;
    //You may need to define more
public:
    //! Hàm của thầy
    Dataset();
    ~Dataset();
    Dataset(List<List<int>*>* data, string* NameCol);
    Dataset(const Dataset& other);
    Dataset& operator=(const Dataset& other);
    bool loadFromCSV(const char* fileName);
    void getShape(int& nRows, int& nCols) const;
    void columns() const;




    void printHead(int nRows = 5, int nCols = 5) const
    {
        //TODO: implement task 2
    }
    void printTail(int nRows = 5, int nCols = 5) const
    {
        //TODO: implement task 2
    }
    bool drop(int axis = 0, int index = 0, std::string columns = "")
    {
        //TODO: implement task 2
        return true;
    }
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const
    {
        //TODO: implement task 2
        return *this;
    }

    int predict(const List<int>* image)
    {
        //TODO: implement task 2
        return 1;
    }
};

class kNN {
private:
    int k;
    Dataset X_train;
    Dataset Y_train;
    //You may need to define more
public:
    kNN(int k = 5):k(5){};
    void fit(const Dataset& X_train, const Dataset& y_train);
    Dataset predict(const Dataset& X_test);
    double score(const Dataset& y_test, const Dataset& y_pred);
};

void train_test_split(Dataset& X, Dataset& y, double test_size, 
                        Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test);

// Please add more or modify as needed