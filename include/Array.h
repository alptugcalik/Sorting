#ifndef ARRAY_H
#define ARRAY_H



class Array{
private:
    int* numbers; // list of numbers
    int sizeN; // size of the array
    string sizeS; // size of the array as string
public:
    Array(); // constructor
    void initArray(); // method to init array
    void loadArray(); // method to load from a file
    void printArray() const; // method to print the array
    void bubbleSort() const; // sort the array using bubble sort
    void selectionSort() const; // sort the array using selection sort
    void quickSort1() const; // sort the array using quick sort1
    void quickSort2() const; // sort the array using quick sort2
    void quickSort3() const; // sort the array using quick sort3


};

#endif // ARRAY_H
