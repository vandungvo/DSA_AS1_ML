#include "kNN.hpp"

//**********************************************************************
//* class Image thừa kế từ List<T>
//**********************************************************************

template <typename T>
void Image<T>::push_back(T value) {
    if (size == 0) {
        head = tail = new Node(value);
    }
    else {
        Node *tmp = new Node(value);
        tail->next = tmp;
        tail = tmp;
    }
    size++;
}

template <typename T>
void Image<T>::push_front(T value) {
    if (size == 0) {
        head = tail = new Node(value);
    }
    else {
        Node *tmp = new Node(value, head);
        head = tmp;
    }
    size++;    
}

template <typename T>
void Image<T>::insert(int index, T value) {
    if (index < 0 || index > size)
        return;
    
    if (index == 0) {
        Node* tmp = new Node(value, head);
        head = tmp;
        size++;
    } else {
        Node* current = head;
        for(int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        Node* tmp = new Node(value, current->next);
        current->next = tmp;
        size++;
    }
}

template <typename T>
void Image<T>::remove(int index) {
    if (index < 0 || index >= size)
        return;

    if (index == 0) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
        size--;
    } else {
        Node* current = head;
        for(int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        Node* tmp = current->next;
        current->next = current->next->next;
        delete tmp;
        size--;
    }
}

template <typename T>
T &Image<T>::get(int index) const {
    if (index < 0 || index >= this->size)
        throw std::out_of_range("get(): Out of range");

    Node *temp = head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return head->pointer;
}

template <typename T>
int Image<T>::length() const {
    return size;
}

template <typename T>
void Image<T>::clear() {
    Node *temp = head;
    while (temp != nullptr)
    {
        Node *next = temp->next;
        delete temp;
        temp = next;
    }
    head = tail = nullptr;
    size = 0;
}

template <typename T>
void Image<T>::print() const
{
    if (size == 0)
        OUTPUT << "nullptr" << endl;
    Node *temp = head;
    for (int i = 0; i < this->size; i++)
    {
        if (i == this->size - 1)
            OUTPUT << temp->pointer << endl;
        else
            OUTPUT << temp->pointer << " ";
        temp = temp->next;
    }
}

template <typename T>
void Image<T>::reverse() {
    Node *prev = nullptr;
    Node *current = head;
    Node *next = nullptr;
    while (current != nullptr)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

template <typename T>
void Image<T>::printStartToEnd(int start, int end) const
{
    Node *temp = head;
    for (int i = start; i < end && i < this->size; i++)
    {
        if (i == end - 1 || i == this->size - 1)
            OUTPUT << temp->pointer << endl;
        else
            OUTPUT << temp->pointer << " ";
    }
}

template <typename T>
List<T> *Image<T>::subList(int start, int end)
{

    if (this->size <= start)
        return nullptr;
    List<T> *result = new Image<T>();

    Node *temp = head;
    for (int i = 0; i < start; i++)
    {
        temp = temp->next;
    }
    for (int i = start; i < end && i < this->size; i++)
    {
        result->push_back(temp->pointer);
        temp = temp->next;
    }
    //^ gợi ý: dùng push_back
    return result;
}

template <typename T>
double Image<T>::distanceEuclidean(const List<T> *image)
{
    double distance = 0.0;
    Node *temp = head;
    for (int i = 0; i < this->size; i++)
    {
        distance += pow(temp->pointer - image->get(i), 2);
        temp = temp->next;
    }
    //^ gợi ý dùng length, get
    return sqrt(distance);
}

//**********************************************************************
//* class Dataset
//**********************************************************************

Dataset::Dataset()
{
    // TODO: implement task 2
}
Dataset::~Dataset()
{
    data->clear();
}
Dataset::Dataset(const Dataset &other)
{
    // TODO: implement task 2
}
Dataset::Dataset(List<List<int> *> *data, string *NameCol)
{
    // TODO: implement task 2
}
Dataset &Dataset::operator=(const Dataset &other)
{
    // TODO: implement task 2
    return *this;
}
bool Dataset::loadFromCSV(const char *fileName)
{
    // TODO: implement task 2
    return true;
}
void Dataset::getShape(int &nRows, int &nCols) const
{
    // TODO: implement task 2
}
void Dataset::columns() const
{
    // TODO: implement task 2
}

//**********************************************************************
//* Class kNN
//**********************************************************************

void kNN::fit(const Dataset &X_train, const Dataset &y_train)
{
    this->X_train = X_train;
    this->Y_train = y_train;
}

Dataset kNN::predict(const Dataset &X_test)
{
    // TODO: implement task 3
    return X_test;
}

double kNN::score(const Dataset &y_test, const Dataset &y_pred)
{
    // TODO: implement task
    return 0.0;
}

//**********************************************************************
//* hàm train_test_split
//**********************************************************************
void train_test_split(Dataset &X, Dataset &y, double test_size,
                      Dataset &X_train, Dataset &X_test,
                      Dataset &y_train, Dataset &y_test)
{
    // TODO: implement task 3
}
