#include <cstdio>
#include <stdexcept>
#include <iostream>
#include <exception>
using namespace std;

template <class T>
class TwoStacks {
 public:
     int top1=-1, top2, s2_ctr;
  // Constructor, initialize the array to size_hint
  TwoStacks(int size_hint = 16) : size_(size_hint), array_(new T(size_hint)) {
      //array_ = new T[size_hint];
      top1 = -1;
      top2 = size_;
      s2_ctr = 0;
   }
  // Destructor
  ~TwoStacks() {
      delete[] array_;
  }

  // Push a value to the first stack
  void push_first(const T& val) {
      if (top1 < top2 -1) {
          top1++;
          array_[top1] = val;
      } else {
    	  cout << "Stack 1 is full" << endl;
    	  reinitializeArray();
      }
  }


  // Push a value to the second stack
  void push_second(const T& val) {
       if (top1 < top2 -1) {
           top2--;
           s2_ctr++;
          array_[top2] = val;
          cout << "push2 val: " << array_[top2] << endl;
       } else {
    	   cout << "Stack 2 is full" << endl;
    	   reinitializeArray();
       }

  }

  // Pop from the first stack and return the value
  T pop_first() {
        if(top1 >= 0) {
            int x = array_[top1];
            top1--;
            return x;
        } else {
        	throw std::out_of_range("Out of range");
        }
  }

  // Pop from the second stack and return the value
  T pop_second() {
        if (top2 < size_){
            int x = array_[top2];
            top2++;
            s2_ctr--;
            return x;
        } else {
        	throw std::out_of_range("Out of range");
        }
  }

  int getMaxArraySize() {
      return (int)sizeof(array_);
  }

  // Return the size of the first stack
  size_t size_first() const {
	  size_t s = top1+1;
      if (s > 0) return s;
      else return 0;
  }

  // Return the size of the second stack
  size_t size_second() const {
/*      size_t s = top2+1-size_;
      if (s > 0)return s;
      else return 0;*/

      return s2_ctr;

  }

  // Return true if the first stack is empty
  bool empty_first() const {
      return size_first() == 0;
  }

  // Return true if the second stack is empty
  bool empty_second() const {
      return size_second() == 0;
  }

  /**
   * Divide the array into two half
   * array[0...(hint/2)-1)] for stack1
   * array[[hint/2)... hint-1] for stack2
   * when it overflows in either stack,
   * copy the elements into two arrays
   * re-initialize the original array to size 2*hint
   * copy stack1 elements from first half of old array to 1st half of new array
   * copy stack2 elements from last half of old array to 2nd half of new array
   */
void reinitializeArray() {
    size_t old_size_ = size_;
    size_ = size_ * 2;
    T* array2 = new T[size_];
    size_t st1_size = size_first();
    for (size_t i = 0; i < st1_size; i++) {
        array2[st1_size-i] = array_[i];
    }
    size_t st2_size = size_second();
    for (size_t j = 0; j < st2_size; j++) {
        array2[size_-j] = array_[old_size_-j];
    }
    *array_ = *array2;
	cout << "Overflow: Stack ReinitializeArray() called: New Array Size : " << size_ << endl;
}
 private:
  int size_;
  T *array_;
};

int main(int argc, char** argv) {
	try {
		TwoStacks<int> ts(20);
		ts.push_first(31);
		ts.push_second(90);
		ts.push_first(38);
		ts.push_first(23);
		cout << "Size of stack1 is " << ts.size_first() << endl;
		cout << "Size of stack 2 is " << ts.size_second() << endl << endl;

		ts.push_second(46);
		cout << "Size of stack1 is " << ts.size_first() << endl;
		cout << "Size of stack 2 is " << ts.size_second() << endl << endl;

		ts.push_first(45);
		cout << "Size of stack1 is " << ts.size_first() << endl;
		cout << "Size of stack 2 is " << ts.size_second() << endl << endl;;

		ts.push_first(64);
		cout << "Size of stack1 is " << ts.size_first() << endl;
		cout << "Size of stack 2 is " << ts.size_second() << endl << endl;

		ts.push_first(74);
		cout << "Size of stack1 is " << ts.size_first() << endl;
		cout << "Size of stack 2 is " << ts.size_second() << endl << endl;

		ts.push_first(36);
		cout << "Size of stack1 is " << ts.size_first() << endl;
		cout << "Size of stack 2 is " << ts.size_second() << endl << endl;


		ts.push_second(53);
		cout << "Size of stack1 is " << ts.size_first() << endl;
		cout << "Size of stack 2 is " << ts.size_second() << endl << endl;

		ts.push_second(12);
		cout << "Size of stack1 is " << ts.size_first() << endl;
		cout << "Size of stack 2 is " << ts.size_second() << endl << endl;

		ts.push_first(21);
		cout << "Size of stack1 is " << ts.size_first() << endl;
		cout << "Size of stack 2 is " << ts.size_second() << endl << endl;
		ts.push_second(47);

		cout << "Size of stack1 is " << ts.size_first() << endl;
		cout << "Size of stack 2 is " << ts.size_second() << endl << endl;

		ts.push_second(65);
		cout << "Size of stack1 is " << ts.size_first() << endl;
		cout << "Size of stack 2 is " << ts.size_second() << endl << endl;

		ts.push_second(21);
		cout << "Size of stack1 is " << ts.size_first() << endl;
		cout << "Size of stack 2 is " << ts.size_second() << endl << endl;
                
                cout << "Popped element from stack1 is " << ts.pop_first() << endl;
		cout << "Popped element from stack2 is " << ts.pop_second() << endl;
		cout << "Size of stack1 is " << ts.size_first() << endl;
		cout << "Size of stack 2 is " << ts.size_second() << endl;
	} catch (exception& e) {

		cout << "Exception : " << e.what() << endl;
	}
    return 0;
}