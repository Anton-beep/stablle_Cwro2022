// The name of the file that we're saving data to
/*void my_itoa(long i, char *result)
{
	int power = 0, j = 0;

	j = i;
	for (power = 1; j>10; j /= 10)
		power *= 10;

	for (; power>0; power /= 10)
	{
		*result++ = '0' + i / power;
		i %= power;
	}
	*result = '\0';
}

short counter(long number){
	short count;
	while (number){
		number /= 10;
		count++;
	}
	return count;
}

void writeIndicators(long leftValue, long rightValue){
  char * filename = "Indicators";

  char * left  = "Left Indicator:";
  int strlen1 = strlen(left);
  char * right = "Right Indicator:";
  int strlen2 = strlen(right);

  long fileHandle = fileOpenWrite(filename);

  counter
	char leftResult[];

  fileWriteData(fileHandle, left,  strlen1 + 1);
  fileWriteData(fileHandle, my_itoa(leftValue), strlen(convert(leftValue)) + 1);

  fileWriteData(fileHandle, right, strlen2 + 1);
  fileWriteData(fileHandle, convert(rightValue), strlen(convert(rightValue)) + 1);

  fileClose(fileHandle);
}
*/
