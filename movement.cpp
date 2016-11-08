/* There are two problems:
   I dont know when I must start slowing down (i do it when im on the half of dis but it doesnt work right)
   I couldn't understand what the what does sphere walking round */

float myState[12];
float target[3];
bool StartDisSaved;
float startDis;

void init()
{
  StartDisSaved = false;
	target[0] = -0.7;
	target[1] = -0.7;
	target[2] = -0.7;
}

float getDis(float* pos1, float* pos2) 
{
    float tmp;
    float qdist;
    for(int i=0; i<3; i++)
        tmp = (pos2[i]-pos1[i]);
        qdist=(tmp*tmp);
    return sqrt( qdist );
}

bool isAlmostEqual(float a, float b, float r) //check 2 float variables if they are almost equal, r is something very little
{
    float res = a-b;
    res = fabsf(res);
    bool ans = (res<=r);
    return ans;
}

void moveMent(float* target_copy)
{
    float targ_relative[3];
    float targ_absolute[3];
    for(int i =0; i<3; ++i)
    {
        targ_absolute[i] = target_copy[i];
        targ_relative[i] = targ_absolute[i] - myState[i];
    }
    
    float curDis = getDis(myState,targ_absolute);
    if (curDis>=0.01)
    {
        DEBUG(("curDis is %f \n", curDis));
        if (!(StartDisSaved))
        {
            startDis = getDis(myState,targ_absolute);
            StartDisSaved = true;
            DEBUG(("Start distance is saved, it is %f \n", startDis));
        }
        if (curDis>(startDis/1.7))
        {
            api.setForces(targ_relative);
            DEBUG(("We are accellerating \n"));
        }
        else
        {
            for(int i = 0; i<3; ++i, targ_relative[i]*=-1);
            api.setForces(targ_relative);
            DEBUG(("We are stopping \n")); 
        }
    }
}

void loop()
{
  api.getMyZRState(myState);
	moveMent(target);
}
