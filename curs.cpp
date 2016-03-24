#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"

void BubbleSort(int a[], int n){ // пузырьковая сортировка
	 for(int i = 0; i < n-1; i++){
	 		 for(int j = n; j >= i+1; j--){
			 		 if(a[j] < a[j-1]){
					 		 int k = a[j];
					      	 a[j] = a[j-1];
							 a[j-1] = k;	 
					  }		 	
  			}
     }	   	 
}

void FillRand(int mass[], int N){ // случайное заполнение без повторов
    int n,k;
    for(int i = 0; i <= N; i++){
            metka:
            n = rand()%(N+1)-0;
            k = 0;
            for(int j = 0; j < i; j++){
                    if(mass[j] == n){ k=1; break; }  
            }
            if(k == 0){ mass[i] = n; }
            else goto metka;
    }    
}

int RunNumber(int a[], int n){ // количество серий в массиве, используется для определения победы
     int k = 0,s = 1; 
     for(int i = 0; i < n-1; i++){
             if(a[i]<a[i+1]) k++;        
             else k = 0;
             if(k == 0) s++;
     }
     return s;
}

void DrawNew(int mass[], int N){ // рисование игрового поля
     int x = 0, y = 0; 
     int sq = 40; // размер квадратиков
     char ch[5];
     for(int i = 0; i <= N; i++){
             if(mass[i] != 0)
             setfillstyle(1,15);
             else setfillstyle(1,0);
             bar(x,y,x+sq,y+sq);
             rectangle(x,y,x+sq,y+sq);
             if(mass[i] != 0){ // заполнение квадратов
                        setbkcolor(15);
                        setcolor(0);
                        if(mass[i] >= 10)   // вывод текста внутри квадрата
                                   outtextxy(x+sq/4-5,y+sq/4,itoa(mass[i],ch,10));
                        else outtextxy(x+sq/4,y+sq/4,itoa(mass[i],ch,10));
             } 
             if((i%4==3) && (N == 15)){ x=0; y+=sq; } // условие начала новой строки при 15
             else if((i==2 || i==5) && (N == 8)){ x=0; y+=sq; } // при 8
             else if(((i+1)%5==0)&&(N == 24)){ x=0; y+=sq; }  // при 24
             else if(((i+1)%10==0)&&(N == 99)){ x=0; y+=sq; } // при 99
             else x+=sq;            
     }
}

int search0(int mass[], int N){
       for(int i = 0; i < N; i++)
               if(mass[i] == 0) return i;
}

int searchL(int n,int N){
    switch(N){
              case 8:{ int mass[] = {3,6};
                        for(int i = 0; i <= 1; i++)
                              if(n == mass[i]) return 1;
              } break;
              case 15:{ int mass[] = {4,8,12};
                        for(int i = 0; i <= 2; i++)
                              if(n == mass[i]) return 1;
              } break; 
              case 24:{ int mass[] = {5,10,15,20};
                        for(int i = 0; i <= 3; i++)
                              if(n == mass[i]) return 1;
                   } break; 
              case 99:{ int mass[] = {10,20,30,40,50,60,70,80,90};
                        for(int i = 0; i <= 8; i++)
                             if(n == mass[i]) return 1;
                   }break; 
    }
    return 0; 
}

int searchR(int n,int N){ 
    switch(N){
              case 8:{ int mass[] = {2,5};
                        for(int i = 0; i <= 1; i++)
                              if(n == mass[i]) return 1;
              } break;
              case 15:{ int mass[] = {3,7,11};
                        for(int i = 0; i <= 2; i++)
                              if(n == mass[i]) return 1;
              } break; 
              case 24:{ int mass[] = {4, 9, 14,19};
                        for(int i = 0; i <= 3; i++)
                              if(n == mass[i]) return 1;
                   } break; 
              case 99:{ int mass[] = {9,19,29,39,49,59,69,79,89};
                        for(int i = 0; i <= 8; i++)
                                if(n == mass[i]) return 1;
                   } break;
    }
    return 0; 
}

int DrawMenu(){
    settextstyle(9,0,2);
    setcolor(0); 
    setbkcolor(15);
    bar(220,120,420,150);
    outtextxy(260,125,"1) 3 x 3");
    bar(220,160,420,190); 
    outtextxy(260,165,"2) 4 x 4");
    bar(220,200,420,230); 
    outtextxy(260,205,"3) 5 x 5");
    bar(220,240,420,270); 
    outtextxy(260,245,"4) 10 x 10");
    bar(220,280,420,310); 
    outtextxy(260,285,"5) Рейтинг");
    setbkcolor(0);
    int ch = getch();
    switch(ch){case 49: return 8; break;
               case 50: return 15; break;
               case 51: return 24; break;
               case 52: return 99; break;
               case 53: return 21; break;
               default: exit(0); break; }
}

void Win(int koll){
     char ch[255];
	 itoa(koll,ch,10);
	 setbkcolor(0);
     setcolor(15);
     strcat(ch," шагов");
     outtextxy(290,125,"Вы выиграли!");      
     outtextxy(290,155,ch);  
     outtextxy(290,155,"Введите имя?");
     int x0=290, i =0;
     char h[255] = "", str[255]="";
     while(1){
              h[0] = getch();  
              outtextxy(x0,180,h);
              x0+=26;
              str[i]=h[0];
              i++;
              if((int)h[0]==13) break;
     }
     FILE *f;
     f = fopen("result.txt","a");
     fprintf(f,"%s %d\n",str,koll);
     fclose(f);
     closegraph(); 
}

void Random(int a[], int N, int step){ 
     int mass[] = {77,72,80,75}; 
     int g = search0(a,N);
     int s = 0;
     switch(N){case 8: s = 30; break;
               case 15: s = 60; break;
               case 24: s = 90; break;
               case 99: s = 300; break;               
               default: s = 100; break; }
     for(int i = 0; i <= s; i++){
			int n = rand()%4-0;
		    switch(mass[n]){
                     case 77: if((g!=0)&&(searchL(g,N)==0)){  
                                      int t = a[g];
                                      a[g] = a[g-1];
                                      a[g-1] = t;
                                      g = g-1;
                                      DrawNew(a,N);   }   break;          
                     case 72: if(g<=N-step){  
                                   int t = a[g];
                                   a[g] = a[g+step];
                                   a[g+step] = t;
                                   g = g+step;
                                   DrawNew(a,N); }
                     break; 
                     case 80: if(g>step-1){  
                                   int t = a[g];
                                   a[g] = a[g-step];
                                   a[g-step] = t;
                                   g = g-step;
                                   DrawNew(a,N);   }
                     break; 
                     case 75: if((g!=N)){  
                                   int t = a[g];
                                   a[g] = a[g+1];
                                   a[g+1] = t;
                                   g = g+1;
                                   DrawNew(a,N); 
                          } 
                     break; 
           			 }
			}
}
     
void Result(int koll){ 
     char ch[255];
     char str[] = "Шагов: ";
     strcat(str,itoa(koll,ch,10));
     setcolor(15); 
     setbkcolor(0);
     outtextxy(450,0,str);     
}     

void Top(){ 
     cleardevice(); 
     setbkcolor(15);
     char str[255];
     int koll;
     FILE *f;
     f = fopen("result.txt","r");
     int x0 = 0, y0 = 0;
     while(!feof(f)){
             fscanf(f,"%s %d\n",str,&koll);
             char ch[255] = ""; 
             outtextxy(x0,y0,strcat(str,itoa(koll,ch,10)));
             y0+=20;
     }
     fclose(f);
     if(getch() == 13){
     closegraph();  return; }
}

int main(){
    menu:
    initwindow(600,400); 
    int N = DrawMenu();
    int matrix[N];
    FillRand(matrix,N);
    int m;
    cleardevice();
    DrawNew(matrix,N); // рисование поля
    int step; // эл-ов в строке, он же шаг для проверки на невозможное перемещение
    if(N == 8) step = 3; 
    else if(N == 15) step = 4;
    else if(N == 24) step = 5;
    else if(N == 99) step = 10;
    else if(N == 21){ Top(); goto menu;}
    BubbleSort(matrix,N);
    Random(matrix,N,step); // перетасовка квадратов
    int g = search0(matrix,N);
    int koll = 0;
    while(1){
      Result(koll);
      if(kbhit()){ int h = getch(); 
           switch(h){case 77: if((g!=0)&&(searchL(g,N)==0)){  
                                      koll++;
                                      int t = matrix[g];
                                      matrix[g] = matrix[g-1];
                                      matrix[g-1] = t;
                                      g = g-1;
                                      DrawNew(matrix,N);   
                                      m = RunNumber(matrix,N); 
                                      if((m == 1) && (matrix[N] == 0)){ Win(koll); goto menu; }
                                      }   
						  break;          
                     case 72: if(g<=N-step){  
                                   koll++;
                                   int t = matrix[g];
                                   matrix[g] = matrix[g+step];
                                   matrix[g+step] = t;
                                   g = g+step;
                                   DrawNew(matrix,N); 
                                   m = RunNumber(matrix,N);
                                   if((m == 1) && (matrix[N] == 0)){ Win(koll); goto menu; }
                          } 
                     break; 
                     case 80: if(g>step-1){  
                                   koll++;
                                   int t = matrix[g];
                                   matrix[g] = matrix[g-step];
                                   matrix[g-step] = t;
                                   g = g-step;
                                   DrawNew(matrix,N);   
                                   m = RunNumber(matrix,N);
                                   if((m == 1) && (matrix[N] == 0)){ Win(koll); goto menu; }
                          } 
                     break; 
                     case 75: if((g!=N)&&(searchR(g,N)==0)){  
                                   koll++;
                                   int t = matrix[g];
                                   matrix[g] = matrix[g+1];
                                   matrix[g+1] = t;
                                   g = g+1;
                                   DrawNew(matrix,N);  
                                   m = RunNumber(matrix,N); 
                                   if((m == 1) && (matrix[N] == 0)){ Win(koll); goto menu; }
                          }
                     break; 
                     case 113: case -23: closegraph(); goto menu; 
                     break; }    
    }        
    }
    m:
    system("PAUSE");
    return 0;   
}
