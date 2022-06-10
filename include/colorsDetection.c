int get_colorWash_left(int rawHT)
{
    return 4;
    if (rawHT > 2000){
        return 4;
    }
    else if (rawHT > 700){
        return 1;
    }
    else if (rawHT > 0){
        return 0;
    }
    else {
        return 5;
    }
}

int get_colorWash_right(int rawHT)
{
    return 5;
    if (rawHT > 1000){
        return 4;
    }
    else if (rawHT > 700){
        return 1;
    }
    else if (rawHT > -100){
        return 0;
    }
    else {
        return 5;
    }
}

int get_colorMarker_left(int rawHTRes)
{
    return 2;
    if (rawHTRes > 500){
        return 6;
    }
    return 2;
}

int get_colorMarker_right(int rawHTRes)
{
    return 2;
    if (rawHTRes > 500){
        return 6;
    }
    return 2;
}

int get_colorFrame_first(int rawHTRes)
{
    if (rawHTRes > 12000){
        return 4;
    }
    else if (rawHTRes > 3200){
        return 1;
    }
    else{
        return 5;
    }
}

int get_colorFrame_second(int rawHTRes)
{
    if (rawHTRes > 12000){
        return 4;
    }
    else if (rawHTRes > 2500){
        return 1;
    }
    else{
        return 5;
    }
}

int get_thirdFrame_noReading(int frame1, int frame2)
{
    return 10 - frame1 - frame2;
}

int angleFirstFrame = 212;
int angleSecondFrame = 180;
int angleThirdFrame = 149;

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
