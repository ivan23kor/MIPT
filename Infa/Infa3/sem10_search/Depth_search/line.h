#ifndef _LINEH_
#define _LINEH_

struct line
{
    int *data; //the line itself
    int top; //number of elements in line
    int max_size; //maximum number of elements in line (for now)
};

int line_ctor (struct line * line1); 
int line_push (struct line * line1, int x);
int line_pop (struct line * line1);
int line_empty (struct line * line1);
int line_dump (struct line * line1);
int line_dtor (struct line * line1);

#endif