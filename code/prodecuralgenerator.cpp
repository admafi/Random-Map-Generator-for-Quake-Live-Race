// Procedural map generator by admafi
//



#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "math.h"
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cxxopts.hpp>

using namespace std;
using namespace std::tr2::sys;
namespace fs = experimental::filesystem;



// This function formats the strings of the brush-coordinates
void parsbrush(int brush[9], ofstream& o, string t)
{


	//ofstream newmap;
	int numbrush = 6;
	int numElement = 8;
	stringstream brushbuff;


	//Add symbols and space
	for (int i = 0; i <= numElement; i++)
	{
		if (i == 0)
		{
			brushbuff << "( ";
		}
		if (i == 3)
		{
			brushbuff << ") ( ";
		}
		if (i == 6)
		{
			brushbuff << ") ( ";
		}
		brushbuff << brush[i] << " ";

	}
	brushbuff << ")";
	o << brushbuff.str() << t << endl;

	return;
}



//This function reads in the prefabs and then formats them
string slurp(ifstream& in, int procnumx, int procnumy)
{
	const int numcount = 5000;
	int inputbrush1[numcount];
	int input;
	stringstream sstr;
	stringstream sstr2;
	stringstream sstr3;
	stringstream sstr4;
	stringstream sstr5;
	stringstream searchstringstream;
	string searchstring;
	string strr;
	string strr2;
	string outputstring;

	sstr << in.rdbuf();
	strr = sstr.str();
	strr.erase(remove_if(strr.begin(), strr.end(), [](char c) { return  !isdigit(c) && !isspace(c); }), strr.end()); //delete everything but numbers
	sstr2 << strr;

	//erase numbers we dont need (from the end)
	while (sstr2)
	{
		getline(sstr2, searchstring);
		searchstring = searchstring.substr(0, searchstring.size() - 28);
		sstr3 << searchstring;
	}


	//convert string to int vector
	vector<int> values;
	int n;
	while (sstr3 >> n) {
			values.push_back(n);
	}


	//do your math tot the prefab vectors
	int u = 0;
	int e = 0;
	int xvalue = 256 * procnumx;
	int yvalue = 256 * procnumy;
	for (u = 0; u < values.size(); u++)
	{
		e++;
		if (e == 1 || e == 4 ||  e == 7)
		{ 
		values[u] += xvalue;
		}
		if (e == 2 || e == 5|| e == 8)
		{
			values[u] += yvalue;
		}

		if (e > 8)
		{
			e = 0;
		}
	}

	//convert int vector back to string and format it
	sstr5 << endl << "{" << endl;
	int s = 0;
	int t = 0;
	int r = 0;
	for (int s = 0; s < values.size(); s++)
	{
		t++;
		r++;
		if (t == 1 && r < 54)
		{
			sstr5 << "( ";
		}
		if (t == 4)
		{
			sstr5 << ") ( ";
		}

		if (t == 7)
		{
			sstr5 << ") ( ";
		}

		if (t == 10)
		{
			sstr5 << ") common/caulk 0 0 0 0.500000 0.500000 0 4 0";
			if (r < 54)
			{
			sstr5 << endl << "( ";
			}
			t = 1;
		}

		if (r == 55)
		{
			sstr5 << endl << "}" << endl << "{" << endl;
			sstr5 << "( ";
			r = 1;
		}

		sstr5 << values[s] << " ";

	}
	sstr5 << ") common/caulk 0 0 0 0.500000 0.500000 0 4 0";
	sstr5 << endl << "}";

	sstr5.seekg(0, ios::end);
	int sstr5size = sstr5.tellg();

/*	for (int i = 0; i < sstr5size; i++)
	{

			sstr5 << "b";

	}*/


	outputstring = sstr5.str();

/*for (int i = 0; i < outputstring.size(); i++) {
		if (i % 3 == 0) sstr5 << '|'; 
		sstr5 << outputstring[i];
	} */

	return sstr5.str();
}




//Main Function
int main(int argc, char* argv[])
{
	int mapsize = 1;
	string mapname;
	int ambientlight = 0;
	int randomtype = 1;
	int randombrushinteger = 5;
	int onlyrandombrushes = 1;
	string message = "Generated with the random map tool by admafi";
	string author = "admafi";
	int minlight = 0;
	int minvertexlight = 0;
	bool celshader = false;
	bool raceentities = true;
	int randomlights = 1;
	int lightbrightness = 300;
	string randomtextstr;
	int randomtextint;
	string music = "bla.wav";
	string roomtextureinput;
	string padstextureinput;
	int maxrandomlightsvalue = 10;
	int maxsemirandomlightsvalue = 10;
	bool enablelightgrid = true;
	bool semirandomlights = true;

	//string lightcolors;
	std::vector<std::string> lightcolors = { "red", "blue", "green", "yellow", "pink", "lightblue" };
	//	if (lightcolors == "red")
	//	{ }

	cxxopts::Options options(argv[0]);

	options.add_options()
		("mapname", "mapname", cxxopts::value(mapname))
		("mapsize", "mapsize", cxxopts::value(mapsize))
		("ambientlight", "ambientlight", cxxopts::value(ambientlight))
		("onlyrandombrushes", "onlyrandombrushes", cxxopts::value(onlyrandombrushes))
		("randomtype", "randomtype", cxxopts::value(randomtype))
		("randombrushinteger", "randombrushinteger", cxxopts::value(randombrushinteger))
		("randomlights", "randomlights", cxxopts::value(randomlights))
		("lightbrightness", "lightbrightness", cxxopts::value(lightbrightness))
		("celshader", "celshader", cxxopts::value(celshader))
		("raceentities", "raceentities", cxxopts::value(raceentities))
		("message", "message", cxxopts::value(message))
		("author", "author", cxxopts::value(author))
		("minlight", "minlight", cxxopts::value(minlight))
		("minvertexlight", "minvertexlight", cxxopts::value(minvertexlight))
		("maxrandomlightsvalue", "maxrandomlightsvalue", cxxopts::value(maxrandomlightsvalue))
		("enablelightgrid", "enablelightgrid", cxxopts::value(enablelightgrid))
		("semirandomlights", "semirandomlights", cxxopts::value(semirandomlights))
		("maxsemirandomlightsvalue", "maxsemirandomlightsvalue", cxxopts::value(maxsemirandomlightsvalue))
		;



	auto result = options.parse(argc, argv);

	if (mapsize < 500)
	{
		mapsize = 500;
	}

	//random number when using random as mapname
	srand(time(0));
	randomtextint = rand() % 9999;
	randomtextstr = std::to_string(randomtextint);

	if (mapname == "random")
	{
		mapname += randomtextstr;
	}

	mapname += ".map"; //add .map in the end


					   //Spawnpoint
	int spawn = mapsize / 2; //in the middle of the map
	int spawn2 = (sqrt(mapsize)) + 20; //a bit away from the wall

									   //Lightentities
	int light1 = (mapsize / 64) + 20;
	int light2 = ((sqrt(mapsize)) * 10) - sqrt(mapsize);
	int light3 = mapsize / 2;
	int light4 = mapsize - 20;

	//Raceentities


	//Textures
	//at some point I will add more textures and also custom textures
	string texture1, texture2, texture3, texture4, texture5, texture6, texture7, texture8, texture9, texture10;
	string tcaulk = " common/caulk 0 0 0 0.500000 0.500000 0 4 0";
	string tmgf = " se_industrial/metal_gold_flake 0 0 0 0.500000 0.500000 0 4 0";
	string twr = " se_industrial/wood_red 0 0 0 0.500000 0.500000 0 4 0";


	//Create Brushes
	int m = mapsize;

	////////////////BRUSHES FOR THE ROOM///////////////////
	// This creates a room depending on the size-value
	// Maybe I will add some more stuff to the basic room in the future. So far it's only 6 Walls.
	// I should make these twodimensional arrays
	// like int groundbrush[6][9]
	//Groundbrush
	int b1s1[9] = { 0, m, 8, 0, 0, 8, 0, 0, 0 }; //brush 1 side 1
	int b1s2[9] = { m, m, -16, 0, m, -16, 0, m, -24 }; //brush 1 side 2
	int b1s3[9] = { m, -8, 104, m, 56, 104, m, 56, 96 }; //brush 1 side 3
	int b1s4[9] = { 0, 0, 8, m, 0, 8, m, 0, 0 }; //brush 1 side 4
	int b1s5[9] = { 0, 0, 8, 0, m, 8, m, m, 8 }; //brush 1 side 5
	int b1s6[9] = { m, m, 0, 0, m, 0, 0, 0, 0 }; //brush 1 side 6
	//Topbrush
	int b2s1[9] = { 0, m, 8 + m, 0, 0, 8 + m, 0, 0, 0 + m }; //brush 2 side 1
	int b2s2[9] = { m, m, -16 + m, 0, m, -16 + m, 0, m, -24 + m }; //brush 2 side 2
	int b2s3[9] = { m, -8, 104 + m, m, 56, 104 + m, m, 56, 96 + m }; //brush 2 side 3
	int b2s4[9] = { 0, 0, 8 + m, m, 0, 8 + m, m, 0, 0 + m }; //brush 2 side 4
	int b2s5[9] = { 0, 0, 8 + m, 0, m, 8 + m, m, m, 8 + m }; //brush 2 side 5
	int b2s6[9] = { m, m, 0 + m, 0, m, 0 + m, 0, 0, 0 + m }; //brush 2 side 6
	//Sidebrush1
	int b3s1[9] = { 0, 0, 0, 0, 0, m, 0, -8, m }; //brush 3 side 1
	int b3s2[9] = { m, -24, 0, 0, -24, 0, 0, -32, 0 }; //brush 3 side 2
	int b3s3[9] = { m, 96, 72, m, 96, 8, m, 88, 8 }; //brush 3 side 3
	int b3s4[9] = { 0, 0, m, m, 0, m, m, -8, m }; //brush 3 side 4
	int b3s5[9] = { 0, 0, m, 0, 0, 0, m, 0, 0 }; //brush 3 side 5
	int b3s6[9] = { m, -8, 0, 0, -8, 0, 0, -8, m }; //brush 3 side 6
	//Sidebrush2
	int b4s1[9] = { 0, 8 + m, 0, 0, 8 + m, m, 0, 0 + m, m }; //brush 4 side 1
	int b4s2[9] = { m, -16 + m, 0, 0, -16 + m, 0, 0, -24 + m, 0 }; //brush 4 side 2
	int b4s3[9] = { m, 104 + m, 72, m, 104 + m, 8, m, 96 + m, 8 }; //brush 4 side 3
	int b4s4[9] = { 0, 8 + m, m, m, 8 + m, m, m, 0 + m, m }; //brush 4 side 4
	int b4s5[9] = { 0, 8 + m, m, 0, 8 + m, 0, m, 8 + m, 0 }; //brush 4 side 5
	int b4s6[9] = { m, 0 + m, 0, 0, 0 + m, 0, 0, 0 + m, m }; //brush 4 side 6
	//Sidebrush3
	int b5s1[9] = { m, 0, 0, m, m, 0, m, m, m }; //brush 5 side 1
	int b5s2[9] = { 8 + m, m, m, 8 + m, m, 0, 8 + m, 0, 0 }; //brush 5 side 2
	int b5s3[9] = { 8 + m, m, m, 8 + m, 0, m, m, 0, m }; //brush 5 side 3
	int b5s4[9] = { 204, 0, 72, 204, 0, 8, 196, 0, 8 }; //brush 5 side 4
	int b5s5[9] = { 84, 0, 0, 84, m, 0, 76, m, 0 }; //brush 5 side 5
	int b5s6[9] = { m + 8, m, 0, m + 8, m, m, m, m, m }; //brush 5 side 6
	//Sidebrush4
	int b6s1[9] = { m - m - 8, 0, 0, m - m - 8, m, 0, m - m - 8, m, m }; //brush 6 side 1
	int b6s2[9] = { 8 + m - m - 8, m, m, 8 + m - m - 8, m, 0, 8 + m - m - 8, 0, 0 }; //brush 6 side 2
	int b6s3[9] = { 8 + m - m - 8, m, m, 8 + m - m - 8, 0, m, m - m - 8, 0, m }; //brush 6 side 3
	int b6s4[9] = { 204 - m - 8, 0, 72, 204 - m - 8, 0, 8, 196 - m - 8, 0, 8 }; //brush 6 side 4
	int b6s5[9] = { 84 - m - 8, 0, 0, 84 - m - 8, m, 0, 76 - m - 8, m, 0 }; //brush 6 side 5
	int b6s6[9] = { m + 8 - m - 8, m, 0, m + 8 - m - 8, m, m, m - m - 8, m, m }; //brush 6 side 6



	//Read prefabs from map files
	ifstream prefabin;
	string temppath;
	string path = "prefabs";
	//ifstream prefabin("prefabs/prefab1.map");




//Create File
	ofstream newmap;
	newmap.open(mapname);

	


	//Writing the file

	//Texture
	texture1 = tmgf;
	texture2 = twr;
	// Information
	newmap << "//Mapname: " << mapname << "\n";
	if (message.size() != 0) //is currently always true
	{
		newmap << "//" << message << "\n"; //custom message
	}
	newmap << endl;
	// Global entity
	newmap << "//global entity\n";
	newmap << "{\n"; //global entity start
	if (author.size() != 0) //is currently always true
	{
		newmap << "\"author\" \"" << author << "\"\n"; //custom author
	}
	if (ambientlight>0)
	{
		newmap << "\"ambient\" \"" << ambientlight << "\"\n"; //custom ambientlight
	}
	if (minlight>0)
	{
		newmap << "\"_minlight\" \"" << minlight << "\"\n"; //custom minlight
	}
	if (minvertexlight>0)
	{
		newmap << "\"_minvertexlight\" \"" << minvertexlight << "\"\n"; //custom minvertexlight
	}
	if (celshader)
	{
		newmap << "\"_celshader\" \"cel/ink\"\n"; //celshader
	}
	if (message.size() != 0) //is currently always true
	{
		newmap << "\"message\" \"" << message << "\"\n"; //custom message
	}
	newmap << "\"classname\" \"worldspawn\"\n"; //this needs to be here
	newmap << endl;

	//Generate the room depending on the mapsize
	newmap << "//Roombrushes\n";
	newmap << "//Groundbrush\n"; //Groundbrush
	newmap << "{\n";
	//time to write the actual brushes
	parsbrush(b1s1, newmap, texture1);
	parsbrush(b1s2, newmap, texture1);
	parsbrush(b1s3, newmap, texture1);
	parsbrush(b1s4, newmap, texture1);
	parsbrush(b1s5, newmap, texture1);
	parsbrush(b1s6, newmap, texture1);
	newmap << "}\n";
	newmap << "//Topbrush\n"; //Topbrush
	newmap << "{\n";
	parsbrush(b2s1, newmap, texture1);
	parsbrush(b2s2, newmap, texture1);
	parsbrush(b2s3, newmap, texture1);
	parsbrush(b2s4, newmap, texture1);
	parsbrush(b2s5, newmap, texture1);
	parsbrush(b2s6, newmap, texture1);
	newmap << "}\n";
	newmap << "//Sidebrush1\n"; //Sidebrush1
	newmap << "{\n";
	parsbrush(b3s1, newmap, texture1);
	parsbrush(b3s2, newmap, texture1);
	parsbrush(b3s3, newmap, texture1);
	parsbrush(b3s4, newmap, texture1);
	parsbrush(b3s5, newmap, texture1);
	parsbrush(b3s6, newmap, texture1);
	newmap << "}\n";
	newmap << "//Sidebrush2\n"; //Sidebrush2
	newmap << "{\n";
	parsbrush(b4s1, newmap, texture1);
	parsbrush(b4s2, newmap, texture1);
	parsbrush(b4s3, newmap, texture1);
	parsbrush(b4s4, newmap, texture1);
	parsbrush(b4s5, newmap, texture1);
	parsbrush(b4s6, newmap, texture1);
	newmap << "}\n";
	newmap << "//Sidebrush3\n"; //Sidebrush3
	newmap << "{\n";
	parsbrush(b5s1, newmap, texture1);
	parsbrush(b5s2, newmap, texture1);
	parsbrush(b5s3, newmap, texture1);
	parsbrush(b5s4, newmap, texture1);
	parsbrush(b5s5, newmap, texture1);
	parsbrush(b5s6, newmap, texture1);
	newmap << "}\n";
	newmap << "//Sidebrush4\n"; //Sidebrush4
	newmap << "{\n";
	parsbrush(b6s1, newmap, texture1);
	parsbrush(b6s2, newmap, texture1);
	parsbrush(b6s3, newmap, texture1);
	parsbrush(b6s4, newmap, texture1);
	parsbrush(b6s5, newmap, texture1);
	parsbrush(b6s6, newmap, texture1);
	newmap << "}\n";
	///////////////////GENERATE PROCEDURAL BRUSHES//////////////////
	newmap << "//Randomly generated brushes\n";
	for (auto & p : fs::recursive_directory_iterator(path))
	{

		if (is_regular_file(p))
		{
			temppath = p.path().string();
			ifstream prefabin(temppath.c_str());
			newmap << "//prefabs\n";
			newmap << slurp(prefabin, 1, 2);
			newmap << endl;
			newmap << endl;

		}
	}

	int r1, r2, r3, r4, r5, r6, r7, r8, r9, r10;
	int proc1 = 20;
	int maxrandombrushes = mapsize / randombrushinteger;
	int randombrushrange = mapsize - sqrt(mapsize);
	int maxrandombrushsize = mapsize - sqrt(mapsize);
	int maxrandombrushheight = mapsize - (mapsize / 2);
	int maxrandombrushheight2 = mapsize / 16;
	int minrandombrushsize = 20;
	int minrandombrushsize2 = 1;

	//race-entities
	int raceoriginstart1 = mapsize / 2; //in the middle of the map
	int raceoriginstart2 = (sqrt(mapsize)) + 120; //a bit away from the wall and from the spawn entity
	srand(time(0));
	int raceoriginend1 = rand() % maxrandombrushsize + minrandombrushsize;
	int raceoriginend2 = mapsize - 100;
	//int rb1[9],rb2[9],rb3[9],rb4[9],rb5[9],rb6[9];
	
	//Global entity end
	newmap << "}\n";
	newmap << endl;
	//Other entities
	//Playerstart entity
	newmap << "//Playerstart Entity\n";
	newmap << "{\n";
	newmap << "\"angle\" \"90\"\n";
	newmap << "\"origin\" \"" << spawn << " " << spawn2 << " " << "40" << "\"\n";
	newmap << "\"classname\" \"info_player_deathmatch\"\n";
	newmap << "}\n";
	//Lightentities
	int lightgrid = (sqrt(mapsize)) / 10;
	if (enablelightgrid)
	{
		newmap << "//Lightentities\n";

		for (int y = 0; y < lightgrid; y++)
		{
			newmap << "{\n"; //light1
			newmap << "\"origin\" \"" << light1 << " " << light2 + (sqrt(mapsize)) * 10 * y << " " << light3 << "\"\n";
			newmap << "\"classname\" \"light\"\n";
			newmap << "\"light\" \"" << lightbrightness << "\"\n";
			newmap << "}\n";
			newmap << "{\n"; //light2
			newmap << "\"origin\" \"" << light4 << " " << light2 + (sqrt(mapsize)) * 10 * y << " " << light3 << "\"\n";
			newmap << "\"classname\" \"light\"\n";
			newmap << "\"light\" \"" << lightbrightness << "\"\n";
			newmap << "}\n";
			newmap << "{\n"; //light3
			newmap << "\"origin\" \"" << light2 + (sqrt(mapsize)) * 10 * y << " " << light1 << " " << light3 << "\"\n";
			newmap << "\"classname\" \"light\"\n";
			newmap << "\"light\" \"" << lightbrightness << "\"\n";
			newmap << "}\n";
			newmap << "{\n"; //light4
			newmap << "\"origin\" \"" << light2 + (sqrt(mapsize)) * 10 * y << " " << light4 << " " << light3 << "\"\n";
			newmap << "\"classname\" \"light\"\n";
			newmap << "\"light\" \"" << lightbrightness << "\"\n";
			newmap << "}\n";
		}
	}
	//Random lightentities
	int lightr1;
	int lightr2;
	int lightr3;
	int maxrandomlights = (mapsize / randombrushinteger) / maxrandomlightsvalue;
	int maxrandomlightsize = mapsize - sqrt(mapsize);
	int minrandomlightsize = 20;
	srand(time(0));
	if (randomlights == 1)
	{
		for (int l = 0; l <= maxrandomlights; l++)
		{
			lightr1 = rand() % maxrandomlightsize + minrandomlightsize;
			lightr2 = rand() % maxrandomlightsize + minrandomlightsize;
			lightr3 = rand() % maxrandomlightsize + minrandomlightsize;

			newmap << "//Random Lightentities\n";
			newmap << "{\n"; //randomlight
			newmap << "\"origin\" \"" << lightr1 << " " << lightr2 << " " << lightr3 << "\"\n";
			newmap << "\"classname\" \"light\"\n";
			newmap << "\"light\" \"" << lightbrightness << "\"\n";
			newmap << "}\n";
		}
	}

	//Semi-random lightentities
	//these lights should shed light on the way between the two race-entities
	srand(time(0));

	//int maxsemirandomlights = (mapsize / randombrushinteger) / maxsemirandomlightsvalue;
	int maxsemirandomlights = ((sqrt(mapsize)) - 5) / 5;
	int getrandomlightsvalue1;
	int getrandomlightsvalue2;
	int getrandomlightsvalue1addvalue;
	int getrandomlightsvalue2addvalue;
	int slopebetweenracepoints = (raceoriginend2 - raceoriginstart2) / (raceoriginend1 - raceoriginstart1);


	if (semirandomlights)
	{
		for (int l = 0; l <= maxsemirandomlights; l++)
		{
			int raceoriginstart2new = raceoriginstart2 + ((sqrt(mapsize)) * 5 * l);
			int raceoriginstart1new = raceoriginstart1 + (raceoriginstart2new / slopebetweenracepoints);


			newmap << "//Semi-Random Lightentities\n";
			newmap << "{\n"; //semi-randomlight
			newmap << "\"origin\" \"" << raceoriginstart1new << " " << raceoriginstart2new << " " << "150" << "\"\n";
			newmap << "\"classname\" \"light\"\n";
			newmap << "\"light\" \"" << lightbrightness << "\"\n";
			newmap << "}\n";
		}
	}
	//Raceentities

	if (raceentities)
	{
		newmap << "//Raceentities\n";
		newmap << "{\n";
		newmap << "\"target\" \"end\"\n";
		newmap << "\"spawnflags\" \"1\"\n";
		newmap << "\"origin\" \"" << raceoriginstart1 << " " << raceoriginstart2 << " " << "40" << "\"\n";
		newmap << "\"classname\" \"race_point\"\n";
		newmap << "}\n";
		newmap << "{\n";
		newmap << "\"targetname\" \"end\"\n";
		newmap << "\"spawnflags\" \"1\"\n";
		newmap << "\"origin\" \"" << raceoriginend1 << " " << raceoriginend2 << " " << "40" << "\"\n";
		newmap << "\"classname\" \"race_point\"\n";
		newmap << "}\n";
	}
	//Close File
	newmap.close();

	//Start q3map2
	system("\"q3map2\\WzMap.exe\" -game quakelive -meta -vis -light -super 2 -filter -bounce 8 -v \"\\rec1.map\""); // start q3map2
																													//system("start q3map2.exe");
																													//The End
	return 0;
}

