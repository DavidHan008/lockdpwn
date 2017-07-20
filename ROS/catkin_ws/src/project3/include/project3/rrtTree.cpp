#include "rrtTree.h"

using namespace std;

rrtTree::rrtTree(){
    count = 0;
    root = NULL;
    ptrTable[0] = NULL;
}

rrtTree::rrtTree(point x_init, point x_goal, cv::Mat map, double map_origin_x, double map_origin_y, double res, int margin) {
    this->x_init = x_init;
    this->x_goal = x_goal;
    this->map_original = map.clone();
    this->map = addMargin(map, margin);
    this->map_origin_x = map_origin_x;
    this->map_origin_y = map_origin_y;
    this->res = res;

    count = 1;
    root = new node;
    ptrTable[0] = root;
    root->idx = 0;
    root->idx_parent = NULL;
    root->location = x_init;
    root->rand = x_init;
    root->cost = 0.0;

    edge_cnt = 0;//project2
    srand (time(NULL));//project2
}

rrtTree::~rrtTree(){
    for (int i = 1; i <= count; i++) {
        delete ptrTable[i];
    }
}

cv::Mat rrtTree::addMargin(cv::Mat map, int margin) {
    cv::Mat map_margin = map.clone();
    int xSize = map.cols;
    int ySize = map.rows;

    for (int i = 0; i < ySize; i++) {
        for (int j = 0; j < xSize; j++) {
            if (map.at<uchar>(i, j) < 125) {
                for (int k = i - margin; k <= i + margin; k++) {
                    for (int l = j - margin; l <= j + margin; l++) {
                        if (k >= 0 && l >= 0 && k < ySize && l < xSize) {
                            map_margin.at<uchar>(k, l) = 0;
                        }
                    }
                }
            }
        }
    }

    return map_margin;
}

void rrtTree::visualizeTree(){
    int thickness = 1;
    int lineType = 8;
    int idx_parent;
    double Res = 2;
    double radius = 6;
    cv::Point x1, x2;

    cv::Mat map_c;
    cv::Mat imgResult;
    cv::cvtColor(this->map_original, map_c, CV_GRAY2BGR);
    cv::resize(map_c, imgResult, cv::Size(), Res, Res);

    cv::circle(imgResult, cv::Point((int)(Res*(x_init.y/res + map_origin_y)), (int)(Res*(x_init.x/res + map_origin_x))), radius, cv::Scalar(0, 0, 255), CV_FILLED);
    cv::circle(imgResult, cv::Point((int)(Res*(x_goal.y/res + map_origin_y)), (int)(Res*(x_goal.x/res + map_origin_x))), radius, cv::Scalar(0, 255, 255), CV_FILLED);

    for(int i = 1; i < this->count; i++) {
        idx_parent = this->ptrTable[i]->idx_parent;
        x1 = cv::Point((int)(Res*(ptrTable[i]->location.y/res + map_origin_y)), (int)(Res*(ptrTable[i]->location.x/res + map_origin_x)));
        x2 = cv::Point((int)(Res*(ptrTable[idx_parent]->location.y/res + map_origin_y)), (int)(Res*(ptrTable[idx_parent]->location.x/res + map_origin_x)));
        cv::line(imgResult, x1, x2, cv::Scalar(255, 0, 0), thickness, lineType);
    }

    cv::namedWindow("Mapping");
    cv::Rect imgROI((int)Res*200,(int)Res*200,(int)Res*400,(int)Res*400);
    cv::imshow("Mapping", imgResult(imgROI));
    cv::waitKey(1);

}

void rrtTree::visualizeTree(std::vector<point> path){
    int thickness = 1;
    int lineType = 8;
    int idx_parent;
    double Res = 2;
    double radius = 6;
    cv::Point x1, x2;

    cv::Mat map_c;
    cv::Mat imgResult;
    cv::cvtColor(this->map_original, map_c, CV_GRAY2BGR);
    cv::resize(map_c, imgResult, cv::Size(), Res, Res);

    cv::circle(imgResult, cv::Point((int)(Res*(x_init.y/res + map_origin_y)), (int)(Res*(x_init.x/res + map_origin_x))), radius, cv::Scalar(0, 0, 255), CV_FILLED);
    cv::circle(imgResult, cv::Point((int)(Res*(x_goal.y/res + map_origin_y)), (int)(Res*(x_goal.x/res + map_origin_x))), radius, cv::Scalar(0, 0, 255), CV_FILLED);

    for(int i = 1; i < this->count; i++) {
        idx_parent = this->ptrTable[i]->idx_parent;
        x1 = cv::Point((int)(Res*(ptrTable[i]->location.y/res + map_origin_y)), (int)(Res*(ptrTable[i]->location.x/res + map_origin_x)));
        x2 = cv::Point((int)(Res*(ptrTable[idx_parent]->location.y/res + map_origin_y)), (int)(Res*(ptrTable[idx_parent]->location.x/res + map_origin_x)));
        cv::line(imgResult, x1, x2, cv::Scalar(255, 0, 0), thickness, lineType);
    }

    thickness = 3;
    for(int i = 1; i < path.size(); i++) {
        x1 = cv::Point((int)(Res*(path[i-1].y/res + map_origin_y)), (int)(Res*(path[i-1].x/res + map_origin_x)));
        x2 = cv::Point((int)(Res*(path[i].y/res + map_origin_y)), (int)(Res*(path[i].x/res + map_origin_x)));
        cv::line(imgResult, x1, x2, cv::Scalar(255, 0, 0), thickness, lineType);
    }

    cv::namedWindow("Mapping");
    cv::Rect imgROI((int)Res*200,(int)Res*200,(int)Res*400,(int)Res*400);
    cv::imshow("Mapping", imgResult(imgROI));
    cv::waitKey(1);

}



// TODO
// 1. Copy your implementation of member functions in Project Assignment #2
void rrtTree::addVertex(point x_new, point x_rand, int idx_near)
{
    // TODO

    this->ptrTable[this->count-1] = root;

    ////
    root = new node;
    this->count++;
    this->ptrTable[this->count-1] = root;
    root->idx = this->count-1;
    root->idx_parent = idx_near;
    root->location = x_new;
    root->rand = x_rand;

}

//public
int rrtTree::generateRRT(double x_max, double x_min, double y_max, double y_min, int K, double MaxStep)
{
    // TODO

    this->edge_cnt = 0;
    //Finish Condition
    if( sqrt(pow((x_goal.x - ptrTable[this->count-1]->location.x),2) + pow((x_goal.y - ptrTable[this->count-1]->location.y),2)) < MaxStep )
    {
        //cout << "Finish " <<endl;

        addVertex( x_goal, ptrTable[this->count-1]->location, this->count-1);

        visualizeTree();

        path_.push_back(x_goal);
        int idx_ = this->count-1;
        while(idx_ > 0)
        {
            idx_ = ptrTable[idx_]->idx_parent;
            path_.push_back(ptrTable[idx_]->location);
            this->edge_cnt++;
            //cout << "idx : " << ptrTable[idx_]->idx << " idx_parent : " << ptrTable[idx_]->idx_parent << endl;
        }
        visualizeTree(path_);
        path_.push_back(ptrTable[0]->location);
        this->edge_cnt++;

        //for (int i = 0 ; i < this->edge_cnt ; i++)
        //    cout <<"[" << i << "] "<< "X : " << path_[i].x << ", Y : " << path_[i].y << endl;

        return this->edge_cnt;//escape this func.
    }

    //Loop RRT
    for( int i = 0 ; i < K ; i++)   //Don't need but just use var 'K'
    {
        //step 3    //return rand_PT
        point rand_PT = randomState(x_max, x_min, y_max, y_min);
        //cout << "[rand] " << ".x : " << rand_PT.x << ", .y : " << rand_PT.y << endl;

        //step 4    //return MinIdx
        int idx_near = nearestNeighbor(rand_PT);
        //cout << "idx_near : " << idx_near << endl;

        //step 6    //return new_PT(MaxDist) //cut the length to MaxDist
        point new_PT = newState(idx_near, rand_PT, MaxStep);
        //cout << "new_PT.x : " << new_PT.x << ", idx_near.y : " << new_PT.y << endl;

        //Collision check
        bool chk_tmp = false;
        chk_tmp = isCollision(ptrTable[idx_near]->location, new_PT);
        //cout<< "chk_tmp : " << chk_tmp << endl;
        if ( chk_tmp )//free
            //step 7    //add new vertex and edge
            addVertex(new_PT, ptrTable[idx_near]->location, idx_near);
    }
    visualizeTree();

    return 0;

}


// 2. Implement generateRRTst
void rrtTree::addVertexCost(point x_new, point x_rand, int idx_parent, double cost)
{
    // TODO
    this->ptrTable[this->count-1] = root;

    ////
    root = new node;
    this->count++;
    this->ptrTable[this->count-1] = root;
    root->idx = this->count-1;
    root->idx_parent = idx_parent;
    root->location = x_new;
    root->rand = x_rand;
    root->cost = cost;

}

int rrtTree::generateRRTst(double x_max, double x_min, double y_max, double y_min, int K, double MaxStep, double Radius)
{
    // TODO 2.
    //Finish Condition
    this->edge_cnt = 0;
    //cout << this->count << endl;
    for (int i = this->count-1 ; i >= 0 ; i--)
    {
        if( sqrt(pow((x_goal.x - ptrTable[i]->location.x),2)
                 + pow((x_goal.y - ptrTable[i]->location.y),2)) < MaxStep/3 )
        {
            //cout << "Finish " <<endl;

            path_.push_back(x_goal);
            int idx_ = i;
            while(idx_ > 0)
            {
                idx_ = ptrTable[idx_]->idx_parent;
                path_.push_back(ptrTable[idx_]->location);
                this->edge_cnt++;
                //cout << "idx : " << ptrTable[idx_]->idx << " idx_parent : " << ptrTable[idx_]->idx_parent << endl;
            }
            visualizeTree(path_);
            //path_.push_back(ptrTable[0]->location);
            this->edge_cnt++;

            //for (int i = 0 ; i < this->edge_cnt ; i++)
            //    cout <<"[" << i << "] "<< "X : " << path_[i].x << ", Y : " << path_[i].y << endl;

            return this->edge_cnt;//escape this func.
        }
    }

/////
    //Loop RRT*
    for( int i = 0 ; i < K ; i++)   //min iteration (relates optimal solution)
    {
        //step 3    //return rand_PT
        point rand_PT = randomState(x_max, x_min, y_max, y_min);
        //cout << "[rand] " << ".x : " << rand_PT.x << ", .y : " << rand_PT.y << endl;

        //step 4    //return MinIdx
        int idx_near = nearestNeighbor(rand_PT);
        //cout << "idx_near : " << idx_near << endl;

        //step 5    //return new_PT(MaxDist) //cut the length to MaxDist
        point new_PT = newState(idx_near, rand_PT, MaxStep);
        //cout << "new_PT.x : " << new_PT.x << ", idx_near.y : " << new_PT.y << endl;

        //step 6    //Collision check
        bool chk_tmp = false;
        chk_tmp = isCollision(ptrTable[idx_near]->location, new_PT);
        //cout<< "chk_tmp : " << chk_tmp << endl;
        if ( chk_tmp )//free
        {
            int parent = chooseParent(idx_near, new_PT, Radius);    //step 7 ~ 13
            reWire(parent, Radius); //step 14 ~ 16
        }
        //visualizeTree();
        //cout << i << endl;
    }
    //visualizeTree();

    return 0;


////


}

int rrtTree::chooseParent(int idx_near, point x_new, double Radius)
{
    double cost = 0.0;
    int parent = 0;

    for(int i = 0 ; i < this->count ; i++)
    {
        if ( isCollision(ptrTable[i]->location, x_new)  //step 11
             && dist(ptrTable[i]->location, x_new) < Radius //step 7
             && ptrTable[i]->cost + dist(ptrTable[i]->location, x_new) //step 9
             <= ptrTable[idx_near]->cost + dist(ptrTable[idx_near]->location, x_new)
             )
        {
            //cout << "NEW " <<endl;

            //step 12
            cost = ptrTable[i]->cost + dist(ptrTable[i]->location, x_new);
            //cout << "cost : " << cost <<endl;
            parent = this->ptrTable[i]->idx;
            //cout << "parent : " << parent <<endl;

            //step 13
            addVertexCost(x_new, ptrTable[idx_near]->location, parent, cost);

            return parent;
        }
        else
        {
            //step 13
            //cout << "---" <<endl;
            cost = ptrTable[idx_near]->cost + dist(ptrTable[idx_near]->location, x_new);
            //cout << "cost : " << cost <<endl;
            parent = this->ptrTable[idx_near]->idx;
            //cout << "parent : " << parent <<endl;

            addVertexCost(x_new, ptrTable[idx_near]->location, parent, cost);

            return parent;
        }

    }
}

void rrtTree::reWire(int parent, double Radius)
{
    //cout << this->count <<endl;
    for(int i = 0 ; i < this->count ; i++)  //step 14
    {
        //cout << (int)isCollision(ptrTable[i]->location, ptrTable[parent]->location) <<endl;
        if ( isCollision(ptrTable[i]->location, ptrTable[parent]->location) //step 15
             && ptrTable[i]->idx != parent  //step 15
             && dist(ptrTable[i]->location, ptrTable[parent]->location) < Radius    //step 15
             && ptrTable[parent]->cost + dist(ptrTable[i]->location, ptrTable[parent]->location) < ptrTable[i]->cost    //step 15
             )
        {
            //step 16
            this->ptrTable[i]->idx_parent = parent;
            this->ptrTable[i]->cost = ptrTable[parent]->cost + dist(ptrTable[i]->location, ptrTable[parent]->location);
            //cout<< "parent idx : " << this->ptrTable[i]->idx_parent <<endl;
        }
    }
}


double rrtTree::dist(point x1, point x2)
{
    return sqrt(pow((x1.x - x2.x),2) + pow((x1.y - x2.y),2));
}

point rrtTree::randomState(double x_max, double x_min, double y_max, double y_min) {
    // TODO
    point rand_PT;

    rand_PT.x = (rand() % (int)(x_max*2.0) + x_min);
    rand_PT.y = (rand() % (int)(y_max*2.0) + y_min);

    return rand_PT;
}

point rrtTree::newState(int idx_near, point x_rand, double MaxStep) {
    // TODO
    double dist = (pow((x_rand.x - ptrTable[idx_near]->location.x),2) + pow((x_rand.y - ptrTable[idx_near]->location.y),2));
    if ( dist < MaxStep )
        return x_rand;
    else
    {
        point x_new_PT;
        double PT_th = atan2(x_rand.y - ptrTable[idx_near]->location.y, x_rand.x - ptrTable[idx_near]->location.x);

        x_new_PT.x = (ptrTable[idx_near]->location.x + MaxStep*cos(PT_th));
        x_new_PT.y = (ptrTable[idx_near]->location.y + MaxStep*sin(PT_th));

        //cout << "ptrTable[root->idx]->location.x : " << ptrTable[root->idx]->location.x
        //        << ", ptrTable[root->idx]->location.y : " << ptrTable[root->idx]->location.y <<endl;

        return x_new_PT;
    }
}


int rrtTree::nearestNeighbor(point x_rand) {
    // TODO

    double min_dist = 99999;
    int min_idx;
    for(int i = 0 ; i < this->count ; i++)
    {
        //cout << "location.x : " << ptrTable[i]->location.x << ", location.y : " << ptrTable[i]->location.y << endl;
        double chk_dist = sqrt(pow((x_rand.x - ptrTable[i]->location.x),2) + pow((x_rand.y - ptrTable[i]->location.y),2));
        //cout << "chk_dist : " << chk_dist << endl;

        if ( chk_dist < min_dist )
        {
            min_dist = chk_dist;
            min_idx = i;
        }
    }

    return min_idx;

}

bool rrtTree::isCollision(point x1, point x2) {
    // TODO
    //x1 : orig pt
    //x2 : rand pt
    //255 : free
    //0 : obs

    int i = 0.0, j = 0.0;
    double x1_orig, x2_orig, y1_orig, y2_orig;
    x1_orig = map_origin_x + x1.x/res;
    y1_orig = map_origin_y + x1.y/res;
    x2_orig = map_origin_x + x2.x/res;
    y2_orig = map_origin_y + x2.y/res;

    point orig, end;
    if (x1_orig > x2_orig)
    {
        orig.x = x2_orig;
        end.x = x1_orig;
    }
    else
    {
        orig.x = x1_orig;
        end.x =  x2_orig;
    }
    if (y1_orig > y2_orig)
    {
        orig.y = y2_orig;
        end.y = y1_orig;
    }
    else
    {
        orig.y = y1_orig;
        end.y =  y2_orig;
    }

    for(int i = (int)orig.x ; i <= (int)end.x ; i++)
        for(int j = (int)orig.y ; j <= (int)end.y ; j++)
            //if((int)map.at<uchar>(i, j) == 0)//obs
            if((int)map.at<uchar>(i, j) <= 127)//obs
                return false;
            else
                continue;

    return true;


}

//public
std::vector<point> rrtTree::backtracking(){
    //Find the nearest leaf node from the goal and track parents of nodes iterativel
    // TODO

    std::vector<point> path_back;
    for (int i = this->edge_cnt-1 ; i >= 0 ; i--)
        path_back.push_back(path_[i]);

//    for (int i = 0 ; i < this->edge_cnt ; i++)
//        cout <<"[" << i << "] "<< "X : " << path_back[i].x << ", Y : " << path_back[i].y << endl;

    return path_back;
}
