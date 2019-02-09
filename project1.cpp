#include <iostream>
using namespace std;

//Programmer: Zhengtao Cai
//Date: 1/26/2019
//Code for project 1 EECS 402, allow users to approximate the area
//between the curve and x axis using rectangles, and get the number
//of rectangles to reach a required precision.

void printMenu();//print a menu of choices available for users to choose from

double toThePower(double val,
                  int    power);

bool evaluateCubicFormula(double aCoeff,
                          double bCoeff,
                          double cCoeff,
                          double dCoeff,
                          double xValue,
                          double &resultVal);

double approximateAreaWithRect(double aCoeff,
                               double bCoeff,
                               double cCoeff,
                               double dCoeff,
                               double startX,
                               double endX,
                               int    numRects);



#ifdef ANDREW_TEST
#include "andrewTest.h"
#else

int main()
{ 
  double aCoeff;
  double bCoeff;
  double cCoeff;
  double dCoeff;//coefficient of the cubic function
  double startX;
  double endX;  //the interval of to be approximated between
  int    numRects;
  double approxErr;
  int    approxNumRects;//rectangles needed for the required precision
  int    yourChoice;
  double correctAns;
  double precision;
  printMenu();
  cout << "YOUR CHOICE: ";
  cin >> yourChoice;
 // cout.setf(ios::fixed);
 // cout.setf(ios::showpoint);
 // cout.precision(6);
  while (yourChoice != 3)
  {
    if (yourChoice == 1)
    {
      cout << "Enter (a b c d) for funtion y = a*x^3 + b*x^2 + c*x + d: ";
      cin >> aCoeff >> bCoeff >> cCoeff >> dCoeff;      
      cout << "Now enter x start and end values: ";
      cin >> startX >> endX;
      cout << "Enter the number of rectangles to use: ";
      cin >> numRects;
      cout << "Rectangle result is: " <<
                 approximateAreaWithRect(aCoeff, bCoeff,
          cCoeff, dCoeff, startX, endX, numRects) << endl;
      // printMenu();
      // cout << "YOUR CHOICE: ";
      // cin >> yourChoice;
    }
    else if (yourChoice == 2)
    {
      cout << "Enter (a b c d) for funtion y = a*x^3 + b*x^2 + c*x + d: ";
      cin >> aCoeff >> bCoeff >> cCoeff >> dCoeff;
      cout << "Now enter x start and end values: ";
      cin >> startX >> endX;
      cout << "Enter correct answer: ";
      cin >> correctAns;
      cout << "Enter precision to reach: ";
      cin >> precision;
      int i = 1;
      do
      {
        approxErr =  approximateAreaWithRect(aCoeff, bCoeff, cCoeff, dCoeff,
        startX, endX, i) - correctAns;
        approxNumRects = i;
        i++;
      }
      while ((toThePower(approxErr,2) > toThePower(precision,2)) && (i <= 101));
      //allow 101 rectangles to determine if
      //100 rectangles were precise enough
      int numRectLimit = 100;//RESUBMISSION CODE UPDATE
      if (approxNumRects <= numRectLimit)
      {
        cout << "Rectangles needed to reach precision: "
                 << approxNumRects << endl;
      } 
      else
      {
        cout << "Tried 100 rectangles without reaching precision" << endl;
      }
      // printMenu();
      // cout << "YOUR CHOICE: ";
      // cin >> yourChoice;
    }
    else
    {
      cout << "Invalid choice, please refer to menu" << endl;
      // printMenu();
      // cout << "YOUR CHOICE: ";
      // cin >> yourChoice;
    }
    printMenu();//RESUBMISSION CODE UPDATE: move printMenu outside of if-else
    cout << "YOUR CHOICE: ";
    cin >> yourChoice;
  }
  cout << "Thanks for using this program" << endl;
  return 0;
}



#endif
void printMenu()
{
  cout << "1. Approximate Integral Using Rectangles" << endl;
  cout << "2. Experiment with Rectangle Precision" << endl;
  cout << "3. Quit The Program" << endl;
}

double toThePower(double val,
                  int    power)
{
  double powResult = 1;
  for (int i = 0; i < power; i++)
  {
    powResult *= val;

  }
  return powResult;
}

bool evaluateCubicFormula(double aCoeff,
                          double bCoeff,
                          double cCoeff,
                          double dCoeff,
                          double xValue,
                          double &resultVal)
{
  resultVal = aCoeff * toThePower(xValue,3) + bCoeff * toThePower(xValue,2) +
                cCoeff * xValue + dCoeff;
  return (resultVal >= 0);
}


double approximateAreaWithRect(double aCoeff,
                               double bCoeff,
                               double cCoeff,
                               double dCoeff,
                               double startX,
                               double endX,
                               int    numRects)
{
  double rectArea;
  double integral = 0;
  double rectWidth = (endX - startX)/numRects;
  double rectHeight = 0;
  double xValue;//x-coordinaties of the mid point of the rectangles
  for (int i = 0; i < numRects; i++)
  {
    xValue = startX + (i + 0.5) * rectWidth;
    if (evaluateCubicFormula(aCoeff, bCoeff, cCoeff, dCoeff,
          xValue, rectHeight))
    {
      rectArea = rectWidth * rectHeight;
    }
    else//add the positive value of the rectangle area when y is negative
    {
      rectArea = rectWidth * rectHeight * (-1);
    }
    integral += rectArea;
  }
  return integral;//RESUBMISSION CODE UPDATE
}

