#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
   int data;
   struct node *next;
};

//함수 선언
void push(struct node **top, int data);
int pop(struct node **top);


int main() { 
   int data;
   struct node *p, *head = NULL;
   
   //값 입력
   while(scanf("%d", &data) == 1) {
      if(data <= 0 ) {
         break; //입력 값이 정수 인지 판별
      }
      push(&head, data); //스택에 추가
   }
   
   printf("print stack\n");

   //데이터 출력과 제거를 동시에 실행
   while (head != NULL)  {
      printf("%d\n", pop(&head));
   }
   
   exit(0);
}

//push() 스택에 데이터 추가 함수
void push(struct node **top, int data) {
   struct node *p = (struct node *) malloc(sizeof(struct node)); //포인터 p에 메모리 동적 할당
   p->data = data; //p의 data 필드에 data값을 저장
   p->next = *top; //p의 next 필드를 최상위 필드로 설정
   *top = p; //스택의 촤상위 포인터를 p로 변경
}

//pop() 스택에서 데이터 제거 함수
int pop(struct node **top) {
    struct node *temp = *top; //최상위 노드 제거를 위해 *top이 가리키는 노드를 임시 저장
    int data = temp->data; //제거할 노드가 가진 데이터를 저장
    *top = temp->next; //현 top을 다음 노드로 연결
    free(temp);//임시 저장 노드 메모리 해제
    return data; //제거된 노드의 데이터를 반환
}
