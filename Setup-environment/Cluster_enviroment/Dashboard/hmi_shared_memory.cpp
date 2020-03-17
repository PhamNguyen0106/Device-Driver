#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <dlt/dlt.h>
#include "hmi_shared_memory.h"
#include "hmi_dashboard.h"

tshared_memory Can_Data;
tshared_memory   *ptr_Can_Data;
key_t Key;
int Id_Shared_Memory;
int Id_Semaphore;
struct sembuf Operation;

#define FILEKEY         "/bin/ls"
#define KEY             10
#define BYTES           sizeof(Can_Data)
#define SEMAPHORES      1

DLT_IMPORT_CONTEXT(hmi_context)

uint8_t hmi_init_shared_memory(void){
    DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING(__FUNCTION__),DLT_STRING("function called"));
    Key =ftok (FILEKEY,KEY);
    if(Key ==-1){
        DLT_LOG(hmi_context,DLT_LOG_ERROR,DLT_STRING("Error with Key for Shared Memory and Semaphore"));
        return 1;
    }
    Id_Semaphore =semget(Key,SEMAPHORES,0777|IPC_CREAT);
    if(Id_Semaphore ==-1){
        DLT_LOG(hmi_context,DLT_LOG_ERROR,DLT_STRING("Error with Semaphore ID, SHARED_MEMORY_ERROR"));
        return 1;
    }
    Id_Shared_Memory =shmget (Key,BYTES,0777);
    if(Id_Shared_Memory ==-1){
        DLT_LOG(hmi_context,DLT_LOG_ERROR,DLT_STRING("Error with Shared Memory ID, SHARED_MEMORY_ERROR"));
        return 1;
    }
    ptr_Can_Data =(tshared_memory *)shmat (Id_Shared_Memory,(char*)0,0);
    if(ptr_Can_Data ==nullptr){
        DLT_LOG(hmi_context,DLT_LOG_ERROR,DLT_STRING("Error getting shared memory, SHARED_MEMORY_ERROR"));
        return 1;
    }
    Operation.sem_num =0;
    Operation.sem_flg =0;
    Operation.sem_op =1;
    return 0;
}

void hmi_deinit_shared_memory(void){
    DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING(__FUNCTION__),DLT_STRING("function called"));
    shmdt ((char*)ptr_Can_Data);
    return;
}

uint8_t hmi_compare_data(tshared_memory*valid_data){
    uint8_t cmp_res;
    DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING(__FUNCTION__),DLT_STRING("function called"));
    Operation.sem_op =-1;
    semop (Id_Semaphore,&Operation,1);
    if(memcmp(ptr_Can_Data,valid_data,sizeof(tshared_memory))==0){
        cmp_res =0;
    }else{
        cmp_res =1;
    }
    Operation.sem_op =1;
    semop (Id_Semaphore,&Operation,1);
    return cmp_res;
}

void hmi_copy_data(tshared_memory*valid_data){
    DLT_LOG(hmi_context,DLT_LOG_INFO,DLT_STRING(__FUNCTION__),DLT_STRING("function called"));
    Operation.sem_op =-1;
    semop (Id_Semaphore,&Operation,1);
    memcpy(valid_data,ptr_Can_Data,sizeof(tshared_memory));
    Operation.sem_op =1;
    semop (Id_Semaphore,&Operation,1);
}
