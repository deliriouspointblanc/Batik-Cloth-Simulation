#include "ofApp.h"

using namespace glm;

bool shouldRemoveRigidBody( const shared_ptr<ofxBulletRigidBody>& ab ) {
    return ab->getPosition().y > 15;
}

//--------------------------------------------------------------
void ofApp::setup() {
  ofDisableArbTex();
  ofEnableNormalizedTexCoords();
    ofSetFrameRate( 60 );
    
    camera.disableMouseInput();
    camera.setDistance( 14 );
    
    camera.setPosition(ofVec3f(0, -4.f, -10.f));
	camera.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));
    
    world.setup();
    world.setCamera(&camera);
    
    
	ground.create( world.world, ofVec3f(0., 5.5, 0.), 0., 50., 1.f, 50.f );
	ground.setProperties(.25, .95);
	ground.add();
    
    camera.enableMouseInput();
    
    
    light.setPosition( 0, -10, 0 );
    
    shared_ptr< ofxBulletSphere > sphere( new ofxBulletSphere() );
    sphere->create( world.world, ofVec3f(0,-2.55,0), 0., 1.75 );
    sphere->enableKinematic();
    sphere->setFriction( 0.8 );
    sphere->add();
    sphere->getCollisionShape()->setMargin( 0.25 );
    rigidBodies.push_back( sphere );

  //Shader
  shader.load("shaders/shader");
  imageText.load("textures/z-interpolation_5015289_9148088.png");
}

//--------------------------------------------------------------
void ofApp::update() {
	world.update();
    
  ofRemove( rigidBodies, shouldRemoveRigidBody );
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofEnableDepthTest();
    ofBackground( ofColor( 34,107,126 ) );
    
    camera.begin();
    
//    world.drawDebug();
    
    ofEnableLighting();
    light.enable();
    ofSetColor( 34,107,126 );
    ground.draw();
    
    ofSetHexColor( 0xF39C12  ); //0xC4EF02
    for( int i = 0; i < rigidBodies.size(); i++ ) {
        rigidBodies[i]->draw();
    }
    
    ofSetColor(0); //221,59,73
//  for( int i = 0; i < patches.size(); i++ ) {
//      patches[i]->getMesh().draw(); //drawWireframe
//  }
  
  ofPushMatrix();
    shader.begin();
  
    shader.setUniform1f("time", ofGetElapsedTimef() / 8 );
    shader.setUniform2f("mousePos", vec2(ofGetMouseX(), ofGetHeight() - ofGetMouseY()));
    shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    shader.setUniformTexture("imageText", imageText.getTexture(), 1);
    //shader.setUniformTexture("fboTexture", fbo.getTexture(), 0);
  //  ofDrawRectangle(0,0, ofGetWidth(), ofGetHeight());
    
    
    //TO-DO: Make a dynamic mesh from the springs, this means I will then be able to apply a texture to it
    for( int i = 0; i < patches.size(); i++ ) {
        patches[i]->getMesh().draw(); //drawWireframe
    }
    
  shader.end();
  ofPopMatrix();
  
    ofSetLineWidth( 1 );
    
    
    
    light.disable();
    ofDisableLighting();
    
    camera.end();
    
    ofDisableDepthTest();
    
    ofSetColor( 220, 220, 220 );
    ofDrawBitmapString("Shoot ball(spacebar): "+ofToString( rigidBodies.size(), 0)+"\nAdd Cloth(p): "+ofToString(patches.size(), 0), 20, 20 );
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if( key == ' ' ) {
        shared_ptr< ofxBulletSphere > ss( new ofxBulletSphere() );
        ss->create( world.world, camera.getPosition(), 0.02, .6 );
        ss->add();
        
        vec3 frc = -camera.getPosition(); //ofVec3f
        vec3 n = normalize(frc); //frc.normalize(); From: https://openframeworks.cc/documentation/glm/
        ss->applyCentralForce( n * 50 );
        
        rigidBodies.push_back( ss );
    }
    
    if( key == 'p' ) {
        patches.clear();
        
        const btScalar	s = 8;
        const btScalar	h = -7;
        const int		r = 64;
        
        shared_ptr<ofxBulletPatch> patch( new ofxBulletPatch() );
        patch->create( &world, ofVec3f(-s,h,-s), ofVec3f(s,h,-s), ofVec3f(-s, h, s ), ofVec3f(s,h,s), r, r );
        patch->getSoftBody()->getCollisionShape()->setMargin(0.25);
        
        patch->getSoftBody()->generateBendingConstraints(1, patch->getSoftBody()->m_materials[0]);
        patch->getSoftBody()->m_materials[0]->m_kLST		=	0.4;
        
        patch->add();
        patch->setMass( 0.25, false );
        
        patch->getSoftBody()->m_cfg.piterations = 20;
        patch->getSoftBody()->m_cfg.citerations = 20;
        patch->getSoftBody()->m_cfg.diterations = 20;
        
        patches.push_back( patch );
    }
    
    if( key == 127 || key == OF_KEY_DEL ) {
        if( patches.size() ) {
            patches.erase( patches.begin() );
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) { 
	
}
