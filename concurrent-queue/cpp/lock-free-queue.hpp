#include <atomic>
#include <memory>

template <typename T>
class lock_free_queue {
 private:
  struct node {
    std::shared_ptr<T> data;
    node* next;

    node() : next(nullptr) {}  //  initialise the node
  };

  std::atomic<node*> head;
  std::atomic<node*> tail;

 public:
  lock_free_queue() {
    this->head = new node();
    this->tail = this->head.load();
  }
  ~lock_free_queue() {
    while (node* const old_head = this->head.load()) {
      this->head.store(old_head->next);
      delete old_head;
    }
  }

  void enqueue(T value) {
    std::shared_ptr<T> new_data = std::make_shared<T>(value);
    node* new_node = new node();
    new_node->data = new_data;

    //  do an infinite loop to change the tail
    while (true) {
      node* current_tail = this->tail.load();
      node* tail_next = current_tail->next;

      //  everything is correct so far, attempt the swap
      if (std::atomic_compare_exchange_strong(current_tail->next, tail_next, new_node, std::memory_order_seq_cst)) {
        this->tail = new_node;
        break;  //  swap worked, break out
      }
    }
  }

  std::shared_ptr<T> dequeue() {
    node* current_head = this->head.load();

    //  do an infinite loop the change the head
    while (true) {
      
    }
  }
};