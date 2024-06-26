#include "kNN.hpp"

void tc1()
{
    //! Load dataset
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");

    dataset.printHead(10, 10);
    cout << endl;
    dataset.printTail(10, 10);
    cout << endl;
    int nRows, nCols;
    dataset.getShape(nRows, nCols);
    cout << "Shape: " << nRows << "x" << nCols << endl;

    //! Extract feature and label
    kNN knn;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);

    feature.getShape(nRows, nCols);
    cout << "Feature shape: " << nRows << "x" << nCols << endl;
    label.getShape(nRows, nCols);
    cout << "Label shape: " << nRows << "x" << nCols << endl;

    //! Split dataset into train and test
    Dataset X_train, X_test, y_train, y_test;
    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);

    X_train.getShape(nRows, nCols);
    cout << "X_train shape: " << nRows << "x" << nCols << endl;
    X_test.getShape(nRows, nCols);
    cout << "X_test shape: " << nRows << "x" << nCols << endl;
    y_train.getShape(nRows, nCols);
    cout << "y_train shape: " << nRows << "x" << nCols << endl;
    y_test.getShape(nRows, nCols);
    cout << "y_test shape: " << nRows << "x" << nCols << endl;

    //! Predict and evaluate
    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);
    double accuracy = knn.score(y_test, y_pred);
    
    cout << "y_pred" << endl;
    y_pred.printHead(10, 10);
    cout << endl;
    cout << "y_test" << endl;
    y_test.printHead(10, 10);
    cout << endl;
    cout << "Accuracy: " << accuracy << endl;
}

int main()
{
    tc1();
    return 0;
}