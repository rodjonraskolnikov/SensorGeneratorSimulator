#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>


using namespace std;

int main(int argc, const char **argv)
{
	int n;
	cout << "inserisci il numero di sensori che sia maggiore o uguale a 3: ";
	cin >> n;
	while(n<3){
		cout << "inserisci il numero di sensori che sia maggiore o uguale a 3: ";
		cin >> n;
	}

	int sim;
	cout << "inserisci il numero di simulazioni che si intendono effettuare maggiore o uguale a 1: ";
	cin >> sim;
	while(sim<1){
		cout << "inserisci il numero di simulazioni che sia maggiore o uguale a 1: ";
		cin >> n;
	}

	int offset;
	int m;
	int temp;
	stringstream stringOffset[sim][n];
	ofstream file("Objects UMC.txt");
	file << "Vars :" << endl;

	// si istanziano le variabili

	for(int k=0; k<sim; k++){
		file << "// variabili della simulazione " << k+1 << endl;
		cout << "inserisci il numero di round per la simulazione " << k+1 << " che sia maggiore o uguale a 3: ";
		cin >> m;
		while(m<3){
			cout << "numero di round deve essere maggiore o uguale a 3: ";
			cin >> m;
		}

		cout << "inserisci la temperatura di partenza per la simulazione " << k+1 << ": ";
		cin >> temp;
		file << "temperature" << k+1 << " :int = " << temp << endl;

		cout << "inserisci la variazione massima di temperatura per la simulazione " << k+1 << ": ";
		cin >> offset;

		srand((unsigned)time(0));
		int offsetTemperature[m];

		// Genera le variazioni di temperatura per la simulazione k

		for(int i=0; i<n; i++){
			stringOffset[k][i] << "[";
			for(int j=0; j< m-1 ; j++){
				offsetTemperature[j] = (rand()%(offset*2))-offset; //valori tra [-offset, +offset -1]
				stringOffset[k][i] << offsetTemperature[j] << ", ";
			}
			offsetTemperature[m-1] = (rand()%(offset*2))-offset;
			stringOffset[k][i] << offsetTemperature[m-1] << "]";
			file << "offsetTemp" << k+1 << "Sensor" << i+1 << " :int = " << stringOffset[k][i].str() << " ," << endl;
		}
		file << endl;
	}

	file << "sensor : obj [] " << endl << endl << "State Top = inizialization, end" << endl << endl << "Transitions:" << endl << endl;
	string tab = "    ";

	// Si istanziano le transizioni

	for(int k=0; k<sim; k++){
		file << "------ Simulazione" << k+1 << " ------" << endl <<"inizialization -> end { -  /" << endl;
		for(int i=0; i<n; i++){
			file << tab << "sensor[" << i << "].update ( temperature" << k+1 << ", offsetTemp" << k+1 << "Sensor" << i+1 << " );" << endl;
		}
		file << "}" << endl << endl;
	}

	file << "end Simulator" << endl << endl << "Objects: " << endl;

	srand((unsigned)time(0));
	stringstream sensor;
	for(int i=0; i<n; i++){
		if(i==0){
			file << "sensor1: Head ( rightSensor = sensor2 )" << endl;
			sensor << "[ sensor1, ";
			}else if (i==n-1){
				file << "sensor" <<  n <<": Tail ( leftSensor = sensor" << (n-1) << " )" << endl;
				sensor << "sensor" << n << " ])";
			}else{
				file <<	"sensor" << i+1 << ": Intermediate ( rightSensor = sensor" << (i+2) <<", leftSensor = sensor" << i << " )" << endl;
				sensor << "sensor" << i+1 << ", ";
			}

		}

	file << "simulator: Simulator ( sensor = " << sensor.str();
	file.close();
	return 0;

}




