int get_colorWash_left(int rawHT)
{
}

int get_colorWash_right(int rawHT)
{
}

int get_colorMarker_left(int rawHTRes)
{
}

int get_colorMarker_right(int rawHTRes)
{
}

int get_colorFrame_first(int rawHT)
{
}

int get_colorFrame_second(int rawHT)
{
}

int get_thirdFrame_noReading(int frame1, int frame2)
{
    return 10 - frame1 - frame2;
}

int angleFirstFrame = 205;
int angleSecondFrame = 180;
int angleThirdFrame = 155;

int findAngleFrameForCube(int cubeCol)
{
    if (cubeCol == global_frames_first)
    {
        return angleFirstFrame;
    }
    else if (cubeCol == global_frames_second)
    {
        return angleSecondFrame;
    }
    else
    {
        return angleThirdFrame;
    }
}
