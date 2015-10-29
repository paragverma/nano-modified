int mcflag = 0;
typedef struct mcpositions{
	size_t xcor;
	ssize_t ycor;
        int x_shift;
	struct mcpositions *next;
} mcpositions;

typedef struct mcarray{
	struct mcpositions *head;
	struct mcpositions *tail;
} mcarray;