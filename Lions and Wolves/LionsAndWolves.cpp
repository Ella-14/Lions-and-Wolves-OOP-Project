//librarii folosite
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <sstream>
#include <random>


//pentru random
using std::vector;
using std::uniform_int_distribution;
using std::mt19937;
using std::random_device;

#define MAX 10000
using namespace std;

class Castle
{
private:
    float costPerDay=10000;
    float costPeriod;
    int period;
public:
    void setPeriod(int p);
    int getPeriod();
    float getCost();
    void calculateSetCost();
};

class Cast
{
private:
    string name;
    string role;
    string dietType;
public:
    void setName(string fn);
    void setRole(string r);
    void setDiet(string d);
    string getName();
    string getRole();
    string getDiet();

};

class Actors:public Cast
{
protected:
    string monster;
    int cost;

public:
    void setMonster(string m);
    string getMonster();
    int makeUpCost()
    {
        cost = 0;
        return cost;
    }

};
class Vampire: public Actors
{
public:
    int makeUpCost()
    {
        cost = 230;
        return cost;
    }
};

class Werewolf: public Actors
{
public:
    int makeUpCost()
    {
        cost = 555;
        return cost;

    }
};

class Siren: public Actors
{
public:
    int makeUpCost()
    {
        cost = 345;
        return cost;

    }
};

class Psychic: public Actors
{
public:

    int makeUpCost()
    {
        cost = 157;
        return cost;
    }
};

class Human: public Actors
{
public:
    int makeUpCost()
    {
        cost = 55;
        return cost;

    }
};

Cast pers[MAX];
Vampire vamp[MAX];
Werewolf were[MAX];
Siren siren[MAX];
Psychic psychic[MAX];
Human human[MAX];

//DECLARARE FUNCTII

int read_csv();
void create_csvCast(int cN,int vN,int wN,int sN, int pN,int hN);
void create_csvCost(float tC, float foodC, float aC, float mC);
void create_csvMenu();
void addExtra(int *k);
void monsterCount(int *vC, int *wC, int *sC, int *pC, int *hC, int k);
void assignDietType(int k);
void calculateDietCost(float *oC,float *vC,float *fC,int k);
float exchangeRonDollar(float ron);

void createMenu();
//MAIN
int main()
{
    //Declarare variabile
    int castNumber;
    float totalCost, transportCost;

    float vampireCost=0,werewolfCost=0,sirenCost=0, psychicCost=0,humanCost=0;
    float monsterCost;

    float twoBedroomPersonCost, threeBedroomPersonCost;
    float accomodationCost;

    float omnivoreCost,vegetarianCost,flexitarianCost;
    float waterCost, coffeeCost,juiceCost;
    float liquidCost, foodCost;



    int vampireCount, werewolfCount, sirenCount, psychicCount, humanCount;
    //Citire din CSV
    castNumber = read_csv();

    // Calculare costuri camere de dormit per noapte
    if(castNumber % 2 == 0)
        twoBedroomPersonCost = (castNumber / 2) * 350;
    else
        twoBedroomPersonCost = (castNumber / 2 + 1) * 350;

    threeBedroomPersonCost = (132 / 3) * 420;

    //Adaugare figuranti
    addExtra(&castNumber);

    // Calculare transport dus-intors ( consideram ca pretul dat este pentru un singur drum)
    if (castNumber % 50 == 0)
        transportCost = (castNumber / 50) * 5680 * 2;
    else
        transportCost = (castNumber / 50 + 1) * 5680 * 2;

    //Calculare costuri lichide (apa, cafea, suc) per zi de lucru
    float water = castNumber;
    float coffee = 0.5 * castNumber;
    float juice = 0.8 * castNumber;

    if(water / 2 == 0)
        waterCost =(water / 2) * 6;
    else
        waterCost =(water / 2 + 1) * 6;

    int coffee1 = (int) coffee;
    if(coffee1 == coffee)
        coffeeCost = 30 * coffee;
    else
        coffeeCost = 30 * (coffee + 1);

    if(juice / 2 == 0)
        juiceCost =(juice / 2) * 8;
    else
        juiceCost =(juice / 2 + 1) * 8;

    liquidCost = waterCost + coffeeCost + juiceCost;


    //asignare dieta in mod random

    assignDietType(castNumber);


    //Calculare costuri pentru mancare per zi de munca
    calculateDietCost(&omnivoreCost, &vegetarianCost, &flexitarianCost, castNumber);

    //Asignare random si numararea cator actori sunt din fiecare categorie
    monsterCount(&vampireCount,&werewolfCount,&sirenCount,&psychicCount,&humanCount,castNumber);

    //Calcularea costului fiecarui tip de machiaj pentru o zi
    for(int i = 0; i < vampireCount; i++)
        vampireCost += vamp[i].makeUpCost();
    for(int i = 0; i < werewolfCount; i++)
        werewolfCost += were[i].makeUpCost();
    for(int i = 0; i < sirenCount; i++)
        sirenCost += siren[i].makeUpCost();
    for(int i = 0; i < psychicCount; i++)
        psychicCost += psychic[i].makeUpCost();
    for(int i = 0; i < humanCount; i++)
        humanCost += human[i].makeUpCost();

    //Creare si afisare cast in csv
    create_csvCast(castNumber,vampireCount,werewolfCount,sirenCount,psychicCount,humanCount);

    //Calculare costuri castel si afisare costuri in csv
    foodCost = liquidCost + omnivoreCost + flexitarianCost + vegetarianCost;
    monsterCost = vampireCost + werewolfCost + sirenCost + psychicCost + humanCost;
    accomodationCost = twoBedroomPersonCost + threeBedroomPersonCost;

    //Transformare din ron in dolari
    foodCost = exchangeRonDollar(foodCost);
    monsterCost = exchangeRonDollar(monsterCost);
    accomodationCost = exchangeRonDollar(accomodationCost);
    transportCost = exchangeRonDollar(transportCost);

    //Creare csv pentru costuri
    create_csvCost(transportCost,foodCost,accomodationCost,monsterCost);

    //realizare meniu
    create_csvMenu();

    return 0;
}

//FUNCTII CLASE

void Cast::setName(string n)
{
    this->name = n;
}

void Cast::setRole(string r)
{
    this->role = r;
}
void Cast::setDiet(string d)
{
    this->dietType = d;
}
string Cast::getName()
{
    return name;
}

string Cast::getRole()
{
    return role;
}
string Cast::getDiet()
{
    return dietType;
}
void Actors::setMonster(string m)
{
    this->monster = m;
}
string Actors::getMonster()
{
    return monster;
}

void Castle::calculateSetCost()
{
    float setCostPeriod = 0;
    try
    {
        if(period % 10 != 0)
            throw period;

        period /= 10;
        for(int i = 0; i < period; i++ )
        {
            setCostPeriod = setCostPeriod + 10 * this->costPerDay;
            setCostPeriod -=  setCostPeriod * 2/100;
        }
        this->costPeriod = setCostPeriod;
    }
    catch (int period)
    {
        int daysLeft = period % 10;
        period /= 10;
        for(int i = 0; i < period; i++ )
        {
            setCostPeriod = setCostPeriod + 10 * this->costPerDay ;
            setCostPeriod -=  setCostPeriod * 2/100;

        }
        setCostPeriod += daysLeft * this->costPerDay;
        this->costPeriod = setCostPeriod;
    }

}

void Castle::setPeriod(int p)
{
    this->period = p;
}

int Castle::getPeriod()
{
    return this -> period;
}

float Castle::getCost()
{
    return this -> costPeriod;
}
//ALTE FUNCTII

void assignDietType(int k)
{
    vector<string> list = {"omnivore", "vegetarian", "flexitarian"};
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, list.size() - 1);
    for(int i = 0; i < k; i++ )
    {
        int randomIndex = dis(gen);
        string randomElement = list[randomIndex];
        pers[i].setDiet(randomElement);
    }
}

void addExtra(int *k)
{
    for(int i = 0; i < 132; i++)
    {
        string text = "Extra cast ";
        text += to_string(i+1);
        pers[*k].setName(text);
        pers[*k].setRole("extra");
        *k = *k + 1;

    }
}

void monsterCount(int *vC, int *wC, int *sC, int *pC, int *hC, int k)
{
    *vC = 0;
    *wC = 0;
    *sC = 0;
    *pC = 0;
    *hC = 0;

    vector<string> list = {"vampire", "werewolf", "siren", "psychic", "human"};

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, list.size() - 1);

    for(int i = 0 ; i < k; i++ )
        if(pers[i].getRole() == "extra" || pers[i].getRole() == " actor")
        {

            int randomIndex = dis(gen);
            string randomElement = list[randomIndex];

            if(randomElement == "vampire")
            {
                vamp[*vC].setName(pers[i].getName());
                vamp[*vC].setRole(pers[i].getRole());
                vamp[*vC].setDiet(pers[i].getDiet());
                vamp[*vC].setMonster("vampire");
                *vC = *vC + 1;
            }


            if(randomElement == "werewolf")
            {
                were[*wC].setName(pers[i].getName());
                were[*wC].setRole(pers[i].getRole());
                were[*wC].setDiet(pers[i].getDiet());
                were[*wC].setMonster("werewolf");
                *wC = *wC + 1;
            }
            if(randomElement == "siren")
            {
                siren[*sC].setName(pers[i].getName());
                siren[*sC].setRole(pers[i].getRole());
                siren[*sC].setDiet(pers[i].getDiet());
                siren[*sC].setMonster("siren");
                *sC = *sC + 1;
            }
            if(randomElement == "psychic")
            {
                psychic[*pC].setName(pers[i].getName());
                psychic[*pC].setRole(pers[i].getRole());
                psychic[*pC].setDiet(pers[i].getDiet());
                psychic[*pC].setMonster("psychic");
                *pC = *pC + 1;
            }
            if(randomElement == "human")
            {
                human[*hC].setName(pers[i].getName());
                human[*hC].setRole(pers[i].getRole());
                human[*hC].setDiet(pers[i].getDiet());
                human[*hC].setMonster("human");
                *hC = *hC + 1;
            }
        }
}

void calculateDietCost(float *oC,float *vC,float *fC, int k)
{
    *oC = 0;
    *vC = 0;
    *fC = 0;

    for(int i = 0; i < k; i++ )
        if(pers[i].getDiet() == "omnivore")
            *oC = *oC + 40;
        else if(pers[i].getDiet() == "vegetarian")
            *vC = *vC + 33;
        else *fC = *fC + 46;
}

float exchangeRonDollar(float ron)
{
    float dollar = ron;
    dollar /= 4.63;
    return dollar;
}

//CITIRE DIN CSV

int read_csv()
{
    fstream fin;
    fin.open("Cast.csv",ios::in);

    vector <string> row;
    string line,word,temp;

    int k = 0;

    while(fin>>temp)
    {
        row.clear();

        getline(fin,line);

        stringstream s(line);

        while (getline(s, word, ','))
        {
            row.push_back(word);
        }
        pers[k].setName(row[0]);
        pers[k].setRole(row[1]);
        k++;
        // cout<<row[0]<<" "<<row[1]<<endl;
    }
    return k;
}

//CREARE CSV-URI

void create_csvCast(int cN,int vN,int wN,int sN, int pN,int hN)
{
    fstream fout;
    remove("newCast.csv");
    fout.open("newCast.csv",ios::out | ios::app);
    for(int i = 0; i < vN; i++ )
        fout << vamp[i].getName() << ","
             << vamp[i].getRole() << ","
             << vamp[i].getDiet() << ","
             << vamp[i].getMonster() << "\n";

    for(int i = 0; i < wN; i++ )
        fout << were[i].getName() << ","
             << were[i].getRole() << ","
             << were[i].getDiet() << ","
             << were[i].getMonster() << endl;

    for(int i = 0; i < sN; i++ )
        fout << siren[i].getName() << ","
             << siren[i].getRole() << ","
             << siren[i].getDiet() << ","
             << siren[i].getMonster() << endl;

    for(int i = 0; i < pN; i++ )
        fout << psychic[i].getName() << ","
             << psychic[i].getRole() << ","
             << psychic[i].getDiet() << ","
             << psychic[i].getMonster() << endl;

    for(int i = 0; i < hN; i++ )
        fout << human[i].getName() << ","
             << human[i].getRole() << ","
             << human[i].getDiet() << ","
             << human[i].getMonster() << endl;

    for(int i = 0; i < cN; i++ )
        if(pers[i].getRole() != " actor" || pers[i].getRole() != " extra" )
            fout << pers[i].getName() << ","
                 << pers[i].getRole() << ","
                 << pers[i].getDiet() << endl;

    fout.close();
    cout<<"Cast csv ready to use!\n";
}

void create_csvCost(float tC, float foodC, float aC, float mC)
{
    fstream fout;
    remove("costs.csv");
    fout.open("costs.csv",ios::out | ios::app);

   fout << "Cost type, 30 days, 45 day, 60 days, 100 days\n";
    fout << "Transportation, " << tC << "$, " << tC << "$, " << tC << "$, " << tC << "$" << endl;
    fout << "Food and drinks, " << 30 * foodC << "$, " << 45 * foodC << "$, " << 60 * foodC << "$, " << 100 * foodC << "$" << endl;
    fout << "Accomodation, " << 30 * aC << "$, " << 45 * aC << "$, " << 60 * aC << "$, " << 100 * aC << "$" << endl;
    fout << "Make-up, " << 30 * mC << "$, " << 45 * mC << "$, " << 60 * mC << "$, " << 100 * mC << "$" << endl;
    fout << "Castle, ";

    float total[4];

    total[0] = 30 * (foodC + aC + mC) + tC;
    total[1] = 45 * (foodC + aC + mC) + tC;
    total[2] = 60 * (foodC + aC + mC) + tC;
    total[3] = 100 * (foodC + aC + mC) + tC;

    Castle c;
    c.setPeriod(30);
    c.calculateSetCost();
    float castleCost = c.getCost();
    castleCost = exchangeRonDollar(castleCost);
    total[0] += castleCost;
    fout << castleCost << "$, ";

    c.setPeriod(45);
    c.calculateSetCost();
    castleCost = c.getCost();
    castleCost = exchangeRonDollar(castleCost);
     total[1] += castleCost;
    fout << castleCost << "$, ";

    c.setPeriod(60);
    c.calculateSetCost();
    castleCost = c.getCost();
    castleCost = exchangeRonDollar(castleCost);
     total[2] += castleCost;
    fout << castleCost << "$, ";

    c.setPeriod(100);
    c.calculateSetCost();
    castleCost = c.getCost();
    castleCost = exchangeRonDollar(castleCost);
    total[3] += castleCost;
    fout << castleCost << "$" << endl;

    fout << "Total, " << total[0] << "$, " << total[1] << "$, " << total[2] << "$, " <<total[3] << "$" << endl;
    fout.close();
    cout<<"Costs csv ready to use!\n";
}

void create_csvMenu()
{
    vector<string> list = {"Chicken soup", "Beef soup", "Spicy Thai coconut chicken soup", "Turkey and Wild Rice Soup", "Cheesy Ham Chowder"};
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, list.size() - 1);

    //SOUPS
    string omnivoreSoup[3];
    for(int i = 0; i < 3; i++ )
    {
        int randomIndex = dis(gen);
        omnivoreSoup[i] = list[randomIndex];
    }

    list = {"Potato soup", "Hearty Vegetable Soup", "Mushroom soup", "Beef Lentil Soup", "Beet Borscht"};

    string vegetarianSoup[3];
    for(int i = 0; i < 3; i++ )
    {
        int randomIndex = dis(gen);
        vegetarianSoup[i] = list[randomIndex];
    }

    list = {"Peruvian Shrimp Chowder", "Shrimp Bisque", "Sanibel Fish Soup", "English Fresh Pea Soup", "Portuguese Fish Soup"};

    string flexitarianSoup[3];
    for(int i = 0; i < 3; i++ )
    {
        int randomIndex = dis(gen);
        flexitarianSoup[i] = list[randomIndex];
    }

    //MAIN DISH

    string omnivoreMain[3];
    list = {"Sticky Sesame Chicken", "Beef Enchiladas", "Chicken Pad Thai", "Sirloin Steak", "Pork Lettuce Wraps"};
    for(int i = 0; i < 3; i++ )
    {
        int randomIndex = dis(gen);
        omnivoreMain[i] = list[randomIndex];
    }

    list = {"Chickpea Curry", "Spinach & ricotta gnocchi", "Vegetarian wellington", "Baked tomato & mozzarella orzo", "Sweet potato parcel"};

    string vegetarianMain[3];
    for(int i = 0; i < 3; i++ )
    {
        int randomIndex = dis(gen);
        vegetarianMain[i] = list[randomIndex];
    }

    list = {"Peruvian Shrimp Chowder", "Shrimp Bisque", "Salmon New Orleans", "Crunchy Fish Pie", "Crispy Thai Chilli Fish"};

    string flexitarianMain[3];
    for(int i = 0; i < 3; i++ )
    {
        int randomIndex = dis(gen);
        flexitarianMain[i] = list[randomIndex];
    }

    //DESERT

    list = {"Peach Crumble", "Red Velvet Cupcakes", "Chocolate Mousse", "Coconut Cookies", "Pistachio Cake"};

    string dessert[3];
    for(int i = 0; i < 3; i++ )
    {
        int randomIndex = dis(gen);
        dessert[i] = list[randomIndex];
    }

    fstream fout;
    remove("menu.csv");
    fout.open("menu.csv",ios::out | ios::app);

    for(int i = 0; i < 3; i++ )
    {
        if(i == 0)
            fout << "1st day menu" << endl;
        else if ( i == 1 )
            fout << "2nd day menu" << endl;
        else
            fout << "3rd day menu" << endl;
        fout << "Omnivore, " << omnivoreSoup[i] << ", " << omnivoreMain[i] << ", " << dessert[i] << endl;
        fout << "Vegetarian, " << vegetarianSoup[i] << ", " << vegetarianMain[i] << ", " << dessert[i] << endl;
        fout << "Flexitarian, " << flexitarianSoup[i] << ", " << flexitarianMain[i] << ", " << dessert[i] << endl;
    }
    fout.close();
    cout<<"Menu csv ready to use!\n";
}
