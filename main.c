
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b)
{
    if (a < b)
    {
        return a;
    }

    else
    {
        return b;
    }
}

////////////////////////// Queue Operations /////////////////////////////////////

struct Queue
{
    int front;
    int rear;
    int *arr;
    int capacity;
};

struct Queue *create_queue(int capacity)
{
    struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
    q->capacity = capacity;
    q->front = -1;
    q->rear = -1;
    q->arr = (int *)malloc(sizeof(int) * q->capacity);
    return q;
}

int isFull(struct Queue *q)
{
    return q->rear == q->capacity;
}

int isEmpty(struct Queue *q)
{
    return ((q->front == q->rear + 1) || (q->front == -1 && q->rear == -1));
}

void enqueue(struct Queue *q, int data)
{
    if (!isFull(q))
    {
        q->rear += 1;
        if (q->front == -1 && q->rear == 0)
        {
            q->front = 0;
        }
        q->arr[q->rear] = data;
    }

    else
    {
        return;
    }
}

int dequeue(struct Queue *q)
{
    if (!isEmpty(q))
    {
        int item = q->arr[q->front];
        q->front += 1;
        return item;
    }

    else
    {
        return -9999; // code ERROR
    }
}

////////////////////////// Graph Operations /////////////////////////////////////

int **create_graph(int n) // n : number of vertices
{
    int **mat = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
    {
        mat[i] = (int *)calloc(sizeof(int), n);
    }

    return mat;
}

void read_graph(int **mat, int n)
{
    int i, j, c; // i: starting vertex and j: ending vertex c : capacity

    while (1)
    {
        printf("Enter the start & end vertex along with the capacity : "), scanf("%d %d %d", &i, &j, &c);
        if (i == -1 && j == -1)
        {
            return;
        }

        mat[i][j] = c;
    }
}

int bfs(int **res_graph, int s, int t, int path[], int n)
{
    struct Queue *q = create_queue(n);
    int *visited = (int *)calloc(sizeof(int), n);
    visited[s] = 1;
    enqueue(q, s);
    path[s] = -1;

    while (!isEmpty(q))
    {
        int dsrc = dequeue(q);

        for (int i = 0; i < n; i++)
        {
            if (res_graph[dsrc][i] > 0 && visited[i] == 0)
            {
                enqueue(q, i);
                visited[i] = 1;
                //printf("%d ", i);
                path[i] = dsrc;
            }
        }
    }

    // for(int i = 0 ; i<n ; i++)
    // {
    //     printf("%d ",path[i]);
    // }

    if (visited[t] == 1)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

////////////////////////// Ford Fulkerson ALgorithm /////////////////////////////////////

int fordFulkerson(int **graph, int s, int t, int n)
{
    int u, v;

    int **res_graph = create_graph(n);
    for (u = 0; u < n; u++)
    {
        for (v = 0; v < n; v++)
        {
            res_graph[u][v] = graph[u][v];
        }
    }

    int path[n];

    int max_flow = 0;

    while (bfs(res_graph, s, t, path, n))
    {
        int path_flow = 1000; // setting it to a large value
        for (v = t; v != s; v = path[v])
        {
            u = path[v];
            path_flow = min(path_flow, res_graph[u][v]);
        }

        for (v = t; v != s; v = path[v])
        {
            u = path[v];
            res_graph[u][v] -= path_flow;
            res_graph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

void display_graph(int **mat, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int n = 6;
    int *visited = (int *)calloc(sizeof(int), n);
    int **graph = create_graph(n);
    read_graph(graph, n);
    display_graph(graph, n);
    printf("Max flow is : %d", fordFulkerson(graph, 0, 5, n));
    return 0;
}