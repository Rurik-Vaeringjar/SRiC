#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_INIT_CAPACITY 6
#define UNDEFINE -1
#define SUCCESS 0


typedef struct
{
	void **items;
	int capacity;
	int total;
} sVectorList;

typedef struct sVector Vector;
struct sVector
{
	sVectorList vectorList;

	int (*pfVectorTotal)(Vector *);
	int (*pfVectorResize)(Vector *, int);
	int (*pfVectorAdd)(Vector *, void *);
	int (*pfVectorSet)(Vector *, int, void *);
	void *(*pfVectorGet)(Vector *, int);
	int (*pfVectorDelete)(Vector *, int);
	int (*pfVectorFree)(Vector *);

}

#endif
