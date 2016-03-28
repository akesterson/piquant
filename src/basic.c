#include "basic.h"
#include "screen.h"
#include "conio.h"
#include "string.h"
#include "stdlib.h"

struct basic_expr expressions[32];
int basic_errno;

char _tokenizer_value[BASIC_TOKENIZER_MAX_LENGTH];
char *_tokenizer_prev;
char *_tokenizer_prev_next;

void _tokenizer_init(void)
{
  _tokenizer_prev = NULL;
  _tokenizer_prev_next = NULL;
}

char *_tokenize(char *ptr, char *token)
{
  char *orig = NULL;
  char *tokenptr = NULL;
  int len = 0;

  if ( ptr == NULL ) {
    return NULL;
  }
  if ( _tokenizer_prev == ptr ) {
    ptr = _tokenizer_prev_next;
  }
  orig = ptr;

  memset(&_tokenizer_value, 0x00, BASIC_TOKENIZER_MAX_LENGTH);
  while ( *ptr != 0x0 ) {
    tokenptr = token;

    /* I don't understand why this works. It shouldn't work. */
    while ( *tokenptr != 0x0 && (*ptr == *tokenptr++) ) {};
    /* ----------------------------------------------------- */

    if ( *tokenptr == 0x00 ) {
      break;
    } else {
      if ( *ptr == '\0' ) {
	ptr -= sizeof(char);
	break;
      }
      ptr += sizeof(char);
      len += 1;
    }
  }
  if ( len > BASIC_TOKENIZER_MAX_LENGTH ) {
    basic_errno = BASIC_ERR_SYNTAX_TOKEN_LENGTH;
    return NULL;
  } else if ( len == 0 ) {
    return NULL;
  }
  memcpy((void *)&_tokenizer_value, (void *)orig, len); 
  _tokenizer_prev_next = (ptr + 1);
  return (char *)&_tokenizer_value;
}

int basic_solve_expr(struct basic_expr *expr, struct basic_variable *result)
{
  if ( expr == NULL || result == NULL ) {
    basic_errno = BASIC_ERR_INTERNAL_NULLPOINTER;
    return NULL;
  }

  switch (expr->type) {
  case BASIC_OPTP_ADD:
    if ( expr->lval_type != BASIC_LVAL_CONST ||
	 ( expr->rval_type != BASIC_RVAL_CONST ) ) {
      basic_errno = BASIC_ERR_INVALID_ARGUMENTS;
      return NULL;
    }
    result->flags = (result->flags | BASIC_VARFLAG_TINT | BASIC_VARFLAG_INIT);
    result->value = (int)expr->lval + (int)expr->rval;
    break;
  case BASIC_OPTP_SUB:
    if ( expr->lval_type != BASIC_LVAL_CONST ||
	 ( expr->rval_type != BASIC_RVAL_CONST ) ) {
      basic_errno = BASIC_ERR_INVALID_ARGUMENTS;
      return NULL;
    }
    result->flags = (result->flags | BASIC_VARFLAG_TINT | BASIC_VARFLAG_INIT);
    result->value = (int)expr->lval - (int)expr->rval;
    break;
  case BASIC_OPTP_MUL:
    if ( expr->lval_type != BASIC_LVAL_CONST ||
	 ( expr->rval_type != BASIC_RVAL_CONST ) ) {
      basic_errno = BASIC_ERR_INVALID_ARGUMENTS;
      return NULL;
    }
    result->flags = (result->flags | BASIC_VARFLAG_TINT | BASIC_VARFLAG_INIT);
    result->value = (int)expr->lval * (int)expr->rval;
    break;
  case BASIC_OPTP_DIV:
    if ( expr->lval_type != BASIC_LVAL_CONST ||
	 ( expr->rval_type != BASIC_RVAL_CONST ) ) {
      basic_errno = BASIC_ERR_INVALID_ARGUMENTS;
      return NULL;
    }
    if ( expr->rval == 0 ) {
      basic_errno = BASIC_ERR_MATH_DBZ;
      return NULL;
    }
    result->flags = (result->flags | BASIC_VARFLAG_TINT | BASIC_VARFLAG_INIT);
    result->value = (int)expr->lval / (int)expr->rval;
    break;
  case BASIC_OPTP_MOD:
    if ( expr->lval_type != BASIC_LVAL_CONST ||
	 ( expr->rval_type != BASIC_RVAL_CONST ) ) {
      basic_errno = BASIC_ERR_INVALID_ARGUMENTS;
      return NULL;
    }
    if ( expr->rval == 0 ) {
      basic_errno = BASIC_ERR_MATH_DBZ;
      return NULL;
    }
    result->flags = (result->flags | BASIC_VARFLAG_TINT | BASIC_VARFLAG_INIT);
    result->value = ((int)expr->lval) - (((int)expr->lval / (int)expr->rval)*(int)expr->rval);
    break;
  case BASIC_OPTP_EQL:
    if ( expr->lval_type != BASIC_LVAL_CONST ||
	 ( expr->rval_type != BASIC_RVAL_CONST ) ) {
      basic_errno = BASIC_ERR_INVALID_ARGUMENTS;
      return NULL;
    }
    result->flags = (result->flags | BASIC_VARFLAG_TINT | BASIC_VARFLAG_INIT);
    if ((int)expr->lval == (int)expr->rval) {
      result->value = BASIC_CONST_TRUE;
    } else {
      result->value = BASIC_CONST_FALSE;
    }
    break;
  case BASIC_OPTP_ASN:
    basic_errno = BASIC_ERR_INTERNAL_UNIMPLEMENTED;
    return NULL;
  default:
    basic_errno = BASIC_ERR_INTERNAL_UNDEFINED_BEHAVIOR;
    return NULL;
  }
  return 1;
}

struct basic_expr *basic_parse_expr(char *expbuf, int expr_depth)
{
  char flags = 0;
  char *subptr = 0;
  char tmpbuf[256];
  struct basic_expr *ret = NULL;

  ret = &expressions[expr_depth];

  _tokenizer_init();
  memset(ret, 0x0, sizeof(struct basic_expr));
  memset((char *)&tmpbuf, 0x0, 256);
  ret->type = BASIC_OPTP_STMT;

  while ( *expbuf != '\0' ) {
    if ( *expbuf == ' ' ) {
      expbuf += sizeof(char);
      continue;
    } else if ( *expbuf == '(' && (*(expbuf+1) != ')')) {
      _cputs("Left paren\n");
      subptr = expbuf + sizeof(char);
      _cputs(subptr);
      ret->left_parens += 1;
    } else if ( *expbuf == '(' && (*(expbuf+1) == '\0')) {
      basic_errno = BASIC_ERR_UNBALANCED_PARENS;
      return NULL;
    } else if ( *expbuf == ')' ) {
      _cputs("Right paren\n");
      ret->right_parens += 1;
    }
    if ( ( ret->left_parens > 0 ) && (ret->left_parens == ret->right_parens) ) {
      if ( ret->lval_type == 0x0 ) {
	memcpy((char *)&tmpbuf, subptr, (expbuf - subptr));
	ret->lval_type = BASIC_LVAL_EXPR;
	ret->left_parens = 0;
	ret->right_parens = 0;
	_cputs("Parenthesis balanced, recursing for lval\n");
	_cputs((char *)&tmpbuf);
	ret->lval = basic_parse_expr(tmpbuf, (expr_depth+1));
	flags = (flags | BASIC_FOUND_LVAL);
      } else if ( (ret->type == BASIC_OPTP_STMT) && (flags & BASIC_FOUND_LVAL) == BASIC_FOUND_LVAL ) {
	_cputs("Parenthesis balanced, multiple lvalues\n");
	goto _basic_parse_multiple_lvalues;
      } else if ( (ret->type != BASIC_OPTP_STMT) && ((flags & BASIC_FOUND_RVAL) == BASIC_FOUND_RVAL)) {
	_cputs("Parenthesis balanced, multiple rvalues\n");
	goto _basic_parse_multiple_rvalues;
      } else if ( ret->type != BASIC_OPTP_STMT ) {
	_cputs("Parenthesis balanced, recursing for rval\n");
	memcpy((char *)&tmpbuf, subptr, ((expbuf - 1) - subptr));
	ret->rval_type = BASIC_RVAL_EXPR;
	ret->rval = basic_parse_expr(tmpbuf, (expr_depth+1));
	flags = (flags | BASIC_FOUND_RVAL);
      } 
    } else if ( (ret->left_parens == 0 ) && (isdigit(*expbuf) == 1) ) {
      _cputs("Found digits with no left parenthesis\n");
      if ( (ret->type == BASIC_OPTP_STMT) && (flags & BASIC_FOUND_LVAL) == BASIC_FOUND_LVAL ) {
	goto _basic_parse_multiple_lvalues;
      } else if ( ret->type == BASIC_OPTP_STMT ) {
	_cputs("Set lvalue\n");
	ret->lval = atoi(_tokenize(expbuf, BASIC_TOKENIZER_TOKENS));
	ret->lval_type = BASIC_LVAL_CONST;
	flags = (flags | BASIC_FOUND_LVAL);
      } else if ( ret->type != BASIC_OPTP_STMT && ((flags & BASIC_FOUND_RVAL) == BASIC_FOUND_RVAL)) {
	goto _basic_parse_multiple_rvalues;
      } else if ( ret->type != BASIC_OPTP_STMT ) {
	_cputs("Set rvalue\n");
	ret->rval = atoi(_tokenize(expbuf, BASIC_TOKENIZER_TOKENS));
	ret->rval_type = BASIC_RVAL_CONST;
	flags = (flags | BASIC_FOUND_RVAL);
      }
    } else if ((flags & BASIC_FOUND_RVAL) != BASIC_FOUND_RVAL) {
      _cputs("No RVAL found, checking for operations\n");
      if ( *expbuf == '+' ) {
	ret->type = BASIC_OPTP_ADD;
      } else if ( *expbuf == '*' ) {
	ret->type = BASIC_OPTP_MUL;
      } else if ( *expbuf == '-' ) {
	ret->type = BASIC_OPTP_SUB;
      } else if ( *expbuf == '/' ) {
	ret->type = BASIC_OPTP_DIV;
      } else if ( *expbuf == '%' ) {
	ret->type = BASIC_OPTP_MOD;
      }
    } else { 
      _cputs("Wat\n");
      basic_errno = BASIC_ERR_SYNTAX_GENERAL;
	return NULL;
    }
    expbuf += sizeof(char);
  }
  _cputs("returning\n");
  return ret;

_basic_parse_multiple_lvalues:
  basic_errno = BASIC_ERR_SYNTAX_MULTIPLE_LVALUES;
  return NULL;
_basic_parse_multiple_rvalues:
  basic_errno = BASIC_ERR_SYNTAX_MULTIPLE_RVALUES;
  return NULL;

}

void basic_print_var(struct basic_variable *var)
{
  char decimal[2];
  decimal[0] = 0;
  decimal[1] = 0;

  if ( ( (var->flags & BASIC_VARFLAG_INIT) == BASIC_VARFLAG_INIT ) &&
       ( (var->flags & BASIC_VARFLAG_TINT) == BASIC_VARFLAG_TINT ) ) {
    decimal[0] = dtoa((int)var->value);
    _cputs(&decimal);
    _cputs("\n");
  }
}

void basic_repl(void)
{
  char keybuff[512];
  char outbuff[128];
  char decimal[2];

  struct basic_expr *expr;
  struct basic_variable result;

  decimal[0] = 0;
  decimal[1] = 0;

  blankScreen();
  setCursorPosition(0, 0);
  _cputs("Piquant Basic v0.1\n\n");

  while ( 1 ) {
    memset((void *)&result, 0x00, sizeof(struct basic_variable));
    expr = NULL;
    _cputs("> ");

    /* Read */

    memset((void *)&keybuff, 0x00, 512);
    memset((void *)&outbuff, 0x00, 128);
    if ( _cgets((char *)&keybuff) != NULL ) {
      _cputs("\n");

      expr = basic_parse_expr((char *)&keybuff, 1);
      if ( expr == NULL ) {
	_cputs("Error: ");
	decimal[0] = dtoa(basic_errno);
	_cputs(&decimal);
	_cputs("\n");
	basic_errno = 0;
	continue;
      }

      /* Evaluate */
      basic_solve_expr(expr, &result);
      if ( basic_errno != 0 ) {
	_cputs("Error: ");
	decimal[0] = dtoa(basic_errno);
	_cputs(&decimal);
	_cputs("\n");
      } else {
	basic_print_var(&result);
      }
    }
  }
}
