/* atom.h - atomic objects from source */
/* (c) in 2010-2014 by Volker Barthelmann and Frank Wille */

#ifndef ATOM_H
#define ATOM_H

/* types of atoms */
#define LABEL 1
#define DATA  2
#define INSTRUCTION 3
#define SPACE 4
#define DATADEF 5
#define LINE 6
#define OPTS 7
#define PRINTTEXT 8
#define PRINTEXPR 9
#define ROFFS 10
#define RORG 11
#define RORGEND 12
#define ASSERT 13

/* a machine instruction */
typedef struct instruction {
  int code;
#if MAX_QUALIFIERS!=0
  char *qualifiers[MAX_QUALIFIERS];
#endif
#if MAX_OPERANDS!=0
  operand *op[MAX_OPERANDS];
#endif
#if HAVE_INSTRUCTION_EXTENSION
  instruction_ext ext;
#endif
} instruction;  

typedef struct defblock {
  size_t bitsize;
  operand *op;
} defblock;

struct dblock {
  size_t size;
  char *data;
  rlist *relocs;
};

struct sblock {
  size_t space;
  expr *space_exp;  /* copied to space, when evaluated as constant */
  size_t size;
  uint8_t fill[MAXPADBYTES];
  expr *fill_exp;   /* copied to fill, when evaluated - may be NULL */
  rlist *relocs;
  taddr maxalignbytes;
};

typedef struct assertion {
  expr *assert_exp;
  char *expstr;
  char *msgstr;
} assertion;

/* an atomic element of data */
typedef struct atom {
  struct atom *next;
  int type;
  taddr align;
  size_t lastsize;
  unsigned changes;
  source *src;
  int line;
  listing *list;
  union {
    instruction *inst;
    dblock *db;
    symbol *label;
    sblock *sb;
    defblock *defb;
    void *opts;
    int srcline;
    char *ptext;
    expr *pexpr;
    expr *roffs;
    taddr *rorg;
    assertion *assert;
  } content;
} atom;

#define MAXSIZECHANGES 5  /* warning, when atom changed size so many times */

instruction *new_inst(char *inst,int len,int op_cnt,char **op,int *op_len);
dblock *new_dblock();
sblock *new_sblock(expr *,size_t,expr *);

void add_atom(section *,atom *);
size_t atom_size(atom *,section *,taddr);
void print_atom(FILE *,atom *);
atom *clone_atom(atom *);

atom *new_inst_atom(instruction *);
atom *new_data_atom(dblock *,taddr);
atom *new_label_atom(symbol *);
atom *new_space_atom(expr *,size_t,expr *);
atom *new_datadef_atom(size_t,operand *);
atom *new_srcline_atom(int);
atom *new_opts_atom(void *);
atom *new_text_atom(char *);
atom *new_expr_atom(expr *);
atom *new_roffs_atom(expr *);
atom *new_rorg_atom(taddr);
atom *new_rorgend_atom(void);
atom *new_assert_atom(expr *,char *,char *);

#endif
