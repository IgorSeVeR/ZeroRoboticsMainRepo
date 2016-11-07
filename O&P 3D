int sps;
float cubeposes[6][3];
bool trianglend;
float pos[3];
float myState[12];
float zoneinfo[4];
float enzone[3];
float mypos[3];
float att[3];
float cube_pos[3];
float s;
bool flag1, flag3;
bool flag;
float s1; 
float s2; 
float s3;
bool team;
int id;
bool freep;
bool first;
bool indo;
float ps[3];
float point[3];

bool isNear(float* pos1, float* pos2, float a)
{
    /*return ((fabsf(pos1[0]-pos2[0]) <= a) && (fabsf(pos1[1]-pos2[1]) <= a) && (fabsf(pos1[2]-pos2[2]) <= a));*/
    int k = 0;
    for(int i= 0; i<3; i++)
    {
        if(fabsf(pos1[i]-pos2[i]) <= a)
            k++;
    }
    if (k==3)
        return true;
    else
        return false;
}

float getDis(float* pos1, float* pos2) 
{
    float tmp;
    float qdist=0;
    for(int i=0; i<3; i++)
        tmp = (pos2[i]-pos1[i]);
        qdist+=(tmp*tmp);
    return sqrt( qdist );
}
int getNearCubeID()
{
    float m;
    float min=5;
    float m1=-1;
    for (int i = 0; i<6; i++)
    {
        m = getDis(myState,cubeposes[i]);
        if ((m<min) && (!(game.itemInZone(i)))) 
        {
            min=m; m1 = i;
        }
    }
    return m1;
}

void setMoving(float* pos1, float* pos2)
{
    api.setPositionTarget(pos1);
    api.setAttitudeTarget(pos2);
}

void init()
{
    indo=true;
    flag = true;
    flag1 = true;
    first = true;
    freep = true;
    flag3 = true;
    trianglend = false;  
    id = 0;
    api.getMyZRState(myState);
    if (myState[1]>0)
    {
        team = true;
        DEBUG(("BLUE"));
        //pos[0] = -0.6;
        //pos[1] = 0.6;
    }    
    else
    {
        team = false;
        DEBUG(("RED"));
        //pos[0] = 0.6;
        //pos[1] = -0.6;
    }
    //pos[2] = 0; 
    
    s1 = 0.162;
    s2 = 0.149;
    s3 = 0.135;
    
    game.dropSPS();
    sps=2;
    
        if(team)
        {
            point[0] = -0.65;
            point[1] = 0.65;
        }
        else
        {
            point[0] = 0.65;
            point[1] = -0.65;
        }
        point[2]=0;
}

int takeCubic()
{
    if (freep)
    {
        freep = false;
        for (int i = 0; i < 2; ++i)
            if ((isNear(enzone,cubeposes[i],0.2))) {id = i; return id;}
        for (int i = 0; i < 6; ++i)
            if ( (isNear(zoneinfo,cubeposes[i],0.3)) && (game.hasItem(i)!=2) && (!(game.itemInZone(i))) ) 
            {
                id = i;
                return i;
            }
        id  = getNearCubeID();
    }
    return id;
}

bool Force(float item[3], int cubnum)
{
    int a = game.getFuelRemaining();
    if (game.getFuelRemaining()<=20) return false;
    if (game.hasItem(cubnum)==0)
    {
        if (!(isNear(myState,cube_pos,0.7))) {api.setForces(item); DEBUG(("FORCED TO CUBE")); return true;}
    }
    if (game.hasItem(cubnum)==1)
    {
        if (!(isNear(myState,zoneinfo,0.5))) {api.setForces(item); DEBUG(("FORCED TO ZONE")); return true;}
    }
    DEBUG(("KEK (LOL"));
    return false;
}

void ThirdPoint(float* point)
{
    
        api.setPositionTarget(point);
        if (isNear(myState,point,0.1))
        {
            game.dropSPS();
            --sps;
            game.getZone(zoneinfo);
            for (int i =0; i<3; ++i) enzone[i] = -zoneinfo[i];
        }
        
        if (flag1)
        {
            float f[3];
            for (int i = 0; i<3; ++i)
            {
                f[i] = point[i] - myState[i];
            }
            api.setForces(f);
            if (isNear(myState,point,0.7))
                flag1 = false;
        }
        
}

void takeCubes(int cubnum)
    {
        
        if ( (game.itemInZone(1))&&(game.itemInZone(0)) )
        {
            for (int i=0; i<3; i++)
            {
                pos[i]=zoneinfo[i];
                att[i]=-myState[i]+pos[i];
            }
            setMoving(pos,att);
        }else
        {
            if (cubnum<2)
            {
                s = s1;
            }
            else if (cubnum<4)
            {
                s = s2;
            }
            else
            {    
                s = s3;
            }
            if (game.hasItem(cubnum) != 1)
            {

                float d[3];
                int m = 0;
                for (int i =0; i<3; ++i)
                {
                    cube_pos[i] = cubeposes[cubnum][i];
                    mypos[i]=myState[i];
                        
                    d[i] = fabsf(mypos[i]-cube_pos[i]);
                    if (d[i]>d[m]) 
                        m = i;
                    att[i]=0;
                }
                att[m] = cube_pos[m]-mypos[m];
                if (sps==2)
                {
                    if (team) cube_pos[2]+=s; else cube_pos[2]-=s;
                } else
                {
                    if (mypos[m]>cube_pos[m])
                    {
                        cube_pos[m]+=s;
                    }
                    else cube_pos[m]-=s;
                }
                    
                if ((isNear(mypos,cube_pos,0.011)) && (fabsf(att[0])<=0.2) && (fabsf(att[1])<=0.2) && (fabsf(att[2])<=0.2))
                {
                    game.dockItem(cubnum);
                    indo = false;
                    if (sps==2)
                    {
                        game.dropSPS();
                        sps--;
                    }
                    flag3 = true;
                    flag1 = true;
                }
                
                
                else
                {
                    for (int i =0;i < 3; ++i)
                    {
                        ps[i] = cube_pos[i]+0.1;
                    }
                    if (flag1)
                    {
                        flag1 = Force(att, cubnum);
                    }
                    setMoving(cube_pos,att);
                }
            }
                
            if (game.hasItem(cubnum)==1)
            {
                for(int i = 0; i< 3 ; i++)
                {
                    mypos[i]=myState[i];
                }
                    for (int i=0; i<3; i++)
                    
                        {
                            pos[i]=zoneinfo[i];
                            att[i]=-mypos[i]+pos[i];
                        }
                    for(int i =0;i < 3; i++)
                    {
                        
                        if (mypos[i]>pos[i]) pos[i]+=0.07;
                        else pos[i]-=0.07;
                    }
                if ( (isNear(mypos,pos,0.2)) && (fabsf(att[0])<=0.1) && (fabsf(att[1])<=0.1) && (fabsf(att[2])<=0.1))
                {
                        game.dropItem();     
                        flag1 = true;
                        freep = true;
                } else
                { 
                    if (flag1)
                    {
                        flag1 = Force(att,cubnum);                   
                    }
                    setMoving(pos,att);
                }
                
            }
        }
    }
            


void loop()
{
    api.getMyZRState(myState);
    for (int i = 0; i<6; ++i)
    {
        game.getItemLoc(cubeposes[i],i);
    }
    if (sps==1)
    {
        ThirdPoint(point);
    }
    else
    {
        if(first)
        {
            first = false;
            freep = false;
            if(team)
                id = 0;
            if(!(team))
                id = 1;
            takeCubes(id);
        }
        else
            takeCubes(takeCubic());
    }
}
