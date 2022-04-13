#include <iostream>
#include "PGM.hpp"

using namespace std;

int main(void)
{
	setlocale(LC_ALL, "Portuguese");

	cout << "olá!" << endl;
	
	PGM *img = new PGM();
	unsigned char corP;

	
	img->ler("feep.pgm");

	//img->gravarQuadroCor(7,1,10,5,255);
	img->pegarQuadro(7,1,10,5);
	//ler o valor de um pixel
	//corP = img->getPixel(1,1);

	//cout << "A cor do pixel(1,1) é " << (int) corP << endl;


	//alterando a cor do pixel(1,1) para branco(255) e gravando o resultado na imagem de saída 
	//img->setPixel(1,1, 255);
	img->gravar("saida.pgm");

	delete img;
	
	return EXIT_SUCCESS; 
}
