#include<iostream>
#include <vector>
#include <cassert>

class IGraph
{
protected:
    int side = 0;
    std::vector<int*> matrix;
public:
    IGraph()
    {
        std::cout << "IGraph created " << std::endl;
    };

    virtual ~IGraph() {
        std::cout << "IGraph destroyed " << std::endl;
    }

    IGraph(IGraph& other)
    {
        ;
    };

    IGraph& operator = (const IGraph& other)
    {
        ;
    }

    // Метод принимает вершины начала и конца ребра и добавляет ребро
    virtual void AddEdge(int from, int to) = 0;
    // Метод должен считать текущее количество вершин
    virtual void VerticesCount() = 0;
    // Для конкретной вершины метод выводит в вектор “вершины” все вершины, в которые можно дойти по ребру из данной
    virtual void GetNextVertices(int vertex) const = 0;
    // Для конкретной вершины метод выводит в вектор “вершины” все вершины, из которых можно дойти по ребру в данную
    virtual void GetPrevVertices(int vertex) const = 0;
    virtual void printMatrix() = 0;
};

class MatrixGraph: public IGraph
{
public:
    MatrixGraph(int inSize)
    {
        side = inSize;
        for(int i = 0; i < side; i++)
        {
            int* tmp_matrix = new int[side];
            matrix.push_back(tmp_matrix);
        }

        for(int i = 0; i < side; i++)
        {
            for(int j = 0; j < side; j++)
            {
                matrix[i][j] = 0;
            }
        }
        std::cout << "MatrixGraph created " << matrix[0] << std::endl;
    }

    MatrixGraph(const MatrixGraph* other)
    {
        std::cout << "Graph copied " << std::endl;
        side = other->side;
        matrix = other->matrix;
    }

    ~MatrixGraph()
    {
        std::cout << "MatrixGraph destroyed " << matrix[0] << std::endl;
        for(int i = 0; i < side; i++)
        {
            delete[] matrix[i];
        }
    }

    void AddEdge(int vertical, int horisontal) override  //функция добавления ребра в матрицу
    {
        assert(vertical > 0 && horisontal > 0);
        assert(vertical <= 10 && horisontal <= 10);
        matrix[vertical-1][horisontal-1] = 1;
    }

    void VerticesCount() override
    {
        int counter = 0;
        for(int i = 0; i < side; i++)
        {
            for(int j = 0; j < side; j++)
            {
                if(matrix[i][j] == 1) counter++;
            }
        }
        std::cout << "Vertices quantity = " << counter << std::endl;
    }

    void GetNextVertices(int vertex) const override
    {
        std::vector<int> targets;
        for(int i = 0; i < side; ++i)
        {
            if(i+1 == vertex)
            {
                for(int j = 0; j < side; ++j)
                {
                    if(matrix[i][j] == 1) targets.push_back(++j);
                }
                break;
            }
        }

        if(targets.size() > 0)
        {
            std::cout << "From " << vertex << " vertex to: ";
            for(int i = 0; i < targets.size(); ++i)
            {
                std::cout << targets[i] << " ";
            }
            std::cout << std::endl;
        }
        else std::cout << "No Target vetices for " << vertex << " vertex" << std::endl;
    }

    void GetPrevVertices(int vertex) const override
    {
        std::vector<int> targets;
        for(int i = 0; i < side; ++i)
        {
            if(matrix[i][vertex-1] == 1)
            {
                targets.push_back(i+1);
            }
        }

        if(targets.size() > 0)
        {
            std::cout << "To " << vertex << " vertex from: ";
            for(int i = 0; i < targets.size(); ++i)
            {
                std::cout << targets[i] << " ";
            }
            std::cout << std::endl;
        }
        else std::cout << "Unreacheble " << vertex << " vertex" << std::endl;
    }

    void printMatrix() override
    {
        for(int i = 0; i < side; i++)
        {
            for(int j = 0; j < side; j++)
            {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

};


class ListGraph : public IGraph
{

};

int main() {

    int graph_size = 5;

    MatrixGraph* my_graph = new MatrixGraph(graph_size);
    my_graph->AddEdge(1,3);
    my_graph->AddEdge(2,4);
    my_graph->AddEdge(1,5);
    my_graph->AddEdge(4,3);
    my_graph->AddEdge(3,1);
    my_graph->printMatrix();
    my_graph->VerticesCount();
    my_graph->GetNextVertices(2);
    my_graph->GetPrevVertices(3);

    MatrixGraph* test_graph(my_graph);

    //delete my_graph;

    my_graph->AddEdge(2,5);
    test_graph->printMatrix();
    test_graph->VerticesCount();
    test_graph->GetNextVertices(5);
    test_graph->GetPrevVertices(2);

    my_graph->printMatrix();

    delete test_graph;

    return 0;
}
