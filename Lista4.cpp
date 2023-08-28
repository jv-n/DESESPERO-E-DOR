#include <iostream>
#include <string>
#include <cassert>
#include <cmath>

using namespace std;

class Aresta
{
    public:
    int x;
    int y;
  
};

class Celula
{
    public:
    int val;
    Celula* par;
    int height;
};

Celula* makeset(int val)
{
    Celula* N = new Celula();
    N->val = val;
    N->par = N;
    N->height = 1;
    
    return N;
}

int main(){

    int casos, maze_size, maze_walls, Q;

    cin >> casos;

    for(int w = 0; w<casos; w++)
    {
        cin >> maze_size >> maze_walls >> Q;
        
        Celula** celulas = new Celula*[maze_size*maze_size];

        for(int j = 0; j<(maze_size*maze_size); j++)
        {
            celulas[j] = makeset(j);
        }

        Aresta* arestas = new Aresta[(2*((maze_size*maze_size) - maze_size))];

        int j = 0; int i = 0;
        
        for(int x = 0; x<(maze_size*maze_size); x++)
        {
            if(i<(2*((maze_size*maze_size) - maze_size)))
            {
            bool added_right = false;
            if((x+1)%maze_size != 0)
            {
                arestas[i].x = x;
                arestas[i].y = x+1;
                added_right = true;
                i++;
            }
            if(j == (maze_size-1))
            {
                j = 0;
                x = x-(maze_size-1);
                    
                while(j<maze_size)
                {
                    arestas[i].x = x;
                    arestas[i].y = x+maze_size;
                      
                    i++;
                    j++;
                }
                j = 0;
                x+=maze_size-1;
            }
            if(added_right)
            {
                j++;
            }
            }     

        }
        
        for(int j =0; j<maze_walls; j++)
        {
            int remotion;
            cin >> remotion; 

            celulas[arestas[remotion].y]->par = celulas[arestas[remotion].x]->par;
                           
        }

        for(int k = 0; k<Q; k++)
        {
            int start;
            int destino;

            cin >> start >> destino;

            if(celulas[start]->par == celulas[destino]->par)
            {
                cout << endl << w << "." << k << " 1";
            } else cout << endl<< w << "." << k << " 0";

        }
        
    }

    return 0;
}