float start(){
    #if TIMER == 1
        float start_time = getTimerValue(T2);
    #endif

    


    #if TIMER == 1
        return getTimerValue(T2) - start_time;
    #else
        return 0;
    #endif
}