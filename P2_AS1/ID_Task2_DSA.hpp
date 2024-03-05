
#include "main.hpp"


template<typename T>
class List {
public:
    //! Hàm của thầy
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0 ;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;

    //! Hàm hỗ trợ thêm
    virtual List<T>* subList(int start, int end) = 0;
    virtual void printStartToEnd(int start, int end) const = 0; 
};

// 
// class Image 
template<typename T>
class Image : public List<T>
{
private:
    class Node{
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
    Image(){
        head = tail = nullptr;
        size = 0;
    }
    ~Image(){
        this->clear();
    }
    void push_back(T value){
        //TODO: implement task 1
    }
    void push_front(T value){
        //TODO: implement task 1 
    }
    void insert(int index, T value){
        //TODO: implement task 1
    }
    void remove(int index){
        //TODO: implement task 1
    }
    T& get(int index) const{
        //TODO: implement task 1
    }
    int length() const{
        return size;
    }
    void clear(){
        //TODO: implement task 1
    }
    void print() const{
        if(size == 0) OUTPUT << "nullptr" << endl;
        Node* temp = head;
        for(int i = 0; i < this->size; i++)
        {
            if(i == this->size - 1) OUTPUT << temp->pointer << endl;
            else OUTPUT << temp->pointer << " ";
            temp = temp->next;
        }
    }
    void reverse(){  
        //TODO: implement task 1
    }
    void printStartToEnd(int start, int end) const{
        //TODO: có chỉnh
        Node* temp = head;
        for(int i = 0; i < start; i++) temp = temp->next;
        for(int i = start; i < end && i < this->size; i++)
        {
            if(i == end - 1 || i == this->size - 1) OUTPUT << temp->pointer << endl;
            else OUTPUT << temp->pointer << " ";
            temp = temp->next;
        }
    } 
    List<T>* subList(int start, int end){
        //TODO: implement task 1
    }
};




class Dataset {
private:
    List<List<int>*>* data;
    List<string>* nameCol;
    //You may need to define more
public:
    //! Hàm khởi tạo
    Dataset()
    {
        this->nameCol = new Image<string>();
        this->data = new Image<List<int>*>();
    }
    //! Hàm hủy
    ~Dataset()
    {
        delete data;
        delete nameCol;
    }
    Dataset(const Dataset& other)
    {
        this->nameCol = new Image<string>();
        this->data = new Image<List<int>*>();
        //TODO: implement Task 2
    }
    Dataset& operator=(const Dataset& other)
    {
        //TODO: implement Task 2
        return *this;
    }
    bool loadFromCSV(const char* fileName)
    {   
        ifstream file(fileName);
        //* kiểm tra mở file
        if(file.is_open())
        {
            string str;
            int number;

            //* xử lý hàng đầu tiên chuyển , thành ' ' dùng thư viện stringstream
            file >> str;
            for (int i = 0; i < str.length(); i++) {
                if (str[i] == ',') str[i] = ' ';
            }
            stringstream ss(str);  
            while(ss >> str) nameCol->push_back(str);

             //* xử lý các hàng còn lại , thành ' ' dùng thư viện stringstream
            while(file >> str)
            {
                for (int i = 0; i < str.length(); i++) {
                    if (str[i] == ',') str[i] = ' ';
                }
                stringstream ss(str);  
                List<int>* temp = new Image<int>();
                while(ss >> number) temp->push_back(number);
                data->push_back(temp);
            }
            return true;
        }
        return false;
    }
    void getShape(int& nRows, int& nCols) const
    {
        //TODO: implement Task 2
    }
    void columns() const
    {
        //TODO: implement Task 2
    }
    void printHead(int nRows = 5, int nCols = 5) const
    {
        if(nRows <= 0 || nCols <= 0) return;
        //TODO: implement Task 2

    }
    void printTail(int nRows = 5, int nCols = 5) const
    {
        if(nRows <= 0 || nCols <= 0)  return;
        //TODO: implement Task 2
    }
    bool drop(int axis = 0, int index = 0, std::string columns = "")
    {
        //TODO: implement Task 2
        return false;
    }
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const
    {
        //TODO: implement Task 2
    }


    double distanceEuclidean(const List<int>* x, const List<int>* y) const{
        //TODO: implement Task 2 copy code từ implement Task 1 chỉnh
    }


    Dataset predict(const Dataset& X_train, const Dataset& Y_train, const int k) const
    {
       //TODO: implement Task 3 
       return Dataset();
    }
    double score(const Dataset& y_test) const
    {   
        //TODO: implement Task 3 
        return -1;
    }
};

class kNN {
private:
    int k;
    Dataset X_train;
    Dataset Y_train;
    //You may need to define more
public:
    kNN(int k = 5):k(k){};
    void fit(const Dataset& X_train, const Dataset& y_train)
    {
        this->X_train = X_train;
        this->Y_train = y_train;
    }
    Dataset predict(const Dataset& X_test)
    { 
        return X_test.predict(this->X_train, this->Y_train, this->k);
    }
    double score(const Dataset& y_test, const Dataset& y_pred)
    {   
        return y_test.score(y_pred);
    }
};

void train_test_split(Dataset& X, Dataset& Y, double test_size, 
                        Dataset& X_train, Dataset& X_test, Dataset& Y_train, Dataset& Y_test)
{
    //* phân chia X
    int nRowsX, nColsX;
    X.getShape(nRowsX, nColsX);
    X_train = X.extract(0, test_size * nRowsX, 0, -1);
    X_test = X.extract(test_size * nRowsX, -1 , 0, -1);

    //* phân chia Y
    int nRowsY, nColsY;
    Y.getShape(nRowsY, nColsY);
    Y_train = Y.extract(0, test_size * nRowsY, 0, -1);
    Y_test = Y.extract(test_size * nRowsY, -1 , 0, -1);
}

// Please add more or modify as needed