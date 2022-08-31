/**
 * @file avl_tool.h
 * @author Moshe Pontch (pontch at gmail.com)
 * @brief AVL tree output to standard output streams
 * @version 1.0
 * @date 2022-08-31
 *
 */
#ifndef _AVL_TOOL__H
#define _AVL_TOOL__H

#include <cmath>
#include <iomanip>
#include <set>
#include <sstream>

#include "avl.h"

using namespace std;

static int _tree_fmt_xalloc = ios_base::xalloc();

namespace avl
{
    enum _fmtchars
    {
        horz_line,
        vert_line,
        top_left,
        top_right,
        bottom_left,
        bottom_right,
        vert_right,
        horz_up,
        space,
        left_bracket,
        right_bracket,
        delimiter,
        unknown,
        _COUNT,
    };

    const char _fmt_char[_fmtchars::_COUNT] = {
        '-', // horz_line
        '|', // vert_line
        '+', // top_left
        '+', // top_right
        '+', // bottom_left
        '+', // bottom_right
        '+', // vert_right
        '+', // horz_up
        ' ', // space
        '(', // left_bracket
        ')', // right_bracket
        ',', // delimiter
        '?', // unknown
    };

    const wchar_t _fmt_wchar[_fmtchars::_COUNT] = {
        L'─', // horz_line
        L'│', // vert_line
        L'┌', // top_left
        L'┐', // top_right
        L'└', // bottom_left
        L'┘', // bottom_right
        L'├', // vert_right
        L'┴', // horz_up
        L' ', // space
        L'(', // left_bracket
        L')', // right_bracket
        L',', // delimiter
        L'?', // unknown
    };

    enum fmtflags
    {
        _simple = 0,
        _summary = 1L << 0,
        _preorder = 1L << 1,
        _postorder = 1L << 2,
        _inorder = 1L << 3,
        _levelorder = 1L << 4,
    };

    static const avl::fmtflags summary = avl::fmtflags::_summary;
    static const avl::fmtflags preorder = avl::fmtflags::_preorder;
    static const avl::fmtflags postorder = avl::fmtflags::_postorder;
    static const avl::fmtflags inorder = avl::fmtflags::_inorder;
    static const avl::fmtflags levelorder = avl::fmtflags::_levelorder;

    template <typename Char>
    const Char _get_fmtchar(avl::_fmtchars);

    template <>
    const char _get_fmtchar<char>(avl::_fmtchars fmt_char)
    {
        return _fmt_char[fmt_char];
    }

    template <>
    const wchar_t _get_fmtchar<wchar_t>(avl::_fmtchars fmt_char)
    {
        return _fmt_wchar[fmt_char];
    }
} // namespace avl

#define _HL avl::_get_fmtchar<Char>(avl::_fmtchars::horz_line)
#define _VL avl::_get_fmtchar<Char>(avl::_fmtchars::vert_line)
#define _TL avl::_get_fmtchar<Char>(avl::_fmtchars::top_left)
#define _TR avl::_get_fmtchar<Char>(avl::_fmtchars::top_right)
#define _BL avl::_get_fmtchar<Char>(avl::_fmtchars::bottom_left)
#define _BR avl::_get_fmtchar<Char>(avl::_fmtchars::bottom_right)
#define _VR avl::_get_fmtchar<Char>(avl::_fmtchars::vert_right)
#define _HU avl::_get_fmtchar<Char>(avl::_fmtchars::horz_up)
#define _SP avl::_get_fmtchar<Char>(avl::_fmtchars::space)
#define _LB avl::_get_fmtchar<Char>(avl::_fmtchars::left_bracket)
#define _RB avl::_get_fmtchar<Char>(avl::_fmtchars::right_bracket)
#define _DL avl::_get_fmtchar<Char>(avl::_fmtchars::delimiter)
#define _UK avl::_get_fmtchar<Char>(avl::_fmtchars::unknown)

static const auto _ordermask = avl::fmtflags::_preorder | avl::fmtflags::_postorder | avl::fmtflags::_inorder | avl::fmtflags::_levelorder;

template <typename Char, typename Traits>
inline avl::fmtflags avl_flags(std::basic_ostream<Char, Traits> &os)
{
    return static_cast<avl::fmtflags>(os.iword(_tree_fmt_xalloc));
}

template <typename Char, typename Traits>
inline avl::fmtflags avl_flags(std::basic_ostream<Char, Traits> &os, avl::fmtflags flags)
{
    os.iword(_tree_fmt_xalloc) = flags;
    return avl_flags(os);
}

template <typename Char, typename Traits>
inline std::basic_ostream<Char, Traits> &avl_simple(std::basic_ostream<Char, Traits> &os)
{
    avl_flags(os, avl::fmtflags::_simple);
    return os;
}

template <typename Char, typename Traits>
inline std::basic_ostream<Char, Traits> &avl_summary(std::basic_ostream<Char, Traits> &os)
{
    os.iword(_tree_fmt_xalloc) |= avl::fmtflags::_summary;
    return os;
}

template <typename Char, typename Traits>
inline std::basic_ostream<Char, Traits> &avl_preorder(std::basic_ostream<Char, Traits> &os)
{
    os.iword(_tree_fmt_xalloc) &= ~_ordermask;
    os.iword(_tree_fmt_xalloc) |= avl::fmtflags::_preorder;
    return os;
}

template <typename Char, typename Traits>
inline std::basic_ostream<Char, Traits> &avl_inorder(std::basic_ostream<Char, Traits> &os)
{
    os.iword(_tree_fmt_xalloc) &= ~_ordermask;
    os.iword(_tree_fmt_xalloc) |= avl::fmtflags::_inorder;
    return os;
}

template <typename Char, typename Traits>
inline std::basic_ostream<Char, Traits> &avl_postorder(std::basic_ostream<Char, Traits> &os)
{
    os.iword(_tree_fmt_xalloc) &= ~_ordermask;
    os.iword(_tree_fmt_xalloc) |= avl::fmtflags::_postorder;
    return os;
}

template <typename Char, typename Traits>
inline std::basic_ostream<Char, Traits> &avl_levelorder(std::basic_ostream<Char, Traits> &os)
{
    os.iword(_tree_fmt_xalloc) &= ~_ordermask;
    os.iword(_tree_fmt_xalloc) |= avl::fmtflags::_levelorder;
    return os;
}

/**
 * @brief avoid std::endl flush
 */
template <typename Char, typename Traits>
inline std::basic_ostream<Char, Traits> &_endl(std::basic_ostream<Char, Traits> &os)
{
    os.put(os.widen('\n'));
    return os;
}

template <class T>
class AvlNodeTool
{
public:
    template <typename Char, typename Traits, typename Allocator>
    static std::basic_ostream<Char, Traits> &preorder(
        std::basic_ostream<Char, Traits> &os,
        const AvlNode<T> *node,
        const std::basic_string<Char, Traits, Allocator> prefix,
        bool is_left = false,
        bool root = true)
    {
        if (node)
        {
            const std::basic_string<Char, Traits, Allocator> this_prefix = root ? std::basic_string<Char, Traits, Allocator>() : prefix + (is_left ? _VR : _BL) + _HL + _HL;
            os << this_prefix << *node << _endl;
            const std::basic_string<Char, Traits, Allocator> next_prefix = root ? std::basic_string<Char, Traits, Allocator>() : prefix + (is_left ? _VL : _SP) + _SP + _SP;
            if (node->left())
            {
                AvlNodeTool<T>::preorder(os, node->left(), next_prefix, node->right(), false);
            }
            if (node->right())
            {
                AvlNodeTool<T>::preorder(os, node->right(), next_prefix, false, false);
            }
        }
        return os;
    }

    template <typename Char, typename Traits, typename Allocator>
    static std::basic_ostream<Char, Traits> &inorder(
        std::basic_ostream<Char, Traits> &os,
        const AvlNode<T> *node,
        const std::basic_string<Char, Traits, Allocator> prefix,
        bool is_left = false,
        bool root = true)
    {
        if (node)
        {
            if (node->left())
            {
                const std::basic_string<Char, Traits, Allocator> left_prefix = root ? std::basic_string<Char, Traits, Allocator>() : prefix + (is_left ? _SP : _VL) + _SP + _SP;
                AvlNodeTool<T>::inorder(os, node->left(), left_prefix, true, false);
            }
            const std::basic_string<Char, Traits, Allocator> this_prefix = root ? std::basic_string<Char, Traits, Allocator>() : prefix + (is_left ? _TL : _BL) + _HL + _HL;
            os << this_prefix << node << _endl;
            if (node->right())
            {
                const std::basic_string<Char, Traits, Allocator> right_prefix = root ? std::basic_string<Char, Traits, Allocator>() : prefix + (is_left ? _VL : _SP) + _SP + _SP;
                AvlNodeTool<T>::inorder(os, node->right(), right_prefix, false, false);
            }
        }
        return os;
    }

    template <typename Char, typename Traits, typename Allocator>
    static std::basic_ostream<Char, Traits> &postorder(
        std::basic_ostream<Char, Traits> &os,
        const AvlNode<T> *node,
        const std::basic_string<Char, Traits, Allocator> prefix,
        bool is_left = false,
        bool root = true)
    {
        if (node)
        {
            const std::basic_string<Char, Traits, Allocator> next_prefix = root ? std::basic_string<Char, Traits, Allocator>() : prefix + (is_left ? _VL : _SP) + _SP + _SP;
            if (node->right())
            {
                AvlNodeTool<T>::postorder(os, node->right(), next_prefix, false, false);
            }
            if (node->left())
            {
                AvlNodeTool<T>::postorder(os, node->left(), next_prefix, node->right(), false);
            }
            const std::basic_string<Char, Traits, Allocator> this_prefix = root ? std::basic_string<Char, Traits, Allocator>() : prefix + (is_left ? _VR : _TL) + _HL + _HL;
            os << this_prefix << *node << _endl;
        }
        return os;
    }

    template <typename Char, typename Traits>
    static std::basic_ostream<Char, Traits> &levelorder(
        std::basic_ostream<Char, Traits> &os,
        AvlNode<T> *node,
        int node_width,
        int width,
        int level,
        bool is_left = false,
        bool is_root = true)
    {
        if (node)
        {
            if (level)
            {
                levelorder(os, node->left(), node_width, width / 2, level - 1, true, false);
                levelorder(os, node->right(), node_width, width / 2, level - 1, false, false);
            }
            else
            {
                const auto width_left = (width - node_width) / 2 - 1;
                if (node->left())
                {
                    os << _s(width_left / 2, _SP) << _TL << _s(width_left - (width_left / 2), _HL);
                }
                else
                {
                    os << _s(width_left + 1, _SP);
                }
                if (is_root)
                {
                    os << setw(0);
                    std::basic_stringstream<Char, Traits, std::allocator<Char>> ss;
                    ss << node;
                    const auto node_length = ss.str().length();
                    const auto node_left = (node_width - node_length) / 2;
                    os << _s(node_left, node->left() ? _HL : _SP) << ss.str() << _s(node_width - node_left - node_length, node->right() ? _HL : _SP);
                }
                else
                {
                    os << setw(node_width);
                    if (is_left)
                    {
                        os << std::setfill(node->right() ? _HL : _SP) << std::left;
                    }
                    else
                    {
                        os << std::setfill(node->left() ? _HL : _SP) << std::right;
                    }
                    os << node;
                }
                const auto width_right = width - node_width - width_left - 2;
                if (node->right())
                {
                    os << _s(width_right - (width_right / 2), _HL) << _TR << _s(width_right / 2, _SP);
                }
                else
                {
                    os << _s(width_right + 1, _SP);
                }
            }
        }
        else
        {
            os << _s(width, _SP);
        }
        return os;
    }

    template <typename Char, typename Traits>
    static std::basic_ostream<Char, Traits> &levelorder(
        std::basic_ostream<Char, Traits> &os,
        AvlNode<T> *node,
        int node_width)
    {
        if (node)
        {
            const auto height = node->height();
            const auto width = int(pow(2, height - 1)) * (node_width + 2);
            for (auto level = 0; level < height; level++)
            {
                levelorder(os, node, node_width, width, level) << _endl;
            }
        }
        return os;
    }

private:
    AvlNodeTool(){};

    static inline const std::string _s(size_t n, const char c)
    {
        return std::string(n, c);
    }

    static inline const std::wstring _s(size_t n, const wchar_t c)
    {
        return std::wstring(n, c);
    }
};

template <class T>
class AvlTreeTool
{
public:
    static bool is_tree(const AvlTree<T> &tree)
    {
        std::set<const AvlNode<T> *> visited;
        return is_tree(visited, tree.root());
    }

    template <typename Char, typename Traits>
    static std::basic_ostream<Char, Traits> &preorder(std::basic_ostream<Char, Traits> &os, const AvlTree<T> &tree)
    {
        AvlNodeTool<T>::preorder(os, tree.root(), std::basic_string<Char, Traits, std::allocator<Char>>());
        return os;
    }

    template <typename Char, typename Traits>
    static std::basic_ostream<Char, Traits> &inorder(std::basic_ostream<Char, Traits> &os, const AvlTree<T> &tree)
    {
        AvlNodeTool<T>::inorder(os, tree.root(), std::basic_string<Char, Traits, std::allocator<Char>>());
        return os;
    }

    template <typename Char, typename Traits>
    static std::basic_ostream<Char, Traits> &postorder(std::basic_ostream<Char, Traits> &os, const AvlTree<T> &tree)
    {
        AvlNodeTool<T>::postorder(os, tree.root(), std::basic_string<Char, Traits, std::allocator<Char>>());
        return os;
    }

    template <typename Char, typename Traits>
    static std::basic_ostream<Char, Traits> &levelorder(std::basic_ostream<Char, Traits> &os, const AvlTree<T> &tree)
    {
        AvlNodeTool<T>::levelorder(os, tree.root(), log10(tree.max_key()) + 1);
        return os;
    }

    template <typename Char, typename Traits>
    static std::basic_ostream<Char, Traits> &summary(std::basic_ostream<Char, Traits> &os, const AvlTree<T> &tree)
    {
        os << "#:" << tree.count() << ",L:" << tree.min_left() << ",R:" << tree.max_right();
        return os;
    }

    template <typename Char, typename Traits>
    static std::basic_ostream<Char, Traits> &flatten(std::basic_ostream<Char, Traits> &os, const AvlTree<T> &tree, const Char delimiter = _DL)
    {
        AvlNode<T> *node = tree.min_left();
        bool first = true;
        os << _LB;
        while (node)
        {
            if (!first)
            {
                os << delimiter;
            }
            first = false;
            os << node->key();
            node = node->next();
        }
        os << _RB << _endl;
        return os;
    }

private:
    AvlTreeTool(){};
};

template <class T, typename Char, typename Traits>
std::basic_ostream<Char, Traits> &operator<<(std::basic_ostream<Char, Traits> &os, const AvlNode<T> &node)
{
    os << node.data;
    return os;
}

template <class T, typename Char, typename Traits>
std::basic_ostream<Char, Traits> &operator<<(std::basic_ostream<Char, Traits> &os, const AvlNode<T> *node)
{
    if (node)
    {
        os << *node;
    }
    else
    {
        const auto flags = avl_flags(os);
        if (flags & avl::fmtflags::_summary)
        {
            os << _UK;
        }
    }
    return os;
}

template <class T, typename Char, typename Traits>
std::basic_ostream<Char, Traits> &operator<<(std::basic_ostream<Char, Traits> &os, const AvlTree<T> &tree)
{
    const auto flags = avl_flags(os);

    if (flags & avl::fmtflags::_summary)
    {
        AvlTreeTool<T>::summary(os, tree) << _endl;
    }

    switch (flags & _ordermask)
    {
    case avl::fmtflags::_preorder:
        AvlTreeTool<T>::preorder(os, tree);
        break;
    case avl::fmtflags::_postorder:
        AvlTreeTool<T>::postorder(os, tree);
        break;
    case avl::fmtflags::_inorder:
        AvlTreeTool<T>::inorder(os, tree);
        break;
    case avl::fmtflags::_levelorder:
        AvlTreeTool<T>::levelorder(os, tree);
        break;
    default:
        AvlTreeTool<T>::flatten(os, tree);
        break;
    }

    return os;
}

#endif // _AVL_TOOL__H
