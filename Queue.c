#include <stdio.h>
#include <stdlib.h>

/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 * Item: An item that is being enqueued to or dequeued from the queue
 *       It is a pointer to the process
 */
typedef struct {
	char *name;
	int starting_time;
	int remaining_time;
} Process, *Item;
/*
 *
 */
typedef struct Node {
	Item data;
	struct Node* next;
} Node;
/*
 *
 */
typedef struct {
    Node *front;
    Node *back;
} Queue;
/*
 *
 */
void init(Queue *q) {
	q->front=NULL;
	q->back=NULL;
}
/*
 *
 */
int isEmpty(Queue *q) {
	if(q->front==NULL)
        return 1;
	return 0;
}
/*
 *
 */
Item dequeue(Queue *q) {
    Item Thing;
    if(q->front==NULL)
        return -1;
    else {
        Thing = q->front->data;
        q->front=q->front->next;
        return Thing;
    }
}
/*
 *
 */
void enqueue(Queue *q, Item val) {

	Node *pointer = malloc(sizeof(Node));
	pointer->data=val;
	pointer->next=NULL;

	if(q->front==NULL){
        q->front=pointer;
        q->back=pointer;
	}
    else{
        q->back->next=pointer;
        q->back=pointer;
    }
}

void insertatend(Queue *q, Item val){
	Node *pointer = malloc(sizeof(Node));
	pointer->data=val;
	pointer->next=NULL;

	if(q->front==NULL){
				q->front=pointer;
				q->back=pointer;
	}else{
		pointer->next = q->front;
		q->front= pointer;
	}
}
/*
 *
 */
void destroy(Queue *q) {

    while(!isEmpty(q)){
    Node *del = q->front;
    q->front = q->front->next;
    free(del);
}
}

void display(Queue *q){

    Queue Display;
    init(&Display);
    printf("[ ");
    while(!isEmpty(q))
    {
        Item x = dequeue(q);
        printf("%s ",x);
        enqueue(&Display,x);
    }

    printf("]\n");

    while(!isEmpty(&Display))
        enqueue(q,dequeue(&Display));

}
/*
 * RoundRobin Scheduling
 */
 void RoundRobin(char* filename)
 {
 	FILE *fp;
   fp = fopen (filename,"r");
   Item x= malloc(sizeof(Process));
   x->name = malloc(20);
   int timeslot;
   int maxtimeslot = 0;
   if(!fp){
     printf("Error opening file\n" );
   }

   Queue a,b;
   init(&a);
   init(&b);
   while(fscanf(fp,"%s %d %d\n",x->name,&x->starting_time,&x->remaining_time)==3){
     insertatend	(&a,x);
		 x= malloc(sizeof(Process));
		 x->name = malloc(20);
	 }





     fclose (fp);

		 Queue q;
	 	init(&q);
		int i =0 ;
    while ( (!isEmpty(&a)) || (!isEmpty(&q))) {
         Item x;
       while (!isEmpty(&a)) {
           x= dequeue(&a);
         if(x->starting_time <= i){
           insertatend(&q,x);
				 }else if ((x->starting_time <= i+1)&&!isEmpty(&q)){
					 enqueue(&q,x);
				 }else {
           enqueue(&b,x);
         }

       }
       while (!isEmpty(&b)) {
         enqueue(&a,dequeue(&b));
       }

       if (!isEmpty(&q)) {

         x = dequeue(&q);
         printf("%s (%d-->%d)",x->name,i,i+1 );
         x->remaining_time--;
         if (!x->remaining_time) {
           printf(" %s halts",x->name );
         }
         if(x->remaining_time>0){

           enqueue(&q,x);
         }

         printf("\n");


       }else if(isEmpty(&q)){
         printf("idle (%d-->%d)\n",i,i+1 );
       }

			 i++;

     }



 }

int main(int argc, char**argv) {

	RoundRobin("5674.txt");
	printf("EOF\n" );

	/*
    Queue q;
    init(&q);
    enqueue(&q,"1.7");
    enqueue(&q,"2.8");
    enqueue(&q,"3.7");
    display(&q);
    dequeue(&q);
    display(&q);
		*/
	return 0;
}
