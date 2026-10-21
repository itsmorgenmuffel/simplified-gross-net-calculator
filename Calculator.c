//----------------------------------------------------------------------------------------------------------------------
/// Simplified Gross-Net Calculator
/// Description: Calculates the social security contribution (SV),
///              the income tax (LSt), and the resulting net salary
///              based on a given gross salary.
///              Net Salary = Gross Salary - SV -LSt
/// Author: Levani Samkharadze
//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USER_PROMPT " > "
#define INVALID_INPUT_MESSAGE "Invalid input!\n"
#define FIRST_TAX_BRACKETS 0
#define SECOND_TAX_BRACKETS 20
#define THIRD_TAX_BRACKETS 30
#define FOURTH_TAX_BRACKETS 40
#define FIFTH_TAX_BRACKETS 50

const double PERCENT_DIVISOR = 100;

// forward declarations
double grossSalary(void);
double socialSecurityContribution(double grossSalary);
int children(void);
double incomeTax(double grossSalary, double socialSecurityContribution, int hasChildren);


/// @brief the main Program
///        calls all function and  at the end prints result. 
/// @param  
/// @return 0 whenn everything successfully
int main(void)
{
  double income = grossSalary();
  double sv = socialSecurityContribution(income);
  int hasChildren = children();

  double tax = incomeTax(income, sv, hasChildren);
///calculete net salary 
  double netSalary = income - sv - tax;

  printf("Gross:\t\t%12.2f\n", income);
  if (sv > 0)
  {
    printf("SV:\t\t%14.2f\n", -sv);
  }
  else
  printf("SV:\t\t%14.2f\n", sv);
  printf("LSt:\t\t%14.2f\n", -tax);
  printf("Net:\t\t%14.2f\n", netSalary);
  
  return 0;
}


///Functions 

/// @brief asks the user to enter the gross Salary and checks
///        if the input is valid
/// @param  no parameters
/// @return  the valid gross salary as a double value
double grossSalary (void)
{
  char userInput[100];
  while(1)
  {
    printf("Your monthly gross income: \n");
    printf("%s", USER_PROMPT);

    if (fgets(userInput, 100, stdin) == NULL)
    {
      printf("%s", INVALID_INPUT_MESSAGE);
      continue;
    }
    if (userInput[0] == '\n')
    {
      printf("%s", INVALID_INPUT_MESSAGE);
      continue;
    }
    char *endptr;
    long income = strtol(userInput, &endptr, 10);

    if (endptr == userInput)
    {
      printf("%s", INVALID_INPUT_MESSAGE);
      continue;    
    }
    if (*endptr != '\n')
    {
      printf("%s", INVALID_INPUT_MESSAGE);
      continue;
    }
    if(income < 0 || income > 5000000)
    {
      printf("%s", INVALID_INPUT_MESSAGE);
      continue;
    }
    else
    {
      return (double)income;
    }
  }
}

/// @brief calculetes the Social security contribution based on the gross salary.
///        for the calculete, i am using the appropriate rate based on the gross salary.
/// @param grossSalary 
/// @return returns social security contribution result
double socialSecurityContribution (double grossSalary)
{
  double rate = 0;
  double basis = grossSalary;

  if (basis <= 460) 
  {
    rate = 0;
  }
  else if (basis <= 1733)
  {
    rate = 15;
  }
  else if (basis <= 1891)
  {
    rate = 16;
  }
  else if (basis <= 2049)
  {
    rate = 17;
  }
  else if (basis <= 5370)
  {
    rate = 18;
  }
  else if (basis >=5770)
  {
    rate = 18;
  }
  double socialSecurityContribution = basis * rate / PERCENT_DIVISOR;
  return socialSecurityContribution;
}

/// @brief asks the user if there are children in household
/// @param  
/// @return 1 if yes, 0 if no
int children(void)
{
  char answer[100];
  while (1)
  {
    printf("Children in household?: \n");
    printf("%s", USER_PROMPT);
    fgets(answer, 100, stdin);
    if (strchr(answer, '\n') == NULL)
    {
      int c;
      while ((c = getchar()) != '\n' && c != EOF);
      printf("%s", INVALID_INPUT_MESSAGE);
      continue;
    }
    else if (answer[0] == '\n')
    {
      printf("%s", INVALID_INPUT_MESSAGE);
      continue;
    }
    if (answer[1] != '\n')
    {
      printf("%s", INVALID_INPUT_MESSAGE);
      continue;
    }
    if (answer[0] == 'y' || answer[0] == 'Y')
    {
      return 1;
    }
    else if (answer[0] == 'n' || answer[0] == 'N')
    {
      return 0;
    }
    printf("%s", INVALID_INPUT_MESSAGE);
  }
}
/// @brief calculetes the income tax based on the  gross salarz and tax  brackets
/// @param grossSalary  theusers gross salary
/// @param socialSecurityContribution the calculeted social security
/// @param hasChildren indiciates if the user has childre, to calculete right
/// @return  calculeted income Tax
double incomeTax(double grossSalary, double socialSecurityContribution, int hasChildren)
{
  double basis = grossSalary - socialSecurityContribution;
  double incomeTax = 0;
  double remaining = basis;
  if (basis <= 1000 && basis >= 0)
  {
    remaining = 0;
  } 
  else if (remaining > 1000)
  {
    remaining-= 1000;
  }
  if (remaining >= 500 && remaining >= 0 )
  {
    incomeTax += 500 * SECOND_TAX_BRACKETS / PERCENT_DIVISOR;
    remaining -= 500;
  }
  else 
  {
    incomeTax += remaining * SECOND_TAX_BRACKETS / PERCENT_DIVISOR;
    remaining = 0;
  }
  if (remaining >= 1000)
  {
    incomeTax += 1000 * THIRD_TAX_BRACKETS / PERCENT_DIVISOR;
    remaining -= 1000;
  }
  else 
  {
    incomeTax += remaining * THIRD_TAX_BRACKETS / PERCENT_DIVISOR;
    remaining = 0;
  }
  if (remaining >= 2500)
  {
    incomeTax += 2500 * FOURTH_TAX_BRACKETS /PERCENT_DIVISOR;
    remaining -= 2500;
  }
  else 
  {
    incomeTax += remaining * FOURTH_TAX_BRACKETS / PERCENT_DIVISOR;
    remaining = 0;
  }
  if (remaining >= 5000)
  {
    incomeTax += 5000 * FIFTH_TAX_BRACKETS / PERCENT_DIVISOR;
    remaining -= 5000;
    }
  else 
  {
    incomeTax += remaining * FIFTH_TAX_BRACKETS / PERCENT_DIVISOR; 
    remaining = 0;
  }
  if (hasChildren == 1)
{
  if(incomeTax >= 100)
     incomeTax -= 100;
  else
     incomeTax = 0;
  }
  return incomeTax;
}

