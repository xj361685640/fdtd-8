#include <fdtd.h>

#include <iostream>
#include <typeinfo>
#include <vector>


using namespace fdtd;

// compile with:
// 			clang++-3.8 -std=c++14 -stdlib=libc++ -I../ test.cpp -o test


int main(int argc, char * argv[]){

	typedef YeeCell<YeeFields3D<double, std::array>, VacuumPolarization, VacuumMagnetization, Neighbor3, PML<StoredPMLx<ThreeD>, StoredPMLy<ThreeD>, StoredPMLz<ThreeD>>> YeeCellVac3D;
	YeeCellVac3D y;

	// std::cout << typeid(y).name() << std::endl;


	typedef YeeCell<YeeFieldsTEM<double, std::array>, VacuumPolarization, VacuumMagnetization, Neighbor1, PML<StoredPMLx<TEM>, NoPMLy, NoPMLz>> YeeCellVacTEM;
	std::vector<YeeCellVacTEM> cells1(50);

	for (auto i=1; i<49; i++){
		cells1[i].setNeighborMin(0, cells1[i-1]);
		cells1[i].setNeighborMax(0, cells1[i+1]);
	}


	for (auto t=0; t<100; t++){
		for_each(++cells1.begin(), --cells1.end(), YeeUpdateD<TEM>(1,c0));
		cells1[25].Dz() = sin(2*pi*0.05*t);
		for_each(++cells1.begin(), --cells1.end(), UpdatePML<TEM>(1, c0));
		for_each(++cells1.begin(), --cells1.end(), ConstantUpdateE<TEM>(1));
	
		for_each(++cells1.begin(), --cells1.end(), YeeUpdateB<TEM>(1,c0));
		for_each(++cells1.begin(), --cells1.end(), ConstantUpdateH<TEM>(1));
	
		// std::cout << "Ez:" ;
		for(auto i=0; i<50; i++) std::cout << ", " << cells1[i].Ez() ;
		std::cout << std::endl;
	}

	return 0;
}