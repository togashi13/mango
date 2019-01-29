 
#include <iostream>
using namespace std;

//Programmer: Zhengtao Cai
//Date: 1/26/2019
//Code for project 1 EECS 402
//Why is the user name before $ different every time
void printMenu();

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

int main(){
  double aCoeff;
  double bCoeff;
  double cCoeff;
  double dCoeff;
  double startX;
  double endX;
  int    numRects;
  int    resultVal;
  double approxErr;
  int    approxNumRects;
  int    yourChoice;
  double correctAns;
  double precision;
  do
  {
    yourChoice = 3;// if user input value that is not 1, 2, or 3, exit.
    printMenu();
    cin >> yourChoice;
    if (yourChoice == 1)
    {
      cout << "Enter (a b c d) for funtion y = a*x^3 + b*x^2 + c*x + d:" << endl;
//      cin >> aCoeff;
//      cin >> bCoeff;
//      cin >> cCoeff;
//      cin >> dCoeff;
      cin >> aCoeff >> bCoeff >> cCoeff >> dCoeff;      
      cout << "Now enter x start and end values: ";
//      cin >> startX;
//      cin >> endX;
      cin >> startX >> endX;
      cout << "Enter the number of rectangles to use: ";
      cin >> numRects;
      cout << "Rectangle result is: " <<  approximateAreaWithRect(aCoeff,
                                                                  bCoeff,
                                                                  cCoeff,
                                                                  dCoeff,
                                                                  startX,
                                                                  endX,
                                                                  numRects) << endl;

    }
    else if (yourChoice == 2)
    {
      cout << "Enter (a b c d) for funtion y = a*x^3 + b*x^2 + c*x + d:" << endl;
      cin >> aCoeff;
      cin >> bCoeff;
      cin >> cCoeff;
      cin >> dCoeff;
      cout << "Now enter x start and end values: ";
      cin >> startX;
      cin >> endX;
      cout << "Enter correct answer: ";
      cin >> correctAns;
      cout << "Enter precision to reach: ";
      cin >> precision;
      int i = 1; // loop initializtion
      do
      {
        if ( i <= 101)
        {
          approxErr =  approximateAreaWithRect( aCoeff,
                                                bCoeff,
                                                cCoeff,
                                                dCoeff,
                                                startX,
                                                endX,
                                                i) - correctAns;
          approxNumRects = i;
          i++;
        }
         else
        {
          cout << "Tried 100 rectangles without reaching precision" << endl;
          break;
        }
      }
      while (toThePower(approxErr,2) > toThePower(precision,2));
      if (approxNumRects <= 100)
      {
        cout << "Rectangles needed to reach precision: " << approxNumRects << endl;
      }	
    }
    else if (yourChoice == 3)
    {
      cout << "Thanks for using this program" << endl;
      return 0;
    }
    else
    {
      cout << "Invalid choice, please refer to menu" << endl;
    }
  }
  while (true);

}



#endif
void printMenu()
{
  cout << "1 Approximate Integral Using Rectangles" << endl;
  cout << "2 Experiment with Rectangle Precision" << endl;
  cout << "3 Quit The Program" << endl;
  cout << "Your Choice: " << endl;
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
  double xValue;
  for (int i = 0; i < numRects; i++)
  {
    xValue = startX + (i + 1/2) * rectWidth;
    if (evaluateCubicFormula(aCoeff, bCoeff, cCoeff, dCoeff,
			    xValue, rectHeight))
    {
      rectArea = rectWidth * rectHeight;
    }
    else
    {
      rectArea = rectWidth * rectHeight * (-1);
    }
    integral += rectArea;
  }
}


