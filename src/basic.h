#ifndef _BASIC_H_
#define _BASIC_H_

#define BASIC_OPTP_ADD 1
#define BASIC_OPTP_SUB 2
#define BASIC_OPTP_MUL 3
#define BASIC_OPTP_DIV 4
#define BASIC_OPTP_MOD 5
#define BASIC_OPTP_EQL 6
#define BASIC_OPTP_ASN 7
#define BASIC_OPTP_STMT 8

#define BASIC_LVAL_EXPR  1
#define BASIC_LVAL_VAR   2
#define BASIC_LVAL_CONST 3
#define BASIC_RVAL_EXPR  4
#define BASIC_RVAL_VAR   5
#define BASIC_RVAL_CONST 6

#define BASIC_FOUND_LVAL 0x0001
#define BASIC_FOUND_RVAL 0x0002

#define BASIC_ERR_SYNTAX_MULTIPLE_LVALUES 1
#define BASIC_ERR_SYNTAX_TOKEN_LENGTH 2
#define BASIC_ERR_SYNTAX_GENERAL 3
#define BASIC_ERR_SYNTAX_MULTIPLE_RVALUES 4
#define BASIC_ERR_INVALID_ARGUMENTS 5
#define BASIC_ERR_INTERNAL_NULLPOINTER 6
#define BASIC_ERR_INTERNAL_MEMORY 7
#define BASIC_ERR_INTERNAL_UNDEFINED_BEHAVIOR 8
#define BASIC_ERR_INTERNAL_UNIMPLEMENTED 9
#define BASIC_ERR_MATH_DBZ 10
#define BASIC_ERR_UNBALANCED_PARENS 11

#define BASIC_TOKENIZER_TOKENS " +-/%*="
#define BASIC_TOKENIZER_MAX_LENGTH 512
#define BASIC_VARNAME_MAX_LENGTH 16

#define BASIC_VARFLAG_INIT 1
#define BASIC_VARFLAG_TINT 2
#define BASIC_VARFLAG_TSTR 4

struct basic_variable {
  char *name;
  char flags;
  void *value;
};

struct basic_expr {
  char type;
  char left_parens;
  char right_parens;
  char lval_type;
  char rval_type;
  char pad;
  void *lval;
  void *rval;
  struct basic_variable result;
};

#define BASIC_CONST_TRUE 1
#define BASIC_CONST_FALSE 0

extern int basic_errno;

void _tokenizer_init(void);
char *_tokenize(char *ptr, char *token);
int basic_solve_expr(struct basic_expr *expr, struct basic_variable *result);
struct basic_expr *basic_parse_expr(char *expbuf, int expr_depth);
void basic_print_var(struct basic_variable *var);

void basic_repl(void);

#endif /* _BASIC_H_ */
