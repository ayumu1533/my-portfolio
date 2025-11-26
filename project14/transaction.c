#include <stdio.h>
//threadを扱うためのinclude
#include<pthread.h>
//現在時刻を持ってくるためのinclude
#include<time.h>
#define N 10000

char waste[N];
int from[N],to[N],amount[N];
int acount[100];
int judge;
pthread_mutex_t mutex1;
pthread_cond_t cvar;
struct timespec x,y;

void busy(int i){
for(i=0;i<amount[i]*100;i++){}
}

void *fun(void *arg){//threadを実行する関数
int thn = (int)arg;
for(int i=0;i<N;i = i+10){
pthread_mutex_lock(&mutex1);
busy(amount[i+thn]);
while(acount[from[i+thn]]-amount[i+thn]<0){
judge = i+thn;
printf("%d ● %d\n",acount[from[i+thn]],amount[i+thn]);
pthread_cond_wait(&cvar,&mutex1);
}
if(i+thn == judge){
	printf("%d ○ %d\n",acount[from[i+thn]],amount[i+thn]);
}

acount[from[i+thn]]-=amount[i+thn];
acount[to[i+thn]]+=amount[i+thn];


pthread_cond_signal(&cvar);

pthread_mutex_unlock(&mutex1);
}
}





int sumAmount(){
int sum =0;
for(int j=0;j<100;j++){
sum += acount[j];
}
return sum;
}


int main(){
clock_gettime(CLOCK_REALTIME,&x);//初期時刻を取得
long startt = x.tv_sec * 1000000000 + x.tv_nsec;//初期時刻starttを宣言
for(int i=0;i<100;i++){
acount[i]=10000;
}
FILE *istream;
int i = 0,val;
istream = fopen("trans.csv","r");
while(1){
	val = fscanf(istream,"%c,%d,%d,%d\n",&waste,&from[i],&to[i],&amount[i]);
	if(val==-1) break;
	i++;
}
fclose(istream);
printf("初期状態のすべての口座の総残高:%d\n",sumAmount());
//mutexの初期化
pthread_mutex_init(&mutex1, NULL);
//条件変数の初期化
pthread_cond_init(&cvar,NULL);

//スレッドを作る
pthread_t th0,th1,th2,th3,th4,th5,th6,th7,th8,th9;
pthread_create(&th0,NULL,fun,(void *)0);
pthread_create(&th1,NULL,fun,(void *)1);
pthread_create(&th2,NULL,fun,(void *)2);
pthread_create(&th3,NULL,fun,(void *)3);
pthread_create(&th4,NULL,fun,(void *)4);
pthread_create(&th5,NULL,fun,(void *)5);
pthread_create(&th6,NULL,fun,(void *)6);
pthread_create(&th7,NULL,fun,(void *)7);
pthread_create(&th8,NULL,fun,(void *)8);
pthread_create(&th9,NULL,fun,(void *)9);

//スレッドの終了を待ち合わせる
pthread_join(th0,NULL);
pthread_join(th1,NULL);
pthread_join(th2,NULL);
pthread_join(th3,NULL);
pthread_join(th4,NULL);
pthread_join(th5,NULL);
pthread_join(th6,NULL);
pthread_join(th7,NULL);
pthread_join(th8,NULL);
pthread_join(th9,NULL);
//各口座の残高
for(int k=0;k<100;k++){
printf("%d\n",acount[k]);
}
printf("現在のすべての講座の総残高：%d\n",sumAmount());

clock_gettime(CLOCK_REALTIME,&y);//現在時刻の取得
long finisht = y.tv_sec * 1000000000 + y.tv_nsec;//初期時刻starttを宣言
printf("経過時間：%ld\tns\n",finisht-startt);//経過時間、その時点でのスレッドを出力
}
