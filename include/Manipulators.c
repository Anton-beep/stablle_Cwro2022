byte taskFlag_setNormAfterWaterFullDown = 0;
byte taskFlag_motorWaterFullDown = 0;

task setNormAfterWaterFullDown(){
    taskFlag_setNormAfterWaterFullDown = 1;
    moveMotor(centMotor, 220, 30, 1);
    resetMotorEncoder(centMotor);
    taskFlag_setNormAfterWaterFullDown = 0;
}

task motorWaterFullDown(){
    taskFlag_motorWaterFullDown = 1;
    int past_enc_centMotor = fabs(nMotorEncoder[centMotor]);
    sleep(200);
    setMotorSpeed(centMotor, -100);
    sleep(100);
    while (fabs(nMotorEncoder[centMotor]) - fabs(past_enc_centMotor) > 1){
        past_enc_centMotor = nMotorEncoder[centMotor];
        sleep(10);
    }
    taskFlag_motorWaterFullDown = 0;
}
