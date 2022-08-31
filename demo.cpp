/**
 * @file demo.cpp
 * @author Moshe Pontch (pontch at gmail.com)
 * @brief Dynamic display of changes in AVL tree
 * @date 2022-08-31
 *
 */
#include <iostream>
#include <list>
#include <thread>

#include "avl_tool.h"

/* use wide characters, comment out for narrow characters */
#define _USE_WCHAR_T

using namespace std;

constexpr auto _ANSI_CLEAR = "\033[2J\033[1;1H";
constexpr auto _ITEM_COUNT = 15;
constexpr auto _STEP_COUNT = 99;
constexpr auto _MAX_VALUE = 999;
constexpr auto _WAIT_IN_MS = 70;

inline int rand_key()
{
    return rand() % _MAX_VALUE;
}

template <typename Char, typename Traits>
int demo(std::basic_ostream<Char, Traits> &os)
{
    AvlTree<int> tree;
    list<int> items;

    srand(time(0));

    os << avl_levelorder << avl_summary;

    for (int i = 0; i < _STEP_COUNT * 2; i++)
    {
        if (tree.count() < _ITEM_COUNT)
        {
            const auto key = rand() % _MAX_VALUE;
            tree.insert(key, {key});
            items.push_back(key);
        }
        else
        {
            int data;
            tree.remove(items.front(), &data);
            items.pop_front();
        }
        os << _ANSI_CLEAR;
        os << tree << endl;
        this_thread::sleep_for(chrono::milliseconds(_WAIT_IN_MS));
    }

    return 0;
}

#ifdef __cplusplus
extern "C"
{
#endif

    int main(int, const char **)
    {
#ifdef _USE_WCHAR_T
        std::locale::global(std::locale(""));
        std::wcout.imbue(std::locale());
        return demo(wcout);
#else
    return demo(cout);
#endif
    }

#ifdef __cplusplus
}
#endif
