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
    bool is_right;
};

class Celula
{
    public:
    int val;
    Celula* par_direita;
    Celula* par_cima;
    int height;
};

Celula* find(Celula* start, Celula* destino)
{
    
}

Celula* makeset(int val)
{
    Celula* N = new Celula();
    N->val = val;
    N->par_direita = N;
    N->par_cima = N;
    N->height = 1;
    
    return N;
}

int main(){

    int casos, maze_size, maze_walls, Q;

    cin >> casos;

    for(int i = 0; i<casos; i++)
    {
        cin >> maze_size >> maze_walls >> Q;
        
        Celula** celulas = new Celula*[maze_size*maze_size];

        for(int j = 0; j<(maze_size*maze_size); j++)
        {
            celulas[j] = makeset(j);
        }

        Aresta* arestas = new Aresta[(2*((maze_size*maze_size) - maze_size))];

        int j = 0; int k = 0;
        
        for(int x = 0; x<(maze_size*maze_size); x++)
        {
            if((x+1)%maze_size != 0)
            {
                arestas[i].x = x;
                arestas[i].y = x+1;
                arestas[i].is_right = true;
                i++;
                j++;
                if(j == maze_size-1)
                {
                    j = 0;
                    x = x-(maze_size-1);
                    
                    while(j<maze_size)
                    {
                        arestas[i].x = x;
                        arestas[i].y = x+maze_size;
                        arestas[i].is_right = false;
                        i++;
                        j++;
                    }
                    j = 0;
                }
            }

        }
        
        for(int j =0; j<maze_walls; j++)
        {
            int remotion;
            cin >> remotion; 

            if(arestas[remotion].is_right)
            {
                celulas[arestas[remotion].y]->par_direita = celulas[arestas[remotion].x];
            } else celulas[arestas[remotion].y]->par_cima = celulas[arestas[remotion].x];               
        }

        for(int k = 0; k<Q; k++)
        {
            int start;
            int destino;

            cin >> start >> destino;

            Celula* temp = celulas[destino];


        }
        
    }

    return 0;
}