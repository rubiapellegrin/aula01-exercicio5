#include "PGM.hpp"

#include <iostream>
using namespace std;

PGM::PGM(){
    pixels = nullptr;
	larg = 0;
	alt = 0;
	tipo = "";
}

PGM::~PGM() {
    if (pixels)
        delete pixels;
    pixels = nullptr;
}


int PGM::getLargura()
{
    return larg;
}

int PGM::getAltura()
{
    return alt;
}


unsigned char* & PGM::getPixels()
{
    return pixels;
}

unsigned char PGM::getPixel(int x, int y){

    if(pixels ==  nullptr)
    {
        cout<<"Erro ao fazer leitura: faça a leitura da imagem antes de ler os pixels";
        return 0;
    }

    return pixels[y*larg + x];
}

void PGM::setPixel(int x, int y, unsigned char cor){

    if(pixels)
        pixels[y*larg + x] = cor;
}


void PGM::criarFundo()
{
    this->tipo = "P2";
    pixels =  new unsigned char [larg * alt];
    for(int i=0;i<larg *alt;i++)
        pixels[i] = 0;  
}

bool PGM::gravarArquivo(string caminho){

    if (!pixels)
        return false;

    ofstream arq;

    arq.open(caminho);
    if (!arq.is_open()) {
        cout << "PGM: endereco do arquivo invalido\n";
        return false;
    }

    arq << tipo << endl;

    arq << larg << " " << alt << endl;

    arq << 255 << endl; // valor máximo de cor fixo em 255

    int tam = larg * alt;
    for (int i = 0; i < tam; i++)
    {
        arq << (int) pixels[i] << endl;
        arq.flush();
    }
        

    arq.close();
    return true;
    
        
}






bool PGM::ler(string caminho) {
    ifstream arq;
    string aux;

    

    arq.open(caminho);
    if (!arq.is_open()) {
        cout << "PGM: endereco do arquivo invalido\n";
        return false;
    }

    if (!lerDado(arq, &aux)) {    ///descarta os caracteres especiais
        cout << "PGM: erro ao ler o tipo da imagem\n";
        return false;
    }
    tipo = aux;


    if (!lerDado(arq, &aux)) {
        cout << "PGM: erro ao ler a largura da imagem\n";
        return false;
    }
    larg = atoi(aux.c_str());

    if (!lerDado(arq, &aux)) {
        cout << "PGM: erro ao ler a altura da imagem\n";
        return false;
    }
    alt = atoi(aux.c_str());


    if (!lerDado(arq, &aux)) {
        cout << "PGM: erro ao ler o valor máximo de cor\n";
        return false;
    }
    vmax = atoi(aux.c_str());

    if (pixels)
        delete pixels;      //descarta o pixel antes de gravar nele
    pixels = new unsigned char[larg * alt];

    int i = 0;
    while (!arq.eof()) {
        if (!lerDado(arq, &aux)) {
            break;
        }

        pixels[i] = (unsigned char) atoi(aux.c_str());
        i++;

    }

    //cout << "i: " << i << endl;
    if (i != larg * alt) {
        cout << "PGM: erro ao ler os pixels\n";
        return false;
    }

    //cout << this->tipo << endl;
    //cout << this->larg << endl;
    //cout << this->alt << endl;
    //cout << this->vmax << endl;


    return true;
}

bool PGM::gravar(string caminho) {

    if (!pixels)
        return false;

    ofstream arq;

    arq.open(caminho);
    if (!arq.is_open()) {
        cout << "PGM: endereco do arquivo invalido\n";
        return false;
    }

    arq << tipo << endl;

    arq << larg << " " << alt << endl;

    arq << 255 << endl; // valor máximo de cor fixo em 255

    int tam = larg * alt;
    for (int i = 0; i < tam; i++)
    {
        arq << (int) pixels[i] << endl;
        arq.flush();
    }
        

    arq.close();
    return true;
}




void PGM::gravarLinha(unsigned char cor,int linha){

    for(int x=0;x<larg;x++){
        pixels[linha*larg + x] = cor;
    }
        
}


void PGM::inverter(){

    unsigned char vetorAuxiliar[alt][larg];
    int destino = alt-1;
    for(int y=0;y<alt;y++){
        for(int x=0;x<larg;x++){
            vetorAuxiliar[destino][x] = pixels[y*larg + x];
        }
        destino--;
    }


    for(int y=0;y<alt;y++){
        for(int x=0;x<larg;x++){
            pixels[y*larg + x] = vetorAuxiliar[y][x];
        }  
    }
         
}

void PGM::gravarQuadroCor(int x1, int y1, int x2, int y2, unsigned char cor){

    for(int x=x1;x<=x2;x++){
        for(int y=y1;y<=y2;y++){
                setPixel(x,y,cor);
        }    
    }
        
}


void PGM::pegarQuadro(int x1, int y1, int x2, int y2){


    unsigned char vetorAuxiliar2[alt][larg];  //vetor auxiliar para guardar o quadro
    unsigned char corO = 0;
    for(int y=y1;y<=y2;y++){
         for(int x=x1;x<=x2;x++){
                vetorAuxiliar2[y][x] = pixels[y*larg + x];
        }    
    }
    criarFundo(); //cria imagem de fundo preto
    for(int y=0;y<alt;y++){
        for(int x=0;x<larg;x++){   //atribui o quadro a imagem
            if(x >=x1 && x<=x2  && y <=y2 && y>=y1)
                pixels[y*larg + x]  = vetorAuxiliar2[y][x];
                
        }  
        
    }
}




void PGM::gravarListrado(unsigned char cor){

        for(int y=50;y<alt;y+=50){
                gravarLinha(cor, y);
        }    
        
}

bool PGM::lerDado(ifstream &arq, string *dado) {
    string aux;
    while (!arq.eof()) {
        arq >> aux;   //le a primeira palavra
        if (aux.size() > 0 && aux[0] == '#') {   //descartar comentarios
            std::getline(arq, aux);
        }else if(aux.size() > 0){
            *dado = aux;
            return true;
        }

        aux = "";
    }
    return false;
}
