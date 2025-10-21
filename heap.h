#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <utility>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator())
  : m_(m), comp_(c), data_()
  {
    if(m_ < 2) m_ = 2;
  }

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap() = default;;

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item)
  {
    data_.push_back(item);
    trickleUp(data_.size() - 1);
  }

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop()
  {
    if(empty()) {
      throw std::underflow_error("pop() on empty heap");
    }
    // Move last to root, remove last, then restore heap
    std::swap(data_.front(), data_.back());
    data_.pop_back();
    if(!data_.empty()) {
      heapify(0);
    }
  }

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const {
    return data_.empty();
  }

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const {
    return data_.size();
  }

private:
  /// Add whatever helper functions and data members you need below

  // Helpers
  size_t parent(size_t i) const {
    return (i - 1) / m_;
  }

  size_t child(size_t i, size_t k) const {
    return i * m_ + k + 1;
  }

  void trickleUp(size_t i)
  {
    while(i > 0) {
      size_t p = parent(i);
      if(comp_(data_[i], data_[p])) {
        std::swap(data_[i], data_[p]);
        i = p;
      } else break;
    }
  }

  void heapify(size_t i) 
  {
    while(true) {
      // Find best (highest priority) among i and its children 
      size_t best = i;
      for(size_t k = 0; k < static_cast<size_t>(m_); k++) {
        size_t cidx = child(i, k);
        if(cidx < data_.size() && comp_(data_[cidx], data_[best])) {
          best = cidx;
        }
      }
      if(best == i) break;
      std::swap(data_[i], data_[best]);
      i = best;
    }
  }
  
private:
  int m_;
  PComparator comp_;
  std::vector<T> data_;




};

// Add implementation of member functions here


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("top() on empty heap");
  }
  return data_.front();
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element



}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("pop() on empty heap");


  }
  // Move last to root, remove last, then restore heap order
  std::swap(data_.front(), data_.back());
  data_.pop_back();
  if(!data_.empty()) {
    heapify(0);
  }



}



#endif

