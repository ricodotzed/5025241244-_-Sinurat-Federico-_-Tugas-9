#include <stdio.h>
#include <math.h>

#define INCREMENT 0.25

double calculateMonthlyPayment(double loanAmount, double annualRate, int years) {
    double monthlyRate = annualRate / 12.0 / 100.0;
    int totalMonths = years * 12;
    return (loanAmount * monthlyRate) / (1 - pow(1 + monthlyRate, -totalMonths));
}

int main() {
    double loanAmount, minRate, maxRate;
    FILE *outputFile;

    printf("Enter the loan amount: ");
    scanf("%lf", &loanAmount);
    printf("Enter the minimum interest rate (%%): ");
    scanf("%lf", &minRate);
    printf("Enter the maximum interest rate (%%): ");
    scanf("%lf", &maxRate);

    outputFile = fopen("Ch11No6_data.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }
    
    fprintf(outputFile, "Loan Amount: $%.2f\n", loanAmount);
    fprintf(outputFile, "Interest    Duration      Monthly      Total\n");
    fprintf(outputFile, "Rate        (years)       Payment      Payment\n");
    
    for (double rate = minRate; rate <= maxRate; rate += INCREMENT) {
        for (int years = 20; years <= 30; years += 5) {
            double monthlyPayment = calculateMonthlyPayment(loanAmount, rate, years);
            double totalPayment = monthlyPayment * years * 12;
            
            fprintf(outputFile, "%6.2f       %2d            %8.2f      %8.2f\n", 
                    rate, years, monthlyPayment, totalPayment);
        }
    }
    
    fclose(outputFile);
    
    printf("Mortgage table has been written to 'Ch11No6_data.txt'.\n");
    return 0;
}