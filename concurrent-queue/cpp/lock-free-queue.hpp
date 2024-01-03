#include <atomic>
#include <memory>

template <typename T>
class lock_free_queue {
 private:
  struct node {
    std::shared_ptr<T> data;
    std::atomic<node*> next;

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
      node* current_tail = this->tail.load(std::memory_order_seq_cst);
      node* tail_next = current_tail->next;

      //  everything is correct so far, attempt the swap
      if (current_tail->next.compare_exchange_strong(tail_next, new_node, std::memory_order_seq_cst, std::memory_order_seq_cst)) {
        this->tail = new_node;
        break;
      }
    }
  }

  std::shared_ptr<T> dequeue() {
    std::shared_ptr<T> return_value = nullptr;

    //  do an infinite loop the change the head
    while (true) {
      node* current_head = this->head.load(std::memory_order_seq_cst);
      node* next_node = current_head->next;

      if (current_head != this->head.load(std::memory_order_seq_cst)) {
        continue;
      }

      if (this->head.compare_exchange_strong(current_head, next_node, std::memory_order_seq_cst)) {
        return_value.swap(next_node->data);
        delete current_head;
        break;
      }
    }
    return return_value;
  }
};