/**
 * call example: 
 * -------------
 * int elem1 = 10;
 * stack s;
 * StackNew( &s, sizeof( int ) );
 * StackPush( &s, &elem1 );
 * StackPop( &s, &elem1 );
 */

typedef struct {
	void *elems;
	int elemSize;
	int loglength;
	int alloclength;
} stack;

void StackNew( stack *s, int elemSize );
void StackDispose( stack *s );
void StackPush( stack *s, void *elemAddr );
void Stack( stack *s, void *elemAddr );

void StackNew( stack *s, int elemSize )
{
	assert( elemSize > 0 );
	s->elemSize = elemSize;
	s->loglength = 0;
	s->alloclength = 4;
	s->elems = malloc( 4 * elemSize );
	assert( s->elems != NULL );
}

void StackDispose( stack *s )
{
	free( s->elems );
}

static void StackGrow( stack *s )
{
	s->alloclength *= 2;
	s->elems = realloc( s->elems, s->alloclength * s->elemSize );
}

void StackPush( stack *s, void *elemAddr )
{
	void *target;

	if ( s->loglength == s->alloclength )
		StackGrow( s );
	target = ( char * ) s->elems + s->loglength * s->elemSize;

	memcpy( target, elemAddr, s->elemSize );
	s->loglength++;
}

void StackPop( stack *s, void *elemAddr )
{
	void *source = ( char * ) s->elems + ( s->loglength - 1 ) * s->elemSize;
	memcpy( elemAddr, source, s->elemSize );
	s->loglength--;
}
