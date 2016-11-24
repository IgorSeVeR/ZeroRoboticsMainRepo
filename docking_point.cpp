float dest[3];
float status[12];
float object[12];

void setV(float v[],float x,float y,float z)/*Definitivo*/{
    v[0] = x;
    v[1] = y;
    v[2] = z;
}
#define ITEM 3
void init(){
    game.dropSPS();game.dropSPS();game.dropSPS();
	float dockDist[]={0.162,0.149,0.135,0.135,0};//order is L,M,S,Special,Adapter
	game.getItemZRState(object,ITEM);
	setV(dest,(dockDist[game.getItemType(ITEM)]*object[6])+object[0],
	          (dockDist[game.getItemType(ITEM)]*object[7])+object[1],
	          (dockDist[game.getItemType(ITEM)]*object[8])+object[2]);//complicated and unreadable stuff that should do the job
    DEBUG(("obj pos:%f %f %f",object[0],object[1],object[2]));
    DEBUG(("dest point:%f %f %f",dest[0],dest[1],dest[2]));
}

void loop(){
    api.getMyZRState(status);
    //position
	api.setPositionTarget(dest);
    DEBUG(("%f %f %f",status[0],status[1],status[2]));
    //attitude
    if (dist(status,dest)<0.2){
        float att[3];
        mathVecSubtract(att, object, status, 3);
        mathVecNormalize(att, 3);
        api.setAttitudeTarget(att);
        if(game.isFacingCorrectItemSide(ITEM))
            DEBUG(("correct facing"));
    }
    //finish?
    else if (game.isFacingCorrectItemSide(ITEM)){
        game.dockItem(ITEM);
        DEBUG(("nope :D"));
    }
    else DEBUG(("something's wrong??"));
}

float dist(float myPos[], float targetPos[]){
    float tempVec[3];
	mathVecSubtract(tempVec,targetPos,myPos,3);
	return mathVecMagnitude(tempVec,3);
}

bool compareVector(float a[], float b[], float approx){
    if  (((a[0] < (b[0]+approx))&&(a[0] > (b[0]-approx))) &&
        ((a[1] < (b[1]+approx))&&(a[1] > (b[1]-approx))) &&
        ((a[2] < (b[2]+approx))&&(a[2] > (b[2]-approx))))
        return true;
    else
        return false;
}
