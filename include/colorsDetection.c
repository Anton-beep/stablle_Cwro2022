int get_colorWash_left(int rawHT)
{
    if (rawHT > 10000){
        return 4;
    }
    else if (rawHT > 4900){
        return 1;
    }
    else if (rawHT > 2000){
        return 5;
    }
    else{
        return 0;
    }
}

int get_colorWash_right(int rawHT)
{
    if (rawHT > 8500){
        return 4;
    }
    else if (rawHT > 4900){
        return 1;
    }
    else if (rawHT > 900){
        return 5;
    }
    else{
        return 0;
    }
}

int get_colorMarker_left(int rawHTRes)
{
    if (rawHTRes > 1600){
        return 6;
    }
    return 2;
}

int get_colorMarker_right(int rawHTRes)
{
    if (rawHTRes > 1700){
        return 6;
    }
    return 2;
}

int get_colorFrame_first(int rawHTRes)
{
    //yellow 56917
    //red  30211
    //black 20935
    if (rawHTRes > 40000){
        return 4;
    }
    else if (rawHTRes > 28000){
        return 1;
    }
    else{
        return 5;
    }
}

int get_colorFrame_second(int rawHTRes)
{
    //yellow 50236
    //red 36518
    //black 13866 || 21802
    if (rawHTRes > 40000){
        return 4;
    }
    else if (rawHTRes > 28000){
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
