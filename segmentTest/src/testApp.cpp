#include "testApp.h"
#include "segment-image.h"

image<rgb> *input ;



//--------------------------------------------------------------
void testApp::setup(){

    
    img.loadImage("a.jpg");
    
    imgSegmented.allocate(img.width, img.height, OF_IMAGE_COLOR);
    
    threshold.allocate(img.width, img.height, OF_IMAGE_COLOR);

    //float sigma
    //float k = atof(argv[2]);
    //int min_size = atoi(argv[3]);
    
    input = new image<rgb>(img.width, img.height);
    
    memcpy(input->data, img.getPixels(), img.width*img.height*3);
    
    int num_ccs;
    image<rgb> *seg = segment_image(input, 0.5, 1000, 50, &num_ccs);
    
    cout << num_ccs << endl;
    
    memcpy(imgSegmented.getPixels(), seg->data, img.width*img.height*3);
    
    
    imgSegmented.update();
    
    
    imgSegAvergageOrigColor.allocate(img.width, img.height, OF_IMAGE_COLOR);
    
    gui.setup();
    
    gui.add(RGBx.setup("sigma",0.5, 0.1, 1));
    
    gui.add(RGBy.setup("c",50, 1, 1000));
    
    gui.add(RGBz.setup("min_size",50, 1, 1000));
    
    gui.add(thresholdSize.setup("threshold",50, 0, 1000));

    
}

//--------------------------------------------------------------
void testApp::update(){

    
    int num_ccs;
    
    
    image<rgb> *seg = segment_image(input, RGBx, RGBy, RGBz, &num_ccs);
    
    //cout << num_ccs << endl;
    
    memcpy(imgSegmented.getPixels(), seg->data, img.width*img.height*3);
    
    
    imgSegmented.update();
    
    delete [] seg->data;
    
    
    map < int, vector < ofColor > > segColorToOrigColor;
    
    unsigned char * pixels = img.getPixels();
    unsigned char * segPixels = imgSegmented.getPixels();
    unsigned char * thresholdPix = threshold.getPixels();
    for (int i = 0; i < img.width; i++){
        for (int j = 0; j < img.height; j++){
            
            int ii = j * img.width + i;
            
            ofColor seg = ofColor( segPixels[ii*3], segPixels[ii*3+1], segPixels[ii*3+2] );
            ofColor pix = ofColor( pixels[ii*3], pixels[ii*3+1], pixels[ii*3+2] );
            
            if (pix.getBrightness() < thresholdSize){
                thresholdPix[ii*3]=0;
                thresholdPix[ii*3+1]=0;
                thresholdPix[ii*3+2]=0;
                
            } else {
                thresholdPix[ii*3]=255;
                thresholdPix[ii*3+1]=255;
                thresholdPix[ii*3+2]=255;
                
            }
            
            
            int hex = seg.getHex();
            
            
            segColorToOrigColor[hex].push_back(pix);
            
        }
        
    }
    
    threshold.update();
    
    
    map < int, ofColor > segColorToAvg;
    
    // so let's map over the colors:
    
    typedef std::map<int, vector < ofColor > >::iterator it_type;
    for(it_type iterator = segColorToOrigColor.begin(); iterator != segColorToOrigColor.end(); iterator++) {
        
        //iterator->first = key
        int segColor =iterator->first;
        vector < ofColor > & colors = iterator->second;
        
        float r,g,b;
        r=g=b=0;
        
        for (int i = 0; i < colors.size(); i++){
            r += colors[i].r / (float)colors.size();
            g += colors[i].g / (float)colors.size();
            b += colors[i].b / (float)colors.size();
            
        }
        
        segColorToAvg[segColor] = ofColor(r,g,b);
        
        
        // Repeat if you also want to iterate through the second map.
    }
    
    
    
    unsigned char * imgSegAvergageOrigColorPix = imgSegAvergageOrigColor.getPixels();
    for (int i = 0; i < img.width; i++){
        for (int j = 0; j < img.height; j++){
            
            int ii = j * img.width + i;
            
            ofColor seg = ofColor( segPixels[ii*3], segPixels[ii*3+1], segPixels[ii*3+2] );
            int segHex = seg.getHex();
            
            ofColor avg = segColorToAvg[segHex];
            
            
            
            if(avg.getBrightness()>170){
                avg.set(241, 178, 220);
            }else if(avg.getBrightness()<=170 && avg.getBrightness()>150){
                avg.set(42, 210, 201);
            }else if(avg.getBrightness()<=150 && avg.getBrightness()>140){
                avg.set(64, 193, 172);
            }else if(avg.getBrightness()<=140 && avg.getBrightness()>110){
                avg.set(103, 135, 183);
            }else if(avg.getBrightness()<=110 && avg.getBrightness()>80){
                avg.set(213, 0, 50);
            }else if(avg.getBrightness()<=80 && avg.getBrightness()>50){
                avg.set(34, 28, 53);
            }else if(avg.getBrightness()<=50){
                avg.set(225, 205, 0);
            }
            
            
            imgSegAvergageOrigColorPix[ ii * 3 ] = avg.r;
            imgSegAvergageOrigColorPix[ ii * 3 + 1] = avg.g;
            imgSegAvergageOrigColorPix[ ii * 3 + 2] = avg.b;
            
        }
        
    }
    
    imgSegAvergageOrigColor.update();
    
    
    
    //delete seg;
    

}

//--------------------------------------------------------------
void testApp::draw(){

    img.draw(0,0);
//    imgSegmented.draw(img.width, 0);
    imgSegAvergageOrigColor.draw(img.width,0);
    
    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    threshold.draw(img.width,0);
    ofDisableAlphaBlending();
    
    gui.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
