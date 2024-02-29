
#include "main.hpp"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

template <typename T>
class List
{
public:
    //! Hàm của thầy
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

    //! Hàm hỗ trợ thêm
    virtual List<T> *subList(int start, int end) = 0;
    virtual void printStartToEnd(int start, int end) const = 0;
    virtual double distanceEuclidean(const List<T> *image) = 0;
};

template <typename T>
class Image : public List<T>
{
private:
    class Node
    {
    public:
        T pointer;
        Node *next;

    public:
        Node(T pointer, Node *next = nullptr) : pointer(pointer), next(next) {}
    };

private:
    Node *head;
    Node *tail;
    int size;

public:
    Image() : head(nullptr), tail(nullptr), size(0) {}
    ~Image() { 
        this->clear(); 
    }
    void push_back(T value) {
        Node *newNode = new Node(value);
        if (size == 0) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    void push_front(T value)
    {
        Node *newNode = new Node(value);
        if (size == 0) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }
    void insert(int index, T value) {
        if (index < 0 || index > size) {
            return;
        }
        if (index == 0) {
            push_front(value);
        }
        else if (index == size) {
            push_back(value);
        }
        else {
            Node *current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }
            Node *newNode = new Node(value, current->next);
            current->next = newNode;
            size++;
        }
    }
    void remove(int index) {
        if (index < 0 || index >= size) {
            return;
        }
        Node *delNode = head;
        if (size == 1) {
            head = tail = nullptr;
        }
        else if (index == 0) {
            delNode = head;
            head = head->next;
        }
        else {
            Node *pre = head;
            for (int i = 0; i < index - 1; i++)
            {
                pre = pre->next;
            }
            delNode = pre->next;
            pre->next = delNode->next;
            if (index == size - 1) {
                tail = pre;
            }
        }
        delete delNode;
        size--;
    }
    T &get(int index) const {
        if (index < 0 || index >= this->size) {
            throw std::out_of_range("get(): Out of range");
        }
        else {
            Node *current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            return current->pointer;
        }
    }
    int length() const {
        return size;
    }
    void clear() {
        Node *temp = head;
        while (temp != nullptr) {
            Node *next = temp->next;
            delete temp;
            temp = next;
        }
        head = tail = nullptr;
        size = 0;
    }
    void print() const {
        if (size == 0) {
            OUTPUT << "nullptr" << endl;
        }
        Node *temp = head;
        for (int i = 0; i < this->size; i++) {
            if (i == this->size - 1) {
                OUTPUT << temp->pointer << endl;
            }
            else {
                OUTPUT << temp->pointer << " ";
            }
            temp = temp->next;
        }
    }
    void reverse() {
        Node *prev = nullptr;
        Node *current = head;
        Node *next = nullptr;
        tail = head;
        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }
    void printStartToEnd(int start, int end) const {
        Node *temp = head;
        for (int i = start; i < end && i < this->size; i++) {
            if (i == end - 1 || i == this->size - 1) {
                OUTPUT << temp->pointer << endl;
            }
            else {
                OUTPUT << temp->pointer << " ";
            }
        }
    }
    List<T> *subList(int start, int end) {
        if (this->size <= start) {
            return nullptr;
        }
        if (end > size) {
            end = size;
        }
        List<T> *result = new Image<T>();
        for (int i = start; i < end; i++) {
            result->push_back(this->get(i));
        }
        return result;
    }
    double distanceEuclidean(const List<T> *image) {
        double distance = 0.0;
        int length = image->length();
        int index = size > length ? size : length;
        for (int i = 0; i < index; i++) {
            int data, idata;
            if (i >= size) {
                data = 0;
            }
            else {
                data = this->get(i);
            }
            if (i >= length) {
                idata = 0;
            }
            else {
                idata = image->get(i);
            }
            distance += pow(data - idata, 2);
        }
        return sqrt(distance);
    }
};

class Dataset
{
private:
    List<List<int> *> *data;
    string *NameCol;
    // You may need to define more
public:
    //! Hàm của thầy
    Dataset();
    ~Dataset();
    Dataset(List<List<int> *> *data, string *NameCol);
    Dataset(const Dataset &other);
    Dataset &operator=(const Dataset &other);
    bool loadFromCSV(const char *fileName);
    void getShape(int &nRows, int &nCols) const;
    void columns() const;

    void printHead(int nRows = 5, int nCols = 5) const
    {
        // TODO: implement task 2
    }
    void printTail(int nRows = 5, int nCols = 5) const
    {
        // TODO: implement task 2
    }
    bool drop(int axis = 0, int index = 0, std::string columns = "")
    {
        // TODO: implement task 2
        return true;
    }
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const
    {
        // TODO: implement task 2
        return *this;
    }

    int predict(const List<int> *image)
    {
        // TODO: implement task 2
        return 1;
    }
};

class kNN
{
private:
    int k;
    Dataset X_train;
    Dataset Y_train;
    // You may need to define more
public:
    kNN(int k = 5) : k(5){};
    void fit(const Dataset &X_train, const Dataset &y_train);
    Dataset predict(const Dataset &X_test);
    double score(const Dataset &y_test, const Dataset &y_pred);
};

void train_test_split(Dataset &X, Dataset &y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &y_train, Dataset &y_test);

// Please add more or modify as needed