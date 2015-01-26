#ifndef _BASIC_H_
#define _BASIC_H_

#define BASIC_MATH_ADD 1
#define BASIC_MATH_SUB 2
#define BASIC_MATH_MUL 3
#define BASIC_MATH_DIV 4
#define BASIC_MATH_MOD 5

#define BASIC_LVAL_EXPR  0
#define BASIC_LVAL_VAR   1
#define BASIC_RVAL_EXPR  2
#define BASIC_RVAL_VAR   3
#define BASIC_RVAL_CONST 4

#define BASIC_FOUND_LVAL 0x0001
#define BASIC_FOUND_RVAL 0x0002

#define BASIC_ERR_SYNTAX_MULTIPLE_LVALUES 1
#define BASIC_ERR_SYNTAX_TOKEN_LENGTH 2
#define BASIC_ERR_SYNTAX_GENERAL 3
#define BASIC_ERR_SYNTAX_MULTIPLE_RVALUES 4

#define BASIC_TOKENIZER_MAX_LENGTH 512

struct basic_math_expr {
  char type;
  char lval_type;
  char rval_type;
  char pad;
  void *lval;
  void *rval;
};

extern int basic_errno;

void run_basic(void);

#endif /* _BASIC_H_ */
