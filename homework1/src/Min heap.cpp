#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}

    virtual bool IsEmpty() const = 0;     // O(1)
    virtual const T& Top() const = 0;     // O(1)
    virtual void Push(const T&) = 0;      // O(log n)
    virtual void Pop() = 0;               // O(log n)
};
template <class T>
class MinHeap : public MinPQ<T> {
private:
    T heap[1000];   
    int size;
public:
    MinHeap() {
        size = 0;     //建立新的樹從根開始
    }
    bool IsEmpty() const override { //看是不是空的
        return size == 0;
    }
    const T& Top() const override {
         if (IsEmpty()) {
        cout << "Heap is empty!" << endl;
        exit(1);  
        }
    return heap[0];
    }
    void Push(const T& data) override {
        if (size < 1000) {
            heap[size] = data;
            int i = size;
            size++;
            while (i > 0 && heap[i] < heap[(i - 1) / 2]) {  // heap[(i - 1) / 2] 用來找父節點
                T temp;
                temp = heap[i];
                heap[i] = heap[(i - 1) / 2];
                heap[(i - 1) / 2] = temp;

                i = (i - 1) / 2;
            }
        }
    }
    void Pop() override {   //queue先進先出 
        if (IsEmpty()) 
        return;
        heap[0] = heap[size - 1];  //用最後面的補位
        size--;

        if (size > 0) {
            int i =0;
            while (true) {
                int left = 2 * i + 1;
                int right = 2 * i + 2;
                int small = i;

             

                if (left < size&& heap[left] < heap[small]) {
                    small = left;
                }
                if (right < size && heap[right] < heap[small]) {
                    small = right;
                }
                if (small != i) {
                    T temp = heap[i];
                    heap[i] = heap[small];
                    heap[small] = temp;
                    i = small;
                }
                else if (small == i) {
                    break;
                }

            }
        }

    }

};
int main() {
    MinHeap<int> test;

    cout << "測試" << endl;

    //Push功能 
    int data[] = { 30, 10, 50, 5, 20 };
    cout << "Push: 30, 10, 50, 5, 20" << endl;

    for (int i = 0; i < 5; i++) {
        test.Push(data[i]);
    }

    //Top功能
    if (!test.IsEmpty()) {
        cout << "目前最小的" << test.Top() << endl;
    }

    //Pop功能
    cout << "\n取出最小值:" << endl;
    while (!test.IsEmpty()) {
        cout << "取出: " << test.Top() << endl;
        if (!test.IsEmpty()) {
            cout << "目前最小的" << test.Top() << endl;
        }
        test.Pop();
    }


    //isempty測試
    cout << "\n是否為空: " << (test.IsEmpty() ? "是" : "否") << endl;

    return 0;
}
