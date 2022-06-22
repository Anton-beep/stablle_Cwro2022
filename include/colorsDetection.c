int get_colorWash_left(int rawHT)
{
    if (rawHT > 180){
        return 4;
    }
    else if (rawHT > 70){ //
        return 1;
    }
    else if (rawHT > 10){
        return 5;
    }
    else{
        return 0;
    }
}

int get_colorWash_right(int rawHT)
{
    if (rawHT > 180){ //
        return 4;
    }
    else if (rawHT > 100){
        return 1;
    }
    else if (rawHT > 10){
        return 5;
    }
    else{
        return 0;
    }
}

int get_colorMarker_left(int rawHTRes)
{
    if (rawHTRes > 2500){
        return 6;
    }
    return 2;
}

int get_colorMarker_right(int rawHTRes)
{
    if (rawHTRes > 2500){
        return 6;
    }
    return 2;
}

int get_colorFrame_first(int rawHTRes)
{
    if (rawHTRes > 75){
        return 4;
    }
    else if (rawHTRes > 40){
        return 1;
    }
    else{
        return 5;
    }
}

int get_colorFrame_second(int rawHTRes)
{
    if (rawHTRes > 200){
        return 4;
    }
    else if (rawHTRes > 55){
        return 1;
    }
    else{
        return 5;
    }
}
