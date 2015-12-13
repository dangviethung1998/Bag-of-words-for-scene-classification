////////////////////////////////////////////////////////////////
/////////////////////code by Arpita S Tugave
////////////////////////////////////////////////////////////////

#include "iostream"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "cv.h"
#include "highgui.h"
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/flann/flann.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <vector>


using namespace cv;
using namespace std;

int main()
{
    Mat image1,image2,image3,image4;

    //read images
    image1 = imread("match1.png",0);
    image2 = imread("match2.png",0);

    vector<KeyPoint> keypointsA,keypointsB;
    Mat descriptorsA,descriptorsB;
    std::vector<DMatch> matches;

    //initialize matcher, extractor and detector
    OrbFeatureDetector detector(1000);
    FREAK extractor;
    BruteForceMatcher<Hamming> matcher;

    //detect,extract and match
    detector.detect(image1,keypointsA);
    detector.detect(image2,keypointsB);
    extractor.compute(image1,keypointsA,descriptorsA);
    extractor.compute(image2,keypointsB,descriptorsB);
    matcher.match(descriptorsA, descriptorsB, matches);

    //erase matches more than 10
    int nofmatches = 10;
    nth_element(matches.begin(),matches.begin()+nofmatches,matches.end());
    matches.erase(matches.begin()+nofmatches+1,matches.end());

    //draw matched point and display
    Mat imgMatch;
    drawMatches(image1, keypointsA, image2, keypointsB, matches, imgMatch);
    imshow("matches", imgMatch);
    waitKey(0);

    return 0;

}
