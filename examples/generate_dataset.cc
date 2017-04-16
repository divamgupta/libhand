// This example will show a hand in a default pose
// and then bend one joint and show the hand again
//
// This is a line-by-line code example

# include <string>
# include "opencv2/opencv.hpp"
# include "file_dialog.h"
# include "hand_pose.h"
# include "hand_renderer.h"
# include "scene_spec.h"
# include <vector>

using namespace libhand;

using namespace std;

int main(int argc, char **argv) {


  try {
    
    string file_name ; //  = "/home/iiitd/libhand/hand_model/scene_spec.yml";

    vector<int> bend ; 
    vector<int> side ; 
    vector<int> twist ; 
    string outFName; // = "test.jpg" ; 
    int theta = 360;
    int phi = 360 ; 
    int tilt = 360 ;
    int dist = 100;

    cout << "enter the scene filename " << endl;
    getline(cin, file_name );

    cout << "enter the output filename " << endl;
    getline(cin, outFName );
    cout << "enter the camera theta (360 )" << endl;
    cin >> theta ;
    cout << "enter the camera phi (360 )" << endl;
    cin >> phi ;
    cout << "enter the camera tilt (360 ) " << endl;
    cin >> tilt ;
    cout << "enter the camera dist ( 100 )" << endl;
    cin >> dist ;

    for( int i=0; i<18 ; i++ )
    {
        int b , s , t ;
        cout << "enter the joint " << i << " bend (360)" << endl;
        cin >> b;
        cout << "enter the joint " << i << " side (360)" << endl;
        cin >> s;
        cout << "enter the joint " << i << " tilt (360)" << endl;
        cin >> t ;
        bend.push_back( b );
        side.push_back( s );
        twist.push_back( t );
    }

   

    

    HandRenderer hand_renderer;

    hand_renderer.Setup();
    SceneSpec scene_spec(file_name);
    hand_renderer.LoadScene(scene_spec);
    cv::Mat pic = hand_renderer.pixel_buffer_cv();
    FullHandPose hand_pose(scene_spec.num_bones());


    for( int i=0; i<18 ; i++ )
    {
        hand_pose.bend(i) = 3.14159 * bend[i] / (180.00  );
        hand_pose.side(i) = 3.14159 * side[i] / (180.00  ) ;
        hand_pose.twist(i) = 3.14159 * twist[i] /  (180.00 )  ;
    }

    HandCameraSpec camera_spec_;
    camera_spec_ = HandCameraSpec(hand_renderer.initial_cam_distance());
    camera_spec_.theta = 3.14159*theta/180.0 ;
    camera_spec_.phi =  3.14159*phi/180.0 ;
    camera_spec_.tilt =  3.14159*tilt/180.0 ;
    camera_spec_.r =  dist/10.0 ;

    hand_pose.SetRotMatrix(camera_spec_);
    hand_renderer.set_camera_spec(camera_spec_); 
    hand_renderer.SetHandPose(hand_pose);
    hand_renderer.RenderHand();

    imwrite( outFName, pic );
    cout << "written : " << outFName << endl;

  } catch (const std::exception &e) {
    cerr << "Exception: " << e.what() << endl;
  }


  return 0;
}
