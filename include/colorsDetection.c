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

short get_wash_color_right(int rawHTRes){
    if (rawHTRes < 10){
        return 0;
    }
    if (rawHTRes > 128){
        return 4;
    }
    else{
		if ((rgb[0] < 35) && (rawHTRes > 10)){
			return 5;
		}
        if ((rgb[0] > rgb[1]) && (rgb[0] > rgb[2])){
            return 1;
        }
    }
    return 0;
}

short get_wash_color_left(int rawHTRes){
    if (rawHTRes < 10){
        return 0;
    }
    if (rawHTRes > 128){
        return 4;
    }
    else{
		if ((rgb[0] < 50) && (rawHTRes > 10)){
			return 5;
		}
        if ((rgb[0] > rgb[1]) && (rgb[0] > rgb[2])){
            return 1;
        }
    }
    return 0;
}