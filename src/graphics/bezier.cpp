#include "graphics/graphics.hpp"

int binomial(int n, int k)
{
    int num, den ;
    if ( n < k )
    {
       return(0) ;
    }
    else
    {
	den = 1;
	num = 1 ;
	for (int i =  1  ; i <= k   ; i = i+1)
	    den =    den * i;
	for (int j = n-k+1; j<=n; j=j+1)
	    num = num * j;
	return(num/den);
    }
}

namespace GUI{

    Bezier::Bezier(Bezier& b){
        color = b.color;
        samples = b.samples;
        swap(list,b.list);
        swap(data,b.data);
    }

    Bezier::Bezier(GUI::Color _color,int _samples):color(_color),samples(_samples){

    }

    void Bezier::addPoint(int p){
        list.push_back(p);
    }

    void Bezier::draw(SDL_Renderer* renderer,Point* points){
        if(data == nullptr)data = new int[2*(samples+1)];

        color.set(renderer);

        float step = 1.0f/samples;
        for(int i = 0;i <= samples;i++){
            float t = step*i;
            float x = 0;
            float y = 0;
            for(int j = 0;j < list.size();j++){
                x += binomial(list.size()-1,j)*pow(1-t,list.size()-j-1)*pow(t,j)*points[list[j]].x;
                y += binomial(list.size()-1,j)*pow(1-t,list.size()-j-1)*pow(t,j)*points[list[j]].y;
            }

            data[2*i+0] = x + 0.5f;
            data[2*i+1] = y + 0.5f;
        }


        SDL_RenderDrawLines(renderer,(SDL_Point*)&data[0],samples+1);
    }

    Bezier::~Bezier(){
        delete[] data;
    }

}
