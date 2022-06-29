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
    else if (rawHTRes > 10){
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
    if (rawHTRes > 160){
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
    if (rawHTRes > 160){
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

short get_indicator_extended_color_left(int rawHTRes, short *rgbRes){
    if (rawHTRes < 6){
        return 0;
    }

    short max = 0;

    if (rgbRes[0] >= rgbRes[1] && rgbRes[0] >= rgbRes[2]) {
        max = rgbRes[0];
    }

    if (rgbRes[1] >= rgbRes[0] && rgbRes[1] >= rgbRes[2]) {
        max = rgbRes[1];
    }

    if (rgbRes[2] >= rgbRes[0] && rgbRes[2] >= rgbRes[1]) {
        max = rgbRes[2];
    }

    short min = 0;

    if (rgbRes[0] <= rgbRes[1] && rgbRes[0] <= rgbRes[2]) {
        min = rgbRes[0];
    }

    if (rgbRes[1] <= rgbRes[0] && rgbRes[1] <= rgbRes[2]) {
        min = rgbRes[1];
    }

    if (rgbRes[2] <= rgbRes[0] && rgbRes[2] <= rgbRes[1]) {
        min = rgbRes[2];
    }

    if ((rawHTRes > 7 && rawHTRes <= 22) && (max - min <= 2)){
        return 5;
    }
    
    if (rawHTRes > 39){
       if (rgbRes[2] > 15){
        return 6;
       }
       else{
        return 4;
       }
    }

    if (rgbRes[0] > rgbRes[1] && rgbRes[0] > rgbRes[2]){
        return 1;
    }
    if (rgbRes[1] >= rgbRes[0] && rgbRes[1] >= rgbRes[2]){
        return 2;
    }
    if (rgbRes[2] > rgbRes[0] && rgbRes[2] > rgbRes[0]){
        return 3;
    }
    return -1;
}

short get_indicator_extended_color_right(int rawHTRes, short *rgbRes){
    if (rawHTRes < 6){
        return 0;
    }

    if (rawHTRes > 7 && rawHTRes <= 21){
        return 5;
    }
    
    if (rawHTRes > 39){
       if (rgbRes[2] > 15){
        return 6;
       }
       else{
        return 4;
       }
    }

    if (rgbRes[0] > rgbRes[1] && rgbRes[0] > rgbRes[2]){
        return 1;
    }
    if (rgbRes[1] >= rgbRes[0] && rgbRes[1] >= rgbRes[2]){
        return 2;
    }
    if (rgbRes[2] > rgbRes[0] && rgbRes[2] > rgbRes[0]){
        return 3;
    }
    return -1;
}
