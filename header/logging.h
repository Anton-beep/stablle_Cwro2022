// The name of the file that we're saving data to
void writeIndicators(long leftValue, long rightValue){
  char * filename = "Indicators";

  char * left  = "Left Indicator:";
  int strlen1 = strlen(left);
  char * right = "Right Indicator:";
  int strlen2 = strlen(right);

  long fileHandle = fileOpenWrite(filename);

  fileWriteData(fileHandle, left,  strlen1 + 1);
  fileWriteLong(fileHandle, leftValue);

  fileWriteData(fileHandle, right, strlen2 + 1);
  fileWriteLong(fileHandle, rightValue);

  fileClose(fileHandle);
}
