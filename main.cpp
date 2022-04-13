#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

#define CUT_OFF 5 // cut off for my sorting algorithm


// global variables for data comparisons
    int compBubble; // number of comparisons for bubble sort
    int compSelect; // number of comparisons for selection sort
    int compQuick1; // number of comparisons for quick sort 1
    int compQuick2; // number of comparisons for quick sort 2
    int compQuick3; // number of comparisons for quick sort 3
    int compQuick4; // number of comparisons for quick sort 4
    int compMySort; // number of comparisons for my sort
    int movsBubble; // number of moves for bubble sort
    int movsSelect; // number of moves for selection sort
    int movsQuick1; // number of moves for quick sort 1
    int movsQuick2; // number of moves for quick sort 2
    int movsQuick3; // number of moves for quick sort 3
    int movsQuick4; // number of moves for quick sort 4
    int movsMySort; // number of moves for my sort

// IMPORTANT NOTE
// (100000/sizeN) represents the number of iterations to find the computation time for sorting algorithms
// when size gets large, since the computation time becomes larger, less loop is required.
// otherwise, more loop is required.

// swap function
template <class T>
void Swap (T& x, T& y ){
    T temp;
    temp = x;
    x = y;
    y = temp;
}

// BUBBLE SORT
template <class T>
void BubbleSort(T A[],int n){
    int i,j;
    int lastExchangeIndex; // index of last change
    i = n-1; // index of last element
    while(i>0){
        lastExchangeIndex = 0;
        for(j=0;j<i;j++){
            compBubble++; // increase the data comparison amount
            if(A[j+1] < A[j]){
                Swap(A[j], A[j+1]); // swap the 2 elements
                movsBubble++; // increase the data move amount
                lastExchangeIndex = j; // change the last exchange index
            }
        }
        i = lastExchangeIndex ;
    }
}

// selection sort
template <class T>
void SelectionSort(T A[], int n){
    int smallIndex;
    int i,j;
    for(i = 0; i<n-1; i++){
        smallIndex = i;
        for(j=i+1;j<n;j++){
            compSelect++; // increase the data comparison amount
            if(A[j] < A[smallIndex])
                smallIndex = j;
        }
        movsSelect++; // increase the data move amount
        Swap(A[i],A[smallIndex]); // swap the small indexed element
        // if there is a smaller element in the list
    }
}

// Quick Sort 1
template <class T>
void QuickSort1(T* A, int low, int high){
    T pivot; // pivot element
    if(low < high){
        int ScanUp = low+1; // init scanup
        int ScanDown = high; // init scandown
        pivot = A[low]; // set pivot
        while(true){
            while(A[ScanUp] <= pivot && ScanUp != high){
                compQuick1++;// increase the data comparison amount
                ScanUp++; // increment scan up until pivot
            }
            while(A[ScanDown] > pivot && ScanDown != low){
                compQuick1++;// increase the data comparison amount
                ScanDown--; // decrement scandown until pivot
            }
            if(ScanUp < ScanDown){
                movsQuick1++; // increase the data move amount
                Swap(A[ScanDown],A[ScanUp]); // swap
            }
            else
                break;
        }
        // swap A[scandown] and A[low]
        Swap(A[ScanDown],A[low]);
        movsQuick1++; // increase the data move amount
        // recursively call
        QuickSort1(A,low,ScanDown-1);
        QuickSort1(A,ScanDown+1,high);
    }

}

// Quick Sort 2
template <class T>
void QuickSort2(T* A, int low, int high){
    T pivot; // pivot element
    if(low < high){
        int ScanUp = low; // init scanup
        int ScanDown = high; // init scandown
        pivot = A[(low+high)/2]; // set pivot as middle element
        while(ScanUp<=ScanDown){ // check is required for this case in order not to go into a infinite loop
            while(A[ScanUp] < pivot && ScanUp != high){
                compQuick2++;// increase the data comparison amount
                ScanUp++; // increment scan up until pivot
            }
            while(A[ScanDown] > pivot && ScanDown != low){
                compQuick2++;// increase the data comparison amount
                ScanDown--; // decrement scandown until pivot
            }
            if(ScanUp <= ScanDown){
                Swap(A[ScanDown],A[ScanUp]); // swap
                movsQuick2++; // increase the data move amount
                ScanUp++; // increment in order to pass the element
                ScanDown--; // increment in order to pass the element
            }
            else
                break;
        }
        // recursively call
        QuickSort2(A,low,ScanDown);
        QuickSort2(A,ScanUp,high);
    }

}

// Quick Sort 3
template <class T>
void QuickSort3(T* A, int low, int high){
    T pivot; // pivot element
    if(low < high){
        int ScanUp = low; // init scanup
        int ScanDown = high; // init scandown
        int newIndex = low + rand()% (high-low+1); // set pivot randomly btw low and high
        pivot = A[newIndex];
        while(ScanUp<=ScanDown){ // check is required for this case in order not to go into a infinite loop
            while(A[ScanUp] < pivot && ScanUp != high){
                compQuick3++;// increase the data comparison amount
                ScanUp++; // increment scan up until pivot
            }
            while(A[ScanDown] > pivot && ScanDown != low){
                compQuick3++;// increase the data comparison amount
                ScanDown--; // decrement scandown until pivot
            }
            if(ScanUp <= ScanDown){
                Swap(A[ScanDown],A[ScanUp]); // swap
                movsQuick3++; // increase the data move amount
                ScanUp++; // increment in order to pass the element
                ScanDown--; // increment in order to pass the element
            }
            else
                break;
        }
        // recursively call
        QuickSort3(A,low,ScanDown);
        QuickSort3(A,ScanUp,high);
    }
}

// Quick Sort 4
template <class T>
void QuickSort4(T* A, int low, int high){
    T pivot; // pivot element
    if(low < high){
        int ScanUp = low; // init scanup
        int ScanDown = high; // init scandown
        // if the size of the array is greater/equal to 3
        if(high-low >= 2){
            int numbers[3];
            // random numbers in the array with indices btw low and high
            numbers[0] = A[low + rand()% (high-low+1)];
            numbers[1] = A[low + rand()% (high-low+1)];
            numbers[2] = A[low + rand()% (high-low+1)];
            BubbleSort(numbers,3); // sort the random numbers
            pivot = numbers[1]; // set the pivot as the median of the numbers
        }
        else
            pivot = A[low]; // if there is not 3 elements in the array, just set the pivot as first element

        while(ScanUp<=ScanDown){ // check is required for this case in order not to go into a infinite loop
            while(A[ScanUp] < pivot && ScanUp != high){
                compQuick4++;// increase the data comparison amount
                ScanUp++; // increment scan up until pivot
            }
            while(A[ScanDown] > pivot && ScanDown != low){
                compQuick4++;// increase the data comparison amount
                ScanDown--; // decrement scandown until pivot
            }
            if(ScanUp <= ScanDown){
                Swap(A[ScanDown],A[ScanUp]); // swap
                movsQuick4++; // increase the data move amount
                ScanUp++; // increment in order to pass the element
                ScanDown--; // increment in order to pass the element
            }
            else
                break;
        }
        // recursively call
        QuickSort4(A,low,ScanDown);
        QuickSort4(A,ScanUp,high);
    }
}

// my sorting algorithm
// the algorithm is based on a cut off number
// if the size of the array part is larger than that number, the algorithm implements quick sort
// with middle element as pivot.
// Otherwise, the algorithm implements a selection sort on the array parts.

template <class T>
void MySort(T* A, int low, int high){
    // check the array size
    if(high-low+1>CUT_OFF){
            // now implement the quick sort
            T pivot; // pivot element
        if(low < high){
            int ScanUp = low; // init scanup
            int ScanDown = high; // init scandown
            pivot = A[(low+high)/2]; // set pivot as middle element
            while(ScanUp<=ScanDown){ // check is required for this case in order not to go into a infinite loop
                while(A[ScanUp] < pivot && ScanUp != high){
                    compMySort++; // increase the data comparison amount
                    ScanUp++; // increment scan up until pivot
                }
                while(A[ScanDown] > pivot && ScanDown != low){
                    compMySort++; // increase the data comparison amount
                    ScanDown--; // decrement scandown until pivot
                }
                if(ScanUp <= ScanDown){
                    Swap(A[ScanDown],A[ScanUp]); // swap
                    movsMySort++; // increase the data move amount
                    ScanUp++; // increment in order to pass the element
                    ScanDown--; // increment in order to pass the element
                }
                else
                    break;
            }
            // recursively call
            MySort(A,low,ScanDown);
            MySort(A,ScanUp,high);
        }
    }
    else{
        int smallIndex;
        int i,j;
        for(i = low; i<high; i++){
            smallIndex = i;
            for(j=i+1;j<high+1;j++){
                compSelect++; // increase the data comparison amount
                if(A[j] < A[smallIndex])
                    smallIndex = j;
        }
        movsSelect++; // increase the data move amount
        Swap(A[i],A[smallIndex]); // swap the small indexed element

    }
    }
}




class Array{
private:
    int* numbers; // list of numbers
    int sizeN; // size of the array
    string sizeS; // size of the array as string


public:
    Array(); // constructor
    void initArray(); // method to init array
    void performanceEvaluation(int Size); // method for performance evaluation
    void loadArray(); // method to load from a file
    void printArray() const; // method to print the array
    // bool print is used for decision to print the resulting array
    // bool compTime is used for decision to compute computation time
    double bubbleSort(bool print = true, bool compTime = false) const; // sort the array using bubble sort
    double selectionSort(bool print = true, bool compTime = false) const; // sort the array using selection sort
    double quickSort1(bool print = true, bool compTime = false) const; // sort the array using quick sort1
    double quickSort2(bool print = true, bool compTime = false) const; // sort the array using quick sort2
    double quickSort3(bool print = true, bool compTime = false) const; // sort the array using quick sort3
    double quickSort4(bool print = true, bool compTime = false) const; // sort the array using quick sort3
    double mySort(bool print = true, bool compTime = false) const; // sort the array using my own algorithm
    void compareAlgorithms() const; // method to compare algorithms
};

Array::Array(){
    numbers = nullptr; // initially array is null
}

// method to initialize array
void Array::initArray(){
    cout<<"Enter the size of the array! Only input integers!"<<endl;
    bool control = true;
    while(true){
    cin>>sizeS;
    // check each char's ascii number
    for(unsigned int i=0; i<sizeS.length();i++){
        if(sizeS[i]<48 || sizeS[i]>57){
            cout<<"Invalid input! Try again!"<<endl;
            control = false;
            break;
        }
        control = true;
    }
    if(control == true) {
            sizeN = stoi(sizeS); // convert str to int
            // check if the size is zero
            if(sizeN == 0){
                cout<<"Array length can not be zero! Try again!"<<endl;
                continue;
            }
            break;
    }
    }

    if(numbers != nullptr)
        delete numbers; // delete previously occupied memory
    numbers = new int[sizeN]; // allocate new memory
    for(int i=0; i<sizeN; i++){
        numbers[i] = rand() % (10*sizeN); // random numbers btw 0 and 10*size
    }
    cout<<"Array is initialized with random numbers!"<<endl;
    printArray();
}

// init array with size (not user input) and do sorting
void Array::performanceEvaluation(int Size){
    // VARIABLES FOR AVERAGING
    long double compB=0,movsB=0,movsS=0,compS=0;
    long double compQ1=0,movsQ1=0;
    long double compQ2=0,movsQ2=0;
    long double compQ3=0,movsQ3=0;
    long double compQ4=0,movsQ4=0;
    long double compM=0,movsM=0;
    double timeB=0,timeS=0,timeQ1=0,timeQ2=0,timeQ3=0,timeQ4=0,timeM=0;
    sizeN = Size;


    for(int i=0;i<5;i++){
        if(numbers != nullptr)
            delete numbers; // delete previously occupied memory
        numbers = new int[sizeN]; // allocate new memory
        for(int j=0; j<sizeN; j++){
            numbers[j] = rand() % (10*sizeN); // random numbers btw 0 and 10*size
        }
        // make the counter variables zero
        compBubble=0; // number of comparisons for bubble sort
        movsBubble=0; // number of moves for bubble sort
        timeB += bubbleSort(false,true); // do not print sorted array
        compB += compBubble; // add comparison amount
        movsB += movsBubble; // add move amount


        // make the counter variables zero
        compSelect=0; // number of comparisons for selection sort
        movsSelect=0; // number of moves for selection sort
        timeS += selectionSort(false,true); // do not print sorted array
        compS += compSelect; // add comparison amount
        movsS += movsSelect; // add move amount

        // make the counter variables zero
        compQuick1=0; // number of comparisons for quick sort 1
        movsQuick1=0; // number of moves for quick sort 1
        timeQ1 += quickSort1(false,true); // do not print sorted array
        compQ1 += compQuick1; // add comparison amount
        movsQ1 += movsQuick1; // add move amount

        // make the counter variables zero
        compQuick2=0; // number of comparisons for quick sort 2
        movsQuick2=0; // number of moves for quick sort 2
        timeQ2 += quickSort2(false,true); // do not print sorted array
        compQ2 += compQuick2; // add comparison amount
        movsQ2 += movsQuick2; // add move amount

        // make the counter variables zero
        compQuick3=0; // number of comparisons for quick sort 3
        movsQuick3=0; // number of moves for quick sort 3
        timeQ3 += quickSort3(false,true); // do not print sorted array
        compQ3 += compQuick3; // add comparison amount
        movsQ3 += movsQuick3; // add move amount

        // make the counter variables zero
        compQuick4=0; // number of comparisons for quick sort 4
        movsQuick4=0; // number of moves for quick sort 4
        timeQ4 += quickSort4(false,true); // do not print sorted array
        compQ4 += compQuick4; // add comparison amount
        movsQ4 += movsQuick4; // add move amount

        // make the counter variables zero
        compMySort=0; // number of comparisons for my sort
        movsMySort=0; // number of moves for my sort
        timeM += mySort(false,true); // do not print sorted array
        compM += compMySort; // add comparison amount
        movsM += movsMySort; // add move amount
    }
    cout<<"Array Size:"<<Size<<endl;
    cout<<"Wait for long time since every algorithm is done 5 times!!!!!!"<<endl;

    cout<<"Algorithm               Average #comparisons              Average #moves              Average time(msec)"<<endl;

    cout<<"Bubble Sort              "<<compB/5<<"                             "<<movsB/5<<"                        "<<timeB/5<<endl;

    cout<<"Selection Sort           "<<compS/5<<"                             "<<movsS/5<<"                         "<<timeS/5<<endl;

    cout<<"Quick Sort1              "<<compQ1/5<<"                            "<<movsQ1/5<<"                        "<<timeQ1/5<<endl;

    cout<<"Quick Sort2              "<<compQ2/5<<"                            "<<movsQ2/5<<"                        "<<timeQ2/5<<endl;

    cout<<"Quick Sort3              "<<compQ3/5<<"                            "<<movsQ3/5<<"                        "<<timeQ3/5<<endl;

    cout<<"Quick Sort4              "<<compQ4/5<<"                            "<<movsQ4/5<<"                        "<<timeQ4/5<<endl;

    cout<<"MySort                   "<<compM/5<<"                              "<<movsM/5<<"                          "<<timeM/5<<endl;

}

// load array
// load is performed such that the array index does not pass the size
// if the number amount in file is less than the size, the remaining numbers will be untouched
void Array::loadArray(){
    if(numbers == nullptr){
        cout<<"Array is not initialized!"<<endl;
        return;
    }
    string line;
    ifstream myfile ("input_array.txt");
    if (myfile.is_open())
    {
    int i=0;
    while ( getline (myfile,line) )
    {
    numbers[i] = stoll(line);
    i++;
    // control for number amount
    // index is not exceed
    if(i == sizeN)
        break;
    }
    myfile.close();
    cout<<"Load is successful."<<endl;
    printArray(); // print the array after load
    }
    else cout << "Unable to open file";
    return;
}

// print array
void Array::printArray() const{
    cout<<"Array: [";
    for(int i=0; i<sizeN; i++){
        cout<<numbers[i]<<" ";
    }
    cout<<"]"<<endl;
}

// bubble sort and returns computation time
double Array::bubbleSort(bool print,bool compTime) const{
    if(numbers == nullptr){
        cout<<"Array is not initialized!"<<endl;
        return -1;
    }

    if(compTime == false){ // time computation is not required
        int newArray[sizeN];
        for(int i=0; i<sizeN;i++)
            newArray[i] = numbers[i]; // assign each member
        BubbleSort(newArray,sizeN);

        // print if bool print is true
        if(print == true){
             cout<<"Sorting using bubble sort..."<<endl;
            cout<<"Sorted Array: [";
            for(int i=0; i<sizeN; i++){
                cout<<newArray[i]<<" ";
            }
            cout<<"]"<<endl;
        }
    }
    else{ // time computation is required
        // construct 100000/sizeN rows in order to make sort 100000/sizeN times
        int newArray[(100000/sizeN)][sizeN];
        for(int j=0; j<(100000/sizeN);j++)
            for(int i=0; i<sizeN;i++)
                newArray[j][i] = numbers[i]; // assign each member
        double start = double(clock()); // start of the bubble sort
        for(int j=0; j<(100000/sizeN);j++){
            compBubble = 0; // number of comparisons is assigned to 0
            movsBubble = 0; // number of moves is assigned to 0
            BubbleSort(newArray[j],sizeN);
        }
        double finish = double(clock()); // end of the bubble sort

        // print if bool print is true
        if(print == true){
             cout<<"Sorting using bubble sort..."<<endl;
            cout<<"Sorted Array: [";
            for(int i=0; i<sizeN; i++){
                cout<<newArray[0][i]<<" ";
            }
            cout<<"]"<<endl;
        }

        return (finish-start)/(100000/sizeN); // divide by loop amount
    }
    return 0;
}

// selection sort and returns computation time
double Array::selectionSort(bool print,bool compTime) const{
    if(numbers == nullptr){
        cout<<"Array is not initialized!"<<endl;
        return -1;
    }

    if(compTime == false){ // time computation is not required
        int newArray[sizeN];
        for(int i=0; i<sizeN;i++)
            newArray[i] = numbers[i]; // assign each member
        SelectionSort(newArray,sizeN);

        // print if bool print is true
        if(print == true){
            cout<<"Sorting using selection sort..."<<endl;
            cout<<"Sorted Array: [";
            for(int i=0; i<sizeN; i++){
                cout<<newArray[i]<<" ";
            }
            cout<<"]"<<endl;
        }
    }
    else{ // time computation is required
        // construct 100000/sizeN rows in order to make sort 100000/sizeN times
        int newArray[(100000/sizeN)][sizeN];
        for(int j=0; j<(100000/sizeN);j++)
            for(int i=0; i<sizeN;i++)
                newArray[j][i] = numbers[i]; // assign each member
        double start = double(clock()); // start of the selection sort
        for(int j=0; j<(100000/sizeN);j++){
            compSelect = 0; // number of comparisons is assigned to 0
            movsSelect = 0; // number of moves is assigned to 0
            SelectionSort(newArray[j],sizeN);
        }
        double finish = double(clock()); // end of the selection sort

        // print if bool print is true
        if(print == true){
            cout<<"Sorting using selection sort..."<<endl;
            cout<<"Sorted Array: [";
            for(int i=0; i<sizeN; i++){
                cout<<newArray[0][i]<<" ";
            }
            cout<<"]"<<endl;
        }

        return (finish-start)/(100000/sizeN); // divide by loop amount
    }

    return 0;
}

// quick sort1 and returns computation time
double Array::quickSort1(bool print,bool compTime) const{
    if(numbers == nullptr){
        cout<<"Array is not initialized!"<<endl;
        return -1;
    }
    if(compTime == false){ // time computation is not required
        int newArray[sizeN];
        for(int i=0; i<sizeN;i++)
            newArray[i] = numbers[i]; // assign each member
        QuickSort1(newArray,0,sizeN-1);

        // print if bool print is true
        if(print == true){
            cout<<"Sorting using quick sort 1 ..."<<endl;
            cout<<"Sorted Array: [";
            for(int i=0; i<sizeN; i++){
                cout<<newArray[i]<<" ";
            }
            cout<<"]"<<endl;
        }
    }
    else{ // time computation is required
        // construct 100000/sizeN rows in order to make sort 100000/sizeN times
        int newArray[(100000/sizeN)][sizeN];
        for(int j=0; j<(100000/sizeN);j++)
            for(int i=0; i<sizeN;i++)
                newArray[j][i] = numbers[i]; // assign each member
        double start = double(clock()); // start of the quick sort
        for(int j=0; j<(100000/sizeN);j++){
            compQuick1 = 0; // number of comparisons is assigned to 0
            movsQuick1 = 0; // number of moves is assigned to 0
            QuickSort1(newArray[j],0,sizeN-1);
        }
        double finish = double(clock()); // end of the quick sort

        // print if bool print is true
        if(print == true){
            cout<<"Sorting using quick sort 1 ..."<<endl;
            cout<<"Sorted Array: [";
            for(int i=0; i<sizeN; i++){
                cout<<newArray[0][i]<<" ";
            }
            cout<<"]"<<endl;
        }

        return (finish-start)/(100000/sizeN); // divide by loop amount
    }

    return 0;
}

// quick sort2 and  returns computation time
double Array::quickSort2(bool print,bool compTime) const{
    if(numbers == nullptr){
        cout<<"Array is not initialized!"<<endl;
        return -1;
    }
    if(compTime == false){ // time computation is not required
        int newArray[sizeN];
        for(int i=0; i<sizeN;i++)
            newArray[i] = numbers[i]; // assign each member
        QuickSort2(newArray,0,sizeN-1);

        // print if bool print is true
        if(print == true){
            cout<<"Sorting using quick sort 2 ..."<<endl;
            cout<<"Sorted Array: [";
            for(int i=0; i<sizeN; i++){
                cout<<newArray[i]<<" ";
            }
            cout<<"]"<<endl;
        }
    }
    else{ // time computation is required
        // construct 100000/sizeN rows in order to make sort 100000/sizeN times
        int newArray[(100000/sizeN)][sizeN];
        for(int j=0; j<(100000/sizeN);j++)
            for(int i=0; i<sizeN;i++)
                newArray[j][i] = numbers[i]; // assign each member
        double start = double(clock()); // start of the quick sort
        for(int j=0; j<(100000/sizeN);j++){
            compQuick2 = 0; // number of comparisons is assigned to 0
            movsQuick2 = 0; // number of moves is assigned to 0
            QuickSort2(newArray[j],0,sizeN-1);
        }
        double finish = double(clock()); // end of the quick sort

        // print if bool print is true
        if(print == true){
            cout<<"Sorting using quick sort 2 ..."<<endl;
            cout<<"Sorted Array: [";
            for(int i=0; i<sizeN; i++){
                cout<<newArray[0][i]<<" ";
            }
            cout<<"]"<<endl;
        }

        return (finish-start)/(100000/sizeN); // divide by loop amount
    }

    return 0;
}

// quick sort3 and  returns computation time
double Array::quickSort3(bool print,bool compTime) const{
   if(numbers == nullptr){
        cout<<"Array is not initialized!"<<endl;
        return -1;
    }

    if(compTime == false){ // time computation is not required
        int newArray[sizeN];
        for(int i=0; i<sizeN;i++)
            newArray[i] = numbers[i]; // assign each member
        QuickSort3(newArray,0,sizeN-1);

        // print if bool print is true
        if(print == true){
            cout<<"Sorting using quick sort 3 ..."<<endl;
            cout<<"Sorted Array: [";
            for(int i=0; i<sizeN; i++){
                cout<<newArray[i]<<" ";
            }
            cout<<"]"<<endl;
        }

    }
    else{ // time computation is required
        // construct 100000/sizeN rows in order to make sort 100000/sizeN times
        int newArray[(100000/sizeN)][sizeN];
        for(int j=0; j<(100000/sizeN);j++)
            for(int i=0; i<sizeN;i++)
                newArray[j][i] = numbers[i]; // assign each member
        double start = double(clock()); // start of the quick sort
        for(int j=0; j<(100000/sizeN);j++){
            compQuick3 = 0; // number of comparisons is assigned to 0
            movsQuick3 = 0; // number of moves is assigned to 0
            QuickSort3(newArray[j],0,sizeN-1);
        }
        double finish = double(clock()); // end of the quick sort

        // print if bool print is true
        if(print == true){
            cout<<"Sorting using quick sort 3 ..."<<endl;
            cout<<"Sorted Array: [";
            for(int i=0; i<sizeN; i++){
                cout<<newArray[0][i]<<" ";
            }
            cout<<"]"<<endl;
        }

        return (finish-start)/(100000/sizeN); // divide by loop amount
    }

    return 0;
}


// quick sort4 and  returns computation time
double Array::quickSort4(bool print,bool compTime) const{
    if(numbers == nullptr){
        cout<<"Array is not initialized!"<<endl;
        return -1;
    }

    if(compTime == false){ // time computation is not required
        int newArray[sizeN];
        for(int i=0; i<sizeN;i++)
            newArray[i] = numbers[i]; // assign each member
        QuickSort4(newArray,0,sizeN-1);

        // print if bool print is true
        if(print == true){
            cout<<"Sorting using quick sort 4 ..."<<endl;
            cout<<"Sorted Array: [";
            for(int i=0; i<sizeN; i++){
                cout<<newArray[i]<<" ";
            }
            cout<<"]"<<endl;
        }

    }
    else{ // time computation is required
        // construct 100000/sizeN rows in order to make sort 100000/sizeN times
        int newArray[(100000/sizeN)][sizeN];
        for(int j=0; j<(100000/sizeN);j++)
            for(int i=0; i<sizeN;i++)
                newArray[j][i] = numbers[i]; // assign each member
        double start = double(clock()); // start of the quick sort
        for(int j=0; j<(100000/sizeN);j++){
            compQuick4 = 0; // number of comparisons is assigned to 0
            movsQuick4 = 0; // number of moves is assigned to 0
            QuickSort4(newArray[j],0,sizeN-1);
        }
        double finish = double(clock()); // end of the quick sort

        // print if bool print is true
        if(print == true){
            cout<<"Sorting using quick sort 4 ..."<<endl;
            cout<<"Sorted Array: [";
            for(int i=0; i<sizeN; i++){
                cout<<newArray[0][i]<<" ";
            }
            cout<<"]"<<endl;
        }

        return (finish-start)/(100000/sizeN); // divide by loop amount
    }

    return 0;
}

// my own algorithm
double Array::mySort(bool print,bool compTime) const{
    if(numbers == nullptr){
        cout<<"Array is not initialized!"<<endl;
        return -1;
    }

    if(compTime == false){ // time computation is not required
        int newArray[sizeN];
        for(int i=0; i<sizeN;i++)
            newArray[i] = numbers[i]; // assign each member
        MySort(newArray,0,sizeN-1);
        // print if bool print is true
        if(print == true){
            cout<<"Sorting using my sort algorithm ..."<<endl;
            cout<<"Sorted Array: [";
            for(int i=0; i<sizeN; i++){
                cout<<newArray[i]<<" ";
            }
            cout<<"]"<<endl;
        }
    }
    else{ // time computation is required
        // construct 100000/sizeN rows in order to make sort 100000/sizeN times
        int newArray[(100000/sizeN)][sizeN];
        for(int j=0; j<(100000/sizeN);j++)
            for(int i=0; i<sizeN;i++)
                newArray[j][i] = numbers[i]; // assign each member
        double start = double(clock()); // start of the mysort
        for(int j=0; j<(100000/sizeN);j++){
            compMySort = 0; // number of comparisons is assigned to 0
            movsMySort = 0; // number of moves is assigned to 0
            MySort(newArray[j],0,sizeN-1);
        }
        double finish = double(clock()); // end of the mysort

        // print if bool print is true
        if(print == true){
            cout<<"Sorting using my sort algorithm ..."<<endl;
            cout<<"Sorted Array: [";
            for(int i=0; i<sizeN; i++){
                cout<<newArray[0][i]<<" ";
            }
            cout<<"]"<<endl;
        }

        return (finish-start)/(100000/sizeN); // divide by loop amount
    }

    return 0;
}

// method to compare algorithms
void Array::compareAlgorithms() const{
    if(numbers == nullptr){
        cout<<"Array is not initialized!"<<endl;
        return;
    }
    double time = 0;
    cout<< "Array size:"<<sizeN<<endl; // print the labels
    if(sizeN>1000)
        cout<<"!!!Array size is too large. It may take time to compute statistics!!!"<<endl;
    cout<<"Algorithm               #comparisons               #moves               time(msec)"<<endl;

    // make the counter variables zero
    compBubble=0; // number of comparisons for bubble sort
    movsBubble=0; // number of moves for bubble sort
    time = bubbleSort(false,true); // do not print sorted array

    cout<<"Bubble Sort              "<<compBubble<<"                            "<<movsBubble<<"                        "<<time<<endl;


    // make the counter variables zero
    compSelect=0; // number of comparisons for selection sort
    movsSelect=0; // number of moves for selection sort
    time = selectionSort(false,true); // do not print sorted array

    cout<<"Selection Sort           "<<compSelect<<"                            "<<movsSelect<<"                        "<<time<<endl;


    // make the counter variables zero
    compQuick1=0; // number of comparisons for quick sort 1
    movsQuick1=0; // number of moves for quick sort 1
    time = quickSort1(false,true); // do not print sorted array

    cout<<"Quick Sort1              "<<compQuick1<<"                            "<<movsQuick1<<"                        "<<time<<endl;


    // make the counter variables zero
    compQuick2=0; // number of comparisons for quick sort 2
    movsQuick2=0; // number of moves for quick sort 2
    time = quickSort2(false,true); // do not print sorted array

    cout<<"Quick Sort2              "<<compQuick2<<"                            "<<movsQuick2<<"                        "<<time<<endl;


    // make the counter variables zero
    compQuick3=0; // number of comparisons for quick sort 3
    movsQuick3=0; // number of moves for quick sort 3
    time = quickSort3(false,true); // do not print sorted array

    cout<<"Quick Sort3              "<<compQuick3<<"                            "<<movsQuick3<<"                        "<<time<<endl;


    // make the counter variables zero
    compQuick4=0; // number of comparisons for quick sort 4
    movsQuick4=0; // number of moves for quick sort 4
    time = quickSort4(false,true); // do not print sorted array

    cout<<"Quick Sort4              "<<compQuick4<<"                            "<<movsQuick4<<"                        "<<time<<endl;


    // make the counter variables zero
    compMySort=0; // number of comparisons for my sort
    movsMySort=0; // number of moves for my sort
    time = mySort(false,true); // do not print sorted array

    cout<<"MySort                   "<<compMySort<<"                            "<<movsMySort<<"                        "<<time<<endl;

}

// a global function to take input as string and convert it to int
long long int takeStringtoLong(){
    long long int number;
    string sizeS;
    bool control = true;
while(true){
    cin>>sizeS;
    // check each char's ascii number
    for(unsigned int i=0; i<sizeS.length();i++){
        if(sizeS[i]<48 || sizeS[i]>57){
            cout<<"Invalid input! Try again!"<<endl;
            control = false;
            break;
        }
        control = true;
    }
    if(control == true) break;
    }
    number = stoll(sizeS);
    // check if the ID is valid
    if(number<10000000000 || number>99999999999){
        cout<<"Invalid TC number!"<<endl;
        return -1;
    }
    return number;
}

// IT SHOULD BE NOTED THAT SORTS ARE IMPLEMENTED ON A NEW ARRAY. NOT ON THE
// EXISTING ONE. AS A RESULT, THE ARRAY IN THE ARRAY CLASS IS NOT CHANGED AFTER
// SORT IMPLEMENTATIONS IN ORDER NOT TO DESTROY THE INITIAL ARRAY

int main()
{
    Array numbers;
    char input;
    cout<<"Welcome to Array Sorter"<<endl;

    while(true){
    cout<<endl;
    cout<<"Choose the operation from the menu:"<<endl;
    cout<<"0. Terminate The Program"<<endl;
    cout<<"1. Initialize Input Array Randomly"<<endl;
    cout<<"2. Load Input Array from a File"<<endl;
    cout<<"3. Perform Bubble Sort"<<endl;
    cout<<"4. Perform Quick Sort"<<endl;
    cout<<"5. Perform Selection Sort"<<endl;
    cout<<"6. Perform My Sort"<<endl;
    cout<<"7. Compare Sorting Algorithms"<<endl;
    cout<<"8. Performance Evaluation (Long waiting time)"<<endl;
    cin>>input;
    cout<<endl;
    // input is taken as char and ascii number of the char is checked to find the integer value
    if(input<48 || input > 56){
        cout<<"Invalid operation! Please enter an integer in the range 0-8!"<<endl;
        continue;
    }
    if(input == 48){
        break;  // terminate the loop
    }
    else if(input == 49){
        numbers.initArray(); // initialize the array
    }
    else if(input == 50){
        numbers.loadArray(); // load the array from file
    }
    else if(input == 51){
        numbers.bubbleSort(); // perform bubble sort
    }
    else if(input == 52){
        char method;
        while(true){
        cout<<"Enter the quick sort method!"<<endl;
        cout<<"Enter '1' -> Take first element as pivot."<<endl;
        cout<<"Enter '2' -> Take middle element as pivot."<<endl;
        cout<<"Enter '3' -> Take pivot randomly."<<endl;
        cout<<"Enter '4' -> Take median of 3 random indexes as pivot."<<endl;
        cin>> method;
        if(method != '1' && method != '2' && method != '3' && method != '4'){
            cout<<"Invalid input! Try again!"<<endl;
            continue;
        }
        break;
        }
        if(method == '1')
            numbers.quickSort1();
        else if (method == '2')
            numbers.quickSort2();
        else if (method == '3')
            numbers.quickSort3();
        else if (method == '4')
            numbers.quickSort4();
    }
    else if(input == 53){
        numbers.selectionSort(); // perform selection sort
    }
    else if(input == 54){
        numbers.mySort();// perform my sort
    }
    else if(input == 55){
        numbers.compareAlgorithms();// perform comparisons
    }
    else if(input == 56){ // performance evaluation
        numbers.performanceEvaluation(100); // evaluate for size 100
        numbers.performanceEvaluation(1000); // evaluate for size 1000
        numbers.performanceEvaluation(5000); // evaluate for size 5000
        numbers.performanceEvaluation(10000); // evaluate for size 10000
        numbers.performanceEvaluation(25000); // evaluate for size 25000
    }
    }
    return 0;
}
