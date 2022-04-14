#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <vector>
#define random(x) rand()%x
template<typename T>
class Node {
public:
    Node() = default;
    Node(T data, int index_level, Node<T>* same_level_next, Node<T>* next_level_next):
        data_(data), 
        index_level_(index_level), 
        same_level_next_(same_level_next), 
        next_level_next_(next_level_next){}        
    ~Node() = default;


    T data_;
    int index_level_;
    Node<T>* same_level_next_;
    Node<T>* next_level_next_;
};

template<typename T>
class skiplist {
public:
    skiplist() = default;
    skiplist(int max_level): max_level_(max_level){
        head_ = new Node<T>*[max_level];
        for (int i = 0; i < max_level; i++) {
            head_[i] = nullptr;
        }
        srand((int)time(0));
    }
    ~skiplist() = default;
    bool insert_node(T data);
    bool delete_node(T data);
    Node<T> get_node(T data);
    bool set_node(T src_data, T dst_data);
    int random_level();
    void show_list();

private:
    Node<T>** head_;
    int max_level_;
    
};

template<typename T>
int skiplist<T>::random_level() {
    int level = 0;
    while (random(100) < 50 && level < max_level_) {
        level++;
    }
    return level;
    //while()
}

template<typename T>
bool skiplist<T>::delete_node(T data) {
    // 从最高层开始找
    bool res = false;
    for (int i = 9; i >= 0; i--) {
        Node<T>* head = head_[i];
        Node<T>* tmp = new Node<T>(-1, -1, head, nullptr);
        auto vir = tmp;
        while (vir) {
            if (vir->same_level_next_ != nullptr && vir->same_level_next_->data_ == data) {
                Node<T>* del = vir->same_level_next_;
                vir->same_level_next_ = vir->same_level_next_->same_level_next_;
                delete del;
                res = true;
            }
            vir = vir->same_level_next_;
        }

    }
    // 在某一层找到了的话，使用 next_level_next_ 继续往下删
    // 如果每一层都没有的话，返回 false
    return res;
}


template<typename T>
bool skiplist<T>::insert_node(T data) {
    // 首先判断需要生成几层索引 a 
    int level = random_level();
    // 从最高索引 a，依次开始往下添加节点
    Node<T>* level_head = head_[level];
    Node<T>* pre_level = nullptr;

    while (level >= 0) {
        
        Node<T>* tmp = new Node<T>(-1, -1, level_head, nullptr);
        Node<T>* vir = tmp;
        // vir->same_level_next_ = level_head;
        // vir->next_level_next_ = nullptr;
        while (vir->same_level_next_ != nullptr && vir->same_level_next_->data_ < data) {
            vir = vir->same_level_next_;
        }
        Node<T>* new_node = new Node<T>(data, level, vir->same_level_next_, nullptr);

        if (head_[level] == nullptr) {
            head_[level] = new_node;
        }
        vir->same_level_next_ = new_node;
        
        if (vir->next_level_next_) {
            level_head = vir->next_level_next_;
        } else if (level > 0) {
            level_head = head_[level - 1];
        }
        if (pre_level) {
            pre_level->next_level_next_ = new_node;
        }
        pre_level = new_node;
        level--;
        delete tmp;
    }

    return true;
}
template<typename T>
void skiplist<T>::show_list() {
    for (int i = 0; i < max_level_; i++) {
        auto level_head = head_[i];
        while (level_head != nullptr) {
            std::cout << level_head->data_ << " ";
            level_head = level_head->same_level_next_;
        }
        std::cout << std::endl;

    }
}

int main() {
    Node<int>* i = new Node<int>(10, 1, nullptr, nullptr);
    auto a = new skiplist<int>(10);
    // std::vector<int> vec(12, 0);
    // for (int i = 0; i < 100000000; i++) {
    //     vec[a->random_level()]++;
    // }
    // for (auto a : vec) {
    //     std::cout << a << std::endl;
    // }
    // std::cout << a->insert_node(10);
    std::cout << "log >>> " << std::endl;
    for (int i = 0; i < 20; i++) {
        a->insert_node(i);
    }
    // a->insert_node(0, 0);
    // a->insert_node(1, 2);
    // a->insert_node(2, 1);
    a->show_list();
    a->delete_node(10);
    a->show_list();
    return 0;
}