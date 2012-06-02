nclude <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

static const char VECTOR_SHALLOW_DELETE = 0x01;
static const char VECTOR_DEEP_DELETE = 0x02;

static const unsigned char VECTOR_PUSH_BACK_LITERAL = 0x01;
static const unsigned char VECTOR_PUSH_BACK_DEFAULT = 0x02;

struct vector
{
	void * data;
	size_t block_size;
	size_t type_of_objects;
};

typedef struct vector vector_t;

vector_t * vector_init(size_t type_of_objects, size_t block_size)
{
	vector_t * new_vector=NULL;
	new_vector=(vector_t *) malloc(sizeof(vector_t));
	if(!new_vector)
	{
		printf("%s\n", "out of memory");
		return 0;
	}

	new_vector->block_size=block_size;

	new_vector->type_of_objects=type_of_objects;

	//now allocate a block for these objects
	new_vector->data = (void *) malloc(type_of_objects*block_size);
	/////////nope:memset(new_vector->data, NULL, block_size);
	memset(new_vector->data, 'x', block_size);

	return new_vector;
}

size_t vector_find_last_index(vector_t * vector)
{
	char * t = (char *) vector->data;
	int count=0;

	while(*t != 'x')
	{
		t = t+1;
		count++;
	}
	return count;
}

void vector_push_back(vector_t * to, size_t type_of_object, void * object, unsigned char options)
{
	size_t where_to_add=0;;
  

	//do type-checking before anything
	//if(type_of_object != sizeof(to->type_of_objects))
	//{
	//	printf("%s\n", "you tried to push_back an object of incompatible type");
	//	return;
	//}

	where_to_add = vector_find_last_index(to) + 1;
	
	//do bounds checking: does this space exist?
	///todo

	memcpy((char *)to->data+where_to_add, object, type_of_object);
    

    if(options == VECTOR_PUSH_BACK_DEFAULT);
	if(options == VECTOR_PUSH_BACK_LITERAL)
	{
		free(object);
	}
}

void * vector_access(vector_t * vector, size_t at)
{
	return ((char *)vector->data + at);
}

void * vector_util_int_literal(const int literal)
{
    int * ptr_to_literal = (int *) malloc(sizeof(int));
    memcpy(ptr_to_literal, &literal, sizeof(int));
    return ptr_to_literal;
}

void * vector_util_str_literal(const char * literal)
{
	char ** ptr_to_literal = NULL;
	size_t len = strlen(literal)+1;

	ptr_to_literal = (char **) malloc(sizeof(char *));
	*ptr_to_literal = (char *) malloc(sizeof(char)*len);
	memcpy(*ptr_to_literal, literal, len);
	
	return *ptr_to_literal;
}

void * vector_util_wstr_literal(const wchar_t * literal);


int main(int argc, char ** argv)
{
	char * result;
	//char * hurr = "why";
	vector_t * test=NULL;

	test = vector_init(sizeof(int), 10);
	vector_push_back(test, sizeof(int), vector_util_int_literal(398), VECTOR_PUSH_BACK_LITERAL);
	vector_push_back(test, sizeof(char)*4, vector_util_str_literal("why"), VECTOR_PUSH_BACK_LITERAL);
	result = (char *) vector_access(test, 1);
	printf("%s\n", result);
	//free(result);
	return 0;
}
