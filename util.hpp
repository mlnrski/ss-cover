#include <memory>

template<typename T>
void annihilate(T *ptr);

template<typename T>
struct Annihilator {
    void operator()(T *ptr) const
    {
        annihilate(ptr);
    }
};