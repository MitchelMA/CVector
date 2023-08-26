#ifndef PRIVATE_H__
#define PRIVATE_H__

#ifndef NODISCARD
    #define NODISCARD
    #if defined(__GNUC__) && !defined(__clang__)
        #undef NODISCARD
        #define NODISCARD [[nodiscard]]
    #endif // __GNUC__ && !__clang__
#endif // !NODISCARD

#endif // !PRIVATE_H__
