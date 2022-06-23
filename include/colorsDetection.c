int get_colorWash_left(int rawHT){
    if (rawHT > 145){
        return 4;
    }
    else if (rawHT > 68){ //
        return 1;
    }
    else if (rawHT > 15){
        return 5;
    }
    else{
        return 0;
    }
}

int get_colorWash_right(int rawHT){
    if (rawHT > 145){ //
        return 4;
    }
    else if (rawHT > 68){
        return 1;
    }
    else if (rawHT > 15){
        return 5;
    }
    else{
        return 0;
    }
}

int get_colorMarker_left(int rawHTRes){
    if (rawHTRes > 3000){
        return 6;
    }
    return 2;
}

int get_colorMarker_right(int rawHTRes){
    if (rawHTRes > 3000){
        return 6;
    }
    return 2;
}

int get_colorFrame_first(int rawHTRes){
    if (rawHTRes > 55){
        return 4;
    }
    else if (rawHTRes > 15){
        return 1;
    }
    else{
        return 5;
    }
}

int get_colorFrame_second(int rawHTRes){
    if (rawHTRes > 25){
        return 4;
    }
    else if (rawHTRes > 15){
        return 1;
    }
    else{
        return 5;
    }
}