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
    
    vector<int> bend ; 
    vector<int> side ; 
    vector<int> twist ; 
    string outFName ; 

    for( int i=0; i<18 ; i++ )
    {
        int b , s , t ;
        // cin >> b >> s >> t ;
        b = 360;
        s = 360;
        t = 360;
        bend.push_back( b );
        side.push_back( s );
        twist.push_back( t );
    }

    cin >> outFName ;

    string file_name = "/home/iiitd/libhand/hand_model/scene_spec.yml";
    cout << "File Name " << file_name << endl;

    HandRenderer hand_renderer;

    hand_renderer.Setup();
    SceneSpec scene_spec(file_name);
    hand_renderer.LoadScene(scene_spec);
    cv::Mat pic = hand_renderer.pixel_buffer_cv();
    FullHandPose hand_pose(scene_spec.num_bones());


    for( int i=0; i<18 ; i++ )
    {
        hand_pose.bend(i) = 3.14159 / (180.00 / bend[i]);
        hand_pose.side(i) = 3.14159 / (180.00 /  side[i]) ;
        hand_pose.twist(i) = 3.14159 /  (180.00 / twist[i] )  ;
    }

    HandCameraSpec camera_spec_;
    camera_spec_ = HandCameraSpec(hand_renderer.initial_cam_distance());
    camera_spec_.theta = 0.0;
    camera_spec_.phi =  0.0;
    camera_spec_.tilt =  0.0;
    camera_spec_.r = 0.0;

    hand_pose.SetRotMatrix(camera_spec_);
    



    hand_renderer.SetHandPose(hand_pose);
    hand_renderer.RenderHand();

    imwrite("test.jpg", pic );

  } catch (const std::exception &e) {
    cerr << "Exception: " << e.what() << endl;
  }

  return 0;
}
