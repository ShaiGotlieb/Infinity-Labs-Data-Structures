#include <stdlib.h> /* malloc() */
#include <string.h> /* memcpy() */
#include <assert.h> /* assert() */
#include "cbuffer.h"

#define TRUE 1
#define FALSE 0

struct cbuffer_s
{
	char *data;
	size_t capacity;
	size_t read;
	size_t used_bytes;
};


int CBufferIsEmpty(const cbuffer_t *cbuffer)
{
	return cbuffer->used_bytes == 0 ? TRUE : FALSE;
}

cbuffer_t *CBufferCreate(size_t capacity)
{
	cbuffer_t *cbuffer = malloc(sizeof(cbuffer_t));
	if (cbuffer == NULL)
	{
		return NULL;
	}

	cbuffer->data = (void*)malloc(capacity);
	if (cbuffer->data == NULL)
	{
		free(cbuffer);
		cbuffer = NULL;

		return NULL;
	}

	cbuffer->capacity = capacity;
	cbuffer->read = 0;
	cbuffer->used_bytes = 0;

	return cbuffer;
}

void CBufferDestroy(cbuffer_t *cbuffer)
{
	free(cbuffer->data);
	cbuffer->data = NULL;
	free(cbuffer);
	cbuffer = NULL;
}

size_t CBufferWrite(cbuffer_t *cbuffer, const void *src, size_t num_bytes_to_write)
{
	size_t written_bytes = 0;
	size_t write_index = 0;
	size_t offset = cbuffer->read + cbuffer->used_bytes;
	size_t leftover = cbuffer->capacity - cbuffer->used_bytes;
	
	assert(cbuffer != NULL);

	if (offset >= cbuffer->capacity) 
	{
		write_index = offset - cbuffer->capacity; 
	}
	else 
	{
		write_index = offset;
	}

	if (leftover < num_bytes_to_write) 
	{
		num_bytes_to_write = leftover; 
	}

 	
	if (write_index + num_bytes_to_write > cbuffer->capacity)
	{
		written_bytes = cbuffer->capacity - write_index;
		
		memcpy((cbuffer->data + write_index), src, written_bytes);
		memcpy(cbuffer->data, (char *)src + written_bytes, (num_bytes_to_write - written_bytes));
		cbuffer->used_bytes += num_bytes_to_write;
		
		return num_bytes_to_write;
	}
	
	memcpy((cbuffer->data + write_index), src, num_bytes_to_write);
	cbuffer->used_bytes += num_bytes_to_write;
	
	return num_bytes_to_write;
}

size_t CBufferRead(cbuffer_t *cbuffer, void *dest, size_t num_bytes_to_read)
{
	size_t written_bytes = 0;
	
	assert(cbuffer != NULL);
	assert(dest != NULL);
	
	written_bytes = cbuffer->capacity - cbuffer->read;
	
	if (TRUE == CBufferIsEmpty(cbuffer)) 
	{
		return 0;
	}

	if (cbuffer->used_bytes < num_bytes_to_read) 
	{
		num_bytes_to_read = cbuffer->used_bytes;
	}
	
	if (written_bytes >= num_bytes_to_read)
	{
		memcpy(dest, cbuffer->data + cbuffer->read, num_bytes_to_read);
		cbuffer->read += num_bytes_to_read;

		if (cbuffer->capacity <= cbuffer->read)
		{
			cbuffer->read = 0;
		}

		cbuffer->used_bytes -= num_bytes_to_read;
		
		return num_bytes_to_read;
	}
		
	memcpy(dest, (cbuffer->data + cbuffer->read), written_bytes);
	memcpy((cbuffer->data + written_bytes), cbuffer->data, num_bytes_to_read - written_bytes);

	cbuffer->read += num_bytes_to_read;
	
	if (cbuffer->capacity <= cbuffer->read)
	{
		cbuffer->read = num_bytes_to_read - written_bytes;
	}
	
	cbuffer->used_bytes -= num_bytes_to_read;
	
	return num_bytes_to_read;
}

size_t CBufferGetCapacity(const cbuffer_t *cbuffer)
{
	return cbuffer->capacity;
}

size_t CBufferGetSize(const cbuffer_t *cbuffer)
{
	return cbuffer->used_bytes;
}

void CBufferClear(cbuffer_t *cbuffer)
{
	cbuffer->read = 0;
	cbuffer->used_bytes = 0;
}
