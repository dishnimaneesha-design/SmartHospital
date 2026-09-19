#include <stdio.h>

int main()
{
    printf("========================================\n");
    printf("       SMART HOSPITAL SYSTEM\n");
    printf("========================================\n");

    int specialtyID[4] = {1, 2, 3, 4};
    char specialtyName[4][30] = {
        "General Practice",
        "Paediatrics",
        "Cardiology",
        "Neurology"
    };

    float consultationFee[4] = {
        1500.00,
        2500.00,
        4500.00,
        5000.00
    };

    int consultationTime[4] = {
        15, 20, 30, 30
    };

    int wardID[4]={1,2,3,4};
    char wardName[4][30]={
        "General Ward",
        "Paediatric Ward",
        "Surgical Ward",
        "ICU"
    };
    float wardDailyRate[4]={
        3000.00,
        6000.00,
        12000.00,
        25000.00

    };

    int wardCapacity[4] = {
    20, 10, 10, 5
    };
    int bedOccupancy[4][20] = {0};

    int dailyCapacity[4] = {
        30, 20, 12, 10
    };

    printf("\nDoctor Specialties:\n");

    for (int i = 0; i < 4; i++)
    {
        printf("%d. %s - LKR %.2f - %d mins - Capacity %d\n",
               specialtyID[i],
               specialtyName[i],
               consultationFee[i],
               consultationTime[i],
               dailyCapacity[i]);
    }
    printf("\nHospital Wards:\n");
    for (int i=0;i<4;i++){
        printf("%d.%s-LKR%.2f/day - Capacity %d\n",
               wardID[i],
               wardName[i],
               wardDailyRate[i],
               wardCapacity[i]);

    }
    printf("\nBed Occupancy:\n");
    for(int i=0;i<4;i++){
        printf("\n%s:\n",wardName[i]);
        for(int j=0;j<wardCapacity[i];j++){
            if(bedOccupancy[i][j]==0){
                printf("Bed %02d : Available\n",j+1);
            }else{
                printf("Bed %02d : Occupied\n", j + 1);

            }

        }
    }




    return 0;
}
