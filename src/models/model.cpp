#include "models/model.hpp"

Model::Model(string path){
    ifstream file(path);

    if(file.is_open()){
        string line;
        Point2D point;
        uint* indexes = new uint[100];

        while(std::getline(file, line)){
            switch(line[0]){
                case 'p':
                    sscanf(&line[1],"%f %f",&point[0],&point[1]);
                    points.push_back(point);
                    break;
                case 'b':
                    int i = 1;
                    int count = 0;

                    while(sscanf(&line[i],"%u",&indexes[count]) == 1){
                        i+= 2;
                        count++;
                    }

                    curves.push_back(Bezier(count,50,indexes));
                    break;
            }
        }

        for (size_t i = 0; i < curves.size(); i++) {
            curves[i].setGenerators(points);
        }

        delete[] indexes;
    } else {
        cout << CONSOLE_RED << "Error opening model file " << path << CONSOLE_RESET << endl;
    }
}


void Model::computeSamples(){
    for (size_t i = 0; i < curves.size(); i++) {
        curves[i].computeSamples();
    }
}

void Model::apply(const ImageTransform& t){
    t.apply(points);
    for (size_t i = 0; i < curves.size(); i++) {
        curves[i].setGenerators(points);
    }    
}

void Model::draw(Image& img){
    for (size_t i = 0; i < curves.size(); i++) {
        curves[i].draw(img);
    }

    img.lowPass(1,true);
    //img.setDataRange(0,1);
}
