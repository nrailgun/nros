#ifndef __NROS_VARG_H
#define __NROS_VARG_H

typedef __builtin_va_list va_list;

#define va_start(v, l)	__builtin_va_start(v, l)

#define va_end(v)	__builtin_va_end(v)

#define va_arg(v, tp)	__builtin_va_arg(v, tp)

#endif /* end of include guard: __NROS_VARG_H */
