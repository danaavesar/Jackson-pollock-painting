#include "Circle.h"
#include "Circle.h"

//--------------------------------------------------------------
void Circle::setup(int x, int y, float _radius){
//    radius = ofRandom(5,20);
    pos.set(x,y);
    radius = _radius;
     random = ofRandom(1,16);
     randomRadi= ofRandom(5,9);
     offset = 50;
     ranPosX = ofRandom(pos.x - offset,pos.x + offset );
     ranPosY = ofRandom(pos.y-offset, pos.y+offset);
}

//--------------------------------------------------------------
void Circle::update(){
    
}

//--------------------------------------------------------------
void Circle::draw(){

        ofEllipse(pos.x, pos.y, radius, radius);

    //random splashes
//    if(random == 3){
//        ofEllipse(ranPosX, ranPosY, randomRadi, randomRadi);
//        ofEllipse(ranPosX, ranPosY, randomRadi, randomRadi);
//        ofEllipse(ranPosX, ranPosY, randomRadi, randomRadi);
//        ofEllipse(ranPosX, ranPosY, randomRadi, randomRadi);
//    }
}

//--------------------------------------------------------------
void Circle::keyPressed(int key){
    
}

//--------------------------------------------------------------
void Circle::keyReleased(int key){
    
}

//--------------------------------------------------------------
void Circle::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void Circle::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void Circle::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void Circle::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void Circle::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void Circle::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void Circle::dragEvent(ofDragInfo dragInfo){
    
}
