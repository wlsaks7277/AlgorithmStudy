/*
*	Operating System Lab
*	    Lab2 (Synchronization)
*
*   lab2_bst_test.c :
*       - thread-safe bst test code.
*       - coarse-grained, fine-grained lock test code
*
* You can compare single thread result, coarse grained result and fine grained result.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#include <malloc/malloc.h>
#include <time.h>
#include <pthread.h>

#include "lab2_sync_types.h"

#define LAB2_TYPE_FINEGRAINED       0
#define LAB2_TYPE_COARSEGRAINED     1
#define LAB2_TYPE_SINGLE            2

#define LAB2_OPTYPE_INSERT          0
#define LAB2_OPTYPE_DELETE          1

void lab2_sync_usage(char *cmd)
{
    printf("\n Usage for %s : \n",cmd);
    printf("    -t: num thread, must be bigger than 0 ( e.g. 4 )\n");
    printf("    -c: test node count, must be bigger than 0 ( e.g. 10000000 ) \n");
}

void lab2_sync_example(char *cmd)
{
    printf("\n Example : \n");
    printf("    #sudo %s -t 4 -c 10000000 \n", cmd);
    printf("    #sudo %s -t 4 -c 10000000 \n", cmd);
}

static void print_result(lab2_tree *tree,int num_threads,int node_count ,int is_sync, int op_type ,double time){
    char *cond[] = {"fine-grained BST  ", "coarse-grained BST", "single thread BST"};
    char *op[] = {"insert","delete"};
    int result_count=0;


    printf("=====  Multi thread %s  %s experiment  =====\n",cond[is_sync],op[op_type]);
    printf("\n Experiment info \n");
    printf("    test node           : %d \n",node_count);
    printf("    test threads        : %d \n",num_threads);
    printf("    execution time      : %lf seconds \n\n",time);

    printf("\n BST inorder iteration result : \n");
    result_count=lab2_node_print_inorder(tree);
    printf("    total node count    : %d \n\n",node_count);


}

void* thread_job_delete(void *arg){

    thread_arg *th_arg = (thread_arg *)arg;
    lab2_tree *tree = th_arg->tree;
    int is_sync = th_arg->is_sync;
    int *data_set = th_arg->data_set;
    int start = th_arg->start, end = th_arg->end;
    int i;
    for(i=start ; i < end; i++ ){
        if(is_sync == LAB2_TYPE_FINEGRAINED)
            lab2_node_remove_fg(tree, data_set[i]);        
        else if(is_sync == LAB2_TYPE_COARSEGRAINED)
            lab2_node_remove_cg(tree, data_set[i]);
    }
}

void* thread_job_insert(void *arg){

    thread_arg *th_arg = (thread_arg *)arg;
    lab2_tree *tree = th_arg->tree;
    int is_sync = th_arg->is_sync;
    int *data = th_arg->data_set;
    int start = th_arg->start, end = th_arg->end;
    int i;

    for (i=start ; i < end ; i++) {               
        lab2_node* node = lab2_node_create(data[i]);
        if(is_sync == LAB2_TYPE_FINEGRAINED)
            lab2_node_insert_fg(tree, node);
        else if(is_sync == LAB2_TYPE_COARSEGRAINED)
            lab2_node_insert_cg(tree, node);
    }
}

void bst_test(int num_threads,int node_count){

    lab2_tree *tree;
    lab2_node *node;    
    struct timeval tv_insert_start, tv_insert_end, tv_delete_start, tv_delete_end, tv_start, tv_end;
    int errors,i=0,count=0;
    int root_data = 40; 
    int term = node_count / num_threads, is_sync;
    double exe_time=0.0;
    thread_arg *threads;
    int *data = (int*)malloc(sizeof(int)*node_count);

    srand(time(NULL));
    for (i=0; i < node_count; i++) { 
        data[i] = rand();
    }

    if (!(threads = (thread_arg*)malloc(sizeof(thread_arg) * num_threads)))
        abort();

    /*
     * single thread insert test.
     */
    gettimeofday(&tv_start, NULL);
    printf("\n");
    tree = lab2_tree_create();
    for (i=0 ; i < node_count ; i++) {               
        lab2_node* node = lab2_node_create(data[i]);
        lab2_node_insert(tree, node);
    }

    gettimeofday(&tv_end, NULL);
    exe_time = get_timeval(&tv_start, &tv_end);
    print_result(tree,num_threads, node_count, LAB2_TYPE_SINGLE,LAB2_OPTYPE_INSERT ,exe_time);
    lab2_tree_delete(tree);

    /* 
     * multi therad insert test coarse-grained 
     */
    is_sync = LAB2_TYPE_COARSEGRAINED;
    tree = lab2_tree_create();

    gettimeofday(&tv_insert_start, NULL);
    for(i=0; i < num_threads ; i++){
        thread_arg *th_arg = &threads[i];
        th_arg->tree = tree;
        th_arg->is_sync = is_sync;
        th_arg->data_set = data;
        th_arg->start = i*term;
        th_arg->end = (i+1)*term;

        pthread_create(&threads[i].thread,NULL,thread_job_insert,(void*)th_arg);
    }

    for (i = 0; i < num_threads; i++)
        pthread_join(threads[i].thread, NULL);

    gettimeofday(&tv_insert_end, NULL);
    exe_time = get_timeval(&tv_insert_start, &tv_insert_end);
    print_result(tree,num_threads, node_count, is_sync,LAB2_OPTYPE_INSERT ,exe_time);
    lab2_tree_delete(tree);

    /*
     *  multi thread insert test fine-grained \
     */
    is_sync = LAB2_TYPE_FINEGRAINED;
    tree = lab2_tree_create();

    gettimeofday(&tv_insert_start, NULL);
    for(i=0; i < num_threads ; i++){
        thread_arg *th_arg = &threads[i];
        th_arg->tree = tree;
        th_arg->is_sync = is_sync;
        th_arg->data_set = data;
        th_arg->start = i*term;
        th_arg->end = (i+1)*term;

        pthread_create(&threads[i].thread,NULL,thread_job_insert,(void*)th_arg);
    }

    for (i = 0; i < num_threads; i++)
        pthread_join(threads[i].thread, NULL);

    gettimeofday(&tv_insert_end, NULL);
    exe_time = get_timeval(&tv_insert_start, &tv_insert_end);
    print_result(tree,num_threads, node_count, is_sync, LAB2_OPTYPE_INSERT,exe_time);
    lab2_tree_delete(tree);
    
    /* 
     * single thread delete test
     */

    tree = lab2_tree_create();
    for (i=0 ; i < node_count ; i++) {               
        lab2_node* node = lab2_node_create(data[i]);
        lab2_node_insert(tree, node);
    }

    gettimeofday(&tv_start, NULL);
    for(i=0 ; i < node_count ; i++){
        lab2_node_remove(tree,data[i]);
    }

    gettimeofday(&tv_end, NULL);
    exe_time = get_timeval(&tv_start, &tv_end);
    print_result(tree ,num_threads, node_count, LAB2_TYPE_SINGLE, LAB2_OPTYPE_DELETE,exe_time);
    lab2_tree_delete(tree);
    
    /* 
     * multi thread delete test coarse-grained  
     */
    is_sync = LAB2_TYPE_COARSEGRAINED;
    tree = lab2_tree_create();

    for (i=0; i < node_count; i++) { 
        node = lab2_node_create(data[i]);
        if(is_sync == LAB2_TYPE_FINEGRAINED)
            lab2_node_insert_fg(tree,node);
        else if(is_sync == LAB2_TYPE_COARSEGRAINED)
            lab2_node_insert_cg(tree,node);
    }            
    
    gettimeofday(&tv_delete_start, NULL);
    for(i=0 ; i < num_threads ; i++){
        thread_arg *th_arg = &threads[i];
        th_arg->tree = tree;
        th_arg->is_sync = is_sync;
        th_arg->data_set = data;
        th_arg->start = i*term;
        th_arg->end = (i+1)*term;

        pthread_create(&threads[i].thread,NULL,thread_job_delete,(void*)th_arg);
    }

    for (i = 0; i < num_threads; i++)
        pthread_join(threads[i].thread, NULL);
    gettimeofday(&tv_delete_end, NULL);
    exe_time = get_timeval(&tv_delete_start, &tv_delete_end);

    print_result(tree,num_threads, node_count, is_sync,LAB2_OPTYPE_DELETE,exe_time);
    lab2_tree_delete(tree);

    /* 
     * multi thread delete test fine-grained  
     */
    is_sync = LAB2_TYPE_FINEGRAINED;
    tree = lab2_tree_create();
    for (i=0; i < node_count; i++) { 
        node = lab2_node_create(data[i]);
        if(is_sync == LAB2_TYPE_FINEGRAINED)
            lab2_node_insert_fg(tree,node);
        else if(is_sync == LAB2_TYPE_COARSEGRAINED)
            lab2_node_insert_cg(tree,node);
    }

    gettimeofday(&tv_delete_start, NULL);
    for(i=0 ; i < num_threads ; i++){
        thread_arg *th_arg = &threads[i];
        th_arg->tree = tree;
        th_arg->is_sync = is_sync;
        th_arg->data_set = data;
        th_arg->start = i*term;
        th_arg->end = (i+1)*term;

        pthread_create(&threads[i].thread,NULL,thread_job_delete,(void*)th_arg);
    }

    for (i = 0; i < num_threads; i++)
        pthread_join(threads[i].thread, NULL);

    gettimeofday(&tv_delete_end, NULL);
    exe_time = get_timeval(&tv_delete_start, &tv_delete_end);

    print_result(tree ,num_threads, node_count, is_sync, LAB2_OPTYPE_DELETE,exe_time);
    lab2_tree_delete(tree);

    printf("\n");

    free(threads);
    free(data);
}






int main(int argc, char *argv[]) 
{
    int thread_count;
    int c_count;
    
    //옵션
    char option;
    
    while( (option = getopt(argc,argv,"t:c:")) != -1 ){
        switch(option) {
            case 't' : thread_count = atoi(optarg); break;
            case 'c' : c_count = atoi(optarg); break;
            default: usage(argv[0]); break;
        }
        
    }
    
    
    loop = c_count;
    loop2 = c_count * thread_count; //single count
    
    Queue_Init(&q0);
    Queue_Init(&q1);
    Queue_Init(&q2);
    
    
    
    
    // ============ 싱글 스레드 큐 삽입 ============
    coarse_grained = 1;
    time_t startTime0=0, endTime0=0;
    float gap0;
    startTime0 = clock();
    
    
    int res0 = -1;
    pthread_t *pthreads0 = NULL;
    
    pthreads0 = (pthread_t*)malloc(sizeof(pthread_t)*thread_count);
    memset(pthreads0, 0x0, sizeof(pthread_t) * thread_count );
    
    for(int i = 0; i < 1; i++)
    {
        res0 = pthread_create(&pthreads0[i], NULL, single_insert, NULL);
        if(res0 == -1){
            printf(" Error: _perf_metadata - pthread_create error \n");
        }
    }
    for(int i = 0; i < 1; i++)
    {
        pthread_join(pthreads0[i], NULL);
    }
    
    
    
    
    //시간 측정
    endTime0 = clock();
    gap0 = (float)(endTime0-startTime0)/(CLOCKS_PER_SEC);
    printf("\n===== 싱글 스레드 큐 삽입(락 없음) =====\n\n");
    printf("Experiment info\n");
    printf("\ttest node\t: %d\n", c_count);
    printf("\ttest thread\t: %d\n", thread_count);
    printf("\t측정 시간\t: %f 초\n\n",gap0);
    
    
    
    
    
    
    
    
    
    
    // ============ 스레드 4개 큐 삽입 coarse ============
    coarse_grained = 1;
    time_t startTime=0, endTime=0;
    float gap;
    startTime = clock();
    
    
    pthread_mutex_init(&m, NULL);
    
    //스레드 만들어주기
    //    for(int i = 0; i < thread_count; i++)
    //    {
    //        pthread_t p[i];
    //        pthread_create(&p[i], NULL, insert, NULL);
    //        pthread_join(p[i], NULL);
    //    }
    
    int res = -1;
    pthread_t *pthreads = NULL;
    
    pthreads = (pthread_t*)malloc(sizeof(pthread_t)*thread_count);
    memset(pthreads, 0x0, sizeof(pthread_t) * thread_count );
    
    for(int i = 0; i < thread_count; i++)
    {
        res = pthread_create(&pthreads[i], NULL, insert, NULL);
        if(res == -1){
            printf(" Error: _perf_metadata - pthread_create error \n");
        }
    }
    for(int i = 0; i < thread_count; i++)
    {
        pthread_join(pthreads[i], NULL);
    }
    
    
    //시간 측정
    endTime = clock();
    gap = (float)(endTime-startTime)/(CLOCKS_PER_SEC);
    printf("\n===== 멀티 스레드 coarse_grained 큐 삽입 =====\n\n");
    printf("Experiment info\n");
    printf("\ttest node\t: %d\n", c_count);
    printf("\ttest thread\t: %d\n", thread_count);
    printf("\t측정 시간\t: %f 초\n\n",gap);
    
    
    
    
    
    
    // ============ 스레드 4개 큐 삽입 fine ============
    coarse_grained = 0;
    
    time_t startTime2=0, endTime2=0;
    float gap2;
    startTime2 = clock();
    
    
    int res2 = -1;
    pthread_t *pthreads2 = NULL;
    
    pthreads2 = (pthread_t*)malloc(sizeof(pthread_t)*thread_count);
    memset(pthreads2, 0x0, sizeof(pthread_t) * thread_count );
    
    for(int i = 0; i < thread_count; i++)
    {
        res2 = pthread_create(&pthreads2[i], NULL, insert, NULL);
        if(res2 == -1){
            printf(" Error: _perf_metadata - pthread_create error \n");
        }
    }
    for(int i = 0; i < thread_count; i++)
    {
        pthread_join(pthreads2[i], NULL);
    }
    
    
    
    //시간 측정
    endTime2 = clock();
    gap2 = (float)(endTime2-startTime2)/(CLOCKS_PER_SEC);
    printf("\n===== 멀티 스레드 fine_grained 큐 삽입 =====\n\n");
    printf("Experiment info\n");
    printf("\ttest node\t: %d\n", c_count);
    printf("\ttest thread\t: %d\n", thread_count);
    printf("\t측정 시간\t: %f 초\n\n",gap2);
    
    
    
    
    
    
    
    
    // ============ 싱글 스레드 큐 삭제 ============
    coarse_grained = 1;
    time_t startTime3=0, endTime3=0;
    float gap3;
    startTime3 = clock();
    
    
    int res3 = -1;
    pthread_t *pthreads3 = NULL;
    
    pthreads3 = (pthread_t*)malloc(sizeof(pthread_t)*thread_count);
    memset(pthreads3, 0x0, sizeof(pthread_t) * thread_count );
    
    for(int i = 0; i < 1; i++)
    {
        res3 = pthread_create(&pthreads3[i], NULL, single_delete, NULL);
        if(res3 == -1){
            printf(" Error: _perf_metadata - pthread_create error \n");
        }
    }
    for(int i = 0; i < 1; i++)
    {
        pthread_join(pthreads3[i], NULL);
    }
    
    
    //시간 측정
    endTime3 = clock();
    gap3 = (float)(endTime3-startTime3)/(CLOCKS_PER_SEC);
    printf("\n===== 싱글 스레드 큐 삭제(락 없음) =====\n\n");
    printf("Experiment info\n");
    printf("\ttest node\t: %d\n", c_count);
    printf("\ttest thread\t: %d\n", thread_count);
    printf("\t측정 시간\t: %f 초\n\n",gap3);
    
    
    
    
    
    // ============ 스레드 4개 큐 삭제 coarse ============
    coarse_grained = 1;
    time_t startTime4=0, endTime4=0;
    float gap4;
    startTime4 = clock();
    
    
    pthread_mutex_init(&m, NULL);
    
    
    int res4 = -1;
    pthread_t *pthreads4 = NULL;
    
    pthreads4 = (pthread_t*)malloc(sizeof(pthread_t)*thread_count);
    memset(pthreads4, 0x0, sizeof(pthread_t) * thread_count );
    
    for(int i = 0; i < thread_count; i++)
    {
        res4 = pthread_create(&pthreads4[i], NULL, q_delete, NULL);
        if(res4 == -1){
            printf(" Error: _perf_metadata - pthread_create error \n");
        }
    }
    for(int i = 0; i < thread_count; i++)
    {
        pthread_join(pthreads4[i], NULL);
    }
    
    
    //시간 측정
    endTime4 = clock();
    gap4 = (float)(endTime4-startTime4)/(CLOCKS_PER_SEC);
    printf("\n===== 멀티 스레드 coarse_grained 큐 삭제 =====\n\n");
    printf("Experiment info\n");
    printf("\ttest node\t: %d\n", c_count);
    printf("\ttest thread\t: %d\n", thread_count);
    printf("\t측정 시간\t: %f 초\n\n",gap4);
    
    
    
    
    
    
    // ============ 스레드 4개 큐 삭제 fine ============
    coarse_grained = 0;
    
    time_t startTime5=0, endTime5=0;
    float gap5;
    startTime5 = clock();
    
    
    int res5 = -1;
    pthread_t *pthreads5 = NULL;
    
    pthreads5 = (pthread_t*)malloc(sizeof(pthread_t)*thread_count);
    memset(pthreads5, 0x0, sizeof(pthread_t) * thread_count );
    
    for(int i = 0; i < thread_count; i++)
    {
        res5 = pthread_create(&pthreads5[i], NULL, q_delete, NULL);
        if(res5 == -1){
            printf(" Error: _perf_metadata - pthread_create error \n");
        }
    }
    for(int i = 0; i < thread_count; i++)
    {
        pthread_join(pthreads5[i], NULL);
    }
    
    
    
    
    //printf("counter : %d \n",counter);
    
    //시간 측정
    endTime5 = clock();
    gap5 = (float)(endTime5-startTime5)/(CLOCKS_PER_SEC);
    printf("\n===== 멀티 스레드 fine_grained 큐 삭제 =====\n\n");
    printf("Experiment info\n");
    printf("\ttest node\t: %d\n", c_count);
    printf("\ttest thread\t: %d\n", thread_count);
    printf("\t측정 시간\t: %f 초\n\n",gap5);
    
    
    
    return 0;
}

