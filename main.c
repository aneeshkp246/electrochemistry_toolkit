#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Function to calculate the EMF of the cell
double calculateEMF(double standardEMF, double concentrationAnode, double concentrationCathode, int electronsTransferred) {
    return standardEMF - ((0.0591 / electronsTransferred) * log10(concentrationAnode / concentrationCathode));
}

// Function to calculate the free energy change
double calculateFreeEnergyChange(double emf, int electronsTransferred) {
    return -emf * electronsTransferred * 96485; // Faraday's constant: 96485 C/mol
}


double calculateEMF_conc_cell(double conc1, double conc2, double n) {
    // Constants for the Nernst equation (R = gas constant, F = Faraday's constant)
    const double R = 8.314;  // J/(mol K)
    const double F = 96485;  // C/mol
    const double T = 298;    // K
    // Calculate emf using the Nernst equation
    double emf = -(R * T) / (n * F) * log(conc1 / conc2);
    return emf;
}

double calculate_cpr(double k, double W, double T, double A, double D)
{
    // Calculate the corrosion penetration rate in mmpy (millimeters per year)
    double CPR_mmpy = (k * W) / (D * A * T);

    // Calculate the corrosion penetration rate in mpy (mils per year)
    // double CPR_mpy = CPR_mmpy * 39.37;
    return CPR_mmpy;
}

int main()
{
    int choice;
    printf("Welcome to the Ultimate Electrochemistry Toolkit!\n\nEnter your choice:\n1. Calculate the EMF of a Galvanic cell\n2. Calculate EMF of a concentration cell\n3. Calculate Corrosion Penetration Rate(CPR) of a Metal\n4. Exit the menu\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
    double standardEMF, concentrationAnode, concentrationCathode;
    int electronsTransferred;
    
    // Input
    printf("Enter the standard EMF of the cell: ");
    scanf("%lf", &standardEMF);
    printf("Enter the concentration of the anode: ");
    scanf("%lf", &concentrationAnode);
    printf("Enter the concentration of the cathode: ");
    scanf("%lf", &concentrationCathode);
    printf("Enter the number of electrons transferred: ");
    scanf("%d", &electronsTransferred);
    
    // Calculate EMF
    double emf = calculateEMF(standardEMF, concentrationAnode, concentrationCathode, electronsTransferred);
    printf("The EMF of the cell is: %.4lf volts\n", emf);
    
    // Calculate and display free energy change
    char choice1;
    printf("Do you want to calculate the free energy change? (y/n): ");
    scanf(" %c", &choice1);
    
    if (choice1 == 'y' || choice1 == 'Y') {
        double freeEnergyChange = calculateFreeEnergyChange(emf, electronsTransferred);
        printf("The free energy change of the cell is: %.4lf Joules/mol\n", freeEnergyChange);
    }
        break;
    
    case 2:
    double conc1, conc2, n, T;

    printf("Enter concentration of species in anode (mol/L) or M: ");
    scanf("%lf", &conc1);

    printf("Enter concentration of species in cathode (mol/L) or M: ");
    scanf("%lf", &conc2);

    printf("Enter the number of electrons transferred (n): ");
    scanf("%lf", &n);

    // Calculate emf
    double emf_conc = calculateEMF_conc_cell(conc1, conc2, n);

    printf("Emf of the concentration cell: %.4lf volts\n", emf_conc);
        break;
    case 3: 
    double k, W, Time, A, D;

    // Prompt the user to enter the values
    printf("Enter the constant 'k': ");
    scanf("%lf", &k);

    printf("Enter the total weight lost (in milligrams): ");
    scanf("%lf", &W);

    printf("Enter the time taken for metal loss (in hours): ");
    scanf("%lf", &Time);

    printf("Enter the surface area of the exposed metal (in cm^2): ");
    scanf("%lf", &A);

    printf("Enter the metal density (in g/cm^3): ");
    scanf("%lf", &D);
    double CPR_mmpy = calculate_cpr(k,W,Time,A,D);
    double CPR_mpy = CPR_mmpy * 39.37;

    // Display the results
    printf("Corrosion Penetration Rate:\n");
    printf("In mmpy (millimeters per year): %.6lf mmpy\n", CPR_mmpy);
    printf("In mpy (mils per year): %.6lf mpy\n", CPR_mpy);
            break;
    case 4: printf("Thank you for using Electrochemical toolkit!");
        exit(0);
    default:printf("Invalid Input! Run the program again and try.");
        break;
    }
    return 0;
}

