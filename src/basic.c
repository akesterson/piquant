#include "basic.h"
#include "screen.h"
#include "conio.h"
#include "string.h"
#include "stdlib.h"

struct basic_math_expr math_expressions[8];
int basic_errno;

char _tokenizer_value[BASIC_TOKENIZER_MAX_LENGTH];
char *_tokenizer_prev;
char *_tokenizer_prev_next;

void _tokenizer_init(void)
{
  _tokenizer_prev = NULL;
  _tokenizer_prev_next = NULL;
}

char *_tokenize(char *ptr, char token)
{
  char *orig = NULL;
  int len = 0;

  if ( ptr == NULL ) {
    return NULL;
  }
  if ( _tokenizer_prev == ptr ) {
    ptr = _tokenizer_prev_next;
  }
  orig = ptr;

  memset(&_tokenizer_value, 0x00, BASIC_TOKENIZER_MAX_LENGTH);
  while ( *ptr != token ) {
    if ( *ptr == '\0' ) {
      ptr -= sizeof(char);
      break;
    }
    ptr += sizeof(char);
    len += 1;
  }
  if ( len > BASIC_TOKENIZER_MAX_LENGTH ) {
    basic_errno = BASIC_ERR_SYNTAX_TOKEN_LENGTH;
    return NULL;
  } else if ( len == 0 ) {
    return NULL;
  }
  memcpy((void *)&_tokenizer_value, (void *)orig, len); 
  _tokenizer_prev_next = (ptr + 1);
  return &_tokenizer_value;
}

struct basic_math_expr *basic_parse_expr(char *expbuf)
{
  struct basic_math_expr *ret = &math_expressions[0];
  char flags = 0;
  char *subptr = 0;

  _tokenizer_init();
  memset(ret, 0x0, sizeof(struct basic_math_expr));

  while ( *expbuf != '\0' ) {
    if ( *expbuf == ' ' ) {
      expbuf += sizeof(char);
      continue;
    } else if ( isdigit(*expbuf) == 1 ) {
      if ( (ret->type == 0) && (flags & BASIC_FOUND_LVAL) == BASIC_FOUND_LVAL ) {
	basic_errno = BASIC_ERR_SYNTAX_MULTIPLE_LVALUES;
	return NULL;
      } else if ( ret->type == 0x0 ) {
	ret->lval = atoi(_tokenize(expbuf, ' '));
	flags = (flags + BASIC_FOUND_LVAL);
      } else if ( ret->type != 0x0 && ((flags & BASIC_FOUND_RVAL) == BASIC_FOUND_RVAL)) {
	basic_errno = BASIC_ERR_SYNTAX_MULTIPLE_RVALUES;
	return NULL;
      } else if ( ret->type != 0x0 ) {
	ret->rval = atoi(_tokenize(expbuf, ' '));
      }
    } else if ( ret->type == 0x0 ) {
      if ( *expbuf == '+' ) {
	ret->type = BASIC_MATH_ADD;
      } else if ( *expbuf == '*' ) {
	ret->type = BASIC_MATH_MUL;
      } else if ( *expbuf == '-' ) {
	ret->type = BASIC_MATH_SUB;
      } else if ( *expbuf == '/' ) {
	ret->type = BASIC_MATH_DIV;
      } else if ( *expbuf == '%' ) {
	ret->type = BASIC_MATH_MOD;
      } else {
	basic_errno = BASIC_ERR_SYNTAX_GENERAL;
	return NULL;
      }
    } else { 
      basic_errno = BASIC_ERR_SYNTAX_GENERAL;
      return NULL;
    }
    expbuf += sizeof(char);
  }
  return ret;
}

void basic_run(void)
{
  char keybuff[512];
  char outbuff[128];
  char decimal;

  struct basic_math_expr *expr;

  blankScreen();
  setCursorPosition(0, 0);
  _cputs("Piquant Basic v0.1\n\n");

  while ( 1 ) {
    _cputs("> ");
    memset((void *)&keybuff, 0x00, 512);
    memset((void *)&outbuff, 0x00, 128);
    if ( _cgets((char *)&keybuff) != NULL ) {
      _cputs("\n");
      _cputs("Analyzing ");
      _cputs((char *)&keybuff);
      _cputs("\n");

      expr = basic_parse_expr((char *)&keybuff);
      if ( expr == NULL ) {
	_cputs("Syntax Error: ");
	decimal = dtoa(basic_errno);
	_cputs(&decimal);
	_cputs("\n");
	continue;
      }

      decimal = dtoa(expr->type);
      memcpy(&outbuff, "Expression type: \0", strlen("Expression type: \0"));
      strncat(&outbuff, &decimal, 1);
      _cputs(&outbuff);
      _cputs("\n");

      decimal = dtoa(expr->lval);
      memcpy(&outbuff, "Expression lval: \0", strlen("Expression lval: \0"));
      strncat(&outbuff, &decimal, 1);
      _cputs(&outbuff);
      _cputs("\n");

      decimal = dtoa(expr->rval);
      memcpy(&outbuff, "Expression rval: \0", strlen("Expression rval: \0"));
      strncat(&outbuff, &decimal, 1);
      _cputs(&outbuff);
      _cputs("\n");
    }
  }
}
