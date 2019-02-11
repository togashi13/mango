#include <iostream>
using namespace std;


//{}header

//Do we need to consider it being other type: setRow, setCol.

//I guess from the name of the function and variable, it should be 
//that we store the RGB value of the given location in outColor, 
//but in p2specs it says: "the output parameter "outColor" is assigned
//to the color of the image pixel at that location." 
//I'm not sure about the "be assigned to" phrase.



const int IMAGE_ROW = 10;
const int IMAGE_COL = 18;
int clipInt(
     int colToClip
     );

class ColorClass
{
   private:
      int red;//amount of each color
      int green;
      int blue;
      //additional member functions must be private
      //{}default ctor set to full white.
      bool clippixels(     
           int colorR,
           int colorG,
           int colorB
           );

   public:
      ColorClass();

      ColorClass(
           int inRed,
           int inGreen,
           int inBlue
           );
      //{}value ctor clipping: set to max and min 
      //  when out of range [0,1000].
      void setToBlack();//set to full colors.
      void setToRed();
      void setToGreen();
      void setToBlue();
      void setToWhite();

      bool setTo(
           int inRed,
           int inGreen,
           int inBlue
           );
      //{}clipping needed, return true if clipping 
      //  is necessary.

      bool setTo(
           ColorClass &inColor
           );
      //{}sets the color's component color values to 
      //  the same as those in the "inColor" input.

      bool addColor(
           ColorClass &rhs
           );
      //{}add RGB in rhs to this object, return if 
      //  clipping is necessary.


      bool subtractColor(
           ColorClass &rhs
           );
      //{}similar to addColor 


      bool adjustBrightness(
           double adjFactor
           );
      //{}brighter if adjFactor > 1, clipping --
      //  true. 
      //  Type cast the color values to int.

      void printComponentValues();
      //{}"R: <red> G: <green> B: <blue>", no newl.
};

ColorClass::ColorClass()
{
   setToWhite();
}

ColorClass::ColorClass(
                 int inRed,
                 int inGreen,
                 int inBlue
                 )
{
   setTo(inRed, inGreen, inBlue);
}

void ColorClass::setToBlack()
{
   setTo(0, 0, 0);
}

void ColorClass::setToRed()
{
   setTo(1000, 0, 0);
}

void ColorClass::setToGreen()
{
   setTo(0, 1000, 0);
}

void ColorClass::setToBlue()
{
   setTo(0, 0, 1000);
}

void ColorClass::setToWhite()
{
   setTo(1000, 1000, 1000);
}


bool ColorClass::setTo(
                 int inRed,
                 int inGreen,
                 int inBlue
                 )
{

   return clippixels(inRed, inGreen, inBlue);

}

bool ColorClass::setTo(
                 ColorClass &inColor
                 )
{

   return clippixels(inColor.red, inColor.green, inColor.blue);

}

bool ColorClass::addColor(
     ColorClass &rhs) 
{
   return clippixels(red + rhs.red, green + rhs.green, 
      blue + rhs.blue);
}

bool ColorClass::subtractColor(
     ColorClass &rhs
     )
{
   return clippixels(red - rhs.red, green - rhs.green,
    blue - rhs.blue);

}

bool ColorClass::adjustBrightness(
     double adjFactor
     )
{
  return clippixels(int(red * adjFactor), int(green * adjFactor), 
   int(blue * adjFactor));
}

void ColorClass::printComponentValues()
{
   cout << "R: " << red << " G: " << green << " B: " << blue;
}

bool ColorClass::clippixels(
     int inRed,
     int inGreen,
     int inBlue
     )
{
   red = clipInt(inRed);
   green = clipInt(inGreen);
   blue = clipInt(inBlue);

   if ((red == inRed) && (green == inGreen) && (blue == inBlue))
   {
      return false;
   }else{
      return true;
   }
}

class RowColumnClass
{
   private:
      int row;
      int col;

   public:
      RowColumnClass();
      //{}default ctor sets both r and c to -99999.

      RowColumnClass(
           int inRow,
           int inCol
           );

      //value ctor

      void setRowCol(
           int inRow,
           int inCol
           );

      void setRow(
           int inRow
           );


      void setCol(
           int inCol
           );

      //simple setters

      int getRow();
      int getCol();

      // simple getters

      void addRowColTo(
           RowColumnClass &inRowCol
           );

      void printRowCol(
           );

      //{}"[<row>,<col>]" no newl.

};

RowColumnClass::RowColumnClass(): row(-99999), col(-99999)
{;}

RowColumnClass::RowColumnClass(
                     int inRow,
                     int inCol
                     ): row(inRow), col(inCol)
{;}

void RowColumnClass::setRowCol(
                     int inRow,
                     int inCol
                     )
{
   row = inRow;
   col = inCol;
}

void RowColumnClass::setRow(
                     int inRow
                     )
{
   row = inRow;
}

void RowColumnClass::setCol(
                     int inCol
                     )
{
   col = inCol;
}


int RowColumnClass::getRow()
{
   return row;
}

int RowColumnClass::getCol()
{
   return col;
}

void RowColumnClass::addRowColTo(
                     RowColumnClass &inRowCol
                     )
{
   row += inRowCol.row;
   col += inRowCol.col;
}



void RowColumnClass::printRowCol()
{
   cout << "[" << row << "," << col << "]";
}

class ColorImageClass
{
private:

   ColorClass pixels [IMAGE_ROW][IMAGE_COL];
   
   //10 rows x 18 cols, but the size of the 
   //image can be changed easily.
public:
   ColorImageClass();
   // default ctor set to full black

   void initializeTo(
        ColorClass &inColor
        );
   //initialize all image pixels to the color 
   //provided.

   bool addImageTo(
        ColorImageClass &rhsImg
        );
   //{}pixels-wise addition, right hand side 
   //  input image added to it.
   //  clipping -- true.

   bool addImages(
        int numImagesToAdd,
        ColorImageClass imagesToAdd []
        );
   //{}sum each image in the imagesToAdd input
   //  parameter and assign to current image.
   //  clipping -- true

   bool setColorAtLocation(
        RowColumnClass &inRowCol,
        ColorClass &inColor
        );
   //{}if the specified location is valid, the
   //  the value is changed to inColor parameter,
   //  and returns true. Otherwise nothing is 
   //  modified and returns false.

   bool getColorAtLocation(
        RowColumnClass &inRowCol,
        ColorClass &outColor
        );
   //{}if row/col provided is valid, returns
   //  true and outColor = color at the loaction
   //  otherwise -- false, outColor is not modified.

   void printImage();
   //{}each pixels is printed using ColorClass format.
   //  newl after the last pixels of each row.
   //  -- between each pixels.


};

ColorImageClass::ColorImageClass()
{
   for (int i = 0; i < IMAGE_ROW; ++i)
   {
      for (int j = 0; j < IMAGE_COL; ++j)
      {
         pixels[i][j].setToBlack();
      }
   }
}

void ColorImageClass::initializeTo(
                      ColorClass &inColor
                      )
{
      for (int i = 0; i < IMAGE_ROW; ++i)
   {
      for (int j = 0; j < IMAGE_COL; ++j)
      {
         pixels[i][j].setTo(inColor);
      }
   }
}

bool ColorImageClass::addImageTo(
                      ColorImageClass &rhsImg
                      )
{
   int numPixClipped = 0;
   for (int i = 0; i < IMAGE_ROW; ++i)
   {
      for (int j = 0; j < IMAGE_COL; ++j)
      {
         if (pixels[i][j].addColor(rhsImg.pixels[i][j]))
         {
            numPixClipped++;
         }
      }
   }  
   return (numPixClipped > 0);
}

bool ColorImageClass::addImages(
                      int numImagesToAdd,
                      ColorImageClass imagesToAdd []
                      )
{
   int numClip = 0;
   for (int i = 0; i < IMAGE_ROW; ++i)
   {
      for (int j = 0; j < IMAGE_COL; ++j)
      {
         pixels[i][j].setToBlack();
      }
   }
   for (int i = 0; i < IMAGE_ROW; ++i)
   {
      for (int j = 0; j < IMAGE_COL; ++j)
      {
         for (int imageIndex = 0; imageIndex < numImagesToAdd; ++imageIndex)
         {
            if (pixels[i][j].addColor(imagesToAdd[imageIndex].pixels[i][j]))
            {
               numClip ++;
            } 
         }
      }
   }
   return (numClip > 0);
}

bool ColorImageClass::setColorAtLocation(
                      RowColumnClass &inRowCol,
                      ColorClass &inColor
                      )
{
   int setRow = inRowCol.getRow();
   int setCol = inRowCol.getCol();
   if ((setRow < IMAGE_ROW) && (setRow >= 0) && 
         (setCol < IMAGE_COL) && (setCol >= 0))
   {
      pixels[setRow][setCol].setTo(inColor);
      return true;
   }else{
      return false;
   }
}

bool ColorImageClass::getColorAtLocation(
                      RowColumnClass &inRowCol,
                      ColorClass &outColor
                      )
{
   int setRow = inRowCol.getRow();
   int setCol = inRowCol.getCol();
   if ((setRow < IMAGE_ROW) && (setRow >= 0) && 
         (setCol < IMAGE_COL) && (setCol >= 0))
   {
      outColor.setTo(pixels[setRow][setCol]);
      return true;
   }else{
      return false;
   }  
}

void ColorImageClass::printImage()
{
   for (int i = 0; i < IMAGE_ROW; ++i)
   {
      for (int j = 0; j < IMAGE_COL; ++j)
      {

         if (j ==  17)
         {
            pixels[i][j].printComponentValues();
            cout << endl;
         }else{
            pixels[i][j].printComponentValues();
            cout << "--";
         }
      }
   }
}
// int main()
// {
  // ColorClass testColor;
  // // RowColumnClass testRowCol;
  // RowColumnClass testRowColOther(9, 17);
  // ColorImageClass testImage;
  // ColorImageClass testImages[3];


  // // // //Test some basic ColorClass operations...
  // // cout << "Initial: ";
  // // testColor.printComponentValues();
  // // cout << endl;

  // // testColor.setToBlack();
  // // cout << "Black: ";
  // // testColor.printComponentValues();
  // // cout << endl;

  // // testColor.setToGreen();
  // // cout << "Green: ";
  // // testColor.printComponentValues();
  // // cout << endl;
  // // testColor.adjustBrightness(0.5559);
  // // cout << "Dimmer Green: ";
  // // testColor.printComponentValues();
  // // cout << endl;
  // // testColor.setTo(110, 200, 30300);
  // // cout << "random: ";
  // // testColor.printComponentValues();
  // // cout << endl;

  // // cout << testColor.setTo(100,200,300) << endl;
  // // cout << testColor.setTo(1,0,10000) << endl;
  // // cout << testColor.setTo(-1, 0 , 1) << endl;
 

  // // ColorClass ok(100, 200, 300);
  // // cout << "ok: ";
  // // ok.printComponentValues();
  // // cout << endl;
  // // ok.setTo(testColor);
  // // ok.printComponentValues();
  // // cout << endl;
  // // cout << "testColor: ";
  // // testColor.setToGreen();
  // // testColor.printComponentValues();
  // // cout << endl;
  // // cout << "ok + testColor: " << ok.addColor(testColor);
  // // ok.printComponentValues();
  // // cout << endl;




  // // //Test some basic RowColumnClass operations...
  // // cout << "Want defaults: ";
  // // testRowCol.printRowCol();
  // // cout << endl;
  
  // // testRowCol.setRowCol(2, 8);
  // // cout << "Want 2,8: ";
  // // testRowCol.printRowCol();
  // // cout << endl;

  // // cout << "Want 111, 222: ";
  // // testRowColOther.printRowCol();
  // // cout << endl;

  // // testRowColOther.setRowCol(4, 2);
  // // testRowCol.addRowColTo(testRowColOther);
  // // cout << "Want 6,10: ";
  // // testRowCol.printRowCol();
  // // cout << endl;

  // // //Test some basic ColorImageClass operations...
  // //testImage.printImage();
  // // testColor.setToRed();
  // // testImage.initializeTo(testColor);
  // // testImage.printImage();
  // // testImage.addImageTo(testImage);
  // // testImage.printImage();

  // // testRowCol.setRowCol(555, 5);
  // // cout << "Want: Color at [555,5]: Invalid Index!" << endl;
  // // cout << "Color at ";
  // // testRowCol.printRowCol();
  // // cout << ": ";
  // // if (testImage.getColorAtLocation(testRowCol, testColor))
  // // {
  // //   testColor.printComponentValues();
  // // }
  // // else
  // // {
  // //   cout << "Invalid Index!";
  // // }
  // // cout << endl;

  // // testRowCol.setRow(4);
  // // cout << "Want: Color at [4,5]: R: 1000 G: 0 B: 0" << endl;
  // // cout << "Color at ";
  // // testRowCol.printRowCol();
  // // cout << ": ";
  // // if (testImage.getColorAtLocation(testRowCol, testColor))
  // // {
  // //   testColor.printComponentValues();
  // // }
  // // else
  // // {
  // //   cout << "Invalid Index!";
  // // }
  // // cout << endl;

  // //Set up an array of images of different colors
  // testColor.setToRed();
  // testColor.adjustBrightness(0.15);
  // testImages[0].initializeTo(testColor);
  // // testImages[0].printImage();
  // testColor.setToBlue();
  // testColor.adjustBrightness(0.5);
  // testImages[1].initializeTo(testColor);
  // // testImages[1].printImage();
  // testColor.setToGreen();
  // testImages[2].initializeTo(testColor);
  // // testImages[2].printImage();
  // // //Modify a few individual pixels colors
  // // testRowCol.setRowCol(4, 2);
  // // testColor.setToWhite();
  // // testImages[1].setColorAtLocation(testRowCol, testColor);

  // // testRowCol.setRowCol(2, 4);
  // // testColor.setToBlack();
  // // testImages[2].setColorAtLocation(testRowCol, testColor);

  // // //Add up all images in testImages array and assign result
  // //to the testImage image
  // // testImage.printImage();
  // testImage.addImages(3, testImages);
  // testImage.setColorAtLocation(testRowColOther, testColor);
  // testImage.printImage();
  // cout <<   testImage.setColorAtLocation(testRowColOther, testColor);



  // // //Check some certain values
  // // cout << "Added values:" << endl;
  // // for (int colInd = 0; colInd < 8; colInd += 2)
  // // {
  // //   testRowCol.setRowCol(4, colInd);
  // //   cout << "Color at ";
  // //   testRowCol.printRowCol();
  // //   cout << ": ";
  // //   if (testImage.getColorAtLocation(testRowCol, testColor))
  // //   {
  // //     testColor.printComponentValues();
  // //   }
  // //   else
  // //   {
  // //     cout << "Invalid Index!";
  // //   }
  // //   cout << endl;
  // // }
  
  // // for (int rowInd = 0; rowInd < 8; rowInd += 2)
  // // {
  // //   testRowCol.setRowCol(rowInd, 4);
  // //   cout << "Color at ";
  // //   testRowCol.printRowCol();
  // //   cout << ": ";
  // //   if (testImage.getColorAtLocation(testRowCol, testColor))
  // //   {
  // //     testColor.printComponentValues();
  // //   }
  // //   else
  // //   {
  // //     cout << "Invalid Index!";
  // //   }
  // //   cout << endl;
  // // }
  
  // // cout << "Printing entire test image:" << endl;
  // // testImage.printImage();

//   return 0;
// }

int main()
{
  // ColorClass testColor;
  // RowColumnClass testRowCol;
  // RowColumnClass testRowColOther(111, 222);
  // ColorImageClass testImage;
  // ColorImageClass testImages[3];

  // //Test some basic ColorClass operations...
  // cout << "Initial: ";
  // testColor.printComponentValues();
  // cout << endl;

  // testColor.setToBlack();
  // cout << "Black: ";
  // testColor.printComponentValues();
  // cout << endl;

  // testColor.setToGreen();
  // cout << "Green: ";
  // testColor.printComponentValues();
  // cout << endl;

  // testColor.adjustBrightness(0.5);
  // cout << "Dimmer Green: ";
  // testColor.printComponentValues();
  // cout << endl;

  // //Test some basic RowColumnClass operations...
  // cout << "Want defaults: ";
  // testRowCol.printRowCol();
  // cout << endl;

  // testRowCol.setRowCol(2, 8);
  // cout << "Want 2,8: ";
  // testRowCol.printRowCol();
  // cout << endl;

  // cout << "Want 111, 222: ";
  // testRowColOther.printRowCol();
  // cout << endl;

  // testRowColOther.setRowCol(4, 2);
  // testRowCol.addRowColTo(testRowColOther);
  // cout << "Want 6,10: ";
  // testRowCol.printRowCol();
  // cout << endl;

  // //Test some basic ColorImageClass operations...
  // testColor.setToRed();
  // testImage.initializeTo(testColor);

  // testRowCol.setRowCol(555, 5);
  // cout << "Want: Color at [555,5]: Invalid Index!" << endl;
  // cout << "Color at ";
  // testRowCol.printRowCol();
  // cout << ": ";
  // if (testImage.getColorAtLocation(testRowCol, testColor))
  // {
  //   testColor.printComponentValues();
  // }
  // else
  // {
  //   cout << "Invalid Index!";
  // }
  // cout << endl;

  // testRowCol.setRow(4);
  // cout << "Want: Color at [4,5]: R: 1000 G: 0 B: 0" << endl;
  // cout << "Color at ";
  // testRowCol.printRowCol();
  // cout << ": ";
  // if (testImage.getColorAtLocation(testRowCol, testColor))
  // {
  //   testColor.printComponentValues();
  // }
  // else
  // {
  //   cout << "Invalid Index!";
  // }
  // cout << endl;

  // //Set up an array of images of different colors
  // testColor.setToRed();
  // testColor.adjustBrightness(0.25);
  // testImages[0].initializeTo(testColor);
  // testColor.setToBlue();
  // testColor.adjustBrightness(0.75);
  // testImages[1].initializeTo(testColor);
  // testColor.setToGreen();
  // testImages[2].initializeTo(testColor);

  // //Modify a few individual pixel colors
  // testRowCol.setRowCol(4, 2);
  // testColor.setToWhite();
  // testImages[1].setColorAtLocation(testRowCol, testColor);

  // testRowCol.setRowCol(2, 4);
  // testColor.setToBlack();
  // testImages[2].setColorAtLocation(testRowCol, testColor);

  // //Add up all images in testImages array and assign result
  // //to the testImage image
  // testImage.addImages(3, testImages);
  
  // //Check some certain values
  // cout << "Added values:" << endl;
  // for (int colInd = 0; colInd < 8; colInd += 2)
  // {
  //   testRowCol.setRowCol(4, colInd);
  //   cout << "Color at ";
  //   testRowCol.printRowCol();
  //   cout << ": ";
  //   if (testImage.getColorAtLocation(testRowCol, testColor))
  //   {
  //     testColor.printComponentValues();
  //   }
  //   else
  //   {
  //     cout << "Invalid Index!";
  //   }
  //   cout << endl;
  // }
  
  // for (int rowInd = 0; rowInd < 8; rowInd += 2)
  // {
  //   testRowCol.setRowCol(rowInd, 4);
  //   cout << "Color at ";
  //   testRowCol.printRowCol();
  //   cout << ": ";
  //   if (testImage.getColorAtLocation(testRowCol, testColor))
  //   {
  //     testColor.printComponentValues();
  //   }
  //   else
  //   {
  //     cout << "Invalid Index!";
  //   }
  //   cout << endl;
  // }
  
  // cout << "Printing entire test image:" << endl;
  // testImage.printImage();

  return 0;
}



int clipInt(int colToClip)
{
   if (colToClip < 0)
   {
      return 0;
   }else if (colToClip > 1000){
      return 1000;
   }else{
      return colToClip;
   }
   
}




