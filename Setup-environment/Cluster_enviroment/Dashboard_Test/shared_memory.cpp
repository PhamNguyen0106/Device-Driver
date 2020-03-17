#include "shared_memory.h"
#include <iostream>
using namespace std;

#define FILEKEY "/bin/ls"
#define KEY 10
#define BYTES sizeof(can_data)
#define SEMAPHORES 1
tshared_memory can_data;
tshared_memory *ptr_can_data;
key_t Key;
int Id_Shared_Memory;
int Id_Semaphore;
struct sembuf Operation;

void hmi_init_shared_memory(void)
{
    /* Calculate Key for Shared Memory and Semaphore */
    Key =ftok(FILEKEY,KEY);
    /* Check if error */
    if(Key ==-1){
        cout<<"Error with Key for Shared Memory and Semaphore"<<endl;
        return;
    }
    /* Create the Semaphore */
    Id_Semaphore =semget (Key,SEMAPHORES,0777|IPC_CREAT);
    /* Check if error */
    if(Id_Semaphore ==-1){
        cout<<"Error with Shared Memory ID"<<endl;
        return;
    }
    /* Create the Shared Memory */
    Id_Shared_Memory =shmget (Key,BYTES,0777|IPC_CREAT);
    /* Check if error */
    if(Id_Shared_Memory ==-1){
        cout<<"Error with Shared Memory ID"<<endl;
        return;
    }/* Semaphore Initialization*/
    semctl(Id_Semaphore,0,SETVAL,1);
    /* Point to Shared Memory */
    ptr_can_data =(tshared_memory *)shmat (Id_Shared_Memory,(char*)0,0);
    /* Check if error */
    if(ptr_can_data ==NULL){
        cout<<"Error reserving shared memory"<<endl;
        return;
    }
    /* Set values for Semaphore */
    Operation.sem_num =0;Operation.sem_flg =0;Operation.sem_op =1;
}
void hmi_deinit_shared_memory()
{
    /* Free the shared memory */
    shmdt ((char*)ptr_can_data);
    shmctl (Id_Shared_Memory,IPC_RMID,(struct shmid_ds *)NULL);
}

void write_int_value(quint16 frame_id, quint32 value)
{
    switch(frame_id){
        case KEY_STATUS:
            /* Change Semaphore to RED */
            Operation.sem_op =-1;
            /* Set the Semaphore to RED */
            semop (Id_Semaphore,&Operation,1);
            /*Write Value */
            ptr_can_data->key_status =(uint8_t)value;
            cout<<"KEY_STATUS"<<" 101"<<"value: "<<ptr_can_data->key_status<<endl;
            /* Change Semaphore to GREEN */
            Operation.sem_op =1;
            /* Set Semaphore to GREEN */
            semop (Id_Semaphore,&Operation,1);
            break;
        case STEERING_WHEEL:
            /* Change Semaphore to RED */
            Operation.sem_op =-1;
            /* Set the Semaphore to RED */
            semop (Id_Semaphore,&Operation,1);
            /* Write Value */
            ptr_can_data->steering_wheel =(uint16_t)value;
            cout<<"STEERING_WHEEL"<<" 103"<<"value: "<<ptr_can_data->steering_wheel<<endl;
            /* Change Semaphore to GREEN */
            Operation.sem_op =1;
            /* Set Semaphore to GREEN */
            semop (Id_Semaphore,&Operation,1);
            break;
        case LANE_DETECT:
            /* Change Semaphore to RED */
            Operation.sem_op =-1;
            /* Set the Semaphore to RED */
            semop (Id_Semaphore,&Operation,1);
            /* Write Value */
            ptr_can_data->lane_detect =(uint16_t)value;
            cout<<"LANE_DETECT"<<" 106"<<"value: "<<ptr_can_data->lane_detect<<endl;
            /* Change Semaphore to GREEN */
            Operation.sem_op =1;
            /* Set Semaphore to GREEN */
            semop (Id_Semaphore,&Operation,1);
            break;
        case CRUISE_CONTROL:
            /* Change Semaphore to RED */
            Operation.sem_op =-1;
            /* Set the Semaphore to RED */
            semop (Id_Semaphore,&Operation,1);
            /* Write Value */
            ptr_can_data->cruise_control =(uint8_t)value;
            cout<<"CRUISE_CONTROL"<<" 107"<<"value: "<<ptr_can_data->cruise_control<<endl;
            /* Change Semaphore to GREEN */
            Operation.sem_op =1;
            /* Set Semaphore to GREEN */
            semop (Id_Semaphore,&Operation,1);
            break;
        case PEDAL_ACCEL:
            /* Change Semaphore to RED */
            Operation.sem_op =-1;
            /* Set the Semaphore to RED */
            semop (Id_Semaphore,&Operation,1);
            /* Write Value */
            ptr_can_data->rpms =(uint16_t)value;
            cout<<"PEDAL_ACCEL"<<" 109"<<"value: "<<ptr_can_data->rpms<<endl;
            /* Change Semaphore to GREEN */
            Operation.sem_op =1;
            /* Set Semaphore to GREEN */
            semop (Id_Semaphore,&Operation,1);
            break;
        case LIGHT_SYSTEM:
            /* Change Semaphore to RED */
            Operation.sem_op =-1;
            /* Set the Semaphore to RED */
            semop (Id_Semaphore,&Operation,1);
            /* Write Value */
            ptr_can_data->lightning = (uint8_t)value;
            cout<<"LIGHT_SYSTEM"<<" 200"<<"value: "<<ptr_can_data->lightning<<endl;
            /* Change Semaphore to GREEN */
            Operation.sem_op =1;
            /* Set Semaphore to GREEN */
            semop (Id_Semaphore,&Operation,1);
            break;
        default:
        break;
    }
}
