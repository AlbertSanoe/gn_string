/**
 * @author: GOU NGAI
 * @brief: This library is aiming to mimic, optimize and be in honor of the utstring library.
 * @date: 2022.10.21
 * @version 2.0
 */

#ifndef GNSTRING_H
#define GNSTRING_H

#include <stdio.h>  /* vsnprintf */
#include <stdlib.h> /* malloc, realloc, free, exit */
#include <stdarg.h> /* va_list, va_start, va_copy, va_end */
#include <stdint.h> /* int8_t */
#include <string.h> /* memcpy, strlen */

#define DEFAULT_INCREASE_SIZE   50
#define MINIMUM_SIZE    1

/**
 * @struct: _gn_string
 * @property:  _ptr    pointer to allocated buffer
 * @property:  _alloc  size(in bytes) of the allocated buffer
 * @property:  _cons   size(in bytes) of the buffer that is consumed, including NULL bit
 */
typedef struct GNSTRING
{
    int8_t *_ptr;
    size_t _alloc;
    size_t _cons;
} gn_string;

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define FALSE_EXIT() exit(-1)
#define LEN_ALLOC(_gn_string) ((_gn_string)->_alloc)  /* size of _alloc */
#define LEN_CONSUME(_gn_string) ((_gn_string)->_cons) /* size of _cons */
#define LEN_DATA(_gn_string) ((_gn_string)->_cons - 1)
#define IDX_NULL(_gn_string) ((_gn_string)->_cons - 1)

/**
 * @brief:  assign the blocks to the buffer
 */
#define BLOCK_ALLOC(_ptr, _amount)                             \
    do                                                         \
    {                                                          \
        if ((_amount) < MINIMUM_SIZE)                          \
        {                                                      \
            FALSE_EXIT();                                      \
        }                                                      \
        (_ptr) = (int8_t *)malloc((_amount) * sizeof(int8_t)); \
        if (!_ptr)                                             \
        {                                                      \
            FALSE_EXIT();                                      \
        }                                                      \
    } while (0)

/**
 * @brief:  reassign the blocks to the buffer(no matter the status of the original one)
 */
#define BLOCK_REALLOC(_ptr, _amount)                                    \
    do                                                                  \
    {                                                                   \
        if ((_amount) < MINIMUM_SIZE)                                   \
        {                                                               \
            FALSE_EXIT();                                               \
        }                                                               \
        (_ptr) = (int8_t *)realloc((_ptr), (_amount) * sizeof(int8_t)); \
        if (!_ptr)                                                      \
        {                                                               \
            FALSE_EXIT();                                               \
        }                                                               \
    } while (0)

/**
 * @brief:  free the buffer
 */
#define BLOCK_FREE(_ptr) \
    do                   \
    {                    \
        free(_ptr);      \
        (_ptr) = NULL;   \
    } while (0)

/**
 * @brief: copy the buffer from src to dest
 */
#define BLOCK_COPY(_dest, _src, _size) \
    do                                 \
    {                                  \
        memcpy(_dest, _src, _size);    \
    } while (0)

/**
 * @brief:  automatically assign 50 bytes to buffer, used AFTER _gn_string is initialized
 */
#define GNSTRING_INIT(_gn_string)                               \
    do                                                          \
    {                                                           \
        BLOCK_ALLOC((_gn_string)->_ptr, DEFAULT_INCREASE_SIZE); \
        (_gn_string)->_alloc = DEFAULT_INCREASE_SIZE;           \
        (_gn_string)->_cons = 1;                                \
        (_gn_string)->_ptr[0] = 0;                              \
    } while (0)

/**
 * @brief: assign bytes to buffer by _amount, used AFTER _gn_string is initialized
 * @param _amount:  the number of bytes for allocation
 */
#define GNSTRING_INIT_N(_gn_string, _amount)        \
    do                                              \
    {                                               \
        BLOCK_ALLOC((_gn_string)->_ptr, (_amount)); \
        (_gn_string)->_alloc = (_amount);           \
        (_gn_string)->_cons = 1;                    \
        (_gn_string)->_ptr[0] = 0;                  \
    } while (0)

/**
 * @brief:  initialize _gn_string type
 */
#define GNSTRING_ALLOC(_gn_string)                                 \
    do                                                             \
    {                                                              \
        gn_string *_gn_string_tmp = NULL;                          \
        (_gn_string_tmp) = (gn_string *)malloc(sizeof(gn_string)); \
        if (!(_gn_string_tmp))                                     \
        {                                                          \
            FALSE_EXIT();                                          \
        }                                                          \
        GNSTRING_INIT(_gn_string_tmp);                             \
        (_gn_string) = (_gn_string_tmp);                           \
    } while (0)

/**
 * @brief:  initialize _gn_string type by _amount
 */
#define GNSTRING_ALLOC_N(_gn_string, _amount)                      \
    do                                                             \
    {                                                              \
        gn_string *_gn_string_tmp = NULL;                          \
        (_gn_string_tmp) = (gn_string *)malloc(sizeof(gn_string)); \
        if (!(_gn_string_tmp))                                     \
        {                                                          \
            FALSE_EXIT();                                          \
        }                                                          \
        GNSTRING_INIT_N(_gn_string_tmp, _amount);                  \
        (_gn_string) = (_gn_string_tmp);                           \
    } while (0)

/**
 * @brief: shadow clear, the data are not overwritten
 */
#define GNSTRING_CLEAR(_gn_string)         \
    do                                     \
    {                                      \
        if (!(_gn_string))                 \
        {                                  \
            break;                         \
        }                                  \
        else                               \
        {                                  \
            (_gn_string)->_cons = 1;       \
            if (!((_gn_string)->_ptr))     \
            {                              \
                break;                     \
            }                              \
            else                           \
            {                              \
                (_gn_string)->_ptr[0] = 0; \
            }                              \
        }                                  \
    } while (0)

/**
 * @brief: deepcopy, the data are all wiped out
 */
#define GNSTRING_DEEPCLEAR(_gn_string)                              \
    do                                                              \
    {                                                               \
        if (!(_gn_string))                                          \
        {                                                           \
            break;                                                  \
        }                                                           \
        else                                                        \
        {                                                           \
            (_gn_string)->_cons = 1;                                \
            if (!((_gn_string)->_ptr))                              \
            {                                                       \
                break;                                              \
            }                                                       \
            else                                                    \
            {                                                       \
                BLOCK_FREE((_gn_string)->_ptr);                     \
                GNSTRING_INIT_N(_gn_string, LEN_ALLOC(_gn_string)); \
            }                                                       \
        }                                                           \
    } while (0)

/**
 * @brief: In adition to the deep cleaning, the size also changes by input
 */
#define GNSTRING_DEEPCLEAR_N(_gn_string, _amount)     \
    do                                                \
    {                                                 \
        if (!(_gn_string))                            \
        {                                             \
            break;                                    \
        }                                             \
        else                                          \
        {                                             \
            (_gn_string)->_cons = 1;                  \
            if (!((_gn_string)->_ptr))                \
            {                                         \
                break;                                \
            }                                         \
            else                                      \
            {                                         \
                BLOCK_FREE((_gn_string)->_ptr);       \
                GNSTRING_INIT_N(_gn_string, _amount); \
            }                                         \
        }                                             \
    } while (0)

#define GNSTRING_RENEW(_gn_string)          \
    do                                      \
    {                                       \
        if (_gn_string)                     \
        {                                   \
            GNSTRING_DEEPCLEAR(_gn_string); \
        }                                   \
        else                                \
        {                                   \
            GNSTRING_ALLOC(_gn_string);     \
        }                                   \
    } while (0)

#define GNSTRING_RENEW_N(_gn_string, _amount)          \
    do                                                 \
    {                                                  \
        if (!(_gn_string))                             \
        {                                              \
            GNSTRING_ALLOC_N(_gn_string, _amount);     \
        }                                              \
        else                                           \
        {                                              \
            GNSTRING_DEEPCLEAR_N(_gn_string, _amount); \
        }                                              \
    } while (0)

#define GNSTRING_REALLOC_N(_gn_string, _amount)         \
    do                                                  \
    {                                                   \
        if ((_amount) != LEN_ALLOC(_gn_string))         \
        {                                               \
            BLOCK_REALLOC((_gn_string)->_ptr, _amount); \
        }                                               \
        LEN_ALLOC(_gn_string) = _amount;                \
    } while (0)

#define GNSTRING_FREE(_gn_string)       \
    do                                  \
    {                                   \
        BLOCK_FREE((_gn_string)->_ptr); \
        (_gn_string)->_alloc = 0;       \
        (_gn_string)->_cons = 0;        \
        free(_gn_string);               \
        (_gn_string) = NULL;            \
    } while (0)

#define GNSTRING_COPY(_cpy, _src) \
    do                            \
    {                             \
        _cpy = _src;              \
    } while (0)

#define GNSTRING_DEEPCOPY(_cpy, _src)                           \
    do                                                          \
    {                                                           \
        if (!(_src))                                            \
        {                                                       \
            GNSTRING_FREE(_cpy);                                \
            break;                                              \
        }                                                       \
        if (!_cpy)                                              \
        {                                                       \
            GNSTRING_ALLOC_N(_cpy, LEN_ALLOC(_src));            \
        }                                                       \
        LEN_ALLOC(_cpy) = LEN_ALLOC(_src);                      \
        LEN_CONSUME(_cpy) = LEN_CONSUME(_src);                  \
        if ((_cpy)->_ptr)                                       \
        {                                                       \
            BLOCK_FREE((_cpy)->_ptr);                           \
        }                                                       \
        BLOCK_ALLOC((_cpy)->_ptr, LEN_ALLOC(_cpy));             \
        BLOCK_COPY((_cpy)->_ptr, (_src)->_ptr, LEN_DATA(_src)); \
        (_cpy)->_ptr[IDX_NULL(_cpy)] = 0;                       \
    } while (0)

#define GNSTRING_SLICE(_sub, _src, _spos, _epos)                                                              \
    do                                                                                                        \
    {                                                                                                         \
        if (!(_src))                                                                                          \
        {                                                                                                     \
            GNSTRING_FREE(_sub);                                                                              \
            break;                                                                                            \
        }                                                                                                     \
        if (!(_sub))                                                                                          \
        {                                                                                                     \
            GNSTRING_ALLOC_N(_sub, LEN_ALLOC(_src));                                                          \
        }                                                                                                     \
        LEN_ALLOC(_sub) = LEN_ALLOC(_src);                                                                    \
        if ((_sub)->_ptr[0])                                                                                  \
        {                                                                                                     \
            BLOCK_FREE((_sub)->_ptr);                                                                         \
            BLOCK_ALLOC((_sub)->_ptr, LEN_ALLOC(_src));                                                       \
            (_sub)->_ptr[0] = 0;                                                                              \
            LEN_CONSUME(_sub) = 1;                                                                            \
        }                                                                                                     \
        BLOCK_COPY((_sub)->_ptr, &((_src)->_ptr[MAX(0, _spos)]), MIN(IDX_NULL(_src), _epos) - MAX(0, _spos)); \
        LEN_CONSUME(_sub) += MIN(IDX_NULL(_src), _epos) - MAX(0, _spos);                                      \
        (_sub)->_ptr[IDX_NULL(_sub)] = 0;                                                                     \
    } while (0)

#define GNSTRING_CONCAT(_dest, _src)                                             \
    do                                                                           \
    {                                                                            \
        if (!(_src))                                                             \
        {                                                                        \
            break;                                                               \
        }                                                                        \
        if (!(_dest))                                                            \
        {                                                                        \
            GNSTRING_DEEPCOPY(_dest, _src);                                      \
            break;                                                               \
        }                                                                        \
        if ((LEN_ALLOC(_dest) - LEN_CONSUME(_dest)) < LEN_DATA(_src))            \
        {                                                                        \
            GNSTRING_REALLOC_N(_dest, LEN_ALLOC(_dest) + LEN_DATA(_src));        \
        }                                                                        \
        memcpy(&((_dest)->_ptr[IDX_NULL(_dest)]), (_src)->_ptr, LEN_DATA(_src)); \
        LEN_CONSUME(_dest) += LEN_DATA(_src);                                    \
        (_dest)->_ptr[IDX_NULL(_dest)] = 0;                                      \
    } while (0)

#define GNSTRING_CONCAT_CH(_dest, _src)                                          \
    do                                                                           \
    {                                                                            \
                                                                                 \
        if (!(_src))                                                             \
        {                                                                        \
            break;                                                               \
        }                                                                        \
        if (!(_dest))                                                            \
        {                                                                        \
            GNSTRING_ALLOC(_dest);                                               \
        }                                                                        \
        if ((LEN_ALLOC(_dest) == LEN_CONSUME(_dest)))                            \
        {                                                                        \
            GNSTRING_REALLOC_N(_dest, LEN_ALLOC(_dest) + DEFAULT_INCREASE_SIZE); \
        }                                                                        \
                                                                                 \
        (_dest)->_ptr[IDX_NULL(_dest)] = (_src);                                 \
        ++LEN_CONSUME(_dest);                                                    \
        (_dest)->_ptr[IDX_NULL(_dest)] = 0;                                      \
    } while (0)

#define GNSTRING_CONCAT_S(_dest, _src)                                                              \
    do                                                                                              \
    {                                                                                               \
        if (!(_src))                                                                                \
        {                                                                                           \
            break;                                                                                  \
        }                                                                                           \
        if (!(_dest))                                                                               \
        {                                                                                           \
            GNSTRING_ALLOC(_dest);                                                                  \
        }                                                                                           \
        if (LEN_ALLOC(_dest) - LEN_CONSUME(_dest) < strlen(_src))                                   \
        {                                                                                           \
            GNSTRING_REALLOC_N(_dest, LEN_ALLOC(_dest) + MAX(strlen(_src), DEFAULT_INCREASE_SIZE)); \
        }                                                                                           \
        memcpy(&(_dest)->_ptr[IDX_NULL(_dest)], &(_src), strlen(_src));                             \
        LEN_CONSUME(_dest) += strlen(_src);                                                         \
        (_dest)->_ptr[IDX_NULL(_dest)] = 0;                                                         \
    } while (0)

static void gn_string_format_va(gn_string *str, const char *format, va_list args)
{
    int n;
    va_list cp;
    for (;;)
    {
#ifdef _WIN32
        cp = args;
#else
        va_copy(cp, args);
#endif
        int8_t *tmp = &str->_ptr[IDX_NULL(str)];
        n = vsnprintf((char *)tmp, LEN_ALLOC(str) - LEN_CONSUME(str), format, cp);
        va_end(cp);

        if ((n > -1) && ((size_t)n < (LEN_ALLOC(str) - LEN_CONSUME(str))))
        {
            LEN_CONSUME(str) += n;
            return;
        }

        if (n > -1)
        {
            GNSTRING_REALLOC_N(str, n + 1);
        }
        else
        {
            GNSTRING_REALLOC_N(str, LEN_ALLOC(str) * 2);
        }
    }
}

#ifdef __GNUC__
static void gn_string_printf(gn_string *str, const char *format, ...)
    __attribute__((format(printf, 2, 3)));
#endif

static void gn_string_printf(gn_string *str, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    gn_string_format_va(str, format, args);
    va_end(args);
}

/*******************************************************************************
 *                      begin substring search functions                       *
 ******************************************************************************/

static void _gn_table(const int8_t *str, long *next, size_t length)
{
    size_t i, j;
    i = 1, j = 0;

    next[0] = 0;

    int pos_next;

    for (pos_next = 1; i < length; ++pos_next)
    {
        if (str[i] == str[j])
        {
            ++i;
            ++j;
            next[pos_next] = j;
        }
        else if (j)
        {
            j = next[j - 1];
            --pos_next;
        }
        else
        {
            next[pos_next] = 0;
            ++i;
        }
    }
}

/* static void _build_next_table_R(const int8_t *str, long *next, size_t length)
{
    size_t i, j;
    i = length - 2, j = length - 1;

    next[length - 1] = 0;

    int pos_next;

    for (pos_next = length - 2; i >= 0; --pos_next)
    {
        if (str[i] == str[j])
        {
            --i;
            --j;
            next[pos_next] = length - j;
        }
        else if (length - 1 - j)
        {
            j = next[j + 1];
            ++pos_next;
        }
        else
        {
            next[pos_next] = 0;
            --i;
        }
    }
} */

/* void build_next_table_R_c(const char *str, long *next, size_t length)
{
    size_t i, j;
    i = length - 2, j = length - 1;

    next[length - 1] = 0;

    int pos_next;

    for (pos_next = length - 2; i >= 0; --pos_next)
    {
        if (str[i] == str[j])
        {
            --i;
            --j;
            next[pos_next] = length - j;
        }
        else if (length - 1 - j)
        {
            j = next[j + 1];
            ++pos_next;
        }
        else
        {
            next[pos_next] = 0;
            --i;
        }
    }
} */

static long gn_search(const int8_t *str, long start_pos, long end_pos, const int8_t *sub, long sub_length)
{
    size_t tar, pos;
    tar = start_pos, pos = 0;

    long *next = (long *)malloc(sub_length * sizeof(long));

    _gn_table(sub, next, sub_length);

    for (; tar < end_pos;)
    {
        if (str[tar] == sub[pos])
        {
            ++tar;
            ++pos;
        }
        else if (pos)
        {
            pos = next[pos - 1];
        }
        else
        {
            ++tar;
        }
    }

    if (pos == sub_length)
    {
        return tar - pos;
    }
    else
    {
        return -1;
    }
}

static size_t gn_search_all(const int8_t *str, const int8_t *sub, long s_length, long sub_length, long *stack)
{
    size_t times = 0;

    size_t tar, pos;
    tar = 0, pos = 0;

    long *next = (long *)malloc(sub_length * sizeof(long));

    _gn_table(sub, next, sub_length);

    for (; tar < s_length;)
    {
        if (str[tar] == sub[pos])
        {
            ++tar;
            ++pos;
        }
        else if (pos)
        {
            pos = next[pos - 1];
        }
        else
        {
            ++tar;
        }

        if (pos == sub_length)
        {
            stack[times] = tar - pos;
            ++times;
            pos = next[pos - 1];
        }
    }

    return times;
}


static void _gn_table_c(const char *str, long *next, size_t length)
{
    size_t i, j;
    i = 1, j = 0;

    next[0] = 0;

    int pos_next;

    for (pos_next = 1; i < length; ++pos_next)
    {
        if (str[i] == str[j])
        {
            ++i;
            ++j;
            next[pos_next] = j;
        }
        else if (j)
        {
            j = next[j - 1];
            --pos_next;
        }
        else
        {
            next[pos_next] = 0;
            ++i;
        }
    }
}

static long gn_search_c(const char *str, long start_pos, long end_pos, const char *sub, size_t sub_length)
{
    size_t tar, pos;
    tar = start_pos, pos = 0;

    long *next = (long *)malloc(sub_length * sizeof(long));

    _gn_table_c(sub, next, sub_length);

    for (; tar < end_pos;)
    {
        if (str[tar] == sub[pos])
        {
            ++tar;
            ++pos;
        }
        else if (pos)
        {
            pos = next[pos - 1];
        }
        else
        {
            ++tar;
        }
    }

    if (pos == sub_length)
    {
        return tar - pos;
    }
    else
    {
        return -1;
    }
}

static size_t gn_search_all_c(const char *str, const char *sub, size_t s_length, size_t sub_length, long *stack)
{
    size_t times = 0;

    size_t tar, pos;
    tar = 0, pos = 0;

    long *next = (long *)malloc(sub_length * sizeof(long));

    _gn_table_c(sub, next, sub_length);

    for (; tar < s_length;)
    {
        if (str[tar] == sub[pos])
        {
            ++tar;
            ++pos;
        }
        else if (pos)
        {
            pos = next[pos - 1];
        }
        else
        {
            ++tar;
        }

        if (pos == sub_length)
        {
            stack[times] = tar - pos;
            ++times;
            pos = next[pos - 1];
        }
    }

    return times;
}

#define gn_string_to_str(_gn_string) ((char *)((_gn_string)->_ptr)) /* return the data in type of pointer to char */
#define gn_string_len(_gn_string) LEN_DATA(_gn_string) /* return the length of gn_string */
#define gn_string_new(_gn_string) GNSTRING_ALLOC(_gn_string)
#define gn_string_new_n(_gn_string,_amount) GNSTRING_ALLOC_N(_gn_string, _amount)
#define gn_string_clear(_gn_string) GNSTRING_CLEAR(_gn_string)
#define gn_string_renew(_gn_string) GNSTRING_RENEW(_gn_string)
#define gn_string_renew_n(_gn_string, _amount) GNSTRING_RENEW_N(_gn_string, _amount)
#define gn_string_resize(_gn_string, _amount) GNSTRING_REALLOC_N(_gn_string, _amount)
#define gn_string_free(_gn_string) GNSTRING_FREE(_gn_string)
#define gn_string_concat(_dest,_src) GNSTRING_CONCAT(_dest, _src)
#define gn_string_concat_c(_dest,_src) GNSTRING_CONCAT_CH(_dest,_src)
#define gn_string_concat_str(_dest,_src) GNSTRING_CONCAT_S(_dest,_src)
#define gn_string_copy(_cpy,_src) GNSTRING_COPY(_cpy, _src)
#define gn_string_deepcopy(_cpy, _src) GNSTRING_DEEPCOPY(_cpy, _src) 
#define gn_string_slice(_sub,_copy,_spos,_epos) GNSTRING_SLICE(_sub,_copy,_spos,_epos)

#endif