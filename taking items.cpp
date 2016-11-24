
float myState[12];
float target[3];
bool StartDisSaved;
float startDis;
bool movingEnded;
float origin[3];
float vectorBetween[3];
float myPos[3];
float current_distance;
float att_target[3];


void init()
{
    StartDisSaved = false;
	target[0] = 0;
	target[1] = 0;
	target[2] = 0;
	for(int i = 0; i < 3; ++i)
	    att_target[i] = target[i]+0.1;
	movingEnded = false;
} 

void getPointForDock(float* pos, float* item_center, float* item_att)
{
    for(int i =0;i < 3; i++)
    {
        pos[i] = item_att[i];
        if (item_center[i] > item_att[i]) pos[i] -= 0.135;
        else pos[i] += 0.135;
    }
}

void takeItem(int number)
{
    float pos[3];
    float att[3];
    float cubeState[12];
    game.getItemZRState(cubeState,number);
    for(int i = 0; i<3; ++ i)
        DEBUG(("%f",cubeState[6+i]))
        att[i] = cubeState[6+i];
    DEBUG(('\n'));
    getPointForDock(pos,cubeState,att);
    for(int i = 0; i<3; ++i)
        att[i] *= -1;
    movement(pos);
    rotation(att);
}

float getDis(float* pos1, float* pos2) 
{
    float tmp;
    float qdist=0;
    for(int i=0; i<3; ++i)
    {
        tmp = (pos2[i]-pos1[i]);
        qdist+=(tmp*tmp);
    }
    return sqrt( qdist );
}

void rotation(float* target)
{
    for(int i = 0; i < 3; ++i)
        myPos[i] = myState[i];
    mathVecSubtract(vectorBetween,target,myPos,3);
    mathVecNormalize(vectorBetween,3);
    api.setAttitudeTarget(vectorBetween);
}

void movement(float* target_copy)
{
    float targ_relative[3];
    float targ_absolute[3];
    for(int i =0; i<3; ++i)
    {
        targ_absolute[i] = target_copy[i];
        targ_relative[i] = targ_absolute[i] - myState[i];
    }
    
    float curDis = getDis(myState,targ_absolute);
    DEBUG(("curDis is %f \n", curDis));
    if (curDis>=0.009)
    {
        if (!(StartDisSaved))
        {
            startDis = getDis(myState,targ_absolute);
            StartDisSaved = true;
            DEBUG(("Start distance is saved, it is %f \n", startDis));
        }
        if (curDis>(startDis/1.6))
        {
            api.setForces(targ_relative);
            DEBUG(("We are accellerating \n"));
        }
        else
        {
            api.setPositionTarget(targ_absolute); 
        }
    }
}

void loop()
{
    api.getMyZRState(myState);
    takeItem(4);
}
