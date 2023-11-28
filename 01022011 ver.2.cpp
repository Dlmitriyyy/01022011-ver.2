#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

class Ion 
{
private:
    vector<int> randomIons;
    vector<int> ionsBeforeReaction;
public:
    Ion() 
    {
        cout << "/-----------------------------------\\" << endl;
        cout << "| Спрацював конструктор класу Іонів.|" << endl;
        cout << "\\-----------------------------------/" << endl << endl;

        randomIons.resize(rand() % 28);

        for (int i = 0; i < randomIons.size(); i++) 
        {
            int tempIon = rand() % 15 - 7;
            randomIons[i] = tempIon;

            while (tempIon == 0) {
                tempIon = rand() % 15 - 7;
                randomIons[i] = tempIon;
            }
        }
    }

    Ion(Ion&& other) noexcept : randomIons(move(other.randomIons)), ionsBeforeReaction(move(other.ionsBeforeReaction)) 
    {
        cout << "/----------------------------------------\\" << endl;
        cout << "| Спрацював конструктор переміщення Іонів.|" << endl;
        cout << "\\----------------------------------------/" << endl << endl;
    }

    Ion& operator=(Ion&& other) noexcept 
    {
        if (this != &other)
        {
            randomIons = move(other.randomIons);
            ionsBeforeReaction = move(other.ionsBeforeReaction);
        }
        return *this;
    }

    void MoveIons(int ion, vector<int>& from, vector<int>& to) 
    {
        auto it = find(from.begin(), from.end(), -ion);
        if (it != from.end()) 
        {
            to.push_back(ion);
            from.erase(it);
        }
    }

    void ProcessReaction() 
    {
        size_t i = 0;
        while (i < randomIons.size()) 
        {
            if (randomIons[i] != 0) 
            {
                int currentIon = randomIons[i];
                auto oppositeIt = find_if(randomIons.begin() + i + 1, randomIons.end(),
                    [currentIon](int x) 
                    {
                        return x == -currentIon;
                    });

                if (oppositeIt != randomIons.end()) 
                {
                    ionsBeforeReaction.push_back(currentIon);
                    ionsBeforeReaction.push_back(*oppositeIt);

                    randomIons.erase(oppositeIt);
                    randomIons.erase(randomIons.begin() + i);
                }
                else 
                {
                    i++;
                }
            }
        }
    }


    ~Ion() 
    {
        cout << endl << "/----------------------------------\\" << endl;
                cout << "| Спрацював деструктор класу Іонів.|" << endl;
                cout << "\\----------------------------------/" << endl;
    }

    void DisplayVectorsBefore()
    {
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Рандомно сгенерований вектор: ";

        for (int i = 0; i < randomIons.size(); i++) 
        {
            if (randomIons[i] > 0) 
            {
                cout << "+" << randomIons[i] << " ";
            }
            else 
            {
                cout << randomIons[i] << " ";
            }
        } 
        cout << endl << "Розмір вектора: " << randomIons.size();
    }

    void DisplayVectorsAfter()
    {

        cout << endl << endl << "Іони які не вступили в реакцію: ";

        for (int i = 0; i < randomIons.size(); i++)
        {
            if (randomIons[i] > 0) 
            {
                cout << "+" << randomIons[i] << " ";
            }
            else 
            {
                cout << randomIons[i] << " ";
            }
        }

        cout << endl << "Розмір вектора: " << randomIons.size();

        cout << endl << endl << "Вектор у який були переміщенні іони після вступу в реакцію: ";

        for (int i = 0; i < ionsBeforeReaction.size(); i++) 
        {
            if (ionsBeforeReaction[i] > 0) 
            {
                cout << "+" << ionsBeforeReaction[i] << " ";
            }
            else 
            {
                cout << ionsBeforeReaction[i] << " ";
            }
        }
        cout << endl << "Розмір вектора: " << ionsBeforeReaction.size();
        cout <<endl << "------------------------------------------------------------------------------------------------------------------------" << endl;
    }
};

int main() 
{
    system("chcp 1251>nul");
    srand(time(0));
    cout << "Ця програма створює рандомний вектор іонів з валентністю від '1' до '7' та зарядом '+' або '-', після цього створюється новий вектор до якого переміщуються іони які вступили в реакцію, а в першому векторі залишаються іони які в цю реакцію  не вступали." << endl << endl;

    Ion ion;
   
    ion.DisplayVectorsBefore();
    ion.ProcessReaction();
    ion.DisplayVectorsAfter();

    return 0;
}
