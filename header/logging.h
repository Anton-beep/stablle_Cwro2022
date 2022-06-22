#if LOGGING == 1
  char * filename = "Logs.txt";
  char * end = "\n";

  long fileHandle = fileOpenWrite(filename);


  void writeIndicators(long leftValue, long rightValue){

    char * left  = " Left Indicator:";
    int strlen1 = strlen(left);
    char * right = "          ------          Right Indicator:";
    int strlen2 = strlen(right);

    char  leftResult[10];
    char rightResult[10];

    sprintf(leftResult, "%f", leftValue);
    sprintf(rightResult, "%f", rightValue);

    fileWriteData(fileHandle, left,  strlen1 + 1);
    fileWriteData(fileHandle, leftResult, strlen(leftResult) + 1);

    fileWriteData(fileHandle, right, strlen2 + 1);
    fileWriteData(fileHandle, rightResult, strlen(rightResult) + 1);
    fileWriteData(fileHandle, end, strlen(end) + 1);
  }

  void writeRightRoomInfo(long rawValue, long colorValue){

    char * raw  = "Raw info:";
    char * color ="          ------          Right Cube:";

    char    rawResult[10];
    char  colorResult[10];

    sprintf(rawResult,   "%f", rawValue);
    sprintf(colorResult, "%d", colorValue);

    fileWriteData(fileHandle, raw,  strlen(raw) + 1);
    fileWriteData(fileHandle, rawResult, strlen(rawResult) + 1);

    fileWriteData(fileHandle, color, strlen(color) + 1);
    fileWriteData(fileHandle, colorResult, strlen(colorResult) + 1);
    fileWriteData(fileHandle, end, strlen(end) + 1);
  }

  void writeLeftRoomInfo(long rawValue, long colorValue){

    char * raw  = "Raw info:";
    char * color ="          ------          Left Cube:";

    char    rawResult[10];
    char  colorResult[10];

    sprintf(rawResult,   "%f", rawValue);
    sprintf(colorResult, "%d", colorValue);

    fileWriteData(fileHandle, raw,  strlen(raw) + 1);
    fileWriteData(fileHandle, rawResult, strlen(rawResult) + 1);

    fileWriteData(fileHandle, color, strlen(color) + 1);
    fileWriteData(fileHandle, colorResult, strlen(colorResult) + 1);
    fileWriteData(fileHandle, end, strlen(end) + 1);
  }

  void writeFramesInfo(long *rawValues, long *colorValues){
    for (short g = 0; g < 3; g++){
      char * frame = "Frame number:";
      char * raw   = "Raw info:";
      char * color = "          ------          Frame Color:";

      char    rawResult[10];
      char  colorResult[10];
      char        number[1];

      sprintf(rawResult,   "%f", rawValues[g]);
      sprintf(colorResult, "%d", colorValues[g]);
      sprintf(number, "%d", g + 1);

      fileWriteData(fileHandle, frame,  strlen(frame) + 1);
      fileWriteData(fileHandle, number, strlen(number) + 1);

      fileWriteData(fileHandle, raw, strlen(raw) + 1);
      fileWriteData(fileHandle, rawResult, strlen(rawResult) + 1);


      fileWriteData(fileHandle, color, strlen(color) + 1);
      fileWriteData(fileHandle, colorResult, strlen(colorResult) + 1);

      fileWriteData(fileHandle, end, strlen(end) + 1);
    }
  }
#endif
