# Smart Hospital & Resource Allocation System

## *Project Overview*

The Smart Hospital & Resource Allocation System is a menu-driven C programming project developed for the CSC 1012 – Introduction to Computer Programming course at the University of Sri Jayewardenepura.
The main purpose of this system is to manage basic hospital operations such as patient registration, doctor specialty selection, emergency priority management, bed allocation, waiting time calculation, and patient billing.
This project demonstrates the use of fundamental C programming concepts including arrays, strings, functions, loops, conditional statements, mathematical calculations, and file handling.

## *Main Features*

- Patient registration
- Patient information management
- Doctor specialty selection
- Emergency / urgency level management
- Waiting time calculation
- Hospital ward selection
- Bed occupancy management
- Bed allocation
- Consultation fee calculation
- Emergency surcharge calculation
- Ward cost calculation
- Age-based subsidy calculation
- Final patient bill calculation
- Patient record display
- Priority queue management
- Hospital performance reports
- Saving and loading hospital data using files

## *Doctor Specialties*

The system includes the following doctor specialties:

1. General Practice (OPD)
2. Paediatrics
3. Cardiology
4. Neurology

Each specialty has its own consultation fee, average consultation time, and daily patient capacity.

## *Hospital Wards*

The system includes four types of hospital wards:

1. General Ward
2. Paediatric Ward
3. Surgical Ward
4. ICU

Each ward has a specific daily rate and bed capacity.

## *Patient Management*

When registering a patient, the system collects important information such as:

- Patient name
- Age
- Urgency level
- Doctor specialty
- Admission status
- Ward selection
- Number of days admitted

The system uses this information to calculate waiting time, hospital charges, discounts, and the final amount payable.

## *Billing System*

The patient's final bill is calculated using:

- Consultation fee
- Emergency surcharge
- Ward admission cost
- Age-based subsidy

The system calculates the gross bill and then applies the relevant discount to determine the final payable amount.

## *Priority Management*

Patients are arranged according to their urgency level.

- Level 3 – Critical
- Level 2 – Urgent
- Level 1 – Normal

Critical patients receive the highest priority, followed by urgent and normal patients.

## *Data Structures Used*

The project uses basic C programming data structures and techniques such as:

- 1D arrays
- 2D arrays
- Parallel arrays
- Strings
- Functions
- Loops
- Conditional statements
- Switch statements
- Mathematical calculations
- File handling

## *File Handling*

The system supports file handling for storing hospital information and patient records.

The following files are used:

- `beds_status.txt` – stores bed occupancy information
- `patient_records.txt` – stores patient billing records

## *Technologies Used*

- C Programming Language
- Code::Blocks
- Git
- GitHub

## *How to Run the Project*

1. Clone or download this repository.
2. Open the `SmartHospital.cbp` project file using Code::Blocks.
3. Build the project.
4. Run the program.
5. Select an option from the main menu.
6. Follow the instructions displayed by the system.
