int get_colorWash_left(int rawHT){
    if (rawHT > 125){ // 156 145
        return 4;
    }
    else if (rawHT > 55){ // 66 71 72
        return 1;
    }
    else if (rawHT > 15){ // 30 39 43
        return 5;
    }
    else{
        return 0;
    }
}

int get_colorWash_right(int rawHT){
    if (rawHT > 130){ // 160 177
        return 4;
    }
    else if (rawHT > 70){ // 84 87
        return 1;
    }
    else if (rawHT > 15){ // 57 59
        return 5;
    }
    else{
        return 0;
    }
}

int get_colorMarker_left(int rawHTRes){
    if (rawHTRes > 2000){
        return 6;
    }
    return 2;
}

int get_colorMarker_right(int rawHTRes){
    if (rawHTRes > 2000){
        return 6;
    }
    return 2;
}

int get_colorFrame_first(int rawHTRes){
    if (rawHTRes > 25){ // 32 36
        return 4;
    }
    else if (rawHTRes > 18){
        return 1;
    }
    else{
        return 5;
    }
}

int get_colorFrame_second(int rawHTRes){
    if (rawHTRes > 40){
        return 4;
    }
    else if (rawHTRes > 15){ // 26 19
        return 1;
    }
    else{
        return 5;
    }
}

short get_people_color(){
    if (ht_results[1] > 175){
        return 4;
    }
    else{
        if ((rgb[0] > rgb[1]) && (rgb[0] > rgb[2])){
            return 1;
        }
        if ((rgb[1] > rgb[0]) && (rgb[1] > rgb[2])){
            return 2;
        }
        if ((rgb[2] > rgb[0]) && (rgb[2] > rgb[1])){
            return 3;
        }
    }
    return 0;
}