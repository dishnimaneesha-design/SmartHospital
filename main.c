#include <stdio.h>
#include <string.h>
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

void sortPatientsByPriority(
                            int urgency[],
                            int patientIDs[],
                            char patientNames[][50],
                            int patientAges[],
                            int patientSpecialties[],
                            int isAdmitted[],
                            int patientWards[],
                            int daysAdmitted[],
                            float patientFinalPayable[],
                            int assignedBedNumber[],
                            int count)
{
    int i, j;
    int tempUrgency;
    int tempID;
    char tempName[50];
    int tempAge;
    int tempSpecialty;
    int tempAdmitted;
    int tempWard;
    int tempDays;
    float tempFinalPayable;

    for (i = 0; i < count - 1; i++){
        for (j = 0; j < count - i - 1; j++){
            if (urgency[j] < urgency[j + 1]){
                strcpy(tempName, patientNames[j]);
                strcpy(patientNames[j], patientNames[j + 1]);
                strcpy(patientNames[j + 1], tempName);

                tempAge = patientAges[j];
                patientAges[j] = patientAges[j + 1];
                patientAges[j + 1] = tempAge;

                tempSpecialty = patientSpecialties[j];
                patientSpecialties[j] = patientSpecialties[j + 1];
                patientSpecialties[j + 1] = tempSpecialty;

                tempAdmitted = isAdmitted[j];
                isAdmitted[j] = isAdmitted[j + 1];
                isAdmitted[j + 1] = tempAdmitted;

                tempWard = patientWards[j];
                patientWards[j] = patientWards[j + 1];
                patientWards[j + 1] = tempWard;

                tempDays = daysAdmitted[j];
                daysAdmitted[j] = daysAdmitted[j + 1];
                daysAdmitted[j + 1] = tempDays;
                tempFinalPayable = patientFinalPayable[j];
                patientFinalPayable[j] = patientFinalPayable[j + 1];
                patientFinalPayable[j + 1] = tempFinalPayable;
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
void savePatientToFile(int id, char name[], int age, int urgency, float payable) {
    FILE *fp = fopen("patient_records.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "ID: PAT-%d | Name: %s | Age: %d | Urgency: %d | Payable: LKR %.2f\n",
                id, name, age, urgency, payable);
        fclose(fp);
    }
    }
void generateAnalyticsReport(
    int count, int urgency[], float finalPayable[], float ageDiscountTotal[],
    int isAdmitted[], int patientWards[], char wardName[][30],
    int wardCapacity[], int bedOccupancy[4][20], char patientNames[][50])
{
    printf("\n========================================\n");
    printf("     PERFORMANCE & ANALYTICS REPORT     \n");
    printf("========================================\n");

    if (count == 0) {
        printf("No patients registered yet.\n");
        return;
    }

    int normalCount = 0, urgentCount = 0, criticalCount = 0;
    float totalRevenue = 0.0f, totalDiscounts = 0.0f;
    float maxBill = -1.0f;
    int highestPayingIndex = -1;

    for (int i = 0; i < count; i++) {
        if (urgency[i] == 1) normalCount++;
        else if (urgency[i] == 2) urgentCount++;
        else if (urgency[i] == 3) criticalCount++;

        totalRevenue += finalPayable[i];
        totalDiscounts += ageDiscountTotal[i];

        if (finalPayable[i] > maxBill) {
            maxBill = finalPayable[i];
            highestPayingIndex = i;
        }
    }

    printf("1. Patient Categorization:\n");
    printf("   - Normal (Level 1)  : %d\n", normalCount);
    printf("   - Urgent (Level 2)  : %d\n", urgentCount);
    printf("   - Critical (Level 3): %d\n", criticalCount);
    printf("   - Total Registered  : %d\n\n", count);

    printf("2. Revenue Summary:\n");
    printf("   - Total Revenue Collected: LKR %.2f\n", totalRevenue);
    printf("   - Total Discounts Granted: LKR %.2f\n\n", totalDiscounts);

    printf("3. Bed Occupancy Percentage per Ward:\n");
    for (int w = 0; w < 4; w++) {
        int occupiedCount = 0;
        for (int b = 0; b < wardCapacity[w]; b++) {
            if (bedOccupancy[w][b] == 1) occupiedCount++;
        }
        float occupancyPercentage = ((float)occupiedCount / wardCapacity[w]) * 100.0f;
        printf("   - %-16s: %.2f%% (%d/%d beds)\n", wardName[w], occupancyPercentage, occupiedCount, wardCapacity[w]);
    }

    if (highestPayingIndex != -1) {
        printf("\n4. Highest-Paying Patient:\n");
        printf("   - Name: %s\n", patientNames[highestPayingIndex]);
        printf("   - Total Bill: LKR %.2f\n", finalPayable[highestPayingIndex]);
    }
}


int main()
{
    char again;


    printf("========================================\n");
    printf("       SMART HOSPITAL SYSTEM\n");
    printf("========================================\n");

    int choice;
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
    int assignedBedNumber[MAX_PATIENTS]={0};
    int daysAdmitted[MAX_PATIENTS];
    float patientFinalPayable[MAX_PATIENTS];
    int patientCount = 0;
    float ageDiscountTotal[MAX_PATIENTS] = {0};

    int dailyCapacity[4] = {
        30, 20, 12, 10
    };
    int specialtyQueue[4] = {0, 0, 0, 0};
    int waitingTime = 0;

    do
    {

        printf("\n========== SMART HOSPITAL MENU ==========\n");
        printf("1. Register Patient\n");
        printf("2. View Registered Patients\n");
        printf("3. Performance Reports & Analytics\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
    {
        if (patientCount >= MAX_PATIENTS)
    {
        printf("\nPatient limit reached. Cannot register more patients.\n");
        continue;
    }


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
    printf("\n========== PATIENT REGISTRATION ==========\n");

    printf("Enter patient name: ");
    scanf(" %49[^\n]", patientName[patientCount]);
    do{
    printf("Enter age: ");
    scanf("%d", &patientAge[patientCount]);

    if (patientAge[patientCount] < 0 ||
        patientAge[patientCount] > 120)
    {
        printf("Invalid age. Please enter an age between 0 and 120.\n");
    }

  } while (patientAge[patientCount] < 0 ||
           patientAge[patientCount] > 120);
  do{
    printf("Enter urgency level (1-Normal, 2-Urgent, 3-Critical): ");
    scanf("%d", &urgencyLevel[patientCount]);
    if (urgencyLevel[patientCount] < 1 ||
        urgencyLevel[patientCount] > 3)
    {
        printf("Invalid urgency level. Please enter 1-3.\n");
    }

  } while (urgencyLevel[patientCount] < 1 ||
           urgencyLevel[patientCount] > 3);

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
  do{
    printf("Is the patient admitted? (1-Yes, 0-No): ");
    scanf("%d", &isAdmitted[patientCount]);
    if (isAdmitted[patientCount] != 0 &&
        isAdmitted[patientCount] != 1){
            printf("Invalid choice. Please enter 1 for Yes or 0 for No.\n");
    }

  } while (isAdmitted[patientCount] != 0 &&
         isAdmitted[patientCount] != 1);

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

     do{
        printf("Enter number of admitted days: ");
        scanf("%d", &daysAdmitted[patientCount]);
        if (daysAdmitted[patientCount] <= 0)
        {
             printf("Invalid number of days. Please enter a positive number.\n");
        }

        } while (daysAdmitted[patientCount] <= 0);
        int wardIndex = patientWard[patientCount] - 1;
        int bedFound = 0;

        for (int j = 0; j < wardCapacity[wardIndex]; j++){
            if (bedOccupancy[wardIndex][j] == 0){
                 bedOccupancy[wardIndex][j] = 1;
                 assignedBedNumber[patientCount] = j + 1;
                 printf("\nBed allocated: %s - Bed %02d\n",
                        wardName[wardIndex], j + 1);

                 bedFound = 1;
                 break;
            }
        }
        if (bedFound == 0){
            printf("No beds are currently available in this ward.\n");
            isAdmitted[patientCount] = 0;
            patientWard[patientCount] = 0;
            daysAdmitted[patientCount] = 0;

            printf("Patient admission cancelled because no bed is available.\n");
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
    patientFinalPayable[patientCount] = finalPayable;

    printf("Age Subsidy Discount: LKR %.2f\n", ageDiscount);
    printf("Final Payable Amount: LKR %.2f\n", finalPayable);

    patientID[patientCount] = 1001 + patientCount;
    printf("\nSelected Specialty: %s\n",
           specialtyName[patientSpecialty[patientCount] - 1]);



    printf("Consultation Time: %d minutes\n",
           consultationTime[patientSpecialty[patientCount] - 1]);



    int selectedSpecialty = patientSpecialty[patientCount] - 1;
    waitingTime = specialtyQueue[selectedSpecialty]
              * consultationTime[selectedSpecialty];
    printf("Estimated Waiting Time: %d minutes\n", waitingTime);
    specialtyQueue[selectedSpecialty]++;


    printf("\n========================================\n");
    printf("   SMART HOSPITAL ADMISSION & BILL      \n");
    printf("----------------------------------------\n");
    printf("Patient ID             : PAT-%d\n", patientID[patientCount]);
    printf("Patient Name           : %s\n", patientName[patientCount]);
    printf("Age                    : %d Years %s\n", patientAge[patientCount],
           (patientAge[patientCount] < 5 || patientAge[patientCount] > 65) ? "(15% Subsidy Eligible)" : "");
    printf("Specialty              : %s\n", specialtyName[selectedSpecialty]);

    if (isAdmitted[patientCount] == 1) {

        printf("Assigned Ward          : %s\n", wardName[patientWard[patientCount] - 1]);
    } else {
        printf("Assigned Ward          : Outpatient (OPD)\n");
    }

    printf("Urgency Level          : Level %d (%s)\n", urgencyLevel[patientCount],
           urgencyLevel[patientCount] == 3 ? "Critical" : (urgencyLevel[patientCount] == 2 ? "Urgent" : "Normal"));
    printf("----------------------------------------\n");
    printf("Base Consultation Fee  : LKR %.2f\n", baseFee);
    printf("Emergency Surcharge    : LKR %.2f\n", emergencySurcharge);
    printf("Ward Stay Cost         : LKR %.2f\n", wardCost);
    printf("----------------------------------------\n");
    printf("Gross Total Bill       : LKR %.2f\n", grossTotal);
    printf("Age Subsidy Discount   : LKR -%.2f\n", ageDiscount);
    printf("----------------------------------------\n");
    printf("Final Payable Amount   : LKR %.2f\n", finalPayable);
    printf("Estimated Waiting Time : %d.00 mins\n", waitingTime);
    printf("========================================\n");


    savePatientToFile(patientID[patientCount], patientName[patientCount],
                      patientAge[patientCount], urgencyLevel[patientCount], finalPayable);

    patientCount++;
    printf("\nPatient registered successfully!\n");

 do{
    printf("\nDo you want to register another patient? (Y/N): ");
    scanf(" %c", &again);
    if (again != 'Y' && again != 'y' &&
        again != 'N' && again != 'n')
    {
        printf("Invalid choice. Please enter Y or N.\n");
    }

 } while (again != 'Y' && again != 'y' &&
         again != 'N' && again != 'n');


    }
    else if (choice == 2){
        printf("\n========== REGISTERED PATIENTS ==========\n");

        if (patientCount == 0){
            printf("No patients registered yet.\n");
        }
        else{
            sortPatientsByPriority(urgencyLevel,
                                   patientID,
                                   patientName,
                                   patientAge,
                                   patientSpecialty,
                                   isAdmitted,
                                   patientWard,
                                   daysAdmitted,
                                   patientFinalPayable,
                                   assignedBedNumber,
                                   patientCount);
            for (int i = 0; i < patientCount; i++)
            {
                 printf("\nPatient ID : %d\n", patientID[i]);
                 printf("Name      : %s\n", patientName[i]);
                 printf("Age       : %d\n", patientAge[i]);
                 printf("Urgency   : %d\n", urgencyLevel[i]);
                 printf("Specialty : %s\n",
                        specialtyName[patientSpecialty[i] - 1]);

                 if (isAdmitted[i] == 1){
                     printf("Ward      : %s\n",
                             wardName[patientWard[i] - 1]);
                     printf("Days      : %d\n", daysAdmitted[i]);

                 }
                 else{
                     printf("Ward      : Not Admitted\n");
                 }
                 printf("Final Payable: LKR %.2f\n",
                        patientFinalPayable[i]);
            }
        }

    }
    else if (choice == 3) {
    generateAnalyticsReport(patientCount, urgencyLevel, patientFinalPayable, ageDiscountTotal,
                           isAdmitted, patientWard, wardName, wardCapacity, bedOccupancy, patientName);
    }

    else if (choice != 4)
    {
        printf("\nInvalid choice. Please enter 1, 2, or 3.\n");
    }



  } while (choice != 3);

  printf("Exiting system...\n");

return 0;
}
