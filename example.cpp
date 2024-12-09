/**
 * @file example.cpp
 * @author Moshe Pontch (pontch at gmail.com)
 * @brief Short example of using the AVL library
 * @date 2022-08-31
 *
 */
#include <bitset>
#include <iostream>
#include <thread>

#include "avl_tool.h"

/* use wide characters, comment out for narrow characters */
#define _USE_WCHAR_T

using namespace std;

struct TestData
{
    int i;
};

template <typename Char, typename Traits>
std::basic_ostream<Char, Traits> &operator<<(std::basic_ostream<Char, Traits> &os, const TestData &data)
{
    const auto flags = avl_flags(os);

    if (flags & avl::preorder)
    {
        os << std::bitset<8>(data.i);
    }
    else if (flags & avl::inorder)
    {
        os << oct << std::showbase << data.i;
    }
    else if (flags & avl::postorder)
    {
        os << hex << std::showbase << data.i;
    }
    else
    {
        os << dec << data.i;
    }

    return os;
}

template <typename Char, typename Traits>
int example(std::basic_ostream<Char, Traits> &os)
{
    AvlTree<TestData> tree;

    srand(time(0));

    for (int i = 0; i < 24; i++)
    {
        const auto key = rand() % 100;
        tree.insert(key, {key});
    }

    os << "summary with the default flat representation" << endl;
    os << avl_summary << tree;
    os << avl_simple; // reset summary
    os << endl
       << "preorder traversal using binary base" << endl;
    os << avl_preorder << tree;
    os << endl
       << "inorder traversal using octal base" << endl;
    os << avl_inorder << tree;
    os << endl
       << "postorder traversal using hexadecimal base" << endl;
    os << avl_postorder << tree;
    os << endl
       << "levelorder traversal using decimal base" << endl;
    os << avl_levelorder << tree;

    return 0;
}

int main(int, const char **)
{
#ifdef _USE_WCHAR_T
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale());
    return example(wcout);
#else
    return example(cout);
#endif
}
