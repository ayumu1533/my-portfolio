//プログラム1C
#include<stdio.h>
//現在時刻を持ってくるためのinclude
#include<time.h>
//threadを扱うためのinclude
#include<pthread.h>
#define COUNT 1000
#define LOOP 10000
//現在時刻を格納する構造体
struct timespec ts[4][COUNT];
//mutexの宣言
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;
pthread_mutex_t mutex3;

void busy(){//時間稼ぎの関数
	for(int i= 0;i<LOOP;i++){}
}

void *fun(void *arg){//threadを実行する関数
int ts_index = 0;
int thn = (int)arg;
//開放するmutexを決めるために用意した変数
int state;
	
	for(int i=0;i<4;i++){//一つのスレッドの経過時間を4個の塊で表現
		while(1){
			if(pthread_mutex_trylock(&mutex1)==0){//mutexを一つ取得できたとき
				if(pthread_mutex_trylock(&mutex2)==0){//mutexの2つ目が取得できたとしたら
					state = 1;
					break;
				}else if(pthread_mutex_trylock(&mutex3)==0){//mutexの2つ目が取得できたとしたら
					state = 2;
					break;//while文を抜ける
				}else{//mutex2つ目が取得できなかったら
					pthread_mutex_unlock(&mutex1);//mutex1を開放
				}
			}
			if(pthread_mutex_trylock(&mutex2)==0){//mutexを一つ取得できたとき
				if(pthread_mutex_trylock(&mutex1)==0){//mutexの2つ目が取得できたとしたら
					state = 3;
					break;
				}else if(pthread_mutex_trylock(&mutex3)==0){//mutexの2つ目が取得できたとしたら
					state = 4;
					break;//while文を抜ける
				}else{//mutex2つ目が取得できなかったら
					pthread_mutex_unlock(&mutex2);//mutex2を開放
				}
			}
			if(pthread_mutex_trylock(&mutex3)==0){//mutexを一つ取得できたとき
				if(pthread_mutex_trylock(&mutex1)==0){//mutexの2つ目が取得できたとしたら
					state = 5;
					break;
				}else if(pthread_mutex_trylock(&mutex2)==0){//mutexの2つ目が取得できたとしたら
					state = 6;
					break;//while文を抜ける
				}else{//mutex2つ目が取得できなかったら
					pthread_mutex_unlock(&mutex3);//mutex3を開放
				}
			}
		}
		//処理A
		for(int j=0;j<250; j++){//現在時刻の取得250回(スレッド遷移を明確に表すため)
			busy();
			clock_gettime(CLOCK_REALTIME,&ts[thn][ts_index]);//現在時刻の取得
			ts_index++;
		}
		//mutexの開放
		if(state == 1 || state == 3){//mutex1,mutex2を開放の時
			pthread_mutex_unlock(&mutex1);
			pthread_mutex_unlock(&mutex2);
		}
		if(state == 2 || state == 5 ){//mutex1,mutex3を開放の時
			pthread_mutex_unlock(&mutex1); 
			pthread_mutex_unlock(&mutex3);
		}
		if(state == 4 || state == 6 ){//mutex2,mutex3を開放の時
			pthread_mutex_unlock(&mutex2); 
			pthread_mutex_unlock(&mutex3);
		}
		//処理B
		busy();
	}
}


int main(){

clock_gettime(CLOCK_REALTIME,&ts[0][0]);//初期時刻を取得
long startt = ts[0][0].tv_sec * 1000000000 + ts[0][0].tv_nsec;//初期時刻starttを宣言

//mutexの初期化
pthread_mutex_init(&mutex1, NULL);
pthread_mutex_init(&mutex2, NULL);
pthread_mutex_init(&mutex3, NULL);
//スレッドを作る
pthread_t th0,th1,th2,th3;
pthread_create(&th0,NULL,fun,(void *)0);
pthread_create(&th1,NULL,fun,(void *)1);
pthread_create(&th2,NULL,fun,(void *)2);
pthread_create(&th3,NULL,fun,(void *)3);

//スレッドの終了を待ち合わせる
pthread_join(th0,NULL);
pthread_join(th1,NULL);
pthread_join(th2,NULL);
pthread_join(th3,NULL);


for(int thn=0;thn<4;thn++){
	for(int i=0;i<COUNT; i++){
		long t = ts[thn][i].tv_sec * 1000000000 + ts[thn][i].tv_nsec;//thread内で格納した現在時刻をtに代入
		printf("%ld\t%d\n",t-startt,thn);//経過時間、その時点でのスレッドを出力
	}
}
}
