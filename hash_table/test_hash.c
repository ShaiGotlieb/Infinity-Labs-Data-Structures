#include <errno.h> /*perror */
#include <fcntl.h> /* open */
#include <math.h> /* sqrt */
#include <stdio.h> /* printf */
#include <stdlib.h>  /* exit status, size_t */
#include <string.h> /* strcpy , strcmp*/
#include <sys/mman.h> /* mmap */
#include <sys/stat.h> /* file size */
#include <unistd.h> /* close */
#include <ctype.h> /* isalpha */
#include <strings.h> /* strcasecmp */

#include "hash.h"
#include "test.h"

#define EMPTY (0)
#define FAILURE (1)
#define FALSE (0)
#define FILE_PATH ("/usr/share/dict/american-english")
#define BOOK_PATH ("/home/ol62/git/ds/hash_table/Star-Wars")
#define HASH_SIZE (14)
#define MAX_WORD_SIZE (46)
#define SCALAR (sqrt(5) - 1)
#define SUCCESS (0)
#define SUCCESS (0)
#define TRUE (1)
#define UNUSED(x) ((void)(x))

typedef struct person_s
{
	size_t age;
	double height;
	size_t id;
	char *fiest_name;

} person_t;


TestResult TestHashCreate();
TestResult TestHashFind();
TestResult TestHashForEach();
TestResult TestHashInsert();
TestResult TestHashIsEmpty();
TestResult TestHashRemove();
TestResult TestHashSize();
TestResult TestHashFromUserInput();

static int Action(void *value, const void *param);
static int ActionReturnFailure(void *value, const void *param);
static int IsMatch(const void *data1, const void *data2, void *param);
static int IsMatchPerson(const void *data1, const void *data2, void *param);
static int IsMatchString(const void *data1, const void *data2, void *param);
static int PrintPerson(void *value, const void *param);

int values[HASH_SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
person_t person[14] ={
	{28, 1.75, 123456780, "shai"},
	{29, 1.70, 123456781, "shachar"},
	{30, 1.71, 123456782, "maayan"},
	{28, 1.72, 123456783, "dan"},
	{45, 1.85, 123456784, "ran"},
	{25, 1.65, 123456785, "refael"},
	{19, 1.45, 123456786, "reut"},
	{44, 1.55, 123456787, "lior"},
	{37, 1.71, 123456788, "benji"},
	{33, 1.69, 312360798, "gil"},
	{32, 1.69, 317865798, "nimrod"},
	{31, 1.59, 313465798, "einat"},
	{25, 1.89, 312265798, "michael"},
	{14, 2.99, 312415798, "tomer"}
};

int main()
{
	RUN_TEST(TestHashCreate);		
	RUN_TEST(TestHashInsert);		
	RUN_TEST(TestHashSize);		
	RUN_TEST(TestHashIsEmpty);		
	RUN_TEST(TestHashFind);	
	RUN_TEST(TestHashForEach);		
	RUN_TEST(TestHashRemove);
	RUN_TEST(TestHashFromUserInput);	

	return (EXIT_SUCCESS);
}

static int Action(void *value, const void *param)
{
	UNUSED(param);

	printf("Inside 'HashForEach'-> data: %d\n", *(int*)value);

	return (SUCCESS);
}

static int PrintPerson(void *value, const void *param)
{
	person_t *p1 = (person_t*)value;

	UNUSED(param);

	printf("name: %s 	| id: %d | height: %.2f | age: %d \n", p1->fiest_name, (int)p1->id, p1->height, (int)p1->age);

	return (SUCCESS);
}

static int ActionReturnFailure(void *value, const void *param)
{
	UNUSED(param);
	UNUSED(value);

	return (FAILURE);
}

static int IsMatch(const void *data1, const void *data2, void *param)
{
	UNUSED(param);

	if (*(int*)data1 == *(int*)data2)
	{
		return (TRUE);
	}

	return (FALSE);
}

static int IsMatchPerson(const void *data1, const void *data2, void *param)
{
	person_t *p1 = (person_t*)data1;
	person_t *p2 = (person_t*)data2;

	UNUSED(param);

	if (p1->id == p2->id)
	{
		return (TRUE);
	}

	return (FALSE);
}

static int IsMatchString(const void *data1, const void *data2, void *param)
{
	UNUSED(param);

	if (0 == strcasecmp((char *)data1, (char *)data2))
	{
		return (TRUE);
	}

	return (FALSE);
}

static size_t HashFunc(const void *key)
{
	return (HASH_SIZE * (*(int*)key * SCALAR));
}

static size_t HashFuncBook(const void *key)
{
	static int i = 0;

	UNUSED(key);
	
	i++;
	return (HASH_SIZE % i);
}

TestResult TestHashCreate()
{
	hash_t *hash_table = HashCreate(HASH_SIZE, HashFunc, IsMatch, NULL);
	
	REQUIRE(NULL != hash_table);

	HashDestroy(hash_table); 

	return (TEST_PASS);
}

TestResult TestHashInsert()
{
	hash_t *hash_table = HashCreate(HASH_SIZE, HashFunc, IsMatch, NULL);
	hash_t *person_hash_table = HashCreate(HASH_SIZE, HashFunc, IsMatchPerson, NULL);
	size_t i;

	for (i = 0; i < HASH_SIZE; ++i)
	{
		REQUIRE(SUCCESS == HashInsert(hash_table, &values[i], &values[i]));
		REQUIRE(SUCCESS == HashInsert(person_hash_table, &person[i], &person[i]));
		
		REQUIRE(i + 1 == HashSize(hash_table));
		REQUIRE(i + 1 == HashSize(person_hash_table));
	}

	REQUIRE(HASH_SIZE == HashSize(hash_table));
	REQUIRE(HASH_SIZE == HashSize(person_hash_table));

	HashDestroy(hash_table); 
	HashDestroy(person_hash_table); 

	return (TEST_PASS);
}

TestResult TestHashRemove()
{
	hash_t *hash_table = HashCreate(HASH_SIZE, HashFunc, IsMatch, NULL);
	hash_t *person_hash_table = HashCreate(HASH_SIZE, HashFunc, IsMatchPerson, NULL);
	size_t i;

	for (i = 0; i < HASH_SIZE; ++i)
	{
		REQUIRE(SUCCESS == HashInsert(hash_table, &values[i], &values[i]));
		REQUIRE(SUCCESS == HashInsert(person_hash_table, &person[i], &person[i]));
	}

	for (i = 0; i < HASH_SIZE; ++i)
	{
		REQUIRE(&values[i] == HashRemove(hash_table, &values[i], &values[i]));
		REQUIRE(&person[i] == HashRemove(person_hash_table, &person[i], &person[i]));
		
		REQUIRE(HASH_SIZE - i - 1 == HashSize(hash_table));
		REQUIRE(HASH_SIZE - i - 1 == HashSize(person_hash_table));
	}

	REQUIRE(TRUE == HashIsEmpty(hash_table));
	REQUIRE(TRUE == HashIsEmpty(person_hash_table));

	HashDestroy(hash_table); 
	HashDestroy(person_hash_table);

	return (TEST_PASS);
}

TestResult TestHashSize()
{
	hash_t *hash_table = HashCreate(HASH_SIZE, HashFunc, IsMatch, NULL);
	hash_t *person_hash_table = HashCreate(HASH_SIZE, HashFunc, IsMatchPerson, NULL);
	size_t i;

	REQUIRE(EMPTY == HashSize(hash_table));

	for (i = 0; i < HASH_SIZE; ++i)
	{
		REQUIRE(SUCCESS == HashInsert(hash_table, &values[i], &values[i]));
		REQUIRE(SUCCESS == HashInsert(person_hash_table, &person[i], &person[i]));
		REQUIRE(i + 1 == HashSize(hash_table));
		REQUIRE(i + 1 == HashSize(person_hash_table));
	}

	REQUIRE(HASH_SIZE == HashSize(hash_table));
	REQUIRE(HASH_SIZE == HashSize(person_hash_table));

	HashDestroy(hash_table); 
	HashDestroy(person_hash_table);

	return (TEST_PASS);
}

TestResult TestHashIsEmpty()
{
	hash_t *hash_table = HashCreate(HASH_SIZE, HashFunc, IsMatch, NULL);
	hash_t *person_hash_table = HashCreate(HASH_SIZE, HashFunc, IsMatchPerson, NULL);
	size_t i;

	REQUIRE(TRUE == HashIsEmpty(hash_table));

	for (i = 0; i < HASH_SIZE; ++i)
	{
		REQUIRE(SUCCESS == HashInsert(hash_table, &values[i], &values[i]));
		REQUIRE(SUCCESS == HashInsert(person_hash_table, &person[i], &person[i]));
		
		REQUIRE(i + 1 == HashSize(hash_table));
		REQUIRE(i + 1 == HashSize(person_hash_table));
	}

	REQUIRE(FALSE == HashIsEmpty(hash_table));
	REQUIRE(FALSE == HashIsEmpty(person_hash_table));

	HashDestroy(hash_table); 
	HashDestroy(person_hash_table); 

	return (TEST_PASS);
}

TestResult TestHashFind()
{
	hash_t *hash_table = HashCreate(HASH_SIZE, HashFunc, IsMatch, NULL);
	hash_t *person_hash_table = HashCreate(HASH_SIZE, HashFunc, IsMatchPerson, NULL);
	size_t i;

	for (i = 0; i < HASH_SIZE; ++i)
	{
		REQUIRE(NULL == HashFind(hash_table, &values[i], &values[i]));
		REQUIRE(NULL == HashFind(person_hash_table, &person[i], &person[i]));
	}

	for (i = 0; i < HASH_SIZE; ++i)
	{
		REQUIRE(SUCCESS == HashInsert(hash_table, &values[i], &values[i]));
		REQUIRE(SUCCESS == HashInsert(person_hash_table, &person[i], &person[i]));
	}

	for (i = 0; i < HASH_SIZE; ++i)
	{
		REQUIRE(&values[i] == HashFind(hash_table, &values[i], &values[i]));
		REQUIRE(&person[i] == HashFind(person_hash_table, &person[i], &person[i]));
	}

	HashDestroy(hash_table);
	HashDestroy(person_hash_table);  

	return (TEST_PASS);
}

TestResult TestHashForEach()
{
	hash_t *hash_table = HashCreate(HASH_SIZE, HashFunc, IsMatch, NULL);
	hash_t *person_hash_table = HashCreate(HASH_SIZE, HashFunc, IsMatchPerson, NULL);
	size_t i;

	for (i = 0; i < HASH_SIZE; ++i)
	{
		REQUIRE(SUCCESS == HashInsert(hash_table, &values[i], &values[i]));
		REQUIRE(SUCCESS == HashInsert(person_hash_table, &person[i], &person[i]));
	}

	REQUIRE(SUCCESS == HashForEach(hash_table, Action, NULL));
	REQUIRE(SUCCESS != HashForEach(hash_table, ActionReturnFailure, NULL));

	REQUIRE(SUCCESS == HashForEach(person_hash_table, PrintPerson, NULL));
	REQUIRE(SUCCESS != HashForEach(person_hash_table, ActionReturnFailure, NULL));

	HashDestroy(hash_table); 
	HashDestroy(person_hash_table); 

	return (TEST_PASS);
}

TestResult TestHashFromUserInput()
{
    const char * mapped;
	hash_t *hash_table = HashCreate(HASH_SIZE, HashFuncBook, IsMatchString, NULL);
	char *user_input = NULL;
	char *words = NULL;
	char *book_words = NULL;
	char *word_ptr = NULL;
	char *book_words_runner = NULL;
    int file_descriptor = 0;
    int status = 0;
    int wait_for_char = TRUE;
    int not_found_counter = 0;
    int found_counter = 0;
    size_t file_size = 0;
    size_t book_size = 0;
    size_t i;
    struct stat stat_struct;
    char c;
    FILE * fp;

    file_descriptor = open(FILE_PATH, O_RDONLY);
    if (0 > file_descriptor)
    {
    	printf("in line: %d\n", __LINE__);
    	perror("ERROR: ");

    	return (TEST_FAIL);
    }

    status = fstat(file_descriptor, &stat_struct);
    if (0 > status)
    {
    	printf("in line: %d\n", __LINE__);
    	perror("ERROR: ");
    	
    	return (TEST_FAIL);
    }
    file_size = stat_struct.st_size;

    mapped = mmap(0, file_size, PROT_WRITE, MAP_PRIVATE, file_descriptor, 0);
    if (MAP_FAILED == mapped)
    {
    	printf("in line: %d\n", __LINE__);
    	perror("ERROR: ");
    	
    	return (TEST_FAIL);
    }

    words = (char*)malloc(sizeof(char *) * file_size);
    if (NULL == words)
    {
    	printf("in line: %d\n", __LINE__);
    	perror("ERROR: ");
    	
    	return (TEST_FAIL);
    }

	user_input = (char*)malloc(sizeof(char *) * MAX_WORD_SIZE);
	if (NULL == user_input)
    {
    	free(words);
    	words = NULL;

    	printf("in line: %d\n", __LINE__);
    	perror("ERROR: ");
    	
    	return (TEST_FAIL);
    }

    strcpy(words, mapped);

    word_ptr = words;

    for (i = 0; i < file_size; i++) 
    {
        if (words[i] == '\n') 
        {
         	words[i] = '\0';
         	HashInsert(hash_table, word_ptr, word_ptr);
         	word_ptr = &words[i];
         	word_ptr++;
    	}
	}

  	printf("Enter name: ");
    scanf("%s", user_input);

	if (NULL != HashFind(hash_table, user_input, user_input))
	{
		printf("'%s' was found! \n", user_input);
	}
	else
	{
		printf("'%s' was not found! \n", user_input);
	}

	file_descriptor = close(file_descriptor);
	if (0 > file_descriptor)
	{
		printf("in line: %d\n", __LINE__);
    	perror("ERROR: ");

    	free(words);
    	words = NULL;
    	free(user_input);
    	user_input = NULL;
    	
    	return (TEST_FAIL);
	}

	fp = fopen(BOOK_PATH, "rw");
	if (NULL == fp)
	{
		free(words);
    	words = NULL;
    	free(user_input);
    	user_input = NULL;

		return (TEST_FAIL);	
	} 

	fseek(fp, 0L, SEEK_END);
	book_size = ftell(fp);
	rewind(fp);

	book_words = (char*)malloc(sizeof(char *) * book_size);
    if (NULL == words)
    {
    	free(words);
    	words = NULL;
    	free(user_input);
    	user_input = NULL;

    	printf("in line: %d\n", __LINE__);
    	perror("ERROR: ");
    	
    	return (TEST_FAIL);
    }

    book_words_runner = book_words;

    i = 0;
	while ((c = fgetc(fp)) != EOF)
	{
		if(!isalpha(c))
		{
			/*printf("%s\n", book_words_runner);*/
			if (FALSE == wait_for_char)
			{
				book_words[i] = '\0';
				wait_for_char = TRUE;

				if (NULL != HashFind(hash_table, book_words_runner, book_words_runner))
				{
					printf("'%s' was found! \n", book_words_runner);
					found_counter++;
				}
				else
				{
					printf("'%s' was not found! \n", book_words_runner);
					not_found_counter++;
				}
				book_words_runner = &book_words[i];
				book_words_runner++;
				i++;
			}
		}
		else
		{
			book_words[i] = c;
			wait_for_char = FALSE;
			i++;
		}
	}

	printf("%d words were found! \n", found_counter);
	printf("%d words NOT found! \n", not_found_counter);

	fclose(fp);

	free(words);
	words = NULL;
	free(user_input);
	user_input = NULL;
	free(book_words);
	book_words = NULL;

	HashDestroy(hash_table);

	return (TEST_PASS);
}