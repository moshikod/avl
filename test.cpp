/**
 * @file demo.cpp
 * @author Moshe Pontch (pontch at gmail.com)
 * @brief Basic test for AVL library
 * @date 2022-08-31
 *
 */#include <chrono>
#include <iostream>

#include "avl_tool.h"

using namespace std;
using namespace std::chrono;

#define LOG(x) clog << x << endl

#define TEST(name, code)                                                                                           \
    bool name()                                                                                                    \
    {                                                                                                              \
        const auto start = high_resolution_clock::now();                                                           \
        bool result = true;                                                                                        \
        switch (0)                                                                                                 \
        {                                                                                                          \
        default:                                                                                                   \
            code;                                                                                                  \
        }                                                                                                          \
        auto duration_ms = duration_cast<microseconds>(high_resolution_clock::now() - start);                      \
        LOG("TEST " << #name << " " << (result ? "SUCCEEDED" : "FAILED") << " (" << duration_ms.count() << "us)"); \
        return result;                                                                                             \
    }

#define TEST_ASSERT(condition, report)                          \
    {                                                           \
        if (!(condition))                                       \
        {                                                       \
            LOG(__FILE__ << ":" << __LINE__ << ": " << report); \
            result = false;                                     \
            break;                                              \
        }                                                       \
    }

#define TEST_MAIN(tests...)             \
    int main(int, const char **)        \
    {                                   \
        bool pass = true;               \
        for (const auto test : {tests}) \
        {                               \
            pass &= test();             \
        }                               \
        return pass ? 0 : 1;            \
    }

struct TestData
{
    int i;
};

typedef AvlTree<TestData> TestTree;

std::ostream &operator<<(std::ostream &os, const TestData &data)
{
    os << "I: " << data.i;
    return os;
}

static TestTree tree;

TEST(avl_populate,
     {
         srand(time(NULL));

         int i;
         int key;

         for (i = 0; i < 10; i++)
         {
             key = rand() % 30 + 1;
             tree.insert(key, {i});
         }
         // LOG(avl_inorder << tree);
         // LOG(avl_simple << tree);
     })

TEST(avl_copy_constructor,
     {
         TestTree tree1(tree);
         TEST_ASSERT(tree == tree1, "same content");
         TEST_ASSERT(&tree != &tree1, "different address");
     })

TEST(avl_assigment_operator,
     {
         TestTree tree1;
         tree1 = tree;
         TEST_ASSERT(tree == tree1, "same content");
         TEST_ASSERT(&tree != &tree1, "different address");
     })

TEST(avl_value_manipulation,
     {
         TestTree tree1(tree);
         tree1.insert(31, {-1});
         TEST_ASSERT(tree != tree1, "value inserted");

         TestData data;
         tree1.remove(31, &data);
         TEST_ASSERT(tree == tree1, "value removed");
     })

#ifdef __cplusplus
extern "C"
{
#endif

    TEST_MAIN(
        avl_populate,
        avl_copy_constructor,
        avl_assigment_operator,
        avl_value_manipulation);

#ifdef __cplusplus
}
#endif
