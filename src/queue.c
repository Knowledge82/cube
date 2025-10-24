#include "cube.h"

t_queue *create_queue(int capacity)
{
	t_queue *queue;

	queue = malloc(sizeof(t_queue));
	if (!queue)
		return (NULL);
	queue->data = malloc(sizeof(t_point) * capacity);
	if (!queue->data)
		return (free(queue), NULL);
	queue->first = 0;
	queue->last = -1;
	queue->current_size = 0;
	queue->capacity = capacity;
	return (queue);
}

void	enqueue(t_queue *queue, t_point point)
{
	if (queue->current_size < queue->capacity)
	{
		queue->last = (queue->last + 1) % queue->capacity;
		queue->data[queue->last] = point;
		queue->current_size++;
	}
	else
		error_msg("Enqueue failed, queue is full");
}

t_point	dequeue(t_queue *queue)
{
	t_point	point;
	point = queue->data[queue->first];
	queue->first = (queue->first + 1) % queue->capacity;
	queue->current_size--;
	return (point);
}

int	is_empty_queue(t_queue *queue)
{
	return (queue->current_size == 0);
}

void	free_queue(t_queue *queue)
{
	if (!queue)
		return ;
	free(queue->data);
	free(queue);
}
