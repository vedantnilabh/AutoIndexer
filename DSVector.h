//
// Created by MARK FONTENOT on 6/7/22.
// Updated by Vedant Nilabh
//

#ifndef PA01_SENTIMENT_DSVECTOR_H
#define PA01_SENTIMENT_DSVECTOR_H
#include <iostream>
template<typename T>
class DSVector {
private:
    int cap;
    int size;
    T* data;
    void resize();
public:
    // add  2 erase methods for value/index, overloaded [], search, iteration - pointers to elements?, ==, !=
    DSVector(int init_capacity = 10);
    DSVector(const DSVector& arg);
    ~DSVector();
    void pushBack(const T& arg);
    T& operator[](int location);
    DSVector& operator=(const DSVector& arg);
    int getSize();
    void Remove(int location);
    T& at(int location);
    int Search(const T& arg);
    void Insert(int location, const T& arg);
    bool operator==(const DSVector & arg) const;
    bool operator!=(const DSVector& arg) const;
    void Sort();
};

template <typename T>
DSVector<T>::DSVector(int init_capacity) {
    // sets size to 0 and sets initial cpacity
    size = 0;
    cap = init_capacity;
    data = new T[cap];
}

template <typename T>
DSVector<T>::DSVector(const DSVector& arg) {
    // creates deep copy
    cap = arg.cap;
    size = arg.size;
    data = new T[cap];
    for(int i = 0; i < size; i++)
        data[i] = arg.data[i];
}

template <typename T>
DSVector<T>::~DSVector() {
    // deletes dynamically allocated array
    delete [] data;
}

template <typename T>
DSVector<T>& DSVector<T>::operator=(const DSVector& arg) {
    // checks self assigment
    if(this != &arg){
        // memory management
        // deep copy created
        delete[] data;
        size = arg.size;
        cap = arg.cap;
        data = new T[cap];
        for (int i = 0; i < size; i++) {
            data[i] = arg.data[i];
        }

    }
    return *this;
}


template<typename T>
void DSVector<T>::pushBack(const T& arg) {
    if(size == cap){
        // resize if needed
        resize();
    }

    data[size] = arg;
    size++;
}

template<typename T>
T& DSVector<T>::operator[](int location) {
    if(location < size && location >= 0){
        return data[location];
    }
    else {
        // error checking, out of bounds
        throw std::out_of_range("Error, attempting to access element at location less than 0 or out of vector bounds");
    }
}

template<typename T>
int DSVector<T>::getSize() {
    return size;
}

template<typename T>
void DSVector<T>::resize() {
    int newSize = cap * 2; //doubling cap/sizw
    cap = newSize;
    T* newdata = new T[cap];
    for(int i = 0; i < size; i++){
        newdata[i] = data[i];
    }
    delete[] data;
    data = newdata;

}

template<typename T>
void DSVector<T>::Remove(int location) {
    // in bounds
    if(location < size){
        int elemCount = 0; // where to copy from
        T* new_data = new T[cap];
        for(int i = 0; i < size; i++){
            if(i != location){
                new_data[elemCount] = data[i];
                elemCount++;
            }
            else{
                continue;
            }
        }
        delete[] data;
        data = new_data;
        size = size - 1;
        return;
    }
    // means location is >= size, error
    throw std::out_of_range("Error, attempting to remove element out of bounds of vector");
}



template<typename T>
T &DSVector<T>::at(int location) {
    // same as []
    if(location < size && location >= 0){
        return data[location];
    }
    else {
        throw std::out_of_range("error, attempting to access element out of range or index less than 0");
    }
}

template<typename T>
bool DSVector<T>::operator==(const DSVector &arg) const {
    // goes through vectors ard compares elements and sizes
    if(data == nullptr || arg.data == nullptr){
        return (data == nullptr && arg.data == nullptr);
    }
    if(size == arg.size){
        for(int i = 0; i < size; i++){
            if(data[i] != arg.data[i]){
                return false;
            }
        }
        return true;
    }
    return false;
}

template<typename T>
bool DSVector<T>::operator!=(const DSVector &arg) const {
    // opposite of ==
    if(data == nullptr || arg.data == nullptr){
        return (data != nullptr || arg.data != nullptr);
    }
    if(size == arg.size){
        for(int i = 0; i < size; i++){
            if(data[i] == arg.data[i]){
                return false;
            }
        }
        return true;
    }
    return true;
}

template<typename T>
int DSVector<T>::Search(const T &arg) {
    int location = -1; // if element not found, return location of -1
    for(int i = 0; i < size; i++){
        if(data[i] == arg){
            location = i;
            break;
        }
    }
    return location;
}

template<typename T>
void DSVector<T>::Insert(int location, const T &arg) {
    if(cap == size){
        // like push_back
        resize();
    }
    if(location > size || location < 0){
        // out of bounds
        throw std::out_of_range("Error, invalid location passed in Insert");
    }
    // creates new array and copy elements over along with specified inserted arg
    T* newData = new T[cap];
    for(int i = 0; i < location; i++){
        newData[i] = data[i];
    }
    newData[location] = arg;
    for(int i = 0; i < size - location; i++){
        newData[i + location + 1] = data[i + location];
    }
    delete[] data;
    data = newData;
    size++;
}

template<typename T>
void DSVector<T>::Sort() {
    // selection sort for DSVector
    for(int i = 0; i < size - 1; i++){
        int min = i;
        for(int j = i + 1; j < size; j++){
            if(data[j] < data[min]){
                min = j;
            }
        }
        // swap min element (won't do anything if i is min
        T temp = data[min];
        data[min] = data[i];
        data[i] = temp;
    }
}


#endif //PA01_SENTIMENT_DSVECTOR_H
