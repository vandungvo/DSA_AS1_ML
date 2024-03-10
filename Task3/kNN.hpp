#include "main.hpp"

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
};

//
// class Image
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
    Image()
    {
        head = tail = nullptr;
        size = 0;
    }
    ~Image()
    {
        this->clear();
    }
    void push_back(T value)
    {
        Node *newNode = new Node(value);
        if (size == 0)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    void push_front(T value)
    {
        Node *newNode = new Node(value);
        if (size == 0)
        {
            head = tail = newNode;
        }
        else
        {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }
    void insert(int index, T value)
    {
        if (index < 0 || index > size)
        {
            return;
        }
        if (index == 0)
        {
            push_front(value);
        }
        else if (index == size)
        {
            push_back(value);
        }
        else
        {
            Node *current = head;
            for (int i = 0; i < index - 1; i++)
            {
                current = current->next;
            }
            Node *newNode = new Node(value, current->next);
            current->next = newNode;
            size++;
        }
    }
    void remove(int index)
    {
        if (index < 0 || index >= size)
        {
            return;
        }
        Node *delNode = head;
        if (size == 1)
        {
            head = tail = nullptr;
        }
        else if (index == 0)
        {
            delNode = head;
            head = head->next;
        }
        else
        {
            Node *pre = head;
            for (int i = 0; i < index - 1; i++)
            {
                pre = pre->next;
            }
            delNode = pre->next;
            pre->next = delNode->next;
            if (index == size - 1)
            {
                tail = pre;
            }
        }
        delete delNode;
        size--;
    }
    T &get(int index) const
    {
        if (index < 0 || index >= this->size)
            throw std::out_of_range("get(): Out of range");
        Node *current = head;
        for (int i = 0; i < index; i++)
            current = current->next;
        return current->pointer;
    }
    int length() const
    {
        return size;
    }
    void clear()
    {
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
    void print() const
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
    void reverse()
    {
        Node *prev = nullptr;
        Node *current = head;
        Node *next = nullptr;
        tail = head;
        while (current != nullptr)
        {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }
    void printStartToEnd(int start, int end) const
    {
        // TODO: có chỉnh
        Node *temp = head;
        for (int i = 0; i < start; i++)
            temp = temp->next;
        for (int i = start; i < end && i < this->size; i++)
        {
            if (i == end - 1 || i == this->size - 1)
                OUTPUT << temp->pointer << endl;
            else
                OUTPUT << temp->pointer << " ";
            temp = temp->next;
        }
    }
    List<T> *subList(int start, int end)
    {
        Image<T> *result = new Image<T>();
        Node *temp = head;
        for (int i = 0; i < start; i++)
            temp = temp->next;
        for (int i = start; i < end && i < this->size; i++)
        {
            result->push_back(temp->pointer);
            temp = temp->next;
        }
        return result;
    }
};

class Dataset
{
private:
    List<List<int> *> *data;
    List<string> *nameCol;
    // You may need to define more
public:
    //! Hàm khởi tạo
    Dataset()
    {
        this->nameCol = new Image<string>();
        this->data = new Image<List<int> *>();
    }
    //! Hàm hủy
    ~Dataset()
    {
        delete data;
        delete nameCol;
    }
    Dataset(const Dataset &other)
    {
        if (other.data->length())
        {
            this->nameCol = new Image<string>();
            this->nameCol = other.nameCol->subList(0, other.nameCol->length());
            int nRows, nCols;
            other.getShape(nRows, nCols);
            this->data = new Image<List<int> *>();
            for (int i = 0; i < nRows; i++)
            {
                List<int> *temp = other.data->get(i)->subList(0, nCols);
                this->data->push_back(temp);
            }
        }
    }
    Dataset &operator=(const Dataset &other)
    {
        if (other.data->length())
        {
            this->nameCol = new Image<string>();
            this->nameCol = other.nameCol->subList(0, other.nameCol->length());
            int nRows, nCols;
            other.getShape(nRows, nCols);
            this->data = new Image<List<int> *>();
            for (int i = 0; i < nRows; i++)
            {
                List<int> *temp = other.data->get(i)->subList(0, nCols);
                this->data->push_back(temp);
            }
        }
        return *this;
    }
    List<List<int> *> *getData() const
    {
        // ! UPDATE file thay
        return data;
    }
    bool loadFromCSV(const char *fileName)
    {
        ifstream file(fileName);
        if (file.is_open())
        {
            string str;
            int number;

            //* xử lý hàng đầu tiên chuyển , thành ' ' dùng thư viện stringstream
            file >> str;
            for (int i = 0; i < str.length(); i++)
            {
                if (str[i] == ',')
                    str[i] = ' ';
            }
            stringstream ss(str);
            while (ss >> str)
                nameCol->push_back(str);

            //* xử lý các hàng còn lại , thành ' ' dùng thư viện stringstream
            while (file >> str)
            {
                for (int i = 0; i < str.length(); i++)
                {
                    if (str[i] == ',')
                        str[i] = ' ';
                }
                stringstream ss(str);
                List<int> *temp = new Image<int>();
                while (ss >> number)
                    temp->push_back(number);
                data->push_back(temp);
            }
            return true;
        }
        return false;
    }
    void getShape(int &nRows, int &nCols) const
    {
        nRows = this->data->length();
        if (nRows)
            nCols = this->data->get(0)->length();
    }
    void columns() const
    {
        this->nameCol->printStartToEnd(0, this->nameCol->length());
    }
    void printHead(int nRows = 5, int nCols = 5) const
    {
        if (nRows <= 0 || nCols <= 0)
            return;
        int mRows = this->data->length();
        int mCols;
        if (mRows)
            mCols = this->data->get(0)->length();
        if (nRows > mRows)
            nRows = mRows;
        if (nCols > mCols)
            nCols = mCols;

        if (mRows)
            this->nameCol->printStartToEnd(0, nCols);
        for (int i = 0; i < nRows; i++)
        {
            this->data->get(i)->printStartToEnd(0, nCols);
        }
    }
    void printTail(int nRows = 5, int nCols = 5) const
    {
        if (nRows <= 0 || nCols <= 0)
            return;
        int mRows = this->data->length();
        int mCols = this->nameCol->length();
        if (nRows > mRows)
            nRows = mRows;
        if (nCols > mCols)
            nCols = mCols;

        if (mRows)
            this->nameCol->printStartToEnd(mCols - nCols, mCols);
        for (int i = mRows - nRows; i < mRows; i++)
        {
            this->data->get(i)->printStartToEnd(mCols - nCols, mCols);
        }
    }
    bool drop(int axis = 0, int index = 0, std::string columns = "")
    {
        int nRows = this->data->length();
        if (!nRows)
            return false;
        if (axis == 0)
        {
            if (index >= nRows || index < 0)
                return false;
            this->data->remove(index);
            return true;
        }
        else if (axis == 1)
        {
            int nCols = this->nameCol->length();
            int index = -1;
            for (int i = 0; i < nCols; i++)
            {
                if (this->nameCol->get(i) == columns)
                {
                    index = i;
                    break;
                }
            }
            if (index == -1)
                return false;
            this->nameCol->remove(index);
            for (int i = 0; i < nRows; i++)
            {
                this->data->get(i)->remove(index);
            }
            return true;
        }
        return false;
    }
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const
    {
        Dataset result;
        int nRows, nCols;
        this->getShape(nRows, nCols);
        if (endRow == -1)
            endRow = nRows - 1;
        else if (endRow >= nRows)
            endRow = nRows - 1;
        if (endCol == -1)
            endCol = nCols;
        else if (endCol > nCols)
            endCol = nCols;
        if (startCol == endCol)
            endCol = startCol + 1;
        if (startRow > endRow || startCol > endCol)
            return Dataset();
        result.nameCol = this->nameCol->subList(startCol, this->nameCol->length());
        for (int i = startRow; i <= endRow; i++)
        {
            List<int> *temp = this->data->get(i)->subList(startCol, endCol);
            result.data->push_back(temp);
        }
        if (result.data->length() == 0 || result.data->get(0)->length() == 0)
            return Dataset();
        return result;
    }

    double distanceEuclidean(const List<int> *a, const List<int> *b) const
    {
        double distance = 0.0;
        for (int i = 0; i < a->length(); i++)
        {
            distance += pow(a->get(i) - b->get(i), 2);
        }
        return sqrt(distance);
    }

    Dataset predict(const Dataset &X_train, const Dataset &Y_train, const int k) const
    {
        if (X_train.data->length() == 0 || Y_train.data->length() == 0 || this->data->length() == 0)
            return Dataset();
        Dataset result;
        result.nameCol = Y_train.nameCol->subList(0, Y_train.nameCol->length());
        int nRows = this->data->length();
        for (int i = 0; i < nRows; i++)
        {
            double distance[X_train.data->length()][2];
            int X_trainRows = X_train.data->length();
            for (int j = 0; j < X_trainRows; j++)
            {
                distance[j][0] = distanceEuclidean(this->data->get(i), X_train.data->get(j));
                distance[j][1] = Y_train.data->get(j)->get(0);
            }
       
            for (int i = 0; i < X_trainRows - 1; i++) {
                for (int j = 0; j < X_trainRows - i - 1; j++) {
                    if (distance[j][0] > distance[j + 1][0]) {
                        swap(distance[j], distance[j + 1]);
                    }
                }
            }

            double kNearest[k][2];
            for (int r = 0; r < k; r++)
            {
                kNearest[r][0] = distance[r][0];
                kNearest[r][1] = distance[r][1];
            }
            int count[10] = {0};
            for (int r = 0; r < k; r++)
            {
                count[(int)kNearest[r][1]]++;
            }
            int max = 0;
            for (int r = 1; r < 10; r++)
            {
                if (count[r] > count[max])
                    max = r;
            }
            List<int> *label = new Image<int>();
            label->push_back(max);
            result.data->push_back(label);
        }
        return result;
    }
    double score(const Dataset &y_predict) const
    {
        int nRows = this->data->length();
        int y_predictRows = y_predict.data->length();
        if (nRows == 0 || y_predictRows == 0)
            return -1;
        if (nRows != y_predictRows)
            return -1;
        int count = 0;
        for (int i = 0; i < nRows; i++)
        {
            if (this->data->get(i)->get(0) == y_predict.data->get(i)->get(0))
                count++;
        }
        return (double)count / nRows;
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
    kNN(int k = 5) : k(k){};
    void fit(const Dataset &X_train, const Dataset &y_train)
    {
        int nRows, nCols;
        X_train.getShape(nRows, nCols);
        if (k > nRows)
            k = nRows;
        this->X_train = X_train;
        this->Y_train = y_train;
    }
    Dataset predict(const Dataset &X_test)
    {
        return X_test.predict(this->X_train, this->Y_train, this->k);
    }
    double score(const Dataset &y_test, const Dataset &y_pred)
    {
        return y_test.score(y_pred);
    }
};

void train_test_split(Dataset &X, Dataset &Y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &Y_train, Dataset &Y_test)
{
    if (test_size >= 1 || test_size <= 0)
    {
        return;
    }

    //* phân chia phần train
    int xRows, xCols, yRows, yCols;
    X.getShape(xRows, xCols);
    Y.getShape(yRows, yCols);

    X_train = X.extract(0, (1 - test_size) * xRows, 0, -1);

    Y_train = Y.extract(0, (1 - test_size) * yRows, 0, 0);

    //* phân chia phần test

    X_test = X.extract((1 - test_size) * xRows + 1, xRows, 0, -1);

    Y_test = Y.extract((1 - test_size) * yRows + 1, yRows, 0, 0);
}

// Please add more or modify as needed