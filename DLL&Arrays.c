#include <stdio.h>
#include <stdlib.h>


typedef struct Node Node;
typedef struct Node{
  int Data;
  Node *Next;
  Node *Prev;
}Node;


typedef struct DoublyLinkedList{
  Node* Header;
  Node* Trailer;
}DoublyLinkedList;
const DoublyLinkedList EmptyList = {NULL, NULL};

size_t length(DoublyLinkedList list);

DoublyLinkedList List;
void InitDLL(DoublyLinkedList *Dll){

  Dll->Header = NULL;
  Dll->Trailer = NULL;
}
void AddNode(DoublyLinkedList *Dll,int Data){
  Node *Temp;
  if(Dll->Header){
    Temp = Dll->Header;
    while (Temp->Next) {
      Temp = Temp->Next;
    }
    Temp->Next = malloc(sizeof(Node));
    Temp->Next->Prev = Temp;
    Temp = Temp->Next;
    Temp->Next = NULL;
    Temp->Data = Data;
    Dll->Trailer = Temp;

  }
  else{
    Dll->Header=malloc(sizeof(Node));
    Dll->Header->Prev = NULL;
    Dll->Header->Next = NULL;
    Dll->Header->Data = Data;
    Dll->Trailer = Dll->Header;

  }
}
DoublyLinkedList convertArrayToDoublyLinkedList(int array[], int size){
  DoublyLinkedList Dll;
  Dll.Header = NULL;
  Dll.Trailer = NULL;
  for (size_t i = 0; i < size; i++) {
    AddNode(&Dll,array[i]);
  }
  return Dll;
}
void destroy(DoublyLinkedList* list){

  Node* Temp = list->Header;
  int len = length(*list);
  for (size_t i = 0; i < len-1; i++) {
    Temp = Temp->Next;
    if(Temp->Prev){
      free(Temp->Prev);
    }
  }
  free(Temp);
  list->Header = 0;
  list->Trailer = 0;


}
DoublyLinkedList dup(DoublyLinkedList list){
  DoublyLinkedList Dup;
  Dup.Header = NULL;
  Dup.Trailer = NULL;
  Node* Temp = list.Header;
  for (size_t i = 0; i < length(list); i++) {
    AddNode(&Dup,Temp->Data);
    Temp = Temp->Next;
  }
  return Dup;

}
DoublyLinkedList concatenate(DoublyLinkedList list1, DoublyLinkedList list2){
  DoublyLinkedList conc;
  InitDLL(&conc);
  conc = list1;

  if (!conc.Trailer) {
    conc = list2;
  }else if(!list2.Header){

  }else{
    Node *n = conc.Trailer;
    conc.Trailer =  list2.Trailer;
    n->Next = list2.Header;
    list2.Header->Prev = n;
  }
  return conc;
}
size_t length(DoublyLinkedList list){
  Node* Temp = list.Header;
  int ID = 0;
  while (Temp) {
    ID++;
    Temp = Temp->Next;
  }
  return ID;
}
int isPalindrome(DoublyLinkedList list){
  Node *T1 = list.Header;
  Node *T2 = list.Trailer;
  for (size_t i = 0; i < length(list)/2; i++) {
    if(T1->Data != T2->Data){
      return 0;
    }
    T1 = T1->Next;
    T2 = T2->Prev;
  }
  return 1;
}
int areEqual(DoublyLinkedList list1, DoublyLinkedList list2){
  Node *T1 = list1.Header;
  Node *T2 = list2.Header;
  if (length(list1) != length(list2)) {
    return 0;
  }
  for (size_t i = 0; i < length(list1)/2; i++) {
    if(T1->Data != T2->Data){
      return 0;
    }
    T1 = T1->Next;
    T2 = T2->Next;
  }
  return 1;

}
void printlnListForward(DoublyLinkedList list){
  Node* Temp = list.Header;
  int ID = 0;
  printf("{" );
  while (Temp) {
    printf(" %d ",Temp->Data );
    Temp = Temp->Next;
  }
  printf("}\n" );

}
void printlnListBackward(DoublyLinkedList list){
  Node* Temp = list.Trailer;
  int ID = 0;
  printf("{" );

  while (Temp) {
    printf(" %d ",Temp->Data );
    Temp = Temp->Prev;
  }
  printf("}\n" );

}


void Investigate(char* title, DoublyLinkedList list) {
  printf("%s\n", title);
  printf("List =         ");
  printlnListForward(list);
  printf("Reverse List = ");
  printlnListBackward(list);
  printf("List Length = %u\n", length(list));
  printf("List isPalindrome = %d\n", isPalindrome(list));
  printf("...................................................\n");
}
/*
*
*/
void testConcatenate1(DoublyLinkedList list1, DoublyLinkedList list2) {
  DoublyLinkedList list3, list4, emptyList1;

  list3 = dup(list1);

  Investigate("List3 = dup(List1)\n==================", list3);
  emptyList1 = dup(EmptyList);

  Investigate("EmptyList1 = dup(EmptyList)\n===========================", emptyList1);
  DoublyLinkedList list5 = concatenate(list3, emptyList1);
  Investigate("List5 = List3<->EmptyList1\n==========================", list5);
  destroy(&list5);


  Investigate("List5 (after destroy)\n=====================", list5);
  //destroy(&list3);			//already destroyed when list5 got destroyed
  //destroy(&emptyList1);		//already destroyed when list5 got destroyed
}
/*
*
*/
void testConcatenate2(DoublyLinkedList list1, DoublyLinkedList list2) {
  DoublyLinkedList list3, list4, emptyList1;
  list3 = dup(list1);

  emptyList1 = dup(EmptyList);
  DoublyLinkedList list6 = concatenate(emptyList1, list3);
  Investigate("List6 = EmptyList1<->List3\n==========================", list6);
  destroy(&list6);
  Investigate("List6 (after destroy)\n=====================", list6);
  //destroy(&list3);			//already destroyed when list6 got destroyed
  //destroy(&emptyList1);		//already destroyed when list6 got destroyed
}
/*
*
*/
void testConcatenate3(DoublyLinkedList list1, DoublyLinkedList list2) {
  DoublyLinkedList list3, list4, emptyList1;

  list3 = dup(list1);
  list4 = dup(list2);
  DoublyLinkedList list7 = concatenate(list3, list4);
  Investigate("List7 = List3<->List4\n=====================", list7);
  destroy(&list7);
  Investigate("List7 (after destroy)\n=====================", list7);
  //destroy(&list3);			//already destroyed when list7 got destroyed
  //destroy(&list4);			//already destroyed when list7 got destroyed
}
/*
*
*/
void testConcatenate() {
  int array1[] = {0, 1, 2, 3, 4, 5, 6};
  int array2[] = {7, 8, 9};

  DoublyLinkedList list1 = convertArrayToDoublyLinkedList(array1, sizeof(array1)/sizeof(*array1));
  Investigate("List1\n=====", list1);
  DoublyLinkedList list2 = convertArrayToDoublyLinkedList(array2, sizeof(array2)/sizeof(*array2));
  Investigate("List2\n=====", list2);

  testConcatenate1(list1, list2);
  testConcatenate2(list1, list2);
  testConcatenate3(list1, list2);
  destroy(&list1);
  destroy(&list2);
}
/*
*
*/
void testPalindrome() {
  int array3[] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 0};
  int array4[] = {7, 8, 9, 9, 8, 7};

  DoublyLinkedList list8 = convertArrayToDoublyLinkedList(array3, sizeof(array3)/sizeof(*array3));
  Investigate("List8\n=====", list8);
  DoublyLinkedList list9 = convertArrayToDoublyLinkedList(array4, sizeof(array4)/sizeof(*array4));
  Investigate("List9\n=====", list9);
  destroy(&list8);
  destroy(&list9);
}
/*
*
*/
void testAreEqual() {
  int array5[] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 0};
  int array6[] = {7, 8, 9, 9, 8, 7};
  int array7[] = {0, 1, 2, 3, 4, 5};

  DoublyLinkedList list10 = convertArrayToDoublyLinkedList(array5, sizeof(array5)/sizeof(*array5));
  Investigate("List10\n=====", list10);
  DoublyLinkedList list11 = convertArrayToDoublyLinkedList(array6, sizeof(array6)/sizeof(*array6));
  Investigate("List11\n=====", list11);
  DoublyLinkedList list12 = convertArrayToDoublyLinkedList(array7, sizeof(array7)/sizeof(*array7));
  Investigate("List12\n=====", list12);
  DoublyLinkedList emptyList1 = dup(EmptyList);
  Investigate("EmptyList1 = dup(EmptyList)\n===========================", emptyList1);
  DoublyLinkedList emptyList2 = dup(EmptyList);
  Investigate("EmptyList2 = dup(EmptyList)\n===========================", emptyList2);

  printf("areEqual(List10, List10) = %d\n", areEqual(list10, list10));
  printf("areEqual(List10, List11) = %d\n", areEqual(list10, list11));
  printf("areEqual(List10, List12) = %d\n", areEqual(list10, list12));
  printf("areEqual(List11, List10) = %d\n", areEqual(list11, list10));
  printf("areEqual(List10, EmptyList1) = %d\n", areEqual(list10, emptyList1));
  printf("areEqual(EmptyList1, List10) = %d\n", areEqual(emptyList1, list10));
  printf("areEqual(EmptyList1, EmptyList2) = %d\n", areEqual(emptyList1, emptyList2));

  destroy(&list10);
  destroy(&list11);
  destroy(&list12);

}
/*
*
*/
main() {
  testConcatenate();
  testPalindrome();
  testAreEqual();
  printf("done\n" );
  return 0;
}
