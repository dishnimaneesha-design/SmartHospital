#include <stdio.h>
#define MAX_PATIENTS 100

float calculateSurcharge(float baseFee, int urgency)
{
    if (urgency == 1){
        return 0;
    }
    else if (urgency == 2){
        return baseFee * 0.20;
    }
    else{
        return baseFee * 0.50;
    }
}


float calculateWardCost(float dailyRate,int days)
{
    if (days == 0){
        return 0;
    }
    return dailyRate * days;
}

float calculateAgeDiscount(float grossTotal, int age)
{
    if (age < 5 || age > 65)
    {
        return grossTotal * 0.15;
    }
    else
    {
        return 0;
    }
}

void sortPatientsByPriority(int urgency[], int patientIDs[], int count)
{
    int i, j;
    int tempUrgency;
    int tempID;

    for (i = 0; i < count - 1; i++){
        for (j = 0; j < count - i - 1; j++){
            if (urgency[j] < urgency[j + 1]){
                tempUrgency = urgency[j];
                urgency[j] = urgency[j + 1];
                urgency[j + 1] = tempUrgency;

                tempID = patientIDs[j];
                patientIDs[j] = patientIDs[j + 1];
                patientIDs[j + 1] = tempID;
            }
        }
    }
}


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
    int patientID[MAX_PATIENTS];
    char patientName[MAX_PATIENTS][50];
    int patientAge[MAX_PATIENTS];
    int urgencyLevel[MAX_PATIENTS];//1 Normal , 2 Urgent , 3 Critical
    int patientSpecialty[MAX_PATIENTS]; //Doctor specialty
    int isAdmitted[MAX_PATIENTS];//1 = admitted, 0 = not admitted
    int patientWard[MAX_PATIENTS];
    int daysAdmitted[MAX_PATIENTS];
    int patientCount = 0;

    int dailyCapacity[4] = {
        30, 20, 12, 10
    };
    int specialtyQueue[4] = {0, 0, 0, 0};
    int waitingTime = 0;

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
    printf("\nPatient data arrays initialized successfully.\n");
    printf("\n========== PATIENT REGISTRATION ==========\n");

    printf("Enter patient name: ");
    scanf(" %[^\n]", patientName[patientCount]);
    printf("Enter age: ");
    scanf("%d", &patientAge[patientCount]);
    printf("Enter urgency level (1-Normal, 2-Urgent, 3-Critical): ");
    scanf("%d", &urgencyLevel[patientCount]);
    //printf("Enter specialty ID (1-4): ");
    //scanf("%d", &patientSpecialty[patientCount]);
    do{
        printf("Enter specialty ID (1-4): ");
        scanf("%d", &patientSpecialty[patientCount]);
        if (patientSpecialty[patientCount] < 1 ||
            patientSpecialty[patientCount] > 4)
        {
            printf("Invalid specialty ID. Please enter 1-4.\n");
        }

    }while (patientSpecialty[patientCount] < 1 ||
            patientSpecialty[patientCount] > 4);

    printf("Is the patient admitted? (1-Yes, 0-No): ");
    scanf("%d", &isAdmitted[patientCount]);

    if(isAdmitted[patientCount]==1){
        do{

            printf("Enter ward ID (1-4): ");
            scanf("%d", &patientWard[patientCount]);
            if(patientWard[patientCount] < 1 ||
               patientWard[patientCount] > 4){
                    printf("Invalid ward ID. Please enter 1-4.\n");
               }
        }while (patientWard[patientCount] < 1 ||
                patientWard[patientCount] > 4);
        printf("Enter number of admitted days: ");
        scanf("%d", &daysAdmitted[patientCount]);
        int wardIndex = patientWard[patientCount] - 1;
        int bedFound = 0;

        for (int j = 0; j < wardCapacity[wardIndex]; j++){
            if (bedOccupancy[wardIndex][j] == 0){
                 bedOccupancy[wardIndex][j] = 1;

                 printf("\nBed allocated: %s - Bed %02d\n",
                        wardName[wardIndex], j + 1);

                 bedFound = 1;
                 break;
            }
        }
        if (bedFound == 0){
            printf("No beds are currently available in this ward.\n");
        }

    }else{
        patientWard[patientCount] = 0;
        daysAdmitted[patientCount] = 0;
    }

    float wardCost = 0;

    if (isAdmitted[patientCount] == 1)
    {
        wardCost = calculateWardCost(
            wardDailyRate[patientWard[patientCount] - 1],
            daysAdmitted[patientCount]);
    }
    printf("\nWard Stay Cost: LKR %.2f\n", wardCost);


    float baseFee;
    float emergencySurcharge;
    baseFee = consultationFee[patientSpecialty[patientCount] - 1];

    emergencySurcharge = calculateSurcharge(
       baseFee,
       urgencyLevel[patientCount]
    );

    printf("Base Consultation Fee: LKR %.2f\n", baseFee);
    printf("Emergency Surcharge: LKR %.2f\n",
           emergencySurcharge);

    float grossTotal = baseFee + emergencySurcharge + wardCost;
    printf("Gross Total: LKR %.2f\n", grossTotal);

    float ageDiscount;
    float finalPayable;

    ageDiscount = calculateAgeDiscount(
         grossTotal,
         patientAge[patientCount]
    );

    finalPayable = grossTotal - ageDiscount;

    printf("Age Subsidy Discount: LKR %.2f\n", ageDiscount);
    printf("Final Payable Amount: LKR %.2f\n", finalPayable);

    patientID[patientCount] = 1001 + patientCount;
    printf("\nSelected Specialty: %s\n",
           specialtyName[patientSpecialty[patientCount] - 1]);


   //float baseFee;
   //float emergencySurcharge;

   //baseFee = consultationFee[patientSpecialty[patientCount] - 1];

   //emergencySurcharge = calculateSurcharge(
     //  baseFee,
     //  urgencyLevel[patientCount]
   //);

    //printf("Emergency Surcharge: LKR %.2f\n",
      //     emergencySurcharge);


    //printf("Consultation Fee: LKR %.2f\n",
      //     consultationFee[patientSpecialty[patientCount] - 1]);

    printf("Consultation Time: %d minutes\n",
           consultationTime[patientSpecialty[patientCount] - 1]);



    int selectedSpecialty = patientSpecialty[patientCount] - 1;
    waitingTime = specialtyQueue[selectedSpecialty]
              * consultationTime[selectedSpecialty];
    printf("Estimated Waiting Time: %d minutes\n", waitingTime);
    specialtyQueue[selectedSpecialty]++;

    patientCount++;
    printf("\nPatient registered successfully!\n");
    printf("\nPriority sorting function added successfully.\n");

    return 0;
}
