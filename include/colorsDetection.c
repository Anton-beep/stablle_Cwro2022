int get_colorWash_left(int rawHT)
{
    if (rawHT > 1000){
        return 4;
    }
    else if (rawHT > 350){
        return 1;
    }
    else if (rawHT > -100){
        return 0;
    }
    else {
        return 5;
    }
}

int get_colorWash_right(int rawHT)
{
    if (rawHT > 3500){
        return 4;
    }
    else if (rawHT > 900){
        return 1;
    }
    else if (rawHT > 400){
        return 0;
    }
    else {
        return 5;
    }
}

int get_colorMarker_left(int rawHTRes)
{
    if (rawHTRes > 1500){
        return 6;
    }
    return 2;
}

int get_colorMarker_right(int rawHTRes)
{
    if (rawHTRes > 1500){
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

int angleFirstFrame = 210;
int angleSecondFrame = 180;
int angleThirdFrame = 150;
