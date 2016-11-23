/* We fly a little longer
   We have to fix it */

float myState[12];
float target[3];
bool StartDisSaved;
float startDis;
bool movingEnded;
float origin[3];
float vectorBetween[3];
float myPos[3];
float current_distance;


void init()
{
    for(int i = 0;i<3;++i, origin[i]=0);
    StartDisSaved = false;
	target[0] = 0.5;
	target[1] = 0.5;
	target[2] = 0.5;
	movingEnded = false;
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
    for(int i = 0; i < 3; ++i, myPos[i] = myState[i]);
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
        if (curDis>(startDis/2))
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
    movement(target);
    rotation(target);
}
