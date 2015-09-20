#ifndef __NROS_ASSERT_H
#define __NROS_ASSERT_H

void assert_fail(const char assertion[], const char file[], unsigned int line,
	const char function[]) __attribute__((noreturn));

#define assert(expr)		\
	((expr) ? (void) 0	\
	 : assert_fail(#expr, __FILE__, __LINE__, __PRETTY_FUNCTION__))

#define assert_eq(expr1, expr2)	\
	assert((expr1) == (expr2))

#define assert_ne(expr1, expr2)	\
	assert((expr1) != (expr2))

#define assert_lt(expr1, expr2)	\
	assert((expr1) < (expr2))

#define assert_gt(expr1, expr2)	\
	assert((expr1) > (expr2))

#define assert_le(expr1, expr2)	\
	assert((expr1) <= (expr2))

#define assert_ge(expr1, expr2)	\
	assert((expr1) >= (expr2))

#endif /* end of include guard: __NROS_ASSERT_H */
